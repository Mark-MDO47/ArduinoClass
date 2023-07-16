# NOTES

**Table of Contents**
* [Top](#notes "Top")
* [Decimal and Binary and Hexadecimal - Oh My](#decimal-and-binary-and-hexadecimal-\--oh-my "Decimal and Binary and Hexadecimal - Oh My")
  * [How do we use decimal and binary and hexadecimal numbers in the code](#how-do-we-use-decimal-and-binary-and-hexadecimal-numbers-in-the-code "How do we use decimal and binary and hexadecimal numbers in the code")
* [Oval](#oval "Oval")
* [Rainbow](#rainbow "Rainbow")
* [Hello World](#hello-world "Hello World")
* [Sawtooth Revisited](#sawtooth-revisited "Sawtooth Revisited")
* [Reminder](#reminder "Reminder")
* [All the Patterns - Extra Credit](#all-the-patterns-\--extra-credit "All the Patterns - Extra Credit")
  * [Pattern Code and Serial Commands](#pattern-code-and-serial-commands "Pattern Code and Serial Commands")
  * [EEPROM Introduction](#eeprom-introduction "EEPROM Introduction")
  * [EEPROM Code](#eeprom-code "EEPROM Code")
  * [Persistence of Vision Spinning Stick](#persistence-of-vision-spinning-stick "Persistence of Vision Spinning Stick")

First we will take a look at **Decimal, Binary, and Hexadecimal** arithmetic, since we will be using some tricks in this realm to implement our patterns.

Then we will continue with our modified FastLED example program from **Part_B**. We will do the following quick projects:
- **Oval** - new Oval pattern - still all red
- **Rainbow** - use Rainbow color scheme for Oval instead of all red
- **Hello World!** - new Hello World! pattern
- **Sawtooth Revisited** - rework the Sawtooth pattern using this new code
- **All the Patterns - Extra Credit** - put it all together, choose pattern and blink rate, save configuration in EEPROM
- **Persistance of Vision Spinning Stick** - I put our project on a stick with a handle so I could spin it around; looks very cool!

## Decimal and Binary and Hexadecimal - Oh My
[Top](#notes "Top")<br>
When programming it eventually becomes necessary to understand decimal, binary, and hexadecimal arithmetic. It is not hard to understand but it does take some time to be proficient in it. Fortunately in this class we don't really need to be quick at it, we just need to be able to figure it out.

We all are used to decimal arithmetic and the notation system based on powers of 10. If you see the decimal number 123 you know, starting from the right and moving left, that it is (3 times ten-to-the-power-zero) + (2 times ten-to-the-power-one) + (1 times ten-to-the-power-two). Since anything (let's ignore infinity and zero at this point) to the power zero is one, that means 123 is three plus twenty plus one hundred.

The same principle applies to binary but every digit is either one or zero and every position is a power of two instead of a power of ten. Again, hexadecimal is the same principle but every digit is from zero to nine then a, b, c, d, e, or f representing 10, 11, 12, 13, 14 or 15; and every position is a power of sixteen instead of ten or two. It is pretty easy to convert binary to hexadecimal and back and hexadecimal has one fourth as many digits and binary.

The following short document goes over this in just a little more detail.
- http://www.eecs.umich.edu/courses/eecs270/270lab/270_docs/HexNumSys.pdf

And now a caution about octal. Octal arithmetic is similar to the above systems with digits confined to 0,1,2,3,4,5,6,7 and the positions based on powers of eight. The difficulty arises from the method the C language uses to flag that the digits should be interpreted as octal: if the number has all **decimal** digits and starts with zero, it is assumed to be **octal**.

This means that in C language, 10 is ten decimal but 010 is eight decimal. In fact if you try to use 09, it will be flagged as an error because 9 is not an octal digit. Having compiler errors tell us when the compiler is misinterpretting our numbers is one thing, having it silently accept 010 as eight is quite another - so **programmor emptor**!

So how do we specify integer constants in the various number systems?
- decimal - just use decimal digits but do not start with zero. If you want the value zero, 0 octal = 0 decimal = 0.
- octal - use octal digits and start with a zero
- hexadecimal - use 0x followed by hexadecimal digits; OK to use either upper or lower case hex letters
- binary - us 0b followed by binary digits

The following statements cause identical values to be stored in "i":
```C
i =       47;
i =      057;
i =     0x2f;
i = 0b101111;
```

There is more to learn, for instance negative numbers in twos-complement or ones-complement and how they behave, but the above will pretty much cover this class.

### How do we use decimal and binary and hexadecimal numbers in the code
[Top](#notes "Top")<br>
In the **loop()** code that we will be discussing for these patterns we will be doing some shifting and masking with hexadecimal numbers to decide which LEDs to light up. Pro tip: this technique uses boolean algebra, the underlying basis of all modern digital computers There was a person named George Boole who invented and developed it. This is what the innermost loop in **Oval** looks like:
```C
  uint8_t bits = oval_pattern_bits[blink_phase];

  for (long int i = 0; i < NUM_LEDS; i++) {
    if (0 == (0x01 & bits))
       ptrn_leds[i] = CRGB::Black;
    else
       ptrn_leds[i] = CRGB::Red;
    bits >>= 1;
  }
```

**oval_pattern_bits** is an array of unsigned 8-bit bytes; the binary bits in each 8-bit byte correspond to whether we want to light up that LED in our LED Stick. The least significant bit corresponds to the LED closest to the wires; each bit after that corresponds to the next LED on the stick.

```
NOTE:
uint8_t is one typedef from a commonly used set of definitions.
These allow specifying unsigned (uint...) or signed (sint...) integers of various multiples of 8 bits, known as a byte.
When the C language was developed, it was specifically designed to work well with the PDP11 architecture
... so such definitions as int had a specific number of bits and specific endian characteristics for bytes and words, etc.
As C was adapted to more computer architectures, it was found to be useful to develop ways to specify these sorts of things
... in a universal way.
By specifying the variable "bits" as "uint8_t" we can be sure we and the reader know what its size in the processor is.
Alternatively we could specify it as "unsigned char" but this is less general and not as intuitive.
This becomes more important when we see that a signed 16-bit integer on different processors could be "short int" or "int"
... but it is always "uint16_t".
```

For instance, the first unsigned 8-bit byte in oval_pattern_bits is 0x18. This corresponds to 0b00011000.  This gets stored into **bits** at the beginning of the code if blink_phase is zero. The least significant bit is on the right and then we go right-to-left. If the bit is a 0 we set the LED black; if it is a 1 we set the LED red.

There is a loop **for (long int i = 0; i < NUM_LEDS; i++) { ... }**. In our case, **NUM_LEDS** is 8 for our 8-LED stick, so we want data arranged with eight bits per chunk. This is convenient since our data comes in 8-bit bytes, so this loop will loop over every bit in **bits** that corresponds to an LED.
- In C language scoping rules you can define a variable for use only within the block of the for loop (usually this block is enclosed in "{}" but sometimes just a single statement) as I did here with the variable "i". There are other places you can do this type of definition too, for instance inside any {}; that is where we defined "bits". Note: I didn't really need to use a long int for this loop, but it only slows the code down a little and I am too lazy to change it.

The **(0x01 & bits)** part of the code "masks" the least significant bit in bits. The "&" is the boolean AND operator; it operates bitwise on the two values. For each bit, if both corresponding bits in the two values are "1" then the resulting bit is "1"; otherwise the resulting bit is "0". There are other boolean operators too such as | for OR, ^ for EXCLUSIVE-OR, etc. Be aware that the operator && is a logical AND not the same as the boolean AND. Logical AND operates on the entire values and produces just one zero or non-zero result; boolean AND operates on each bit within the values and produces a result for each bit separately. A common mistake is to use && when you wanted to use & or vice versa.

After we have masked and looked at the least significant to choose red or black for this led, we shift the value in **bits** to the right with **bits >>= 1;**. The operator is the right-shift operator ">>"; it is used in a typical C language pattern where {opr} is any operator (such as >>, <<, +, -, *, /, and more) then
- symbol {opr}= value;
  - is the same as
- symbol = symbol {opr} value;

For example:
- **i += 1;** is the same as **i = i + 1;**
- **bits >>= 1;** is the same as **bits = bits >> 1;**

This doesn't make much difference in these examples but here is an example where it cuts down on copy/paste errors:
- **data_array[idx*5 % 17].another_array[idx2\*17 % 5][idx3] += 1;**

Here is the way the loop operates when we start with bits = 0x18;
| i | bits | (0x01 & bits) | store | bits >>= 1 |
| --- | --- | --- | --- | --- |
| 0 | 0b00011000 | 0 | ptrn_leds[0] = CRGB::Black; | 0b00001100 |
| 1 | 0b00001100 | 0 | ptrn_leds[1] = CRGB::Black; | 0b00000110 |
| 2 | 0b00000110 | 0 | ptrn_leds[2] = CRGB::Black; | 0b00000011 |
| 3 | 0b00000011 | 1 | ptrn_leds[3] = CRGB::Red; | 0b00000001 |
| 4 | 0b00000001 | 1 | ptrn_leds[4] = CRGB::Red; | 0b00000000 |
| 5 | 0b00000000 | 0 | ptrn_leds[5] = CRGB::Black; | 0b00000000 |
| 6 | 0b00000000 | 0 | ptrn_leds[6] = CRGB::Black; | 0b00000000 |
| 7 | 0b00000000 | 0 | ptrn_leds[7] = CRGB::Black; | 0b00000000 |
 
## Oval
[Top](#notes "Top")<br>
The idea is to draw ovals, circles, and maybe eyes with our LED Stick.<br>
Each step left-to-right is a "blink" in the following diagram.

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/OvalPattern.png "Image of Oval pattern; each step left-to-right is a blink")

Note: the following spreadsheet helps with calculations for the patterns (does the so-called bit-busting).
- https://github.com/Mark-MDO47/ArduinoClass/blob/master/02_PersistenceOfVision/Pattern_Calcs.xlsx

Copy the Sawtooth.ino file into a directory named Oval with filename Oval.ino, then open it in the Arduino IDE.

Here is where all our work organizing the code for Part B Sawtooth pays off. Except for changing Sawtooth to Oval, there are very few changes to make.

Now do global replaces with case sensitivity on as shown below:
| Replace this | With this |
| --- | --- |
| sawtooth_ | oval_ |
| Sawtooth | Oval |
| SAWTOOTH | OVAL |

That wasn't too bad. Maybe we should have used "pattern_" instead of oval_ and sawtooth_ so there wouldn't be so much of this.

Now for the actual changes. First change the count to 52
- **#define OVAL_CALLS_THEN_REPEAT 52 // the Oval pattern does this many calls then repeats**

The oval_blink_pattern() routine now looks like this
```C
void oval_blink_pattern(long int blink_phase, CRGB * ptrn_leds) {
  // oval_pattern_bits one bit per LED to be on. Most Significant bit is first LED, etc.
  static uint8_t oval_pattern_bits[OVAL_CALLS_THEN_REPEAT] = { 0x18, 0x24, 0x42, 0x81, 0x81, 0x81, 0x42, 0x24, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x50, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x24, 0x42, 0x81, 0x81, 0x99, 0x99, 0x81, 0x81, 0x42, 0x24, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00 };
  uint8_t bits = oval_pattern_bits[blink_phase];

  for (long int i = 0; i < NUM_LEDS; i++) {
    if (0 == (0x01 & bits))
       ptrn_leds[i] = CRGB::Black;
    else
       ptrn_leds[i] = CRGB::Red;
    bits >>= 1;
  }

} // end oval_blink_pattern()
```

All done; you now have the all-red Oval pattern!

## Rainbow
[Top](#notes "Top")<br>
Why should we always use LED colors Black and Red? Does FastLED have an excellent method to vary colors in an interesting way?

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

All done; now you have the Rainbow version of the Oval pattern.

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
#define OVAL_CALLS_THEN_REPEAT 52 // the Oval pattern does this many calls then repeats
```

... to
```C
// Mark-MDO47 Oval pattern or Hello pattern
// #define PATTERN_OVAL 1
#define PATTERN_HELLO 1

#ifdef PATTERN_HELLO
#define PTRN_CALLS_THEN_REPEAT 70 // the HELLO WORLD! pattern does this many calls then repeats
static uint8_t  pattern_bits[PTRN_CALLS_THEN_REPEAT] = { 0xFF, 0x18, 0x18, 0x18, 0xFF, 0x00, 0xFF, 0x89, 0x89, 0x89, 0x00, 0xFF, 0x01, 0x01, 0x01, 0x00, 0xFF, 0x01, 0x01, 0x01, 0x00, 0x7E, 0x81, 0x81, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x01, 0x0E, 0x01, 0xFE, 0x00, 0x00, 0x7E, 0x81, 0x81, 0x7E, 0x00, 0xFF, 0x98, 0x94, 0x63, 0x00, 0xFF, 0x01, 0x01, 0x01, 0x00, 0xFF, 0x81, 0x42, 0x3C, 0x00, 0xF9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
#else // PATTERN_OVAL
#define PTRN_CALLS_THEN_REPEAT 52 // the Oval pattern does this many calls then repeats
static uint8_t pattern_bits[PTRN_CALLS_THEN_REPEAT] = { 0x18, 0x24, 0x42, 0x81, 0x81, 0x81, 0x42, 0x24, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x50, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x24, 0x42, 0x81, 0x81, 0x99, 0x99, 0x81, 0x81, 0x42, 0x24, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00 };
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
  static uint8_t oval_pattern_bits[OVAL_CALLS_THEN_REPEAT] = { 0x18, 0x24, 0x42, 0x81, 0x81, 0x81, 0x42, 0x24, 0x18, 0x00, 0x40, 0xA0, 0x48, 0x14, 0x08, 0x20, 0x53, 0x23, 0x00, 0x18, 0x24, 0x42, 0x81, 0x81, 0x99, 0xA5, 0xA5, 0x99, 0x81, 0x81, 0x42, 0x24, 0x18, 0x00 };
  uint8_t bits = oval_pattern_bits[blink_phase];
```

... to
```C
  // pattern_bits one bit per LED to be on. Most Significant bit is first LED, etc.
  uint8_t bits = pattern_bits[blink_phase];
```

Now you have the Rainbow version of the Hello World! pattern.

My version of this can be found here
- https://github.com/Mark-MDO47/ArduinoClass/blob/master/ArduinoCode/HelloWorld/HelloWorld.ino

A YouTube of this code in operation demonstrating use of the button to stop and start can be found here
- https://youtu.be/I-3vgafNRE8

## Sawtooth Revisited
[Top](#notes "Top")<br>
As an exercise to the reader, see if you can add a third pattern that is the Sawtooth pattern from before. Use the approach that the Oval and Hello World patterns use: a stored pattern. It should only take a few lines of code, maybe 5 or 6. It will be good practice with hexadecimal and binary arithmetic.

When you have done this, compare it with my implementation
- https://github.com/Mark-MDO47/ArduinoClass/blob/master/ArduinoCode/SawtoothRevisited/SawtoothRevisited.ino

## Reminder
[Top](#notes "Top")<br>
The connections for our normal projects (not extra credit) do not change; this is just here for a reminder.

| Wire Color | Schematic | LED Stick | Purpose |
| --- | --- | --- | --- |
| Black | VSS | GND | Ground |
| Red | VDD | VCC | +5 Volts |
| White | DIN | IN | Serial Data |

Here is a reminder of our desired wiring

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/02_PersistenceOfVision.png" width="1002" height="530" alt="Image of wiring diagram for Persistence of Vision">

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/02_PersistenceOfVision_Fritzing.png" width="750" alt="Fritzing image of wiring diagram for Persistence of Vision">

## All the Patterns - Extra Credit
[Top](#notes "Top")<br>
We have made a program that can be edited and compiled to do any of the three patterns. Now I want to expand it to allow selecting options from the USB serial port while the code is running:
- select the pattern to display
- select whether to use the Rainbow colors or a single-color
  - select which color (Red, Green, or Blue) to use if using single-color
- select how long to wait between blinks

In addition, I want to save the current state of my selections in EEPROM (Electrically Erasable Programmable Read-only Memory) in the Arduino, so that the next time the Arduino is powered up it will start with those same selections. As the chicken said while crossing the road, "I have my reasons".

### Pattern Code and Serial Commands
[Top](#notes "Top")<br>
I am just going to show the highlights of converting to use any of the patterns and the other menu options, not a line-by-line edit.<br>

It is possible to use the built-in capability **serialEvent()**, which gets called automagically after **loop()** completes. Except the documentation says it doesn't happen for all Arduinos. And the documentation and sample program are really old.

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/IDE_LoadSerialEvent.png "Image of IDE loading SerialEvent example")

Because it is trivially easy to implement a similar capability ourselves, and it does not leave the reader wondering how in the world **serialEvent()** gets called, and I like my code to be blindingly obvious (see my comment in section Sawtooth in https://github.com/Mark-MDO47/ArduinoClass/tree/master/02_PersistenceOfVision/Part_B), I will once again suggest we poke our fingers in the gears.

The goal is to read commands from the USB serial port. To do this and fit within our **setup()/loop()** architecture, we need to meet the following goals
- it should be reasonably encapsulated (because I am lazy)
- if there is nothing to do, we don't waste a lot of time figuring this out and just let **loop()** fall through to handling the next sensor or device
- if there are characters to read, we should read them quickly and put them somewhere and then let **loop()** fall through...
- when we detect end-of-command (linefeed or '\n'), we either notify the **loop()** code or call the processing routine ourselves

For our purposes, we will use **Serial.available()** to detect when character(s) are available to read and **Serial.read()** to read a single character at a time. We do NOT want to use **Serial.readln()** because that would stop Arduino execution until we get a complete line.

The basic idea is:
- show_menu_options() will show what the possible commands are
- handle_serial_input_command() will accept a command and set the appropriate configuration
- ptrn_blink() will look at the configuration and do what it says

First we convert the patterns to use separate mnemonics and remove the #ifdef statements that compile only one of them:
```C
#define SAWTOOTH_CALLS_THEN_REPEAT 14 // the Sawtooth pattern does this many calls then repeats
static uint8_t sawtooth_pattern_bits[SAWTOOTH_CALLS_THEN_REPEAT] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40 };

#define OVAL_CALLS_THEN_REPEAT 52 // the Oval pattern does this many calls then repeats
static uint8_t oval_pattern_bits[OVAL_CALLS_THEN_REPEAT] = { 0x18, 0x24, 0x42, 0x81, 0x81, 0x81, 0x42, 0x24, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x50, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x24, 0x42, 0x81, 0x81, 0x99, 0x99, 0x81, 0x81, 0x42, 0x24, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00 };

#define HELLO_CALLS_THEN_REPEAT 70 // the HELLO WORLD! pattern does this many calls then repeats
static uint8_t hello_pattern_bits[HELLO_CALLS_THEN_REPEAT] = { 0xFF, 0x18, 0x18, 0x18, 0xFF, 0x00, 0xFF, 0x89, 0x89, 0x89, 0x00, 0xFF, 0x01, 0x01, 0x01, 0x00, 0xFF, 0x01, 0x01, 0x01, 0x00, 0x7E, 0x81, 0x81, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x01, 0x0E, 0x01, 0xFE, 0x00, 0x00, 0x7E, 0x81, 0x81, 0x7E, 0x00, 0xFF, 0x98, 0x94, 0x63, 0x00, 0xFF, 0x01, 0x01, 0x01, 0x00, 0xFF, 0x81, 0x42, 0x3C, 0x00, 0xF9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
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
static uint8_t * gPatternsBits[PATTERN_MAX_NUM]   = { sawtooth_pattern_bits, oval_pattern_bits, hello_pattern_bits };
static const char * gPatternsNames[PATTERN_MAX_NUM]   = { "Sawtooth", "Oval", "HelloWorld!" };
static int gPatternsRepeat[PATTERN_MAX_NUM] = { SAWTOOTH_CALLS_THEN_REPEAT, OVAL_CALLS_THEN_REPEAT, HELLO_CALLS_THEN_REPEAT };
int gPatternToShow = 0;
#define COLORS_ALL_ONE 0
#define COLORS_RAINBOW 1
static int gMenuMsecCounts[] = { 1, 3, 5, 10, 20, 40 };
int gOneOrRainbow = COLORS_ALL_ONE; // 0 = ALL_ONE, 1 = RAINBOW
CRGB gTheColorChoices[] = { CRGB::Red, CRGB::Green, CRGB::Blue };
static const char * gTheColorStrings[] = { "Red", "Green", "Blue" };
int gTheOneColorIndex = 0;

#define MENU_CHOICES_NUM 14
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

We add code to show the menus and currently selected options, and also to accept new options.<br>
NOTE that we are using the **F()** macro to save strings in program memory instead of using precious Arduino RAM. 
- https://github.com/Mark-MDO47/ArduinoClass/tree/master/99_Resources#progmem-and-f-macro-to-save-ram
```C
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
     Serial.print(F("Error: number ")); Serial.print(tmp); Serial.println(F(" is not valid"));
   }
   // TODO FIXME add code to put configuration into EEPROM
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

At the beginning of **setup()**
```C
  Serial.begin(115200);         // this serial communication is for general debug; set the USB serial port to 115,200 baud
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  while (Serial.available()) Serial.read(); // clear any startup junk from the serial queue
  memset((void *)serial_input_buf, 0, SERIAL_INPUT_BUF_LEN); // clear buffer; good idea for zero-terminated strings
```

At the end of **setup()**
```C
  Serial.println(F("")); // print a blank line in case there is some junk from power-on
  Serial.println(F("ArduinoClass init..."));
  show_menu_options();
```

Replace the code in **ptrn_blink()** with this:
```C
void ptrn_blink(long int blink_phase, CRGB * ptrn_leds) {
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
} // end ptrn_blink()
```


### EEPROM Introduction
[Top](#notes "Top")<br>
These Arduino Nanos have 32Kbyte of FLASH memory (program storage), 2Kbyte of SRAM, and 1Kbyte of EEPROM.
- FLASH memory (no acronym) was an offshoot of EEPROM. For the Arduino Nano it is erasable and writeable in blocks of many bytes.
- EEPROM (Electrically Eraseable Programmable Read-Only Memory) is, for the Arduino Nano, erasable and writeable in blocks of one byte.
- SRAM (Static Random Access Memory) is, for the Arduino Nano, readable and writeable in blocks of one byte. There is typically no published limit on the number of times it can be read or written.

Note: 1Kbyte (capital K) typically means 1,024 bytes; 1,024 is considered to be the "binary thousand" since it is 2 to the power 10 and 1,000 is 10 to the power 3.

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

Given that FLASH is written only when we change the program and EEPROM would be written while the program is running, it is likely that EEPROM will use up all its erase/write cycles before FLASH will. In Arduino, the EEPROM is specified to handle 100,000 erase/write cycles for each position (byte). EEPROM reads are unlimited. However, the Arduino Nanos I use are cheap $2 clones instead of the official Arduino Nano at close to $25; therfore I don't want to push it. As you will see, we use **EEPROM.update()** that first reads the EEPROM byte and if it is the same value we were about to write it skips the write. If we used **EEPROM.write()** then it would do the write whether or not it was needed. I also created a debugging-only routine **eeprom_store_if_change()** which does the same thing as **EEPROM.update()** but also prints some debugging information, but **eeprom_store_if_change()** is unused in the final version.

When the Arduino powers up, how will it know if the parameters stored in EEPROM are valid or if it is a new Arduino out of the bag and the values are random? To handle this I store a simple checksum along with the parameters in EEPROM. If the EEPROM checksum doesn't match the EEPROM configuration data then I store a fresh set of configuration data in EEPROM.
Because I use a one-byte checksum (you could use a more elaborate checksum if you want) there is a one in 256 chance that random data will have a checksum that matches it. Because I am lazy, I accept that chance: if the first time I program an Arduino it behaves crazy then I can either write something to the configuration value or I can one-time change the expected value of the checksum to be different (for example; 1 + the normal checksum) and then it will put good configuration data in EEPROM. Later I can either leave the expectation at this new value or change it back.

### EEPROM CODE
[Top](#notes "Top")<br>
We add the following after **#include <FastLED.h>**
```C
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
```

We add the following prior to **setup()**
```C
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
```

After these additions, there are only two changes to make.

Near the start of **setup()** after **memset((void *)serial_input_buf, 0, SERIAL_INPUT_BUF_LEN)** add:
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

### Persistence of Vision Spinning Stick
[Top](#notes "Top")<br>
To make it easier to see the persistence of vision, I put our wand onto a piece of wood with a handle on it. I added some buttons so I could experiment with different color schemes, patterns and interval rates without having to hook up to a USB cable. It is probably the ugliest and most ad-hoc persistence of vision wand in the universe, but it works!
- https://github.com/Mark-MDO47/ArduinoClass/blob/master/02_PersistenceOfVision/02_PersistenceOfVision_stick.pdf

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/02_PersistenceOfVision_PartC_stick_topView.png" width="640" alt="Top view of Persistence of Vision Spinning Stick">

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/02_PersistenceOfVision_PartC_stick_sideView.png" width="640" alt="Side view of Persistence of Vision Spinning Stick">

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/02_PersistenceOfVision_PartC_stick_schematic.png" width="1000" alt="Side view of Persistence of Vision Spinning Stick">

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/02_PersistenceOfVision_PartC_stick_Fritzing.png" width="750" alt="Fritzing image of wiring diagram for Persistence of Vision Spinning Stick">

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/WhirlingStick_HelloWorld.jpg" width="1000" alt="Image of spinning LED Stick Blinking Hello World">

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/WhirlingStick_WhirledPeas.jpg" width="1000" alt="Image of spinning LED Stick Blinking Whirled Peas">

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/WhirlingStick_SawTooth.jpg" width="1000" alt="Image of spinning LED Stick Blinking Sawtooth">

Code changes were made to handle the four buttons.<br>
After **// Nano pin D-7     LEDstick DIN** add<br>
```C
// Nano pin D-5     Button Yellow - change delay time
// Nano pin D-4     Button Blue   - change pattern
// Nano pin D-3     Button White  - change Rainbow or Single Color
// Nano pin D-2     Button Green  - change the single color
```

After **#define DATA_PIN 7** add<br>
```C
// Buttons to experiment with conditions
#define BUTTON_PIN_YELLOW_DLY 5 // change delay time
#define BUTTON_PIN_BLUE_PTRN  4 // change pattern
#define BUTTON_PIN_WHITE_RNBW 3 // change Rainbow or Single Color
#define BUTTON_PIN_GREEN_SCLR 2 // change the single color
```

We will no longer use btn_pressed in this code<br>
Replace the **ptrn_phase(btn_pressed)** routine and its comments with this<br>
```C
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
```

Replace the **ptrn_fill(btn_pressed, ptrn_leds)** routine and its comments with this<br>
```C
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// ptrn_fill(ptrn_leds) - 
//    returns: int with either value HIGH==blinked the LEDs or LOW==did not blink
//
// ptrn_leds   - where to store the pattern

int ptrn_fill(CRGB * ptrn_leds) {
  int did_blink = LOW;
  long int blink_phase = ptrn_phase();

  ptrn_blink(blink_phase, ptrn_leds);
  did_blink = HIGH;

  return(did_blink);
} // end ptrn_fill()
```

Replace the **handle_leds(...)** routine and its comments with this<br>
```C
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// handle_leds(...) - get the pattern and then display on LEDs
//    returns: int with either value HIGH==blinked the LEDs or LOW==did not blink
//

int handle_leds() {
  int did_blink = ptrn_fill(fastled_array); // fill the pattern into RAM

  FastLED.show(); // show the pattern on LEDs

  return(did_blink); // HIGH if blink, LOW if pause
} // end handle_leds()
```

Completely remove the **handle_button(btn_pin)** routine and its comments.

After **handle_serial_input()**, add the following
```C
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
  if (idx >= (1+MENU_LAST_PATTERN-MENU_FIRST_PATTERN)) idx = 0;
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
```

In **setup()** replace the line **pinMode(BUTTON_PIN, INPUT_PULLUP);* with the following<br>
```C
  pinMode(BUTTON_PIN_YELLOW_DLY, INPUT_PULLUP); // digital INPUT_PULLUP means voltage HIGH unless grounded
  pinMode(BUTTON_PIN_BLUE_PTRN, INPUT_PULLUP); // digital INPUT_PULLUP means voltage HIGH unless grounded
  pinMode(BUTTON_PIN_WHITE_RNBW, INPUT_PULLUP); // digital INPUT_PULLUP means voltage HIGH unless grounded
  pinMode(BUTTON_PIN_GREEN_SCLR, INPUT_PULLUP); // digital INPUT_PULLUP means voltage HIGH unless grounded
```

In **loop()** replace the comment and line **int button_up = handle_button(BUTTON_PIN);** with the following:
```C
  // buttons will step through parameter options
  handle_buttons();
```

In **loop()** replace the line **handle_leds(button_up);** with the following:
```C
    handle_leds(); // Mark-MDO47 generate pattern to display and display it
```
