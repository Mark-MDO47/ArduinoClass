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
 * Sawtooth.ino is code for https://github.com/Mark-MDO47/ArduinoClass/tree/master/02_PersistenceOfVision/Part_B
 * 
 * Persistence of Vision Sawtooth pattern
 */

 // connections:
// 
// Nano pin 5V      LEDstick VCC
// Nano pin GND     LEDstick GND
// Nano pin D-7     LEDstick DIN
//
// Nano pin D-3     Button

#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 8 // Mark-MDO47 we have 8 LEDs

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 7 // Mark-MDO47 we use pin 7 for LEDs
// #define CLOCK_PIN 13 // Mark-MDO47 we don't use CLOCK_PIN with this LED Strip

// Mark-MDO47 we will use a button
#define BUTTON_PIN 3 // Mark-MDO47 we use pin 3 for button

// Mark-MDO47 Sawtooth pattern repeat count
#define SAWTOOTH_CALLS_THEN_REPEAT 14 // the Sawtooth pattern does this many calls then repeats

// Variables will change:
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// Define the array of leds
CRGB fastled_array[NUM_LEDS];

// constants won't change:
const long interval = 1;           // interval at which to blink (milliseconds)

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// sawtooth_phase(btn_pressed) - determine the state of what the phase of pattern generation is
//    returns: long int with either value >= 0 phase to blink or value < 0 paused
//
// btn_pressed - the pushbutton status; pressed==LOW, not-pressed==HIGH
//       btn_pressed LOW means reset to start of pattern and wait for btn_pressed HIGH
//       note that ONLY this routine interprets btn_pressed

long int sawtooth_phase(int btn_pressed) {
  static long int current_phase = -1;

  if (LOW == btn_pressed) {
    current_phase = -1; // reset pattern and pause
  } else {
    current_phase += 1;
    current_phase %= SAWTOOTH_CALLS_THEN_REPEAT; // loop through the number of calls before repeat
  }
  
  return(current_phase);
} // end sawtooth_phase()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// sawtooth_pause_pattern(blink_phase, ptrn_leds) - 
//    fills ptrn_leds with all CRGB:Black
//    returns: none
//
// blink_phase - ignored
// ptrn_leds   - where to store the pattern

void sawtooth_pause_pattern(long int blink_phase, CRGB * ptrn_leds) {

  // pause pattern - all CRGB::Black
  for (long int i = 0; i < NUM_LEDS; i++) {
    ptrn_leds[i] = CRGB::Black;
  }

} // end sawtooth_pause_pattern()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// sawtooth_blink_pattern(blink_phase, ptrn_leds) - 
//    fills ptrn_leds with next pattern based on blink_phase
//    returns: none
//
// blink_phase - long int, range 0-13
// ptrn_leds   - where to store the pattern

void sawtooth_blink_pattern(long int blink_phase, CRGB * ptrn_leds) {
  static const int led_on_array_per_call[SAWTOOTH_CALLS_THEN_REPEAT] = { 0, 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1 };

  // blink pattern - all CRGB:Black except one CRGB::Red
  for (long int i = 0; i < NUM_LEDS; i++) {
    ptrn_leds[i] = CRGB::Black;
  }
  ptrn_leds[led_on_array_per_call[blink_phase]] = CRGB::Red;

} // end sawtooth_blink_pattern()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// sawtooth_fill_pattern(btn_pressed, ptrn_leds) - 
//    returns: int with either value HIGH==blinked the LEDs or LOW==did not blink
//
// btn_pressed - the pushbutton status; pressed==LOW, not-pressed==HIGH
// ptrn_leds   - where to store the pattern

int sawtooth_fill_pattern(int btn_pressed, CRGB * ptrn_leds) {
  int did_blink = LOW;
  long int blink_phase = sawtooth_phase(btn_pressed);

  if (blink_phase < 0) {
    sawtooth_pause_pattern(blink_phase, ptrn_leds);
    did_blink = LOW;
  } else {
    sawtooth_blink_pattern(blink_phase, ptrn_leds);
    did_blink = HIGH;
  }

  return(did_blink);
} // end sawtooth_fill_pattern

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// handle_leds(...) - get the pattern and then display on LEDs
//    returns: int with either value HIGH==blinked the LEDs or LOW==did not blink
//
// btn_pressed - the pushbutton status; pressed==LOW, not-pressed==HIGH
//       note that this routine does not know what to do with btn_pressed;
//       the pattern routines (in this case Sawtooth) know what to do with btn_pressed

int handle_leds(int btn_pressed) {
  int did_blink = sawtooth_fill_pattern(btn_pressed, fastled_array); // fill the pattern into RAM

  FastLED.show(); // show the pattern on LEDs

  return(did_blink); // HIGH if blink, LOW if pause
} // end handle_leds()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// handle_button(btn_pin) - determine the state of a single button or any digital input, HIGH or LOW
//    returns: int with either value HIGH or LOW
//
// btn_pin is the pin number of the digital pin we sense for the button, range 1-13 inclusive

int handle_button(int btn_pin) {
  return(digitalRead(btn_pin)); // the pushbutton status; pressed==LOW, not-pressed==HIGH
} // end handle_button()


void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP); // digital INPUT_PULLUP means voltage HIGH unless grounded

  // ## Clockless types ##
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(fastled_array, NUM_LEDS);  // GRB ordering is assumed
}

void loop() { 
  // check to see if it's time to "blink" the LED strip; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();

  // Mark-MDO47 the pushbutton status; pressed==LOW, not-pressed==HIGH
  int button_up = handle_button(BUTTON_PIN);

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    handle_leds(button_up); // Mark-MDO47 generate pattern to display and display it
  }
}
