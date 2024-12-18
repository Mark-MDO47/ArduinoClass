# NOTES

## Back to Root of Class
Click this link to back to go back to the root of the Arduino class
- https://github.com/Mark-MDO47/ArduinoClass/tree/master


**Table Of Contents**
* [Top](#notes "Top")
* [Back to Root of Class](#back-to-root-of-class "Back to Root of Class")
* [Code for FastLEDBlink](#code-for-fastledblink "Code for FastLEDBlink")
* [Wiring for FastLEDBlink](#wiring-for-fastledblink "Wiring for FastLEDBlink")
* [Try It](#try-it "Try It")

We will use a slightly modified FastLED example program **Blink** to make sure we are talking to the LED stick correctly and check that the order of colors to send matches what we need.

## Code for FastLEDBlink
[Top](#notes "Top")<br>
Copy the code or the file from here and put it in a directory named FastLEDBlink with filename FastLEDBlink.ino and open it with the Arduino IDE
- https://github.com/FastLED/FastLED/blob/master/examples/Blink/Blink.ino

If for some reason you do not have access to the internet you can find a copy (from 2023-08) in this area under _Examples_FastLED/Blink
- https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode

Take a look at the code. You should be able to identify the steps before and in **setup()** we talked about earlier
- Line 05: include the FastLED file (**#include <FastLED.h>**)
- Line 14: tell it what pin is to be used for serial communication
- Line 08: tell it how many LEDs are in the string attached to that pin
- Implicit in Line 23: tell it what order the three bytes go onto the data line: RGB, RBG, GBR, etc.
- Line 18: use the typedef (a C-language construct for an activity-specific data type) **CRGB** to create an array for data storage when the data is sent to the LEDs. The name of the array **leds** is arbitrary; we could change it if we want but would need to change it everywhere.
- Line 23: use **FastLED.addLeds(...)** to point at the array leds and give it the information about pin, number of LEDs, and color order.

And you should be able to identify the code in **loop()**
- Lines 66 and 70: fill array "leds" with the RGB colors we want for each LED (they used a different name than we will)
- Lines 67 and 71: call FastLED.show() to send the color commands to the LED strip

Of course we cannot resist putting our fingers in the gears so we will make just a few changes.
- Line 08: change definition for NUM_LEDS from 1 to 8
- Line 14: change definition for DATA_PIN from 3 to 7
- Line 66: we will fill all 8 locations, we want the first four CRGB::Red, the next three CRGB::Green and the last one CRGB::Blue
  - you can use loops if you want or just set them one at a time (leds[0] through leds[7])
- Line 70: we will fill all 8 locations with CRGB::Black
  - you can use a loop if you want or just set them one at a time

**NOTE** The reason for us to use all 8 LEDs is to make sure they all work. The reason for different numbers of the three colors is so we can tell in one experiment if we have the right color order in the 3-byte color command. This will let us confirm whether the NEOPIXEL initialization statement in **setup()** is the correct one for our LED strip or not.

## Wiring for FastLEDBlink
[Top](#notes "Top")<br>
Connect up the LED stick and try it out. Remember:
- red wire is for 5 Volts from Arduino to LED stick (VCC)
- black wire is for Ground between Arduino and LED stick (GND)
- white wire is for serial_data output from Arduino to LED stick (IN)

Below is an image of the LED Stick showing details of the connections between the colored wires and the LED Stick. Apologies for my soldering technique. You can see that the colors of the wire match the list above.
![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/02_PersistanceOfVision_PartA_LEDstickSoldering.png "Image of 02_PersistanceOfVision Part A: LED Stick Soldering")

Below is an image of the LED Stick and the end of its harness. The harness is long enough to wave through the air without risk of yanking the rest of the electronics along, as long as the rest of the electronics is held down so the mass of the harness doesn't pull it. The yellow nobs periodically along the harness are cable zip-ties. Note that the pin connectors have been solder-spliced onto the red, white and black wires and covered with heat shrink tubing; this is a more permanent way to insulate the wire than electrical tape, which degrades over time faster than the heat shrink tubing.
![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/02_PersistanceOfVision_PartA_LEDstickHarness.png "Image of 02_PersistanceOfVision Part A: LED Stick Harness")

Here is a youtube showing what the Blink pattern (first four CRGB::Red, the next three CRGB::Green and the last one CRGB::Blue) looks like, followed by an image of the color order. Because that observed color pattern matches our expected color pattern, we can be confident that the initialization call that was used in our **setup()** routine (the one that was not a comment) works for this LED stick.
- https://youtu.be/cnjk-xBvyEo

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/02_PersistanceOfVision_PartA_FastLEDblink.png "Image of 02_PersistanceOfVision Part A: FastLED Blink.png")

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/02_PersistanceOfVision_PartA_FastLEDblink_setup.png "Image of setup for 02_PersistanceOfVision Part A: FastLED Blink.png")

This describes how the markings on the pads on the LED Stick correspond to the wire color I soldered on and to the naming convention of the schematic.

| Wire Color | Schematic | LED Stick | Purpose |
| --- | --- | --- | --- |
| Black | VSS | GND | Ground |
| Red | VDD | VCC | +5 Volts |
| White | DIN | IN | Serial Data |

Below is a schematic of our desired wiring. I have inserted the color scheme above into the schematic for clarity.

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/02_PersistenceOfVision.png" width="1002" height="530" alt="Image of wiring diagram for Persistence of Vision">

Below is a Fritzing of our desired wiring.
<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/02_PersistenceOfVision_Fritzing.png" width="750" alt="Fritzing image of wiring diagram for Persistence of Vision">

## Try It
[Top](#notes "Top")<br>
OK - you have done the code, you have wired it up and checked your wiring - go ahead and try it!

You can see how easy it is to use the FastLED library. Completion of this project already puts you into a fairly small percentage of hobbyist Arduino users, to be able to use a sophisticated output device **and set it to do exactly what you want, not what some demo program does**. Congratulations!
