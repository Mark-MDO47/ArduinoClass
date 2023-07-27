/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

/*
 * Modified by Mark Olson for his Arduino class https://github.com/Mark-MDO47/ArduinoClass
 * 
 * We are using an Arduino Nano with a USB mini-B connector
 *            V3.0 ATmega328P 5V 16M CH340 Compatible to Arduino Nano V3
 *            32Kbyte Flash (program storage), 2Kbyte SRAM, 1Kbyte EEPROM
 *            http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf
 *            http://www.pighixxx.com/test/pinouts/boards/nano.pdf
 *
 * Blink.ino is code for https://github.com/Mark-MDO47/ArduinoClass/tree/master/01_BlinkingLED
 * 
 * Added a button
 * Added an external LED
 */

 // connections:
// 
// Nano pin D-3     old-style LED
//
// Nano pin D-5     Button

#define DPIN_LED_OUT 3 // in case we want to move it, only need to change this
#define DPIN_BTN_IN  5 // this pin is used to sense the external button
static int loop_count = 0;

// the setup function runs once when you press reset or power the board
void setup() {

  pinMode(LED_BUILTIN, OUTPUT); // initialize digital pin LED_BUILTIN as an output.
  pinMode(DPIN_LED_OUT, OUTPUT);      // digital OUTPUT means we control voltage on pin, HIGH or LOW
  pinMode(DPIN_BTN_IN, INPUT_PULLUP); // digital INPUT_PULLUP means voltage HIGH unless grounded

  Serial.begin(115200);         // this serial communication is for general debug; set the USB serial port to 115,200 baud

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println(""); // print a blank line in case there is some junk from power-on
  Serial.println(F("ArduinoClass init..."));
}

// the loop function runs over and over again forever
void loop() {
  int btn_val = digitalRead(DPIN_BTN_IN);

  if (HIGH == btn_val) { // push button to STOP light blinking
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(DPIN_LED_OUT, LOW);   // turn the external LED off
  } // end if btn_val HIGH
  delay(1000);                       // wait for a second
  if (HIGH == btn_val) {
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(DPIN_LED_OUT, HIGH);  // turn the external LED on
  } // end if btn_val HIGH
  delay(1000);                       // wait for a second

  loop_count += 1;    // instead of loop_count = loop_count + 1
  Serial.print("Button ");
  if (HIGH == btn_val) {
    Serial.print("UP   (GO)  ");
  } else {
    Serial.print("DOWN (STOP)");
  } // end if statement on btn_val
  Serial.print(" loop_count: "); Serial.println(loop_count);
}
