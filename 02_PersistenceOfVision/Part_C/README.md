# NOTES

**Table of Contents**
* [Top](#notes "Top")
* [Oval](#oval "Oval")
* [Rainbow](#rainbow "Rainbow")
* [Hello World](#hello-world "Hello World")
* [Sawtooth Revisited](#sawtooth-revisited "Sawtooth Revisited")
* [All the Patterns - Extra Credit](#all-the-patterns-\--extra-credit "All the Patterns - Extra Credit")
  * [Pattern Code](#pattern-code "Pattern Code")
  * [EEPROM Introduction](#eeprom-introduction "EEPROM Introduction")
  * [EEPROM Code](#eeprom-code "EEPROM Code")
* [Reminder](#reminder "Reminder")

We will continue with our modified FastLED example program from **Part_B**. We will do the following quick projects:
- **Oval** - new Oval pattern - still all red
- **Rainbow** - use Rainbow color scheme for Oval instead of all red
- **Hello World!** - new Hello World! pattern
- **Sawtooth Revisited** - rework the Sawtooth pattern using this new code
- **All the Patterns - Extra Credit** - put it all together, add in EEPROM usage

## Oval
[Top](#notes "Top")<br>
The idea is to draw ovals, circles, and maybe eyes with our LED Stick.<br>
Each step left-to-right is a "blink" in the following diagram.

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/OvalPattern.png "Image of Oval pattern; each step left-to-right is a blink")

Note: this spreadsheet helps with calculations for the patterns (does the so-called bit-busting).
- https://github.com/Mark-MDO47/ArduinoClass/blob/master/02_PersistenceOfVision/Pattern_Calcs.xlsx

Copy the Sawtooth.ino file into a directory named Oval with filename Oval.ino, then open it in the Arduino IDE.

Here is where all our work organizing the code for Part B Sawtooth pays off. Except for changing Sawtooth to Oval, there are very few changes to make.

Now do global replaces with case sensitivity on as shown below:
| Replace this | With this |
| --- | --- |
| sawtooth_ | oval_ |
| Sawtooth | Oval |
| SAWTOOTH | OVAL |

That wasn't too bad. Maybe we should have used "pattern_" instead if oval_ and sawtooth_ so there wouldn't be so much of this.

Now for the actual changes. First change the count to 34 
- **#define OVAL_CALLS_THEN_REPEAT 34 // the Oval pattern does 34 calls then repeats**

The oval_blink_pattern() routine now looks like this
```C
void oval_blink_pattern(long int blink_phase, CRGB * ptrn_leds) {
  // oval_pattern_bits one bit per LED to be on. Most Significant bit is first LED, etc.
  static unsigned int oval_pattern_bits[OVAL_CALLS_THEN_REPEAT] = { 0x18, 0x24, 0x42, 0x81, 0x81, 0x81, 0x42, 0x24, 0x18, 0x00, 0x40, 0xA0, 0x48, 0x14, 0x08, 0x20, 0x53, 0x23, 0x00, 0x18, 0x24, 0x42, 0x81, 0x81, 0x99, 0xA5, 0xA5, 0x99, 0x81, 0x81, 0x42, 0x24, 0x18, 0x00 };
  unsigned int bits = oval_pattern_bits[blink_phase];

  for (long int i = 0; i < NUM_LEDS; i++) {
    if (0 == (0x01 & bits))
       ptrn_leds[i] = CRGB::Black;
    else
       ptrn_leds[i] = CRGB::Red;
    bits >>= 1;
  }

} // end oval_blink_pattern()
```

## Rainbow
[Top](#notes "Top")<br>
Why should we always use Black and Red? Does FastLED have an excellent method to vary colors in an interesting way?

The answer is YES! They have two routines I know of that would work for this purpose:
- fill_rainbow
- fill_gradient
- see https://fastled.io/docs/3.1/group___colorutils.html

Up until now we have limited the current draw by having only at most one of the three colors in each LED active.  Now we are going to use colors that have all three colors active. We use BRIGHTMAX and FastLED.setBrightness() to limit the current draw.

Put this up with the other #define statements
```C
#define BRIGHTMAX 40 // set to 250 for MUCH brighter
#define FASTLED_RAINBOWPTRNLEN 64 // number of shades to cycle through
#define FASTLED_RAINBOWHUEROTATE 500 // rotate hues every 500th color pick
```

Put this immediately after the last #define statement
```C
static CRGB rainbow_array[FASTLED_RAINBOWPTRNLEN]; // rainbow pattern colors
static uint8_t gHue = 0; // rotating "base color"
static uint16_t gHue_rotate_countdown = FASTLED_RAINBOWHUEROTATE;
static uint16_t next_rainbow = 0;
```

And put this into **setup()** after **FastLED.addLeds**
```C
  FastLED.setBrightness(BRIGHTMAX); // help keep our power draw through Arduino Nano down
  fill_rainbow(rainbow_array, FASTLED_RAINBOWPTRNLEN, gHue, 21); // this fills up the colors to send later
```
Now we can make the changes in **oval_blink_pattern()**. Simply replace **ptrn_leds[i] = CRGB::Red;** with the following
```C
    if (0 == (0x80 & bits))
       ptrn_leds[i] = CRGB::Black;
    else {
      ptrn_leds[i] = rainbow_array[next_rainbow++];
      if (next_rainbow >= FASTLED_RAINBOWPTRNLEN) next_rainbow = 0;
      gHue_rotate_countdown -= 1;
      if ((0 == gHue_rotate_countdown) || (gHue_rotate_countdown >= FASTLED_RAINBOWHUEROTATE)) {
        gHue_rotate_countdown = FASTLED_RAINBOWHUEROTATE;
        gHue += 4; // rotating "base color"
        fill_rainbow(rainbow_array, FASTLED_RAINBOWPTRNLEN, gHue, 21); // this fills up the colors to send later
      }
    }
```

My version of this can be found here
- https://github.com/Mark-MDO47/ArduinoClass/blob/master/ArduinoCode/Oval/Oval.ino

## Hello World
[Top](#notes "Top")<br>
I wasn't really planning on this but I suddenly realized I could turn this into a "Hello World!" program.

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/HelloWorldPattern.png "Image of Oval Hello World pattern; each step left-to-right is a blink")

Copy the Oval.ino file into a directory named HelloWorld with filename HelloWorld.ino, then open it in the Arduino IDE.

Change
```C
// Mark-MDO47 Oval pattern
#define OVAL_CALLS_THEN_REPEAT 34 // the Oval pattern does 34 calls then repeats
```

... to
```C
// Mark-MDO47 Oval pattern or Hello pattern
// #define PATTERN_OVAL 1
#define PATTERN_HELLO 1

#ifdef PATTERN_HELLO
#define PTRN_CALLS_THEN_REPEAT 58 // the HELLO WORLD! pattern does 58 calls then repeats
static unsigned int  pattern_bits[PTRN_CALLS_THEN_REPEAT] = { 0xFF, 0x18, 0x18, 0x18, 0xFF, 0x00, 0xFF, 0x89, 0x89, 0x89, 0x00, 0xFF, 0x01, 0x01, 0x01, 0x00, 0xFF, 0x01, 0x01, 0x01, 0x00, 0x7E, 0x81, 0x81, 0x7E, 0x00, 0xE0, 0x1E, 0x01, 0x1E, 0xE0, 0x1E, 0x01, 0x1E, 0xE0, 0x00, 0x7E, 0x81, 0x81, 0x7E, 0x00, 0xFF, 0x98, 0x94, 0x63, 0x00, 0xFF, 0x01, 0x01, 0x01, 0x00, 0xFF, 0x81, 0x42, 0x3C, 0x00, 0xF9, 0x00 };
#else // PATTERN_OVAL
#define PTRN_CALLS_THEN_REPEAT 34 // the Oval pattern does 34 calls then repeats
static unsigned int pattern_bits[PTRN_CALLS_THEN_REPEAT] = { 0x18, 0x24, 0x42, 0x81, 0x81, 0x81, 0x42, 0x24, 0x18, 0x00, 0x40, 0xA0, 0x48, 0x14, 0x08, 0x20, 0x53, 0x23, 0x00, 0x18, 0x24, 0x42, 0x81, 0x81, 0x99, 0xA5, 0xA5, 0x99, 0x81, 0x81, 0x42, 0x24, 0x18, 0x00 };
#endif // PATTERN_HELLO
```

Change
```C
    current_phase %= OVAL_CALLS_THEN_REPEAT; // loop through the number of calls before repeat
```

... to
```C
    current_phase %= PTRN_CALLS_THEN_REPEAT; // loop through the number of calls before repeat
```

Change
```C
  // oval_pattern_bits one bit per LED to be on. Most Significant bit is first LED, etc.
  static unsigned int oval_pattern_bits[OVAL_CALLS_THEN_REPEAT] = { 0x18, 0x24, 0x42, 0x81, 0x81, 0x81, 0x42, 0x24, 0x18, 0x00, 0x40, 0xA0, 0x48, 0x14, 0x08, 0x20, 0x53, 0x23, 0x00, 0x18, 0x24, 0x42, 0x81, 0x81, 0x99, 0xA5, 0xA5, 0x99, 0x81, 0x81, 0x42, 0x24, 0x18, 0x00 };
  unsigned int bits = oval_pattern_bits[blink_phase];
```

... to
```C
  // pattern_bits one bit per LED to be on. Most Significant bit is first LED, etc.
  unsigned int bits = pattern_bits[blink_phase];
```

My version of this can be found here
- https://github.com/Mark-MDO47/ArduinoClass/blob/master/ArduinoCode/HelloWorld/HelloWorld.ino

A YouTube of this code in operation demonstrating use of the button to stop and start can be found here
- https://youtu.be/I-3vgafNRE8

## Sawtooth Revisited
[Top](#notes "Top")<br>
As an exercise to the reader, see if you can add a third pattern that is the Sawtooth pattern from before. It should only take a few lines of code, maybe 5 or 6. It will be good practice with hexadecimal and binary arithmetic.

When you have done this, compare it with my implementation
- https://github.com/Mark-MDO47/ArduinoClass/blob/master/ArduinoCode/SawtoothRevisited/SawtoothRevisited.ino

## All the Patterns - Extra Credit
[Top](#notes "Top")<br>
We have made a program that can be edited and compiled to do any of the three patterns. Now I want to expand it to allow selecting options from the USB serial port while the code is running:
- select the pattern to display
- select whether to use the Rainbow colors or a single-color
  - select which color (Red, Green, or Blue) to use if using single-color
- select how long to wait between blinks

In addition, I want to save the current state of my selections in EEPROM (Electrically Erasable Programmable Read-only Memory) in the Arduino, so that the next time the Arduino is powered up it will start with those same selections. As the chicken said while crossing the road, "I have my reasons".

### Pattern Code
[Top](#notes "Top")<br>
I am just going to show the highlights of converting to use any of the patterns and the other menu options, not a line-by-line edit.<br>
The basic idea is:
- show_menu_options() will show what the possible commands are
- handle_serial_input_command() will accept a command and set the appropriate configuration
- ptrn_blink() will look at the configuration and do what it says

First we convert the patterns to use separate mnemonics and remove the #ifdef statements that compile only one of them:
```C
#define SAWTOOTH_CALLS_THEN_REPEAT 14 // the Sawtooth pattern does this many calls then repeats
static unsigned int sawtooth_pattern_bits[SAWTOOTH_CALLS_THEN_REPEAT] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40 };

#define OVAL_CALLS_THEN_REPEAT 34 // the Oval pattern does this many calls then repeats
static unsigned int oval_pattern_bits[OVAL_CALLS_THEN_REPEAT] = { 0x18, 0x24, 0x42, 0x81, 0x81, 0x81, 0x42, 0x24, 0x18, 0x00, 0x40, 0xA0, 0x48, 0x14, 0x08, 0x20, 0x53, 0x23, 0x00, 0x18, 0x24, 0x42, 0x81, 0x81, 0x99, 0xA5, 0xA5, 0x99, 0x81, 0x81, 0x42, 0x24, 0x18, 0x00 };

#define HELLO_CALLS_THEN_REPEAT 55 // the HELLO WORLD! pattern does this many calls then repeats
static unsigned int hello_pattern_bits[HELLO_CALLS_THEN_REPEAT] = { 0xFF, 0x18, 0x18, 0x18, 0xFF, 0x00, 0xFF, 0x89, 0x89, 0x89, 0x00, 0xFF, 0x01, 0x01, 0x01, 0x00, 0xFF, 0x01, 0x01, 0x01, 0x00, 0x7E, 0x81, 0x81, 0x7E, 0x00, 0xFE, 0x01, 0x0E, 0x01, 0xFE, 0x00, 0x00, 0x7E, 0x81, 0x81, 0x7E, 0x00, 0xFF, 0x98, 0x94, 0x63, 0x00, 0xFF, 0x01, 0x01, 0x01, 0x00, 0xFF, 0x81, 0x42, 0x3C, 0x00, 0xF9, 0x00 };
```

Then we do some replaces:
| Replace this | With this |
| --- | --- |
| oval_phase | ptrn_phase |
| oval_pause_pattern | ptrn_pause |
| oval_blink_pattern | ptrn_blink |
| oval_fill_pattern | ptrn_fill |
| PTRN_CALLS_THEN_REPEAT | gPatternsRepeat[gPatternToShow] |

Next we add definitions to allow the controlling configuration variables and USB serial port menus
```C
#define PATTERN_MAX_NUM 3 // 0-2 are patterns
static unsigned int * gPatternsBits[PATTERN_MAX_NUM]   = { sawtooth_pattern_bits, oval_pattern_bits, hello_pattern_bits };
static char * gPatternsNames[PATTERN_MAX_NUM]   = { "Sawtooth", "Oval", "HelloWorld!" };
static int gPatternsRepeat[PATTERN_MAX_NUM] = { SAWTOOTH_CALLS_THEN_REPEAT, OVAL_CALLS_THEN_REPEAT, HELLO_CALLS_THEN_REPEAT };
int gPatternToShow = 0;
#define COLORS_ALL_ONE 0
#define COLORS_RAINBOW 1
static int gMenuMsecCounts[] = { 1, 3, 5, 10, 20, 40 };
int gOneOrRainbow = COLORS_ALL_ONE; // 0 = ALL_ONE, 1 = RAINBOW
CRGB gTheColorChoices[] = { CRGB::Red, CRGB::Green, CRGB::Blue };
static char * gTheColorStrings[] = { "Red", "Green", "Blue" };
int gTheOneColorIndex = 0;

#define MENU_CHOICES_NUM 14
static char * gMenuChoices[MENU_CHOICES_NUM] = {
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
};
#define MENU_FIRST_MSEC           0
#define MENU_LAST_MSEC            5
#define MENU_FIRST_COLOR_PATTERN  6
#define MENU_LAST_COLOR_PATTERN   7
#define MENU_FIRST_COLOR_CHOICE   8
#define MENU_LAST_COLOR_CHOICE   10
#define MENU_FIRST_PATTERN       11
#define MENU_LAST_PATTERN (MENU_FIRST_PATTERN+PATTERN_MAX_NUM-1)

#define SERIAL_MAX_INPUT_LEN 5 // maximum number of characters to accept in one command; otherwise flush to next newline and process what we have
#define SERIAL_INPUT_BUF_LEN (SERIAL_MAX_INPUT_LEN + 5) // size of our actual buffer; room for terminating '\0' and a little extra
static char serial_input_buf[SERIAL_INPUT_BUF_LEN]; // one character for terminating '\0'
```

We add code to show the menus and currently selected options, and also to accept new options
```C
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// show_menu_options() - print the menu options
//    returns: nothing
void show_menu_options() {
  Serial.println(""); Serial.println("Menu Choices:");
  for (int i = 0; i < MENU_CHOICES_NUM; i++) {
     Serial.println(gMenuChoices[i]);
  }
  Serial.println("");
  Serial.print("Interval: "); Serial.print(gInterval); Serial.println(" millisec");
  Serial.print("Color Pattern: "); Serial.println( COLORS_ALL_ONE == gOneOrRainbow ? "All One Color" : "Rainbow" );
  Serial.print("The One Color: ");  Serial.println(gTheColorStrings[gTheOneColorIndex]);
  Serial.print("POVPattern: "); Serial.print( gPatternToShow ); Serial.print(" "); Serial.println(gPatternsNames[gPatternToShow]);
} // end show_menu_options()

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
   } else if ((MENU_FIRST_PATTERN <= tmp) && (MENU_LAST_PATTERN >= tmp)) {
     gPatternToShow = tmp-MENU_FIRST_PATTERN;
   } else {
     Serial.print("Error: number "); Serial.print(tmp); Serial.println(" is not valid");
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
```

At the end of **setup()**
```C
  Serial.begin(115200);         // this serial communication is for general debug; set the USB serial port to 115,200 baud
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  while (Serial.available()) Serial.read(); // clear any startup junk from the serial queue
  memset((void *)serial_input_buf, 0, SERIAL_INPUT_BUF_LEN); // clear buffer; good idea for zero-terminated strings

  Serial.println(""); // print a blank line in case there is some junk from power-on
  Serial.println("ArduinoClass init...");
  show_menu_options();
```

Replace the code in **ptrn_blink()** with this:
```C
void ptrn_blink(long int blink_phase, CRGB * ptrn_leds) {
  // pattern_bits one bit per LED to be on. Most Significant bit is first LED, etc.
  unsigned int bits = gPatternsBits[gPatternToShow][blink_phase];
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
} // end ptrn_blink()
```


### EEPROM Introduction
[Top](#notes "Top")<br>
These Arduino Nanos have 32Kbyte of FLASH memory (program storage), 2Kbyte of SRAM, and 1Kbyte of EEPROM.
- FLASH memory (no acronym) was an offshoot of EEPROM. For the Arduino Nano it is erasable and writeable in blocks of many bytes.
- EEPROM (Electrically Eraseable Programmable Read-Only Memory) is, for the Arduino Nano, erasable and writeable in blocks of one byte.
- SRAM (Static Random Access Memory) is, for the Arduino Nano, readable and writeable in blocks of one byte. There is typically no published limit on the number of times it can be read or written.

Note: 1Kbyte (capital K) typically means 1,024 bytes; 1,024 is considered to be the "binary thousand) since it is 2 to the power 10 and 1,000 is 10 to the power 3.

In Arduino practice:
- FLASH memory is used to store the program code. It can also be used to store constant strings and other data (see section on PROGMEM and F macro in https://github.com/Mark-MDO47/ArduinoClass/tree/master/99_Resources).
- SRAM is used for variables that change often. If you write **static int xxx;** or **int func(int a) { int xxx; xxx = a+1; return(xxx); };**, then **xxx** will be in SRAM.
- EEPROM is used to save things that are
  - changed during program execution
  - need to be remembered the next time the program runs

The Arduino EEPROM interface is simplicity itself:
- early in the *.ino (maybe after #include <FastLED.h>) file put the line **#include <EEPROM.h>**
- when you want to write a byte to EEPROM, call **EEPROM.write(address, byteValue);**
- when you want to read a byte from EEPROM, call **readValue = EEPROM.read(address);**

Given that FLASH is written only when we change the program and EEPROM would be written while the program is running, it is likely that EEPROM will use up all its erase/write cycles before FLASH will. In Arduino, the EEPROM is specified to handle 100,000 erase/write cycles for each position (byte). EEPROM reads are unlimited. However, the Arduino Nanos I use are cheap $2 clones instead of the official Arduino Nano at close to $25; therfore I don't want to push it. As you will see, I use a simple routine I wrote called **eeprom_store_if_change** that first reads the EEPROM byte and if it is the same value we were about to write it skips the write. This is a very simple routine and I am sure you could easily write your own version of it. Otherwise you can use my version in https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/AllThePatterns

When the Arduino powers up, how will it know if the parameters stored in EEPROM are valid or if it is a new Arduino out of the bag and the values are random? To handle this I store a simple checksum along with the parameters in EEPROM. If the EEPROM checksum doesn't match the EEPROM configuration data then I store a fresh set of configuration data in EEPROM.
Because I use a one-byte checksum (you could use a more elaborate checksum if you want) there is a one in 256 chance that random data will have a checksum that matches it. Because I am lazy, I accept that chance: if the first time I program an Arduino it behaves crazy then I can either write something to the configuration value or I can one-time change the expected value of the checksum to be different (for example; 1 + the normal checksum) and then it will put good configuration data in EEPROM. Later I can either leave the expectation at this new value or change it back.

### EEPROM CODE
[Top](#notes "Top")<br>
We add the following after **#include <FastLED.h>**
```C
#include <EEPROM.h>          // to store configuration info

#define EEPROM_OFFSET_gInterval         0x0
#define EEPROM_OFFSET_gOneOrRainbow     0x1
#define EEPROM_OFFSET_gTheOneColorIndex 0x2
#define EEPROM_OFFSET_gPatternToShow    0x3
#define EEPROM_LAST_NON_CHKSM           0xE // EEPROM address of last non-checksum data
#define EEPROM_INVERTED_CHKSM           0xF // EEPROM address of checksum data
#define EEPROM_BYTES_PER_CONFIG (EEPROM_INVERTED_CHKSM+1)
```

We add the following prior to **setup()**
```C
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// eeprom_store_if_change(offset, byteValue) - write byte to EEPROM if it is different than current EEPROM
//    we don't want to write EEPROM unless needed
// offset - where to store the byte in EEPROM, offset from gEepromConfigStart
// byteValue - byte value to store at that offset in EEPROM configuration
//
void eeprom_store_if_change(int offset, uint8_t byteValue) {
  uint8_t nowValue;

  nowValue = EEPROM.read(offset);
  if (nowValue != byteValue) {
    EEPROM.write(offset, byteValue);
  } // if we needed to write to EEPROM
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
  return((uint8_t) (~chksumValue));
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

  eeprom_store_if_change(offset, byteValue);
  invChksumValue = eeprom_calc_inverted_checksum();
  eeprom_store_if_change(EEPROM_INVERTED_CHKSM, invChksumValue);
} // end eeprom_store_with_chksum()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// eeprom_init_from_ram()
//   set EEPROM configuration to current state
//
void eeprom_init_from_ram() {

  eeprom_store_if_change(EEPROM_OFFSET_gInterval,         gInterval);
  eeprom_store_if_change(EEPROM_OFFSET_gOneOrRainbow,     gOneOrRainbow);
  eeprom_store_if_change(EEPROM_OFFSET_gTheOneColorIndex, gTheOneColorIndex);
  if (EEPROM_OFFSET_gPatternToShow < EEPROM_LAST_NON_CHKSM) {
    eeprom_store_if_change(EEPROM_OFFSET_gPatternToShow,  gPatternToShow);
    for (uint8_t offset = 0; offset < EEPROM_LAST_NON_CHKSM; offset++) {
      eeprom_store_if_change(offset, 0); // zero fill the rest
    } // end fill with zero to one less than LAST_NON_CHKSM
    eeprom_store_with_chksum(EEPROM_LAST_NON_CHKSM, 0); // last non-checksum
  } else { // this was the last byte before checksum
    eeprom_store_with_chksum(EEPROM_OFFSET_gPatternToShow, gPatternToShow);
  } // end if this was the last byte before checksum
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
```

After these additions, there are only two changes to make.

At the start of **setup()** add:
```C
  // either initialize EEPROM configuration info or initialize RAM from EEPROM configuration info
  eeprom_check_init(); // see if EEPROM checksum is good; if not update EEPROM from RAM
  ram_init_from_eeprom(); // update RAM from EEPROM
```

In **handle_serial_input_command()** replace line **// TODO FIXME add code to put configuration into EEPROM** with:
```C
   eeprom_init_from_ram(); // store any new config in EEPROM
```

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/02_PersistanceOfVision_PartC_Oval_setup.png "Image of setup for 02_PersistanceOfVision Part C: Oval Setup")

## Reminder
[Top](#notes "Top")<br>
The connections do not change; this is just here for a reminder.

| Wire Color | Schematic | LED Stick | Purpose |
| --- | --- | --- | --- |
| Black | VSS | GND | Ground |
| Red | VDD | VCC | +5 Volts |
| White | DIN | IN | Serial Data |

Here is a reminder of our desired wiring

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/02_PersistenceOfVision.png" width="1002" height="530" alt="Image of wiring diagram for Persistence of Vision">
