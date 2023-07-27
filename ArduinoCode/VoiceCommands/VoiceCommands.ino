/// @file    Blink.ino
/// @brief   Blink the first LED of an LED strip
/// @example Blink.ino

/*
 * Modified by Mark Olson for his Arduino class https://github.com/Mark-MDO47/ArduinoClass
 * 
 * We are using an Arduino Nano with a USB mini-B connector
 *            V3.0 ATmega328P 5V 16M CH340 Compatible to Arduino Nano V3
 *            32Kbyte Flash (program storage), 2Kbyte SRAM, 1Kbyte EEPROM
 *            http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf
 *            http://www.pighixxx.com/test/pinouts/boards/nano.pdf
 *
 * VoiceCommands.ino is code for https://github.com/Mark-MDO47/ArduinoClass/tree/master/04_TheFinale
 * 
 * Voice Commands - this Arduino gets voice commands from DF2301QG and sends pattern number
 *     to the other Arduino, which controls the LEDs and Bluetooth speaker.
 */

 // connections:
// 
// Nano pin 5V      LEDstick VCC
// Nano pin GND     LEDstick GND
//
// These are definitions for the DFRobot SKU DF2301QG-EN from the Gravity product line
//     voice command module
//   https://www.dfrobot.com/product-2665.html
//   https://wiki.dfrobot.com/SKU_DF2301QG-EN_Gravity_Voice_Recognition_Module_I2C_UART#target_4
// Nano pin 5V      DF2301QG VCC
// Nano pin GND     DF2301QG GND
// Nano pin D-10    DF2301QG UART TX (Nano RX) GREEN wire
// Nano pin D-12    DF2301QG UART RX (Nano TX) BLUE wire
//
// These are the connections to send pattern number to the other Arduino
// XFR valid   D-2  WHITE  - HI when other three pins are valid
// XFR value 1 D-3  ORANGE - power 2^0 - part of 3-bit pattern number
// XFR value 2 D-4  YELLOW - power 2^1 - part of 3-bit pattern number
// XFR value 4 D-5  BLUE   - power 2^2 - part of 3-bit pattern number

#include "Arduino.h"

// DFRobot SKU DF2301QG-EN communications
#include "SoftwareSerial.h"                  // to talk to myDFPlayer without using up debug serial port
#include "DFRobot_DF2301Q.h"
#include "DF2301QG_cmds.h" // my list of command ID codes

// DF2301QG voice command module definitions
#define DF2301QG_RX_PIN 10 // DF2301QG UART TX (Nano RX)
#define DF2301QG_TX_PIN 12 // DF2301QG UART RX (Nano TX)
/**
   @brief DFRobot_URM13_RTU constructor
   @param serial - serial ports for communication, supporting hard and soft serial ports
   @param rx - UART The pin for receiving data
   @param tx - UART The pin for transmitting data
*/
SoftwareSerial softSerial(/*rx =*/DF2301QG_RX_PIN, /*tx =*/DF2301QG_TX_PIN);
DFRobot_DF2301Q_UART asr(/*softSerial =*/&softSerial);

#define PATTERN_MAX_NUM 5 // 0-5 are patterns

// List of patterns to cycle through.
char * gPatternStrings[1+PATTERN_MAX_NUM] = { "0 rainbow", "1 rainbowWithGlitter", "2 confetti", "3 sinelon", "4 juggle", "5 bpm" };
uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gPrevPattern = -1; // previous pattern number


// These are the connections to send pattern number to the other Arduino
#define XFR_PIN_WHITE_VALID 2 // set to HIGH for others valid
#define XFR_PIN_ORANGE_1    3 // power 2^0 - part of 3-bit pattern number
#define XFR_PIN_YELLOW_2    4 // power 2^1 - part of 3-bit pattern number
#define XFR_PIN_BLUE_4      5 // power 2^1 - part of 3-bit pattern number


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// handle_DF2301QG() - process DF2301QG voice command module data.
//    returns: pattern number 0 <= num <= PATTERN_MAX_NUM
//
uint8_t handle_DF2301QG() {
  uint8_t pattern = gCurrentPatternNumber; // integer pattern number from 0 thru 5 inclusive
  uint8_t CMDID; // command code received from DFRobot DF2301QG

  CMDID = asr.getCMDID(); // Get the ID for spoken command word; 0 means no command

  if ((DF2301QG_Display_number_zero <= CMDID) && (CMDID <= DF2301QG_Display_number_five)) {
    pattern = CMDID - DF2301QG_Display_number_zero;
    Serial.print(F("Set pattern ")); Serial.println(pattern);
  } else if (CMDID != 0) {
    Serial.print(F("DF2301QG cmd ID ")); Serial.println(CMDID);
  }
  return(pattern);
} // end handle_DF2301QG()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// xfr_pattern(pat_num) - transfer pattern number to other Arduino
//    returns: none
//
void xfr_pattern(uint8_t pat_num) {
  digitalWrite(XFR_PIN_WHITE_VALID, LOW);   // set valid off
  delay(1); // make sure no timing issue with other Arduino

  if (0 == (pat_num & 0x01)) digitalWrite(XFR_PIN_ORANGE_1, LOW);
  else                       digitalWrite(XFR_PIN_ORANGE_1, HIGH);

  if (0 == (pat_num & 0x02)) digitalWrite(XFR_PIN_YELLOW_2, LOW);
  else                       digitalWrite(XFR_PIN_YELLOW_2, HIGH);

  if (0 == (pat_num & 0x02)) digitalWrite(XFR_PIN_BLUE_4, LOW);
  else                       digitalWrite(XFR_PIN_BLUE_4, HIGH);

  delay(1); // probably doesn't need delay here, but belt and suspenders
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

  // Init the DF2301QG voice command module
  while (!(asr.begin())) {
    Serial.println("Communication with device failed, please check connection");
    delay(3000);
  }

  softSerial.listen();
  // here if want to reset the DF2301QG voice command module
  // asr.resetModule();

  /* possible DF2301QG "SET" commands
     DF2301Q_UART_MSG_CMD_SET_VOLUME: Set volume, the set value range 1-7 
     DF2301Q_UART_MSG_CMD_SET_ENTERWAKEUP: Enter wake-up state; set value 0
     DF2301Q_UART_MSG_CMD_SET_MUTE Mute mode; set value 1: mute, 0: unmute
     DF2301Q_UART_MSG_CMD_SET_WAKE_TIME ; Wake-up duration; the set value range 0-255s
  */
  asr.settingCMD(DF2301Q_UART_MSG_CMD_SET_MUTE, 0);
  asr.settingCMD(DF2301Q_UART_MSG_CMD_SET_VOLUME, 7);
  asr.settingCMD(DF2301Q_UART_MSG_CMD_SET_WAKE_TIME, 20);

  // tell that DF2301QG voice command module is ready
  asr.playByCMDID(DF2301QG_Retreat);

  Serial.println("ArduinoClass init...");
} // end setup()

#define WAIT_FOR 100 // wait 100 milliseconds
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
    Serial.println(gPatternStrings[gCurrentPatternNumber]);
  }
} // end loop()
