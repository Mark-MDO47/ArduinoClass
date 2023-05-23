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
 * https://github.com/Mark-MDO47/ArduinoClass/tree/master/02_PersistenceOfVision/Part_D
 * 
 * Demo Reel 100 with Sonar Ranging (Theremin) and Sound
 */

 // connections:
// 
// Nano pin 5V      LEDstick VCC
// Nano pin GND     LEDstick GND
// Nano pin D-6     LEDstick DIN
//
// Nano pin 5V      SR04 VCC
// Nano pin GND     SR04 GND
// Nano pin D-12    SR04 Trig
// Nano pin D-10    SR04 Echo
//
// Nano pin D-3     button
//
// Nano pin D-7     YX5200 TX
// Nano pin D-8     YX5200 RX
// Nano pin D-9     YX5200 BUSY

#include <FastLED.h>

#include "Arduino.h"
#include "SoftwareSerial.h"                  // to talk to myDFPlayer without using up debug serial port
#include "DFRobotDFPlayerMini.h"             // to communicate with the YX5200 audio player

#define DPIN_SWSRL_RX    8  // serial in  - talk to DFPlayer audio player (YX5200)
#define DPIN_SWSRL_TX    7  // serial out - talk to DFPlayer audio player (YX5200)
#define DPIN_AUDIO_BUSY  9  // digital input - signals when audio finishes

SoftwareSerial mySoftwareSerial(DPIN_SWSRL_RX, DPIN_SWSRL_TX); // to talk to YX5200 audio player
DFRobotDFPlayerMini myDFPlayer;                                // to talk to YX5200 audio player
void DFsetup();                                                // how to initialize myDFPlayer

#define DPIN_SWSRL_RX    8  // serial in  - talk to DFPlayer audio player (YX5200)
#define DPIN_SWSRL_TX    7  // serial out - talk to DFPlayer audio player (YX5200)
#define DPIN_AUDIO_BUSY  9  // digital input - signals when audio finishes

#define SOUNDNUM_INTRO   7 // our introduction
#define SOUNDNUM_CASSINI 8 // Cassini Saturn sound - SPACE!!!
#define SOUND_DEFAULT_VOL     25  // default volume - 25 is pretty good
#define SOUND_BKGRND_VOL      20  // background volume
#define SOUND_ACTIVE_PROTECT 250  // milliseconds to keep SW twiddled sound active after doing myDFPlayer.play(mySound)
 uint32_t state_timerForceSoundActv = 0;  // end timer for enforcing SOUND_ACTIVE_PROTECT
 
// How many leds in your strip?
#define NUM_LEDS 8 // Mark-MDO47 we have 8 LEDs

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 7 // Mark-MDO47 we use pin 7 for LEDs
// #define CLOCK_PIN 13 // Mark-MDO47 we don't use CLOCK_PIN with this LED Strip

// Mark-MDO47 FastLED definitions
#define BRIGHTMAX 40 // set to 250 for MUCH brighter
#define FRAMES_PER_SECOND 120

#define SERIAL_MAX_INPUT_LEN 5 // maximum number of characters to accept in one command; otherwise flush to next newline and process what we have
#define SERIAL_INPUT_BUF_LEN (SERIAL_MAX_INPUT_LEN + 5) // size of our actual buffer; room for terminating '\0' and a little extra
#define PATTERN_MAX_NUM 5 // 0-5 are patterns
static char serial_input_buf[SERIAL_INPUT_BUF_LEN]; // one character for terminating '\0'

// Variables will change:
static uint8_t gHue = 0; // rotating "base color"

// Define the array of leds
CRGB leds[NUM_LEDS];

// our current pattern number, from 0 thru 5 inclusive
uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// handle_serial_input_command(inbuf) - process serial input command (decimal number).
//    returns: nothing
//
// inbuf - pointer to start of zero-terminated string, no linefeed ('\n')
//         expected to be a decimal number
//
// if input number is valid, store into pattern_num

void handle_serial_input_command(char * inbuf) {
   long int tmp = atoi(inbuf);
   if ((0 <= tmp) && (PATTERN_MAX_NUM >= tmp)) {
     gCurrentPatternNumber = tmp;
     gPatternNumberChanged = 1; // alerts the announcement of the pattern
   }
} // end handle_serial_input_command()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// handle_serial_input() - process serial input. When a command is received, call handle_serial_input_command() 
//    returns: nothing
//
// Process SERIAL_MAX_INPUT_INPUT_EACH_CALL characters at a time, in case we are reading characters from a machine.
// End of command is signaled by the character '\n'
// Only valid characters in command are decimal digits
//
// serial_input_buf - where to store the serial input command
#define SERIAL_MAX_INPUT_INPUT_EACH_CALL 6 // maximum number of characters to read each call

void handle_serial_input() {
  static int serial_input_flushing = 0;
  static long int serial_input_next_char_idx = 0; // where to store the next character
  char inchar;
  long int inchar_count = 0;

  while (Serial.available()) {
    // whether saving the characters or flushing the input queue, we always read characters.
    inchar = (char) Serial.read();
    inchar_count += 1;
    if (inchar == '\n') {
      // again in either case, we process command if we see end of line
      handle_serial_input_command(serial_input_buf);
      memset((void *)serial_input_buf, 0, SERIAL_INPUT_BUF_LEN); // clear buffer
      serial_input_next_char_idx = 0; // where to store the next character
      serial_input_flushing = 0; // no longer flushing
      break; // process only one command, return back to loop for next command
    } else if (serial_input_flushing) {
      if (SERIAL_MAX_INPUT_INPUT_EACH_CALL <= inchar_count) break; // if flushing and max chars consumed, return back to loop()
    } else {
      // here we are storing characters
      if (SERIAL_MAX_INPUT_LEN <= (serial_input_next_char_idx+1)) {
        // already stored the max number of characters, now we are flushing
        serial_input_flushing = 1;
      } else if (isDigit(inchar)) {
        // room to store character and character is a digit, store it
        serial_input_buf[serial_input_next_char_idx++] = inchar;
      }
      // check if max chars consumed; if so return back to loop(), if more chars allowed, stay in our "while" loop
      if (SERIAL_MAX_INPUT_INPUT_EACH_CALL <= inchar_count) break;
    } // end either process or flush characters
  } // end while serial input data available
} // end handle_serial_input()

void setup() { 
  // ## Clockless types ##
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  FastLED.setBrightness(BRIGHTMAX); // help keep our power draw through Arduino Nano down

  pinMode(DPIN_AUDIO_BUSY,  INPUT_PULLUP); // tells when audio stops

  Serial.begin(115200);         // this serial communication is for general debug; set the USB serial port to 115,200 baud
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  while (Serial.available()) Serial.read(); // clear any startup junk from the serial queue
  memset((void *)serial_input_buf, 0, SERIAL_INPUT_BUF_LEN); // clear buffer; good idea for zero-terminated strings

  Serial.println(""); // print a blank line in case there is some junk from power-on
  Serial.println("ArduinoClass init...");
  Serial.println("Commands:");
  Serial.println("0: rainbow");
  Serial.println("1: rainbowWithGlitter");
  Serial.println("2: confetti");
  Serial.println("3: sinelon");
  Serial.println("4: juggle");
  Serial.println("5: bpm");
  Serial.println("");

  mySoftwareSerial.begin(9600); // this is control to DFPlayer audio player
  // initialize the DFPlayer audio player
  DFsetup();

}

void loop() {
  // process USB serial command characters if present
  if (Serial.available()) handle_serial_input();

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
