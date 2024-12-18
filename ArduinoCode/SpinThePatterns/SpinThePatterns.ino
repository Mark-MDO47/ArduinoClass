/// @file    Blink.ino
/// @brief   Blink the first LED of an LED strip
/// @example Blink.ino

/*
 * Modified by Mark Olson for his Arduino class https://github.com/Mark-MDO47/ArduinoClass
 * 
 * https://github.com/Mark-MDO47/ArduinoClass/tree/master/02_PersistenceOfVision/Part_C
 * 
 * We are using an Arduino Nano with a USB mini-B connector
 *            V3.0 ATmega328P 5V 16M CH340 Compatible to Arduino Nano V3
 *            32Kbyte Flash (program storage), 2Kbyte SRAM, 1Kbyte EEPROM
 *            http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf
 *            http://www.pighixxx.com/test/pinouts/boards/nano.pdf
 *
 * SpinThePatterns.ino is code for https://github.com/Mark-MDO47/ArduinoClass/tree/master/02_PersistenceOfVision/Part_C
 *
 * Persistence of Vision SpinThePatterns
 */

 // connections:
// 
// Nano pin 5V      LEDstick VCC
// Nano pin GND     LEDstick GND
// Nano pin D-7     LEDstick DIN
//
// Nano pin D-5     Button Yellow - change delay time
// Nano pin D-4     Button Blue   - change pattern
// Nano pin D-3     Button White  - change Rainbow or Single Color
// Nano pin D-2     Button Green  - change the single color

#include <FastLED.h>
#include <EEPROM.h>          // to store configuration info

#define EEPROM_DEBUG_PRINT(a)   // Serial.print((a))   // set to blank to remove EEPROM debug print statements
#define EEPROM_DEBUG_PRINTLN(a) // Serial.println((a)) // set to blank to remove EEPROM debug print statements

#define EEPROM_OFFSET_gInterval         0x0
#define EEPROM_OFFSET_gOneOrRainbow     0x1
#define EEPROM_OFFSET_gTheOneColorIndex 0x2
#define EEPROM_OFFSET_gPatternToShow    0x3
#define EEPROM_LAST_NON_CHKSM           0xE // EEPROM address of last non-checksum data
#define EEPROM_INVERTED_CHKSM           0xF // EEPROM address of checksum data
#define EEPROM_BYTES_PER_CONFIG (EEPROM_INVERTED_CHKSM+1)

// How many leds in your strip?
#define NUM_LEDS 8 // Mark-MDO47 we have 8 LEDs

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 7 // Mark-MDO47 we use this pin for LEDs
// #define CLOCK_PIN 13 // Mark-MDO47 we don't use CLOCK_PIN with this LED Strip

// Buttons to experiment with conditions
#define BUTTON_PIN_YELLOW_DLY 5 // change delay time
#define BUTTON_PIN_BLUE_PTRN  4 // change pattern
#define BUTTON_PIN_WHITE_RNBW 3 // change Rainbow or Single Color
#define BUTTON_PIN_GREEN_SCLR 2 // change the single color

#define SAWTOOTH_CALLS_THEN_REPEAT 14 // the Sawtooth pattern does this many calls then repeats
static uint8_t sawtooth_pattern_bits[SAWTOOTH_CALLS_THEN_REPEAT] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40 };

#define OVAL_CALLS_THEN_REPEAT 52 // the Oval pattern does this many calls then repeats
static uint8_t oval_pattern_bits[OVAL_CALLS_THEN_REPEAT] = { 0x18, 0x24, 0x42, 0x81, 0x81, 0x81, 0x42, 0x24, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x50, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x24, 0x42, 0x81, 0x81, 0x99, 0x99, 0x81, 0x81, 0x42, 0x24, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00 };

