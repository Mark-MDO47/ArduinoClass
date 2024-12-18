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
 * VC_DemoReel.ino is code for https://github.com/Mark-MDO47/ArduinoClass/tree/master/04_TheFinale
 * Major kudos to Daniel Garcia and Mark Kriegsman for the FANTASTIC FastLED library and examples!!!
 *    A sad note that Daniel Garcia, co-author of FastLED library, was on the dive boat that caught fire and has passed.
 *    Here is some info on the FastLED Reddit https://www.reddit.com/r/FastLED/
 *
 * The LED patterns are from Mark Kriegsman's classic DemoReel100.ino https://github.com/FastLED/FastLED/tree/master/examples/DemoReel100
 *
 * I also hand-edited a smiley face. It would be near criminal to use a voice command module with a
 *
 * VoiceCommand Demo Reel - this Arduino receives voice-commanded pattern numbers from the other
 *   Arduino and displays the appropriate DemoReel100 pattern on the LEDs and announces the pattern
 *   name on the Bluetooth speaker.
 *
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
// Nano pin D-8     YX5200 TX; Arduino RX
// Nano pin D-9     YX5200 RX; Arduino TX
// Nano pin D-11    YX5200 BUSY; HIGH when audio finishes

// These are the connections to receive pattern number from the other Arduino
// Nano pin D-2  XFR valid   - WHITE  - HIGH when other three pins are valid
// Nano pin D-3  XFR value 1 - ORANGE - power 2^0 - part of 3-bit pattern number
// Nano pin D-4  XFR value 2 - YELLOW - power 2^1 - part of 3-bit pattern number
// Nano pin D-5  XFR value 4 - BLUE   - power 2^2 - part of 3-bit pattern number



#include <FastLED.h>

#include "Arduino.h"
#include "SoftwareSerial.h"                  // to talk to myDFPlayer without using up debug serial port
#include "DFRobotDFPlayerMini.h"             // to communicate with the YX5200 audio player

#define NUMOF(x) (sizeof((x)) / sizeof((*x)))

#define DPIN_SWSRL_TX    9  // serial out - talk to DFPlayer audio player (YX5200)
#define DPIN_SWSRL_RX    8  // serial in  - talk to DFPlayer audio player (YX5200)
#define DPIN_AUDIO_BUSY 11  // digital input - HIGH when audio finishes

SoftwareSerial mySoftwareSerial(/*rx =*/DPIN_SWSRL_RX, /*tx =*/DPIN_SWSRL_TX); // to talk to YX5200 audio player
              // SoftwareSerial(rxPin,         txPin,       inverse_logic)
DFRobotDFPlayerMini myDFPlayer;                                // to talk to YX5200 audio player
void DFsetup();                                                // how to initialize myDFPlayer

#define SOUNDNUM_INTRO   7 // our introduction
#define SOUNDNUM_CASSINI 8 // Cassini Saturn sound - SPACE!!!
#define SOUND_DEFAULT_VOL     25  // default volume - 25 is pretty good
#define SOUND_BKGRND_VOL      15  // background volume
#define SOUND_ACTIVE_PROTECT 250  // milliseconds to keep SW twiddled sound active after doing myDFPlayer.play(mySound)
uint32_t state_timerForceSoundActv = 0;  // end timer for enforcing SOUND_ACTIVE_PROTECT
uint8_t state_introSoundPlaying = 1; // we start with the intro sound

// These are the connections to receive pattern number from the other Arduino
#define XFR_PIN_WHITE_VALID 2 // set to HI for others valid
#define XFR_PIN_ORANGE_1    3 // power 2^0 - part of 3-bit pattern number
#define XFR_PIN_YELLOW_2    4 // power 2^1 - part of 3-bit pattern number
#define XFR_PIN_BLUE_4      5 // power 2^1 - part of 3-bit pattern number

// How many leds in your strip?
#define NUM_LEDS 241 // number of WS2812B LEDs

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
#define SMILEY_COLOR_ALL_ONE
// #define SMILEY_COLOR_RAINBOW

