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
 * https://github.com/Mark-MDO47/ArduinoClass/tree/master/03_SonarRangeDetector
 * 
 * Theremin
 */

 // connections:
// 
// Nano pin 5V      LEDstick VCC
// Nano pin GND     LEDstick GND
// Nano pin D-7     LEDstick DIN
//
// Nano pin 5V      SR04 VCC
// Nano pin GND     SR04 GND
// Nano pin D-12    SR04 Trig
// Nano pin D-10    SR04 Echo
//
// Nano pin D-3     button
//
// Nano pin D-8     YX5200 TX
// Nano pin D-9     YX5200 RX
// Nano pin D-11    YX5200 BUSY

#include <FastLED.h>
#include <Ultrasonic.h>

#include "Arduino.h"
#include "SoftwareSerial.h"                  // to talk to myDFPlayer without using up debug serial port
#include "DFRobotDFPlayerMini.h"             // to communicate with the YX5200 audio player

#define DPIN_SWSRL_TX    8  // serial out - talk to DFPlayer audio player (YX5200)
#define DPIN_SWSRL_RX    9  // serial in  - talk to DFPlayer audio player (YX5200)
#define DPIN_AUDIO_BUSY 10  // digital input - signals when audio finishes

SoftwareSerial mySoftwareSerial(DPIN_SWSRL_RX, DPIN_SWSRL_TX); // to talk to YX5200 audio player
DFRobotDFPlayerMini myDFPlayer;                                // to talk to YX5200 audio player
void DFsetup();                                                // how to initialize myDFPlayer

#define SOUNDNUM_INTRO   7 // our introduction
#define SOUNDNUM_CASSINI 8 // Cassini Saturn sound - SPACE!!!
#define SOUND_DEFAULT_VOL     25  // default volume - 25 is pretty good
#define SOUND_BKGRND_VOL      20  // background volume
#define SOUND_ACTIVE_PROTECT 250  // milliseconds to keep SW twiddled sound active after doing myDFPlayer.play(mySound)
 uint32_t state_timerForceSoundActv = 0;  // end timer for enforcing SOUND_ACTIVE_PROTECT
 
// How many leds in your strip?
#define NUM_LEDS 8 // Mark-MDO47 number of WS2812B LEDs

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 7 // Mark-MDO47 we use pin 7 for LEDs
// #define CLOCK_PIN 13 // Mark-MDO47 we don't use CLOCK_PIN with this LED Strip

// Ultrasonic HC_SR04 definitions
#define ULTRA_TRIG_PIN 12 // HC-SR04 Trigger digital pin
#define ULTRA_ECHO_PIN 10 // HC-SR04 Trigger echo pin
#define ULTRA_CM_PER_REGION 9 // HC-SR04 every this many CM is a different pattern
#define ULTRA_IGNORE_INITIAL_CM 3 // HC-SR04 ignore the first 3 CM since valid range starts at 2 CM

// instantiate my HC-SR04 data object
Ultrasonic my_ultra = Ultrasonic(ULTRA_TRIG_PIN, ULTRA_ECHO_PIN); // default timeout is 20 milliseconds

// Mark-MDO47 FastLED definitions
#define BRIGHTMAX 40 // set to 250 for MUCH brighter
#define FRAMES_PER_SECOND 120

#define PATTERN_MAX_NUM 5 // 0-5 are patterns

// Variables will change:
static uint8_t gHue = 0; // rotating "base color"

// Define the array of leds
CRGB leds[NUM_LEDS];