#define HELLO_CALLS_THEN_REPEAT 70 // the HELLO WORLD! pattern does this many calls then repeats
static uint8_t hello_pattern_bits[HELLO_CALLS_THEN_REPEAT] = { 0xFF, 0x18, 0x18, 0x18, 0xFF, 0x00, 0xFF, 0x89, 0x89, 0x89, 0x00, 0xFF, 0x01, 0x01, 0x01, 0x00, 0xFF, 0x01, 0x01, 0x01, 0x00, 0x7E, 0x81, 0x81, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x01, 0x0E, 0x01, 0xFE, 0x00, 0x00, 0x7E, 0x81, 0x81, 0x7E, 0x00, 0xFF, 0x98, 0x94, 0x63, 0x00, 0xFF, 0x01, 0x01, 0x01, 0x00, 0xFF, 0x81, 0x42, 0x3C, 0x00, 0xF9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

#define PEAS_CALLS_THEN_REPEAT 72 // the Whirled Peas! pattern does this many calls then repeats
static uint8_t peas_pattern_bits[PEAS_CALLS_THEN_REPEAT] = { 0xFE, 0x01, 0x0E, 0x01, 0xFE, 0x00, 0xFF, 0x18, 0x18, 0x18, 0xFF, 0x00, 0x81, 0xFF, 0x81, 0x00, 0xFF, 0x98, 0x94, 0x63, 0x00, 0x01, 0x00, 0xFF, 0x01, 0x01, 0x01, 0x00, 0xFF, 0x89, 0x89, 0x89, 0x00, 0xFF, 0x81, 0x42, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x90, 0x90, 0x60, 0x00, 0xFF, 0x89, 0x89, 0x89, 0x00, 0x00, 0x1F, 0x68, 0x88, 0x68, 0x1F, 0x00, 0x00, 0x72, 0x89, 0x89, 0x46, 0x00, 0xF9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

#define FLAG_CALLS_THEN_REPEAT 22  // the Flag Red/White/Blue pattern does this many calls then repeats
static uint8_t flag_pattern_bits_red[FLAG_CALLS_THEN_REPEAT] = { 0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0x00,0x00,0x00,0x00,0x00,0x00 };
static uint8_t flag_pattern_bits_white[FLAG_CALLS_THEN_REPEAT] = { 0x54,0xA4,0x54,0xA4,0x54,0xA4,0x04,0x54,0x54,0x54,0x54,0x54,0x54,0x54,0x54,0x54,0x00,0x00,0x00,0x00,0x00,0x00 };
static uint8_t flag_pattern_bits_blue[FLAG_CALLS_THEN_REPEAT] = { 0xA0,0x50,0xA0,0x50,0xA0,0x50,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };

// Mark-MDO47 additions for rainbow colors
#define BRIGHTMAX 40 // set to 250 for MUCH brighter
#define FASTLED_RAINBOWPTRNLEN 64 // number of shades to cycle through
#define FASTLED_RAINBOWHUEROTATE 500 // rotate hues every 500th color pick

// Mark-MDO47 additions for rainbow colors
static CRGB rainbow_array[FASTLED_RAINBOWPTRNLEN]; // rainbow pattern colors
static uint8_t gHue = 0; // rotating "base color"
static uint16_t gHue_rotate_countdown = FASTLED_RAINBOWHUEROTATE;
static uint16_t next_rainbow = 0;

#define PATTERN_1BIT_MAX_NUM 4 // number of one-bit patterns (either one color or rainbow color)
#define PATTERN_3BIT_MAX_NUM 1 // number of three-bit patterns (Red/White/Blue Flag)

static uint8_t * gPatternsBits[PATTERN_1BIT_MAX_NUM]   = { sawtooth_pattern_bits, oval_pattern_bits, hello_pattern_bits, peas_pattern_bits };
static uint8_t * g_RWB_pattern_bits[3] = { flag_pattern_bits_red, flag_pattern_bits_white, flag_pattern_bits_blue };
static CRGB g_RWB_colors[3] = { CRGB::Red, CRGB::White/3, CRGB::Blue };
static const char * gPatternsNames[PATTERN_1BIT_MAX_NUM+PATTERN_3BIT_MAX_NUM]   = { "Sawtooth", "Oval", "HelloWorld!", "Whirled Peas!", "Flag" };
static int gPatternsRepeat[PATTERN_1BIT_MAX_NUM+PATTERN_3BIT_MAX_NUM] = { SAWTOOTH_CALLS_THEN_REPEAT, OVAL_CALLS_THEN_REPEAT, HELLO_CALLS_THEN_REPEAT, PEAS_CALLS_THEN_REPEAT, FLAG_CALLS_THEN_REPEAT };
int gPatternToShow = 0;
#define COLORS_ALL_ONE 0
#define COLORS_RAINBOW 1
static int gMenuMsecCounts[] = { 1, 3, 5, 10, 20, 40 };
int gOneOrRainbow = COLORS_ALL_ONE; // 0 = ALL_ONE, 1 = RAINBOW
CRGB gTheColorChoices[] = { CRGB::Red, CRGB::Green, CRGB::Blue };
static const char * gTheColorStrings[] = { "Red", "Green", "Blue" };
int gTheOneColorIndex = 0;

#define MENU_FIRST_MSEC           0
#define MENU_LAST_MSEC            5
#define MENU_FIRST_COLOR_PATTERN  6
#define MENU_LAST_COLOR_PATTERN   7
#define MENU_FIRST_COLOR_CHOICE   8
#define MENU_LAST_COLOR_CHOICE   10
#define MENU_FIRST_1BIT_PATTERN       11
#define MENU_LAST_1BIT_PATTERN (MENU_FIRST_1BIT_PATTERN+PATTERN_1BIT_MAX_NUM-1)
#define MENU_FIRST_3BIT_PATTERN (MENU_LAST_1BIT_PATTERN+1)
#define MENU_LAST_3BIT_PATTERN MENU_FIRST_3BIT_PATTERN

#define MENU_CHOICES_NUM (MENU_LAST_3BIT_PATTERN+1)
static const char * gMenuChoices[MENU_CHOICES_NUM] = {
  " 0 set interval 1 ms",
  " 1 set interval 3 ms",
  " 2 set interval 5 ms",
  " 3 set interval 10 ms",
  " 4 set interval 20 ms",
  " 5 set interval 40 ms",
  " 6 set colors ALL ONE",
  " 7 set colors RAINBOW",
  " 8 set the one color RED",
  " 9 set the one color GREEN",
  "10 set the one color BLUE",
  "11 set pattern Sawtooth",
  "12 set pattern Oval",
  "13 set pattern HelloWorld!",
  "14 set pattern WhirledPeas!",
  "15 set pattern R/W/B Flag",
}; // end gMenuChoices{}

#define SERIAL_MAX_INPUT_LEN 5 // maximum number of characters to accept in one command; otherwise flush to next newline and process what we have
#define SERIAL_INPUT_BUF_LEN (SERIAL_MAX_INPUT_LEN + 5) // size of our actual buffer; room for terminating '\0' and a little extra
static char serial_input_buf[SERIAL_INPUT_BUF_LEN]; // one character for terminating '\0'

// Variables will change:
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// Define the array of leds
CRGB fastled_array[NUM_LEDS];

long gInterval = 5;           // interval at which to blink (milliseconds)

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// show_menu_options() - print the menu options
//    returns: nothing
void show_menu_options() {
  Serial.println(F("")); Serial.println(F("Menu Choices:"));
  for (int i = 0; i < MENU_CHOICES_NUM; i++) {
     Serial.println(gMenuChoices[i]);
  }
  Serial.println(F(""));
  Serial.print(F("Interval: ")); Serial.print(gInterval); Serial.println(" millisec");
  Serial.print(F("Color Pattern: ")); Serial.println( COLORS_ALL_ONE == gOneOrRainbow ? "All One Color" : "Rainbow" );
  Serial.print(F("The One Color: "));  Serial.println(gTheColorStrings[gTheOneColorIndex]);
  Serial.print(F("POVPattern: ")); Serial.print( gPatternToShow ); Serial.print(" "); Serial.println(gPatternsNames[gPatternToShow]);
} // end show_menu_options()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// ptrn_phase() - determine the state of what the phase of pattern generation is
//    returns: long int with either value >= 0 phase to blink or value < 0 paused
//

long int ptrn_phase() {
  static long int current_phase = -1;

  current_phase += 1;
  current_phase %= gPatternsRepeat[gPatternToShow]; // loop through the number of calls before repeat
  
  return(current_phase);
} // end ptrn_phase()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// ptrn_pause(blink_phase, ptrn_leds) - 
//    fills ptrn_leds with all CRGB:Black
//    returns: none
//
// blink_phase - ignored
// ptrn_leds   - where to store the pattern

void ptrn_pause(long int blink_phase, CRGB * ptrn_leds) {

  // pause pattern - all CRGB::Black
  for (long int i = 0; i < NUM_LEDS; i++) {
    ptrn_leds[i] = CRGB::Black;
  }

} // end ptrn_pause()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// ptrn_3bit_blink(blink_phase, ptrn_leds) - 
//    fills ptrn_leds with next pattern based on blink_phase and FLAG Red/White/Blue pattern
//    returns: none
//
// blink_phase - long int, range 0-13
// ptrn_leds   - where to store the pattern
//
// GLOBALS
// gPatternToShow - either 1BIT_PATTERN or 3BIT_PATTERN

void ptrn_3bit_blink(long int blink_phase, CRGB * ptrn_leds) {
  for (long int i = 0; i < NUM_LEDS; i++) { ptrn_leds[i] = CRGB::Black; }
  for (int i_rwb = 0; i_rwb < 3; i_rwb++) {
    uint8_t bits = g_RWB_pattern_bits[i_rwb][blink_phase];
    for (long int i = 0; i < NUM_LEDS; i++) {
      if (0 != (0x01 & bits)) {
        ptrn_leds[i] = g_RWB_colors[i_rwb];
      } // end if this LED is not black
      bits >>= 1;
    } // end for all LEDs/bits
  } // end for (i_rwb)

} // end ptrn_3bit_blink()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// ptrn_1bit_blink(blink_phase, ptrn_leds) - 
//    fills ptrn_leds with next pattern based on blink_phase
//    returns: none
//
// blink_phase - long int, range 0-13
// ptrn_leds   - where to store the pattern
//
// GLOBALS
// gPatternToShow - either 1BIT_PATTERN or 3BIT_PATTERN

void ptrn_1bit_blink(long int blink_phase, CRGB * ptrn_leds) {
  // pattern_bits one bit per LED to be on. Most Significant bit is first LED, etc.
  uint8_t bits = gPatternsBits[gPatternToShow][blink_phase];
  for (long int i = 0; i < NUM_LEDS; i++) {
    if (0 == (0x01 & bits))
       ptrn_leds[i] = CRGB::Black;
    else {
      if (COLORS_ALL_ONE == gOneOrRainbow) {
         ptrn_leds[i] = gTheColorChoices[gTheOneColorIndex];
      } else if (COLORS_RAINBOW == gOneOrRainbow) {
        ptrn_leds[i] = rainbow_array[next_rainbow++];
        if (next_rainbow >= FASTLED_RAINBOWPTRNLEN) next_rainbow = 0;
        gHue_rotate_countdown -= 1;
        if ((0 == gHue_rotate_countdown) || (gHue_rotate_countdown >= FASTLED_RAINBOWHUEROTATE)) {
          gHue_rotate_countdown = FASTLED_RAINBOWHUEROTATE;
          gHue += 4; // rotating "base color"
          fill_rainbow(rainbow_array, FASTLED_RAINBOWPTRNLEN, gHue, 21); // this fills up the colors to send later
        }
      } // end if <color_scheme> == gOneOrRainbow
    } // end if this LED is not black
    bits >>= 1;
  } // end for all LEDs/bits
} // end ptrn_1bit_blink()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// ptrn_fill(ptrn_leds) - 
//    returns: int with either value HIGH==blinked the LEDs or LOW==did not blink
//
// ptrn_leds   - where to store the pattern

int ptrn_fill(CRGB * ptrn_leds) {
  int did_blink = LOW;
  long int blink_phase = ptrn_phase();

  if (gPatternToShow > (PATTERN_1BIT_MAX_NUM-1)) {
    ptrn_3bit_blink(blink_phase, ptrn_leds);
  } else {
    ptrn_1bit_blink(blink_phase, ptrn_leds);
  }
  did_blink = HIGH;

  return(did_blink);
} // end ptrn_fill()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// handle_leds(...) - get the pattern and then display on LEDs
//    returns: int with either value HIGH==blinked the LEDs or LOW==did not blink
//

int handle_leds() {
  int did_blink = ptrn_fill(fastled_array); // fill the pattern into RAM

  FastLED.show(); // show the pattern on LEDs

  return(did_blink); // HIGH if blink, LOW if pause
} // end handle_leds()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// handle_serial_input_command(inbuf) - process serial input command (decimal number).
//    returns: nothing
//
// inbuf - pointer to start of zero-terminated string, no linefeed ('\n')
//         expected to be a decimal number
//
// if input number is valid, store new configuration info and put it in EEPROM, then show menu

void handle_serial_input_command(char * inbuf) {
   long int tmp = atoi(inbuf);
   if ((MENU_FIRST_MSEC <= tmp) && (MENU_LAST_MSEC >= tmp)) {
     gInterval = gMenuMsecCounts[tmp-MENU_FIRST_MSEC];
   } else if ((MENU_FIRST_COLOR_PATTERN <= tmp) && (MENU_LAST_COLOR_PATTERN >= tmp)) {
     gOneOrRainbow = tmp-MENU_FIRST_COLOR_PATTERN;
   } else if ((MENU_FIRST_COLOR_CHOICE <= tmp) && (MENU_LAST_COLOR_CHOICE >= tmp)) {
     gTheOneColorIndex = tmp-MENU_FIRST_COLOR_CHOICE;
   } else if ((MENU_FIRST_1BIT_PATTERN <= tmp) && (MENU_LAST_3BIT_PATTERN >= tmp)) {
     gPatternToShow = tmp-MENU_FIRST_1BIT_PATTERN;
   } else {
     Serial.print(F("Error: number ")); Serial.print(tmp); Serial.println(F(" is not valid"));
   }
   eeprom_init_from_ram(); // store any new config in EEPROM
   show_menu_options();
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// step_delay_value() - button press to step through delay values
//    returns: nothing

void step_delay_value() {
  for (int idx = 0; idx < (1+MENU_LAST_MSEC-MENU_FIRST_MSEC); idx += 1) {
    if (gInterval == gMenuMsecCounts[idx]) {
      // Serial.print(F("step idx ")); Serial.print(idx); Serial.print(F(" add-one "));
      idx += 1;
      // Serial.print(idx); Serial.print(F(" range-check "));
      if (idx >= (1+MENU_LAST_MSEC-MENU_FIRST_MSEC)) idx = 0;
      // Serial.println(idx);
      gInterval = gMenuMsecCounts[idx];
      break;
    } // end if found current entry so set next entry
  } // end for loop
  eeprom_init_from_ram(); // store any new config in EEPROM
  // show_menu_options(); // DEBUG
} // end step_delay_value()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// step_pattern_value() - button press to step through pattern values
//    returns: nothing

void step_pattern_value() {
  int idx = gPatternToShow + 1;
  if (idx >= (1+MENU_LAST_3BIT_PATTERN-MENU_FIRST_1BIT_PATTERN)) idx = 0;
  gPatternToShow = idx;
  eeprom_init_from_ram(); // store any new config in EEPROM
} // end step_pattern_value()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// step_rainbow_single_value() - button press to step through Rainbow or Single Color
//    returns: nothing

void step_rainbow_single_value() {
  int idx = gOneOrRainbow + 1;
  if (idx >= (1+MENU_LAST_COLOR_PATTERN-MENU_FIRST_COLOR_PATTERN)) idx = 0;
  gOneOrRainbow = idx;
  eeprom_init_from_ram(); // store any new config in EEPROM
} // end step_rainbow_single_value()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// step_single_color_value() - button press to step through single color values
//    returns: nothing

void step_single_color_value() {
  int idx = gTheOneColorIndex + 1;
  if (idx >= (1+MENU_LAST_COLOR_CHOICE-MENU_FIRST_COLOR_CHOICE)) idx = 0;
  gTheOneColorIndex = idx;
  eeprom_init_from_ram(); // store any new config in EEPROM
} // end step_single_color_value()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// handle_buttons() - Handle the four buttons to change parameters
//    returns: int with either value HIGH or LOW
//
// BUTTON_PIN_YELLOW_DLY 2 // change delay time
// BUTTON_PIN_BLUE_PTRN  3 // change pattern
// BUTTON_PIN_WHITE_RNBW 4 // change Rainbow or Single Color
// BUTTON_PIN_GREEN_SCLR 5 // change the single color
//
// NOTE: we can use either USB Serial keyboard entry to change parameters or the buttons
// ALSO NOTE: we don't do a complete job of debounce, but if you press and hold the button before release then it almost always works.

void handle_buttons() {
  static int last_yellow = HIGH;
  static int last_blue = HIGH;
  static int last_white = HIGH;
  static int last_green = HIGH;

  if (LOW == digitalRead(BUTTON_PIN_YELLOW_DLY)) {
    if (HIGH == last_yellow) {
      step_delay_value();
    }
    last_yellow = LOW;
  } else {
    last_yellow = HIGH;
  }

  if (LOW == digitalRead(BUTTON_PIN_BLUE_PTRN)) {
    if (HIGH == last_blue) {
      step_pattern_value();
    }
    last_blue = LOW;
  } else {
    last_blue = HIGH;
  }


  if (LOW == digitalRead(BUTTON_PIN_WHITE_RNBW)) {
    if (HIGH == last_white) {
      step_rainbow_single_value();
    }
    last_white = LOW;
  } else {
    last_white = HIGH;
  }


  if (LOW == digitalRead(BUTTON_PIN_GREEN_SCLR)) {
    if (HIGH == last_green) {
      step_single_color_value();
    }
    last_green = LOW;
  } else {
    last_green = HIGH;
  }

} // end handle_buttons()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// eeprom_store_if_change(offset, byteValue) - write byte to EEPROM if it is different than current EEPROM
//    we don't want to write EEPROM unless needed
//    this routine is just for debugging; use EEPROM.update() unless debugging
// offset - where to store the byte in EEPROM, offset from gEepromConfigStart
// byteValue - byte value to store at that offset in EEPROM configuration
//
void eeprom_store_if_change(int offset, uint8_t byteValue) {
  uint8_t nowValue;

  nowValue = EEPROM.read(offset);
  EEPROM_DEBUG_PRINT(F("DEBUG eeprom_store_if_change BEFORE: want ")); EEPROM_DEBUG_PRINT(byteValue); EEPROM_DEBUG_PRINT(F(" have ")); EEPROM_DEBUG_PRINT(nowValue); EEPROM_DEBUG_PRINT(F(" offset ")); EEPROM_DEBUG_PRINTLN(offset);

  if (nowValue != byteValue) {
    EEPROM.write(offset, byteValue);
  } // if we needed to write to EEPROM

  EEPROM_DEBUG_PRINT(F("DEBUG eeprom_store_if_change AFTER: want ")); EEPROM_DEBUG_PRINT(byteValue); EEPROM_DEBUG_PRINT(F(" have ")); EEPROM_DEBUG_PRINT(EEPROM.read(offset)); EEPROM_DEBUG_PRINT(F(" offset ")); EEPROM_DEBUG_PRINTLN(offset); EEPROM_DEBUG_PRINTLN(F(" "));
} // end eeprom_store_if_change()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// eeprom_check_init - check if EEPROM has valid values; if not, copy current RAM values to it
//    we use a very crude checksum approach
//
void eeprom_check_init() {
  uint8_t invChksumValue;
  uint8_t nowValue;

  // read RBG non-checksum bytes from EEPROM and calculate checksum; compare with stored checksum
  invChksumValue = eeprom_calc_inverted_checksum();
  nowValue = EEPROM.read(EEPROM_INVERTED_CHKSM);
  EEPROM_DEBUG_PRINT(F("eeprom_check_init: exp: ")); EEPROM_DEBUG_PRINT(invChksumValue); EEPROM_DEBUG_PRINT(F(" act: ")); EEPROM_DEBUG_PRINTLN(nowValue);
  if (nowValue != invChksumValue) {
    // checksum does not match; factory reset our EEPROM configuration area
    Serial.println(F("eeprom_check_init: checksum bad; re-initialize"));
    eeprom_init_from_ram();
  } // end if checksum does not match
} // end eeprom_check_init()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// eeprom_calc_inverted_checksum() - calculate the inverted checksum of EEPROM
//    we use a very crude checksum approach
//
uint8_t eeprom_calc_inverted_checksum() {
  int offset;
  uint8_t chksumValue; // non-inverted checksum
  uint8_t byteValue;

  // read config non-checksum bytes from EEPROM and calculate checksum
  for (offset = chksumValue = 0; offset <= EEPROM_LAST_NON_CHKSM; offset++) {
    byteValue = EEPROM.read(offset);
    chksumValue += byteValue;
  } // end caclulate checksum
  return((uint8_t) (~(chksumValue)));
} // end eeprom_calc_inverted_checksum()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// eeprom_store_with_chksum(offset, byteValue) - store byteValue at EEPROM address and update checksum
//    we use a very crude checksum approach
// offset - where to store the byte in EEPROM, offset from gEepromConfigStart
// byteValue - byte value to store at that offset in EEPROM configuration
//
void eeprom_store_with_chksum(int offset, uint8_t byteValue) {
  uint8_t nowValue;
  uint8_t invChksumValue;

  EEPROM.update(offset, byteValue);
  invChksumValue = eeprom_calc_inverted_checksum();
  EEPROM.update(EEPROM_INVERTED_CHKSM, invChksumValue);
} // end eeprom_store_with_chksum()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// eeprom_init_from_ram()
//   set EEPROM configuration to current state
//
void eeprom_init_from_ram() {

  EEPROM_DEBUG_PRINTLN(F("DEBUG eeprom_init_from_ram BEFORE:"));
  EEPROM_DEBUG_PRINT(F("   gInterval         RAM: "));EEPROM_DEBUG_PRINT(gInterval); EEPROM_DEBUG_PRINT(F(" EEPROM: ")); EEPROM_DEBUG_PRINTLN( EEPROM.read(EEPROM_OFFSET_gInterval));
  EEPROM_DEBUG_PRINT(F("   gOneOrRainbow     RAM: "));EEPROM_DEBUG_PRINT(gOneOrRainbow); EEPROM_DEBUG_PRINT(F(" EEPROM: ")); EEPROM_DEBUG_PRINTLN( EEPROM.read(EEPROM_OFFSET_gOneOrRainbow));
  EEPROM_DEBUG_PRINT(F("   gTheOneColorIndex RAM: "));EEPROM_DEBUG_PRINT(gTheOneColorIndex); EEPROM_DEBUG_PRINT(F(" EEPROM: ")); EEPROM_DEBUG_PRINTLN( EEPROM.read(EEPROM_OFFSET_gTheOneColorIndex));
  EEPROM_DEBUG_PRINT(F("   gPatternToShow    RAM: "));EEPROM_DEBUG_PRINT(gPatternToShow); EEPROM_DEBUG_PRINT(F(" EEPROM: ")); EEPROM_DEBUG_PRINTLN( EEPROM.read(EEPROM_OFFSET_gPatternToShow)); EEPROM_DEBUG_PRINTLN(F(" "));

  EEPROM.update(EEPROM_OFFSET_gInterval,         gInterval);
  EEPROM.update(EEPROM_OFFSET_gOneOrRainbow,     gOneOrRainbow);
  EEPROM.update(EEPROM_OFFSET_gTheOneColorIndex, gTheOneColorIndex);
  if (EEPROM_OFFSET_gPatternToShow < EEPROM_LAST_NON_CHKSM) {
    EEPROM.update(EEPROM_OFFSET_gPatternToShow,  gPatternToShow);
    for (uint8_t offset = EEPROM_OFFSET_gPatternToShow+1; offset < EEPROM_LAST_NON_CHKSM; offset++) {
      EEPROM.update(offset, 0); // zero fill the rest
    } // end fill with zero to one less than LAST_NON_CHKSM
    eeprom_store_with_chksum(EEPROM_LAST_NON_CHKSM, 0); // last non-checksum
  } else { // this was the last byte before checksum
    eeprom_store_with_chksum(EEPROM_OFFSET_gPatternToShow, gPatternToShow);
  } // end if this was the last byte before checksum

  EEPROM_DEBUG_PRINTLN(F("DEBUG eeprom_init_from_ram AFTER:"));
  EEPROM_DEBUG_PRINT(F("   gInterval         RAM: "));EEPROM_DEBUG_PRINT(gInterval); EEPROM_DEBUG_PRINT(F(" EEPROM: ")); EEPROM_DEBUG_PRINTLN( EEPROM.read(EEPROM_OFFSET_gInterval));
  EEPROM_DEBUG_PRINT(F("   gOneOrRainbow     RAM: "));EEPROM_DEBUG_PRINT(gOneOrRainbow); EEPROM_DEBUG_PRINT(F(" EEPROM: ")); EEPROM_DEBUG_PRINTLN( EEPROM.read(EEPROM_OFFSET_gOneOrRainbow));
  EEPROM_DEBUG_PRINT(F("   gTheOneColorIndex RAM: "));EEPROM_DEBUG_PRINT(gTheOneColorIndex); EEPROM_DEBUG_PRINT(F(" EEPROM: ")); EEPROM_DEBUG_PRINTLN( EEPROM.read(EEPROM_OFFSET_gTheOneColorIndex));
  EEPROM_DEBUG_PRINT(F("   gPatternToShow    RAM: "));EEPROM_DEBUG_PRINT(gPatternToShow); EEPROM_DEBUG_PRINT(F(" EEPROM: ")); EEPROM_DEBUG_PRINTLN( EEPROM.read(EEPROM_OFFSET_gPatternToShow));
  EEPROM_DEBUG_PRINTLN(F(" "));
} // end eeprom_factory_init(configToProc)

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// ram_init_from_eeprom()
//   set EEPROM configuration to current state
//
void ram_init_from_eeprom() {
  gInterval         = EEPROM.read(EEPROM_OFFSET_gInterval);
  gOneOrRainbow     = EEPROM.read(EEPROM_OFFSET_gOneOrRainbow);
  gTheOneColorIndex = EEPROM.read(EEPROM_OFFSET_gTheOneColorIndex);
  gPatternToShow    = EEPROM.read(EEPROM_OFFSET_gPatternToShow);
} // end ram_init_from_eeprom()

void setup() {
  Serial.begin(115200);         // this serial communication is for general debug; set the USB serial port to 115,200 baud
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  while (Serial.available()) Serial.read(); // clear any startup junk from the serial queue
  memset((void *)serial_input_buf, 0, SERIAL_INPUT_BUF_LEN); // clear buffer; good idea for zero-terminated strings

  // either initialize EEPROM configuration info or initialize RAM from EEPROM configuration info
  eeprom_check_init(); // see if EEPROM checksum is good; if not update EEPROM from RAM
  ram_init_from_eeprom(); // update RAM from EEPROM

  pinMode(BUTTON_PIN_YELLOW_DLY, INPUT_PULLUP); // digital INPUT_PULLUP means voltage HIGH unless grounded
  pinMode(BUTTON_PIN_BLUE_PTRN, INPUT_PULLUP); // digital INPUT_PULLUP means voltage HIGH unless grounded
  pinMode(BUTTON_PIN_WHITE_RNBW, INPUT_PULLUP); // digital INPUT_PULLUP means voltage HIGH unless grounded
  pinMode(BUTTON_PIN_GREEN_SCLR, INPUT_PULLUP); // digital INPUT_PULLUP means voltage HIGH unless grounded

  // ## Clockless types ##
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(fastled_array, NUM_LEDS);  // GRB ordering is assumed
  FastLED.setBrightness(BRIGHTMAX); // help keep our power draw through Arduino Nano down
  fill_rainbow(rainbow_array, FASTLED_RAINBOWPTRNLEN, gHue, 21); // this fills up the colors to send later

  Serial.println(F("")); // print a blank line in case there is some junk from power-on
  Serial.println(F("ArduinoClass init..."));
  show_menu_options();
} // end setup()

void loop() { 
  // check to see if it's time to "blink" the LED strip; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();

  // buttons will step through parameter options
  handle_buttons();

  // Mark-MDO47 handle serial input if any
  handle_serial_input();

  if (currentMillis - previousMillis >= gInterval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    handle_leds(); // Mark-MDO47 generate pattern to display and display it
  }
} // end loop()
