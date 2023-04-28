# NOTES

**Table of Contents**
* [Top](#notes "Top")
* [Oval](#oval "Oval")
* [Rainbow](#rainbow "Rainbow")
* [Hello World](#hello-world "Hello World")
* [Sawtooth Revisited](#sawtooth-revisited "Sawtooth Revisited")
* [All the Patterns - Extra Credit](#all-the-patterns-\--extra-credit "All the Patterns - Extra Credit")
  * [EEPROM]("eeprom "EEPROM")
  * [EEPROM Code]("eeprom-code "EEPROM Code")
* [Reminder](#reminder "Reminder")

We will continue with our modified FastLED example program from **Part_B** to perform our **Oval** pattern.

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
    if (0 == (0x80 & bits))
       ptrn_leds[i] = CRGB::Black;
    else
       ptrn_leds[i] = CRGB::Red;
    bits <<= 1;
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

### EEPROM
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

Given that FLASH is written only when we change the program and EEPROM would be written while the program is running, it is likely that EEPROM will use up all its write/erase cycles before FLASH will. In Arduino, the EEPROM is specified to handle 100,000 write/erase cycles for each position (byte). EEPROM reads are unlimited. However, the Arduino Nanos I use are cheap $2 clones instead of the official Arduino Nano at close to $25; therfore I don't want to push it. As you will see, I use a simple routine I wrote called **eeprom_store_if_change** that first reads the EEPROM byte and if it is the same value we were about to write it skips the write. This is a very simple routine and I am sure you could easily write your own version of it. Otherwise you can use my version in https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/AllThePatterns

When the Arduino powers up, how will it know if the parameters stored in EEPROM are valid or if it is a new Arduino out of the bag and the values are random? To handle this I store a simple checksum along with the parameters in EEPROM. If the EEPROM checksum doesn't match the EEPROM configuration data then I store a fresh set of configuration data in EEPROM.
Because I use a one-byte checksum (you could use a more elaborate checksum if you want) there is a one in 256 chance that random data will have a checksum that matches it. Because I am lazy, I accept that chance: if the first time I program an Arduino it behaves crazy then I can either write something to the configuration value or I can one-time change the expected value of the checksum to be different (for example; 1 + the normal checksum) and then it will put good configuration data in EEPROM. Later I can either leave the expectation at this new value or change it back.

### EEPROM CODE
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
  eeprom_check_init();
  ram_init_from_eeprom();
```

In **handle_serial_input_command()** just before **show_menu_options();** add:
```C
   eeprom_init_from_ram(); // store any new config in EEPROM
```

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