#ifdef SMILEY_COLOR_ALL_ONE
static const CRGB all_one_loop_array[] = {CRGB::Red, CRGB::White, CRGB::Blue, CRGB::Green };
#endif // SMILEY_COLOR_ALL_ONE
#ifdef SMILEY_COLOR_RAINBOW
static CRGB rainbow_array[FASTLED_RAINBOWPTRNLEN]; // rainbow pattern colors
#endif // SMILEY_COLOR_RAINBOW
static uint8_t gHue = 0; // rotating "base color"
static uint16_t gHue_rotate_countdown = FASTLED_RAINBOWHUEROTATE;
static uint16_t next_rainbow = 0;

// with three bits for pattern numbers, we can only go from 0 through 7 inclusive
#define PATTERN_MAX_NUM 5 // 0-5 are patterns
#define PATTERN_SMILEY_ONLY 98 // pattern if just toggled smiley on
#define PSUEDO_PATTERN_SMILEY_ON  (PATTERN_MAX_NUM+1)   // 6 to turn smiley face on
#define PSUEDO_PATTERN_SMILEY_OFF (PSUEDO_PATTERN_SMILEY_ON+1) // 7 to turn smiley face on


// Define the array of leds
CRGB leds[NUM_LEDS];

// our current pattern number, from 0 thru 5 inclusive
uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gLatestTruePatternNumber = 0; // latest true pattern (not psuedo-pattern)
uint8_t gPrevPattern = 99; // previous pattern number
uint8_t gPatternNumberChanged = 0; // non-zero if need to announce pattern number
uint8_t gSmileyFaceOn = 0; // non-zero to turn on smiley face


typedef struct {
  uint8_t idx_start;
  uint8_t idx_end;
} led_idx_t;
static const led_idx_t lower_smile[] = { {108, 115}, {141, 147} };
static const led_idx_t upper_smile[] = { {153, 153}, {175, 175}, {183, 183}, {201, 201}, {204, 205}, {219, 219} };
static const led_idx_t eyes[] = { {159, 160}, {168, 169}, {188, 189}, {195, 196} };

#define DFCHANGEVOLUME 0 // zero does not change sound
// #define DFPRINTDETAIL 1 // if need detailed status from myDFPlayer (YX5200 communications)
#define DFPRINTDETAIL 0  // will not print detailed status from myDFPlayer
#if DFPRINTDETAIL // routine to do detailed debugging
  void DFprintDetail(uint8_t type, int value); // definition of call
#else  // no DFPRINTDETAIL
  #define DFprintDetail(type, value) // nothing at all
#endif // #if DFPRINTDETAIL

/////////////////////////////////////////////////////////////////////////////////////////////////////////
#if DFPRINTDETAIL
void DFprintDetail(uint8_t type, int value) {
  switch (type) {
  case TimeOut:
    Serial.println(F("Time Out!"));
    break;
  case WrongStack:
    Serial.println(F("Stack Wrong!"));
    break;
  case DFPlayerCardInserted:
    Serial.println(F("Card Inserted!"));
    break;
  case DFPlayerCardRemoved:
    Serial.println(F("Card Removed!"));
    break;
  case DFPlayerCardOnline:
    Serial.println(F("Card Online!"));
    break;
  case DFPlayerUSBInserted:
    Serial.println("USB Inserted!");
    break;
  case DFPlayerUSBRemoved:
    Serial.println("USB Removed!");
    break;
  case DFPlayerPlayFinished:
    Serial.print(F("Number:"));
    Serial.print(value);
    Serial.println(F(" Play Finished!"));
    break;
  case DFPlayerError:
    Serial.print(F("DFPlayerError:"));
    switch (value) {
    case Busy:
      Serial.println(F("Card not found"));
      break;
    case Sleeping:
      Serial.println(F("Sleeping"));
      break;
    case SerialWrongStack:
      Serial.println(F("Get Wrong Stack"));
      break;
    case CheckSumNotMatch:
      Serial.println(F("Check Sum Not Match"));
      break;
    case FileIndexOut:
      Serial.println(F("File Index Out of Bound"));
      break;
    case FileMismatch:
      Serial.println(F("Cannot Find File"));
      break;
    case Advertise:
      Serial.println(F("In Advertise"));
      break;
    default:
      break;
    } // end switch (value)
    break;
  default:
    break;
  }  // end switch (type)
} // end DFprintDetail()
#endif // DFPRINTDETAIL

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
  static uint8_t init_minmax = 2;
  static uint32_t prev_msec;
  static uint32_t max_msec = 0;
  static uint32_t min_msec = 999999;
  uint32_t diff_msec = 0;
  uint32_t now_msec = millis();