// our current pattern number, from 0 thru 5 inclusive
uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gPrevPattern = 99; // previous pattern number
uint8_t gPatternNumberChanged = 0; // non-zero if need to announce pattern number


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// DFstartSound(tmpSoundNum, tmpVolume) - start tmpSoundNum if it is valid
//
// tmpSoundNum is the sound file number. For our Arduino Class this is 1 through 8 inclusive
//
// Had lots of trouble with reliable operation using playMp3Folder. Came to conclusion
//    that it is best to use the most primitive of YX5200 commands.
// Also saw strong correlation of using YX5200 ACK and having even more unreliable
//    operation, so turned that off in DFinit.
// The code checking DPIN_AUDIO_BUSY still needs the delay but 250 millisec is probably overkill.
// There is code checking myDFPlayer.available() that can maybe also be removed now
//    that the dubugging for above is finished. Now that I am using myDFPlayer.play(),
//    it only seems to trigger when I interrupt a playing sound by starting another.
//    It is sort of interesting but not needed.
//
void  DFstartSound(uint16_t tmpSoundNum, uint16_t tmpVolume) {
  uint16_t idx;
  bool prevHI;
  uint16_t mySound = tmpSoundNum;

  myDFPlayer.volume(tmpVolume);  // Set volume value. From 0 to 30 - FIXME 25 is good
  myDFPlayer.play(mySound); //play specific mp3 in SD: root directory ###.mp3; number played is physical copy order; first one copied is 1
  // myDFPlayer.playMp3Folder(mySound); //play specific mp3 in SD:/MP3/####.mp3; File Name(0~9999) NOTE: this did not work reliably
  state_timerForceSoundActv = millis() + SOUND_ACTIVE_PROTECT; // handle YX5200 problem with interrupting play

} // end DFstartSound()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// DFcheckSoundDone()
//
// if pattern number changed
//   interrupt sound and start sound to announce the new pattern
// else if we are past the "protected" period when we force SoundActv because YX5200 doesn't respond immediately
//   if current sound is done
//     start the Cassini sound with background volume
//
void DFcheckSoundDone() {
  if (0 != gPatternNumberChanged) {
    DFstartSound(gCurrentPatternNumber+1, SOUND_DEFAULT_VOL);
    gPatternNumberChanged = 0;
  } else if (millis() >= state_timerForceSoundActv) {
    if (LOW == digitalRead(DPIN_AUDIO_BUSY)) {
      DFstartSound(SOUNDNUM_CASSINI, SOUND_BKGRND_VOL);
    }
  }
} // end DFcheckSoundDone()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// DFsetup()
void DFsetup() {
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial, false, true)) {  // Use softwareSerial to communicate with mp3 player
    Serial.println(F("Unable to begin DFPlayer:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(1);
    }
  }
  myDFPlayer.EQ(DFPLAYER_EQ_BASS); // our speaker is quite small
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD); // device is SD card
  myDFPlayer.volume(SOUND_DEFAULT_VOL);  // Set volume value. From 0 to 30 - FIXME 25 is good
  delay(3); // allow bluetooth connection to complete
  Serial.println(F("DFPlayer Mini online."));

  DFstartSound(SOUNDNUM_INTRO, SOUND_DEFAULT_VOL);
} // end DFsetup()

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
char * gPatternStrings[1+PATTERN_MAX_NUM] = { "0 rainbow dist(cm): ", "1 rainbowWithGlitter dist(cm): ", "2 confetti dist(cm): ", "3 sinelon dist(cm): ", "4 juggle dist(cm): ", "5 bpm dist(cm): " };
int gUltraDistance = 0; // latest measured distance in centimeters

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// handle_ultra() - process HC-SR04 data.
//    returns: pattern number 0 <= num <= PATTERN_MAX_NUM
//

int handle_ultra() {
  int pattern; // integer pattern number from 0 thru 5 inclusive
  // get the range reading from the Ultrasonic sensor in centimeters
  int ultra_dist;
  
  gUltraDistance= (my_ultra.read(CM));
    ultra_dist = gUltraDistance - ULTRA_IGNORE_INITIAL_CM;
  if (ultra_dist < 0) ultra_dist = 0;
  pattern = ultra_dist / ULTRA_CM_PER_REGION;
  if (pattern > 5) pattern = 5;

  return(pattern);
} // end handle_ultra()

void setup() { 
  // ## Clockless types ##
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  FastLED.setBrightness(BRIGHTMAX); // help keep our power draw through Arduino Nano down

  pinMode(DPIN_AUDIO_BUSY,  INPUT_PULLUP); // tells when audio stops

  Serial.begin(115200);         // this serial communication is for general debug; set the USB serial port to 115,200 baud
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println(""); // print a blank line in case there is some junk from power-on
  Serial.println("ArduinoClass init...");
}

void loop() {
  EVERY_N_MILLISECONDS( 200 ) { gCurrentPatternNumber = handle_ultra(); }
  if (gPrevPattern != gCurrentPatternNumber) {
    gPrevPattern = gCurrentPatternNumber;
    gPatternNumberChanged = 1; // alerts the announcement of the pattern
    Serial.print(gPatternStrings[gCurrentPatternNumber]); Serial.println(gUltraDistance);
  }

  // whenever current sound is done, go back to Cassini
  DFcheckSoundDone();

  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
}