/*
 * Modified by Mark Olson for his Arduino class https://github.com/Mark-MDO47/ArduinoClass
 * 
 * We are using an Arduino Nano with a USB mini-B connector
 *            V3.0 ATmega328P 5V 16M CH340 Compatible to Arduino Nano V3
 *            32Kbyte Flash (program storage), 2Kbyte SRAM, 1Kbyte EEPROM
 *            http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf
 *            http://www.pighixxx.com/test/pinouts/boards/nano.pdf
 *
 * VoiceCommands_I2C.ino is code for https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/ChristmasTree
 *
 * Voice Commands - this Arduino gets voice commands from DF2301QG in I2C mode and sends pattern number
 *     to the other Arduino, which controls the LEDs and Bluetooth speaker.
 *
 * Note that A4 and A5 are special pins for the Arduino Nano (and several other models):
 *     they are used for the I2C interface.
 */

// connections:
//
// Nano pin 5V      LEDstick VCC
// Nano pin GND     LEDstick GND
//
// These are definitions for the DFRobot DF2301QG SKU SEN0539-EN from the Gravity product line
//     voice command module
//   https://www.dfrobot.com/product-2665.html
//   https://wiki.dfrobot.com/SKU_SEN0539-EN_Gravity_Voice_Recognition_Module_I2C_UART
// Nano pin VIN   DF2301QG VCC - VIN will be connected to UBEC/Battery power
// Nano pin GND   DF2301QG GND
// Nano pin A4    DF2301QG I2C SDA (data)  GREEN wire
// Nano pin A5    DF2301QG I2C SCL (clock) BLUE wire
//
// These are the connections to send pattern number to the other Arduino
// XFR valid   D-2  WHITE  - HI when other three pins are valid
// XFR value 1 D-3  ORANGE - power 2^0 - part of 3-bit pattern number
// XFR value 2 D-4  YELLOW - power 2^1 - part of 3-bit pattern number
// XFR value 4 D-5  BLUE   - power 2^2 - part of 3-bit pattern number

#define DEBUG_PRINT 1  // one for printing, zero for no printing
#if DEBUG_PRINT
#define DEBUG_DO_PRINT(a)   Serial.print(a)
#define DEBUG_DO_PRINTLN(a) Serial.println(a)
#else // DEBUG_PRINT
#define DEBUG_DO_PRINT(a)   // Serial.print(a)
#define DEBUG_DO_PRINTLN(a) // Serial.println(a)
#endif // DEBUG_PRINT

#include "Arduino.h"

// DFRobot SKU DF2301QG-EN communications
#include "DFRobot_DF2301Q.h"
#include "DF2301QG_cmds.h" // my list of command ID codes

// DF2301QG voice command module definitions
//    no definitions; pins A4 and A5 are automatically chosen for I2C
//I2C communication
DFRobot_DF2301Q_I2C asr;

#define DF2301QG_VOLUME_MIN   1
#define DF2301QG_VOLUME_MAX   15 // I2C indicates 20 might be possible
int8_t gDFvolume = DF2301QG_VOLUME_MAX; // signed so that could always detect "-= 1", even if MIN changes to 0


#define PATTERN_MAX_NUM 7 // 0-7 are patterns

// List of patterns to cycle through.
char * gPatternStrings[8 /*1+PATTERN_MAX_NUM*/] = { "0 rainbow", "1 rainbowWithGlitter", "2 confetti", "3 sinelon", "4 juggle", "5 bpm", "6 spinner", "7 popColor" };
uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gPrevPattern = 255; // previous pattern number - will always start with a "change" in pattern


