# NOTES

**Table of Contents**
* [Top](#notes "Top")
* [Oval](#oval "Oval")
* [Variation](#variation "Variation")
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
## Variation
Why should we always us Black and Red? Does FastLED have an excellent method to vary colors in an interesting way?

The answer is YES!

## Reminder
[Top](#notes "Top")<br>
The connections do not change; this is just here for a reminder.

Remember:
- red wire is for 5 Volts from Arduino to LED stick (4-7VDC)
- black wire is for Ground between Arduino and LED stick (GND)
- white wire is for serial_data output from Arduino to LED stick (IN)

Here is a protosupplies.com image of the LED stick detail showing labels

![alt text](https://protosupplies.com/wp-content/uploads/2020/09/WS2812-RGB-8-LED-Stick-Module-With-Right-Angle-Header.jpg "protosupplies.com image LED stick detail showing labels")

Here is a reminder of our desired wiring

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/02_PersistenceOfVision.png" width="1002" height="530" alt="Image of wiring diagram for Persistence of Vision">
