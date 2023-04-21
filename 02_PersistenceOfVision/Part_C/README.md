# NOTES

**Table of Contents**
* [Top](#notes "Top")
* [Oval](#oval "Oval")
* [Rainbow](#rainbow "Rainbow")
* [Hello World](#hello-world "Hello World")
* [Sawtooth Revisited](#sawtooth-revisited "Sawtooth Revisited")
* [Reminder](#reminder "Reminder")

We will continue with our modified FastLED example program from **Part_B** to perform our **Oval** pattern.

## Oval
[Top](#notes "Top")<br>
The idea is to draw ovals, circles, and maybe eyes with our LED Stick.<br>
Each step left-to-right is a "blink" in the following diagram.

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/OvalPattern.png "Image of Oval pattern; each step left-to-right is a blink")

Here is where all our work organizing the code for Part B Sawtooth pays off. Except for changing Sawtooth to Oval, there are very few changes to make.

Copy the Sawtooth.ino file into a directory named Oval with filename Oval.ino, then open it in the Arduino IDE.

Now do global replaces with case sensitivity on as shown below:
| Replace this | With this |
| --- | --- |
| sawtooth_ | oval_ |
| Sawtooth | Oval |
| SAWTOOTH | OVAL |

That wasn't too bad. Maybe we should have used "pattern_" instead so there wouldn't be so much of this.

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

As an exercise to the reader, see if you can add a third pattern that is the Sawtooth pattern from before. It should only take a few lines of code, maybe 3 or 4. It will be good practice with hexadecimal and binary arithmetic.

When you have done this, compare it with my implementation
- https://github.com/Mark-MDO47/ArduinoClass/blob/master/ArduinoCode/AllThreePatterns_RedOrRainbow/AllThreePatterns_RedOrRainbow.ino

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
