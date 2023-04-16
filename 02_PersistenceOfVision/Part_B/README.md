# NOTES

**Table of Contents**
* [Top](#notes "Top")
* [Blink](#blink "Blink")

We will use a slightly modified FastLED example program **Blink** to make sure we are talking to the LED stick correctly and check that the order of colors to send matches what we need.

## Blink
Copy the code or the file from here and put it in a directoy named Blink and open it with the Arduino IDE
- https://github.com/FastLED/FastLED/blob/master/examples/Blink/Blink.ino

Take a look at the code. You should be able to identify the steps before and in **setup()** we talked about earlier
- Line 05: include the FastLED file (**#include <FastLED.h>**)
- Line 14: tell it what pin is to be used for serial communication
- Line 08: tell it how many LEDs are in the string attached to that pin
- Implicit in Line 23: tell it what order the three bytes go onto the data line: RGB, RBG, GBR, etc.
- Line 18: use the typedef (a C-language construct for an activity-specific data type) **CRGB** to create an array for data storage when the data is sent to the LEDs. We will call this array fastled_array, but the name is arbitrary.
- Line 23: use **FastLED.addLeds(...)** to point at fastled_array and give it the information about pin, number of LEDs, and color order.

And you should be able to identify the code in **loop()**
- Lines 66 and 70: fill array "leds" with the RGB colors we want for each LED (they used a different name than we will)
- Lines 67 and 71: call FastLED.show() to send the color commands to the LED strip

Of course I cannot resist putting my fingers in the gears so we will make just a few changes.
- Line 08: change definition for NUM_LEDS from 1 to 8
- Line 14: change definition for DATA_PIN from 3 to 7
- Line 66: we will fill all 8 locations, we want the first four CRGB::Red, the next three CRGB::Green and the last one CRGB::Blue
  - you can use loops if you want or just set them one at a time
- Line 70: we will fill all 8 locations with CRGB::Black
  - you can use a loop if you want or just set them one at a time

The reason I want to use all 8 LEDs is to make sure they all work. The reason I use different numbers of the three colors is so we can tell in one experiment if we have the right color order in the 3-byte color command.

Once you have made these changes, connect up the LED stick and try it out. Remember:
- red wire is for 5 Volts from Arduino to LED stick (4-7VDC)
- black wire is for Ground between Arduino and LED stick (GND)
- white wire is for serial_data output from Arduino to LED stick (IN)

Here is a protosupplies.com image of the LED stick detail showing labels

![alt text](https://protosupplies.com/wp-content/uploads/2020/09/WS2812-RGB-8-LED-Stick-Module-With-Right-Angle-Header.jpg "protosupplies.com image LED stick detail showing labels")

Here is a reminder of our desired wiring

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/02_PersistenceOfVision.png" width="1002" height="530" alt="Image of wiring diagram for Persistence of Vision">
