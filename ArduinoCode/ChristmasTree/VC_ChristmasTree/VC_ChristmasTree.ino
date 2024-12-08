/*
 * Modified by Mark Olson for his Arduino class https://github.com/Mark-MDO47/ArduinoClass
 *
 * We are using an Arduino Nano with a USB mini-B connector
 *            V3.0 ATmega328P 5V 16M CH340 Compatible to Arduino Nano V3
 *            32Kbyte Flash (program storage), 2Kbyte SRAM, 1Kbyte EEPROM
 *            http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf
 *            http://www.pighixxx.com/test/pinouts/boards/nano.pdf
 *
 * VoiceCommand Christmas Tree - this Arduino receives voice-commanded pattern numbers from the other
 *   Arduino and displays the appropriate DemoReel100 pattern on the LEDs
 *
 * This is a modified version of https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/VC_DemoReel
 *    which was part of https://github.com/Mark-MDO47/ArduinoClass/tree/master/04_TheFinale
 *
 * VC_ChristmasTree.ino is code for https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/ChristmasTree
 * Major kudos to Daniel Garcia and Mark Kriegsman for the FANTASTIC FastLED library and examples!!!
 * 
 *    A sad note that Daniel Garcia, co-author of FastLED library, was on the dive boat that caught fire and has passed.
 *    Here is some info on the FastLED Reddit https://www.reddit.com/r/FastLED/
 *
 * The LED patterns are from Mark Kriegsman's classic DemoReel100.ino https://github.com/FastLED/FastLED/tree/master/examples/DemoReel100
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

// definition time to wait between switching through all patterns
#define WAIT_FOR_MSEC 6000   // milliseconds to wait before switching to next pattern for allPatterns()

// Mark-MDO47 FastLED definitions
#define BRIGHTMAX 40 // set to 250 for MUCH brighter
#define FRAMES_PER_SECOND 120
#define FASTLED_RAINBOWPTRNLEN 64 // number of shades to cycle through
#define FASTLED_RAINBOWHUEROTATE 500 // rotate hues every 500th color pick

static uint8_t gHue = 0; // rotating "base color"
static uint16_t gHue_rotate_countdown = FASTLED_RAINBOWHUEROTATE;
static uint16_t next_rainbow = 0;

// with three bits for pattern numbers, we can only go from 0 through 7 inclusive
#define PATTERN_MAX_NUM 7 // 0-7 are patterns

// Define the array of leds
CRGB leds[NUM_LEDS];

// our current pattern number, from 0 thru 5 inclusive
uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gLatestTruePatternNumber = 0; // latest true pattern (not psuedo-pattern)
uint8_t gPrevPattern = 99; // previous pattern number

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

// Now for my home-grown patterns

void spinner() {
  // every 4th LED will spin back and forth in sawtooth pattern
  static uint16_t BeatsPerMinute = 67*256; // 8.8 fixed point binary
  uint16_t i;
  CRGBPalette16 palette = PartyColors_p;
  #define SPIN_HOLD 4
  static uint16_t spin_hold = 0;
  static uint16_t spin = 0;
  if (0 == (spin_hold % SPIN_HOLD)) {
    spin += 1;
    spin_hold = (spin_hold+1) % SPIN_HOLD;
  } else {
    spin_hold = (spin_hold+1) % SPIN_HOLD;
    return;
  }

  for (i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  for (i = 0; i < NUM_LEDS; i += 4) {
    leds[(i+spin) % NUM_LEDS] = ColorFromPalette(palette, (gHue+(i*2)) % 256, 255);
  }
} // end spinner()

void popColor() {
  // pops rings of different colors
  #define POP_COLORS 9
  static CRGB pop_colors[POP_COLORS] = { CRGB::NavajoWhite, CRGB::Red, CRGB::Green, CRGB::Blue, CRGB::Yellow, CRGB::Magenta, CRGB::Cyan, CRGB::DarkOrchid, CRGB::DeepPink };
  #define NUM_CIRCLES 4
  static uint8_t circle_idx_start_end[NUM_CIRCLES+1] = { 0, 8, 16, 24, 36 };
  #define POP_HOLD 16
  #define POP_CYCLE (POP_COLORS * NUM_CIRCLES * POP_HOLD)
  static uint32_t pop_cycle_A = 0;
  static uint32_t pop_cycle_B = 2;
  uint8_t circle_idx_A = (pop_cycle_A/POP_HOLD) % NUM_CIRCLES;
  uint8_t color_idx_A = (pop_cycle_A/POP_HOLD) % POP_COLORS;
  uint8_t circle_idx_B = (pop_cycle_B/POP_HOLD) % NUM_CIRCLES;
  uint8_t color_idx_B = (pop_cycle_B/POP_HOLD) % POP_COLORS;
  int i;

  for (i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  for (i = circle_idx_start_end[circle_idx_A]; i < circle_idx_start_end[circle_idx_A+1]; i++) {
    leds[i] = pop_colors[color_idx_A];
  }
  for (i = circle_idx_start_end[circle_idx_B]; i < circle_idx_start_end[circle_idx_B+1]; i++) {
    leds[i] = pop_colors[color_idx_B];
  }
  // next cycle
  pop_cycle_A = (pop_cycle_A+1) % POP_CYCLE;
  if (0 != (pop_cycle_A % POP_COLORS)) pop_cycle_B = (pop_cycle_B+1) % POP_CYCLE;
} // end popColor() 

// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { allPatterns, rainbowWithGlitter, confetti, sinelon, juggle, bpm, spinner, popColor };
char * gPatternStrings[1+PATTERN_MAX_NUM] = { "0 allPatterns", "1 rainbowWithGlitter", "2 confetti", "3 sinelon", "4 juggle", "5 bpm", "6 spinner", "7 popColor" };

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// code to allow switching through all the patterns
void allPatterns()
{
  uint32_t nowMillisec =  millis();
  static uint8_t allPatternNumber = 1; // where we are when cycling through all patterns
  static uint32_t allSwitchMillisec = 0;  // last time we switched patterns

  if (nowMillisec >= (allSwitchMillisec + WAIT_FOR_MSEC)) {
    uint8_t tmp = allPatternNumber + 1;
    if ((tmp > PATTERN_MAX_NUM) || (0 == tmp)) { tmp = 1; }  // good practice to never store invalid value
    allPatternNumber = tmp;
    allSwitchMillisec = nowMillisec;
  }
  // Call the current all-pattern function once, updating the 'leds' array
  gPatterns[allPatternNumber]();
}  // end allPatterns()

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