#if DFCHANGEVOLUME
  myDFPlayer.volume(tmpVolume);  // Set volume value. From 0 to 30 - FIXME 25 is good
#if DFPRINTDETAIL
  if (myDFPlayer.available()) {
    Serial.print(F(" DFstartSound ln "));
    Serial.print((uint16_t) __LINE__);
    Serial.println(F(" myDFPlayer problem after volume"));
    DFprintDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
  }
#endif // DFPRINTDETAIL
#endif // DFCHANGEVOLUME

  myDFPlayer.play(mySound); //play specific mp3 in SD: root directory ###.mp3; number played is physical copy order; first one copied is 1
  // Serial.print(F("DEBUG DFstartSound myDFPlayer.play(")); Serial.print((uint16_t) mySound); Serial.println(F(")"));
  state_timerForceSoundActv = millis() + SOUND_ACTIVE_PROTECT; // handle YX5200 problem with interrupting play

  if (init_minmax) {
    init_minmax -= 1;
  }  else {
    diff_msec = now_msec - prev_msec;
    if (diff_msec > max_msec) {
      max_msec = diff_msec;
      // Serial.print(F("max_msec ")); Serial.println(max_msec);
    } else if (diff_msec < min_msec) {
      min_msec = diff_msec;
      // Serial.print(F("min_msec ")); Serial.println(min_msec);
    }
  }
  prev_msec = now_msec;
} // end DFstartSound()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// DFcheckSoundDone()
//
// notBusy means (HIGH == digitalRead(DPIN_AUDIO_BUSY)) && (millis() >= state_timerForceSoundActv)
//    DPIN_AUDIO_BUSY goes HIGH when sound finished, but may take a while to start
//    state_timerForceSoundActv is millisec count we have to wait for to before checking DPIN_AUDIO_BUSY
//
void DFcheckSoundDone() {
  uint8_t myBusy = (HIGH != digitalRead(DPIN_AUDIO_BUSY)) || (millis() < state_timerForceSoundActv);
  uint8_t playNumber = 99; // this means don't change

  if (0 != state_introSoundPlaying) { // intro still playing
    if (0 == myBusy) { // can play a non-intro sound
      if (0 != gPatternNumberChanged) { // start pattern sound
        if (PATTERN_SMILEY_ONLY == gCurrentPatternNumber) {
          playNumber = SOUNDNUM_CASSINI; // we don't have a sound for smiley face
        } else {
          playNumber = gCurrentPatternNumber+1; // sound numbers start at 1
        }
      } else { // start Cassini sound
        playNumber = SOUNDNUM_CASSINI; // this should never execute, we start with gPatternNumberChanged=1
      } // end start a sound
    } // end if can play a non-intro sound
  } else { // intro done
    if (0 != gPatternNumberChanged) { // always start new pattern number sound
      if (PATTERN_SMILEY_ONLY == gCurrentPatternNumber) {
        playNumber = SOUNDNUM_CASSINI; // we don't have a sound for smiley face
      } else {
        playNumber = gCurrentPatternNumber+1; // sound numbers start at 1
      }
    } else if (0 == myBusy) { // sound finished and no new pattern, start Cassini
      playNumber = SOUNDNUM_CASSINI;
    }
  } // end if intro done

  if ((99 != playNumber) && (PATTERN_SMILEY_ONLY != gCurrentPatternNumber)) { // there is a new sound to play
    gPatternNumberChanged = 0;
    state_introSoundPlaying = 0;
    if (SOUNDNUM_CASSINI == playNumber) {
      DFstartSound(SOUNDNUM_CASSINI, SOUND_BKGRND_VOL);
    } else {
      DFstartSound(gCurrentPatternNumber+1, SOUND_DEFAULT_VOL);
    }
  } // end if there is a new sound to play
} // end DFcheckSoundDone()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// DFsetup()
void DFsetup() {
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial, false, true)) {  // Use softwareSerial to communicate with mp3 player
    Serial.println(F("Unable to begin DFPlayer:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true) {
      delay(1);
    }
  }
  myDFPlayer.EQ(DFPLAYER_EQ_BASS); // our speaker is quite small
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD); // device is SD card
  myDFPlayer.volume(SOUND_DEFAULT_VOL);  // Set volume value. From 0 to 30 - FIXME 25 is good
  delay(3000); // allow bluetooth connection to complete
  Serial.println(F("DFPlayer Mini online."));

  DFstartSound(SOUNDNUM_INTRO, SOUND_DEFAULT_VOL);
} // end DFsetup()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// insertSmileyFace() - over-write a smiley face onto the pattern
//
void insertSmileyFace() {
  static const led_idx_t * uplow_smile[] = { lower_smile, upper_smile, eyes };
  static const uint8_t * uplow_smile_numof[] = { NUMOF(lower_smile), NUMOF(upper_smile), NUMOF(eyes) };
  led_idx_t * smile_led_idx;

#ifdef SMILEY_COLOR_ALL_ONE
  static uint8_t onoff = 0;
  static uint32_t all_one_loop = 0;
  onoff = (onoff+1) % 32;
  if (15 == onoff) all_one_loop += 1;
#endif // SMILEY_COLOR_ALL_ONE

  for (uint8_t i = 0; i < NUMOF(uplow_smile); i++) {
    smile_led_idx = uplow_smile[i];
    uint8_t numof = uplow_smile_numof[i];
    for (uint8_t j = 0; j < numof; j++) {
      for (uint8_t k = smile_led_idx[j].idx_start; k <= smile_led_idx[j].idx_end; k++) {
        // fill the LEDs for the smiley face

#ifdef SMILEY_COLOR_ALL_ONE
//        if (onoff & 0x8)  leds[k] = all_one_loop_array[all_one_loop % NUMOF(all_one_loop_array)];
//        else              leds[k] = CRGB::Black;
        leds[k] = all_one_loop_array[all_one_loop % NUMOF(all_one_loop_array)];
#endif // SMILEY_COLOR_ALL_ONE
#ifdef SMILEY_COLOR_RAINBOW
        leds[k] = rainbow_array[next_rainbow++];
        if (next_rainbow >= FASTLED_RAINBOWPTRNLEN) next_rainbow = 0;
        gHue_rotate_countdown -= 1;
        if ((0 == gHue_rotate_countdown) || (gHue_rotate_countdown >= FASTLED_RAINBOWHUEROTATE)) {
          gHue_rotate_countdown = FASTLED_RAINBOWHUEROTATE;
          gHue += 4; // rotating "base color"
          fill_rainbow(rainbow_array, FASTLED_RAINBOWPTRNLEN, gHue, 21); // this fills up the colors to send later
        }
#endif // SMILEY_COLOR_RAINBOW

      } // end fill the LEDs for the smiley face
    } // for all led_idx_t in this part
  } // for all parts of uplow_smile
} // end insertSmileyFace()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// do_smiley_background() - background all-black if just toggled to smiley face
//
void do_smiley_background() {
  for (uint16_t i=0; i < NUM_LEDS; i++) leds[i] = CRGB::Black;
} // do_smiley_background

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
// PSUEDO_PATTERN_SMILEY_ON or PSUEDO_PATTERN_SMILEY_OFF will affect the smiley face
//   but will not change the pattern number EXCEPT for the first time it toggles on
//   and (possibly) the first time it toggles off.
//
uint8_t rcv_pattern() {
  uint8_t the_pattern = gCurrentPatternNumber; // if new pattern not valid, we return this
  uint8_t the_pattern_before_smiley = 0;
  if (HIGH == digitalRead(XFR_PIN_WHITE_VALID)) { // we have at least 1 millisec to do read
    the_pattern = 0;
    if (HIGH == digitalRead(XFR_PIN_ORANGE_1)) the_pattern += 1;
    if (HIGH == digitalRead(XFR_PIN_YELLOW_2)) the_pattern += 2;
    if (HIGH == digitalRead(XFR_PIN_BLUE_4)) the_pattern += 4;
    // handle smiley
    if (PSUEDO_PATTERN_SMILEY_ON == the_pattern) {
      if (0 == gSmileyFaceOn) {
        the_pattern = PATTERN_SMILEY_ONLY; // first time we toggle on
      } else { // this really should not happen
        the_pattern = gCurrentPatternNumber;
      }
      gSmileyFaceOn = 1;
    } else if (PSUEDO_PATTERN_SMILEY_OFF == the_pattern) {
      the_pattern = gLatestTruePatternNumber; // return to last true pattern
      gSmileyFaceOn = 0;
    } else { // it is a true pattern not a psuedo-pattern
      gLatestTruePatternNumber = the_pattern;
    }
  } // end if valid pattern number to read
  return(the_pattern);
} // end rcv_pattern()

