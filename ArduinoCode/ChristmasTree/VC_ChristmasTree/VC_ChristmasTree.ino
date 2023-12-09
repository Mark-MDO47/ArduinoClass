/*
 * Modified by Mark Olson for his Arduino class https://github.com/Mark-MDO47/ArduinoClass
 *
 * We are using an Arduino Nano with a USB mini-B connector
 *            V3.0 ATmega328P 5V 16M CH340 Compatible to Arduino Nano V3
 *            32Kbyte Flash (program storage), 2Kbyte SRAM, 1Kbyte EEPROM
 *            http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf
 *            http://www.pighixxx.com/test/pinouts/boards/nano.pdf
 *
 * VC_DemoReel.ino is code for https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/ChristmasTree
 * Major kudos to Daniel Garcia and Mark Kriegsman for the FANTASTIC FastLED library and examples!!!
 *    A sad note that Daniel Garcia, co-author of FastLED library, was on the dive boat that caught fire and has passed.
 *    Here is some info on the FastLED Reddit https://www.reddit.com/r/FastLED/
 *
 * The LED patterns are from Mark Kriegsman's classic DemoReel100.ino https://github.com/FastLED/FastLED/tree/master/examples/DemoReel100
 *
 * VoiceCommand Christmas Tree - this Arduino receives voice-commanded pattern numbers from the other
 *   Arduino and displays the appropriate DemoReel100 pattern on the LEDs
 *
 */

// connections:
//
// Nano pin D-7     WS2812B Christmas Tree Ornaments
//
// These are the connections to receive pattern number from the other Arduino
// Nano pin D-2  XFR valid   - WHITE  - HIGH when other three pins are valid
// Nano pin D-3  XFR value 1 - ORANGE - power 2^0 - part of 3-bit pattern number
// Nano pin D-4  XFR value 2 - YELLOW - power 2^1 - part of 3-bit pattern number
// Nano pin D-5  XFR value 4 - BLUE   - power 2^2 - part of 3-bit pattern number



#include <FastLED.h>

#include "Arduino.h"

#define NUMOF(x) (sizeof((x)) / sizeof((*x)))

void DFsetup();                                                // how to initialize myDFPlayer

// These are the connections to receive pattern number from the other Arduino
#define XFR_PIN_WHITE_VALID 2 // set to HI for others valid
#define XFR_PIN_ORANGE_1    3 // power 2^0 - part of 3-bit pattern number
#define XFR_PIN_YELLOW_2    4 // power 2^1 - part of 3-bit pattern number
#define XFR_PIN_BLUE_4      5 // power 2^1 - part of 3-bit pattern number

// How many leds in your strip?
#define NUM_LEDS 36 // number of WS2812B LEDs

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 7 // Mark-MDO47 we use pin 7 for LEDs
// #define CLOCK_PIN 13 // Mark-MDO47 we don't use CLOCK_PIN with this LED Strip

// Mark-MDO47 FastLED definitions
#define BRIGHTMAX 40 // set to 250 for MUCH brighter
#define FRAMES_PER_SECOND 120
#define FASTLED_RAINBOWPTRNLEN 64 // number of shades to cycle through
#define FASTLED_RAINBOWHUEROTATE 500 // rotate hues every 500th color pick

static uint8_t gHue = 0; // rotating "base color"
static uint16_t gHue_rotate_countdown = FASTLED_RAINBOWHUEROTATE;
static uint16_t next_rainbow = 0;

// with three bits for pattern numbers, we can only go from 0 through 7 inclusive
#define PATTERN_MAX_NUM 5 // 0-5 are patterns

// Define the array of leds
CRGB leds[NUM_LEDS];

// our current pattern number, from 0 thru 5 inclusive
uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gLatestTruePatternNumber = 0; // latest true pattern (not psuedo-pattern)
uint8_t gPrevPattern = 99; // previous pattern number
uint8_t gPatternNumberChanged = 0; // non-zero if need to announce pattern number

typedef struct {
  uint8_t idx_start;
  uint8_t idx_end;
} led_idx_t;


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// The brilliant (no pun intended) Demo Reel 100 patterns!
void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( gHue, 255, 192);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  uint8_t dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}

// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };
char * gPatternStrings[1+PATTERN_MAX_NUM] = { "0 rainbow dist", "1 rainbowWithGlitter dist", "2 confetti dist", "3 sinelon dist", "4 juggle dist", "5 bpm dist" };

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// rcv_pattern() - receive pattern number from other Arduino
//    returns: uint8_t pattern number 0 <= num <= PATTERN_MAX_NUM
//
uint8_t rcv_pattern() {
  uint8_t the_pattern = gCurrentPatternNumber; // if new pattern not valid, we return this
  if (HIGH == digitalRead(XFR_PIN_WHITE_VALID)) { // we have at least 1 millisec to do read
    the_pattern = 0;
    if (HIGH == digitalRead(XFR_PIN_ORANGE_1)) the_pattern += 1;
    if (HIGH == digitalRead(XFR_PIN_YELLOW_2)) the_pattern += 2;
    if (HIGH == digitalRead(XFR_PIN_BLUE_4)) the_pattern += 4;
    gLatestTruePatternNumber = the_pattern;
  } // end if valid pattern number to read
  return(the_pattern);
} // end rcv_pattern()

void setup() {
  // ## Clockless types ##
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  FastLED.setBrightness(BRIGHTMAX); // help keep our power draw through Arduino Nano down

  Serial.begin(115200);         // this serial communication is for general debug; set the USB serial port to 115,200 baud
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  pinMode(XFR_PIN_WHITE_VALID, INPUT);
  pinMode(XFR_PIN_ORANGE_1,    INPUT);
  pinMode(XFR_PIN_YELLOW_2,    INPUT);
  pinMode(XFR_PIN_BLUE_4,      INPUT);

  Serial.println(""); // print a blank line in case there is some junk from power-on
  Serial.println("ArduinoClass Christmas Tree init...");

}  // end setup()

void loop() {
  EVERY_N_MILLISECONDS( 200 ) {
    gCurrentPatternNumber = rcv_pattern();
  }
  if (gPrevPattern != gCurrentPatternNumber) {
    gPrevPattern = gCurrentPatternNumber;
    gPatternNumberChanged = 1; // alerts the announcement of the pattern
    Serial.println(gPatternStrings[gCurrentPatternNumber]);
  }

  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND);

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) {
    gHue++;  // slowly cycle the "base color" through the rainbow
  }
}