// These are the connections to send pattern number to the other Arduino
#define XFR_PIN_WHITE_VALID 2 // set to HIGH for others valid
#define XFR_PIN_ORANGE_1    3 // power 2^0 - part of 3-bit pattern number
#define XFR_PIN_YELLOW_2    4 // power 2^1 - part of 3-bit pattern number
#define XFR_PIN_BLUE_4      5 // power 2^2 - part of 3-bit pattern number


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// handle_DF2301QG() - process DF2301QG voice command module data.
//    returns: pattern number 0 <= num <= PATTERN_MAX_NUM
//
uint8_t handle_DF2301QG() {
  uint8_t pattern = gCurrentPatternNumber; // integer pattern number from 0 thru PATTERN_MAX_NUM inclusive
  uint8_t vol_tmp;
  uint8_t CMDID; // command code received from DFRobot DF2301QG

  CMDID = asr.getCMDID(); // Get the ID for spoken command word; 0 means no command

  switch (CMDID) {
    case DF2301QG_Display_number_zero: case DF2301QG_Display_number_one: case DF2301QG_Display_number_two:
    case DF2301QG_Display_number_three: case DF2301QG_Display_number_four: case DF2301QG_Display_number_five:
    case DF2301QG_Display_number_six: case DF2301QG_Display_number_seven:
      // pattern case: we send a pattern number to companion Arduino Nano
      pattern = CMDID - DF2301QG_Display_number_zero;
      DEBUG_DO_PRINT(F("Set pattern ")); DEBUG_DO_PRINTLN(pattern);
      break;
    case DF2301QG_Volume_up: case DF2301QG_Volume_down: case DF2301QG_Change_volume_to_maximum:
    case DF2301QG_Change_volume_to_minimum: case DF2301QG_Change_volume_to_medium:
      // non-pattern case - just change the volume
      if (DF2301QG_Volume_up == CMDID) gDFvolume += 1;
      else if (DF2301QG_Volume_down == CMDID) gDFvolume -= 1;
      else if (DF2301QG_Change_volume_to_maximum == CMDID) gDFvolume = DF2301QG_VOLUME_MAX;
      else if (DF2301QG_Change_volume_to_minimum == CMDID) gDFvolume = DF2301QG_VOLUME_MIN;
      else if (DF2301QG_Change_volume_to_medium == CMDID) gDFvolume = (DF2301QG_VOLUME_MAX + DF2301QG_VOLUME_MIN) / 2;
      // now check that we are still in range
      if (gDFvolume > DF2301QG_VOLUME_MAX) gDFvolume = DF2301QG_VOLUME_MAX;
      if (gDFvolume < DF2301QG_VOLUME_MIN) gDFvolume = DF2301QG_VOLUME_MIN;
      asr.setVolume(gDFvolume);
      DEBUG_DO_PRINT(F("Set volume ")); DEBUG_DO_PRINTLN(gDFvolume);
      break;
    case 0:
      // just ignore it
      break;
    default:
      // command ID we do not handle; just print it
      DEBUG_DO_PRINT(F("DF2301QG cmd ID ")); DEBUG_DO_PRINTLN(CMDID);
      break;
  } // end switch (CMDID)

  return(pattern);
} // end handle_DF2301QG()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// xfr_pattern(pat_num) - transfer pattern number to other Arduino
//    returns: none
//
// note: Arduino delay(n) will delay at least n-1 milliseconds, unlike the rest of the world, so add 1
//   see https://forum.arduino.cc/t/problem-with-delay-and-millis/686674
//
void xfr_pattern(uint8_t pat_num) {
  digitalWrite(XFR_PIN_WHITE_VALID, LOW);   // set valid off
  delay(1+1); // make sure no timing issue with other Arduino

  if (0 == (pat_num & 0x01)) digitalWrite(XFR_PIN_ORANGE_1, LOW);
  else                       digitalWrite(XFR_PIN_ORANGE_1, HIGH);

  if (0 == (pat_num & 0x02)) digitalWrite(XFR_PIN_YELLOW_2, LOW);
  else                       digitalWrite(XFR_PIN_YELLOW_2, HIGH);

  if (0 == (pat_num & 0x04)) digitalWrite(XFR_PIN_BLUE_4, LOW);
  else                       digitalWrite(XFR_PIN_BLUE_4, HIGH);

  delay(1+1); // probably doesn't need delay here, but makes pretty Oscope trace
  digitalWrite(XFR_PIN_WHITE_VALID, HIGH);   // set valid ON
} // end xfr_pattern()

void setup() {

  pinMode(XFR_PIN_WHITE_VALID, OUTPUT);
  digitalWrite(XFR_PIN_WHITE_VALID, LOW);   // set valid off
  pinMode(XFR_PIN_ORANGE_1, OUTPUT);
  pinMode(XFR_PIN_YELLOW_2, OUTPUT);
  pinMode(XFR_PIN_BLUE_4, OUTPUT);

  Serial.begin(115200);         // this serial communication is for general debug; set the USB serial port to 115,200 baud
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println(""); // print a blank line in case there is some junk from power-on
  Serial.println("ArduinoClass Christmas Tree startup...");

  // Init the DF2301QG voice command module
  while (!(asr.begin())) {
    DEBUG_DO_PRINTLN("Communication with device failed, please check connection");
    delay(3000);
  }

  delay(5000); // let DF2301QG finish reset
  // here if want to reset the DF2301QG voice command module
  // asr.resetModule();

  asr.setMuteMode(0);
  // asr.setVolume(gDFvolume);
  asr.setWakeTime(20);

  // tell that DF2301QG voice command module is ready
  asr.playByCMDID(DF2301QG_Retreat);

  Serial.println("ArduinoClass Christmas Tree init...");
} // end setup()

#define WAIT_FOR 50 // wait this many milliseconds between checking for voice commands
void loop() {
  static uint32_t prev_millisec = 0;
  static uint32_t now_millisec = 0;
  if ((now_millisec = millis()) >= (prev_millisec + WAIT_FOR)) {
    prev_millisec = now_millisec;
    gCurrentPatternNumber = handle_DF2301QG();
  }
  if (gPrevPattern != gCurrentPatternNumber) {
    gPrevPattern = gCurrentPatternNumber;
    // Call the transfer pattern function, sending pattern to other Arduino
    xfr_pattern(gCurrentPatternNumber);
    // DEBUG_DO_PRINTLN(gPatternStrings[gCurrentPatternNumber]);
  }
} // end loop()