void setup() {
  // ## Clockless types ##
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  FastLED.setBrightness(BRIGHTMAX); // help keep our power draw through Arduino Nano down
#ifdef SMILEY_COLOR_RAINBOW
  fill_rainbow(rainbow_array, FASTLED_RAINBOWPTRNLEN, gHue, 21); // this fills up the colors to send later
#endif // SMILEY_COLOR_RAINBOW

  Serial.begin(115200);         // this serial communication is for general debug; set the USB serial port to 115,200 baud
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  pinMode(DPIN_AUDIO_BUSY, INPUT_PULLUP); // HIGH when audio stops

  pinMode(XFR_PIN_WHITE_VALID, INPUT);
  pinMode(XFR_PIN_ORANGE_1,    INPUT);
  pinMode(XFR_PIN_YELLOW_2,    INPUT);
  pinMode(XFR_PIN_BLUE_4,      INPUT);

  mySoftwareSerial.begin(9600); // this is control to DFPlayer audio player

  // initialize the YX5200 DFPlayer audio player
  DFsetup();

  Serial.println(""); // print a blank line in case there is some junk from power-on
  Serial.println("ArduinoClass init...");

}  // end setup()

void loop() {
  EVERY_N_MILLISECONDS( 200 ) {
    gCurrentPatternNumber = rcv_pattern();
  }
  if (gPrevPattern != gCurrentPatternNumber) {
    gPrevPattern = gCurrentPatternNumber;
    gPatternNumberChanged = 1; // alerts the announcement of the pattern
    if (PATTERN_SMILEY_ONLY != gCurrentPatternNumber) {
      Serial.println(gPatternStrings[gCurrentPatternNumber]);
    } else {
      Serial.println(F("Smiley Face Only"));
    }
  }

  // whenever current sound is done, go back to Cassini
  DFcheckSoundDone();

  // Call the current pattern function once, updating the 'leds' array
  if (PATTERN_SMILEY_ONLY != gCurrentPatternNumber) {
    gPatterns[gCurrentPatternNumber]();
  } else {
    do_smiley_background();
  }
  // if doing smiley face, insert that here
  if (gSmileyFaceOn) {
    insertSmileyFace();
  }

  // send the 'leds' array out to the actual LED strip
  FastLED.show();
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND);

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) {
    gHue++;  // slowly cycle the "base color" through the rainbow
  }
}
