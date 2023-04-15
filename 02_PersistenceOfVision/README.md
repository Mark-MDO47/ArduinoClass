# NOTES

**Table of Contents**
* [Top](#notes "Top")
* [Human Vision Persistence](#human-vision-persistence "Human Vision Persistence")
* [WS2811 and WS2812B individually addressable color LEDs](#ws2811-and-ws2812b-individually-addressable-color-leds "WS2811 and WS2812B individually addressable color LEDs")
* [The Circuit](#the-circuit "The Circuit")
* [The Code](#the-code "The Code")
  * [The Code - Timing Without Delays](#the-code-\--timing-without-delays "The Code - Timing Without Delays")
  * [The Code - FastLED](#the-code-\--fastled "The Code - FastLED")
  * [The Code - What are we Doing](#the-code-\--what-are-we-doing "The Code - What are we Doing")
* [Resources](#resources "Resources")

## Human Vision Persistence
Louis Le Prince is generally credited to be the first person to record and show moving pictures. Yes, there is actually something that Thomas Edison did NOT invent.
- https://en.wikipedia.org/wiki/Louis_Le_Prince

The effect that allows us to enjoy movies is known as the persistence of vision: the human eye continues to "see" light for a short time after the light stops. You can try this by simply closing your eyes and seeing spots where the light was brightest. Over time it was discovered that a playback speed of 24 frames per second was fast enough to make the pictures appear to move.

In this exercise we will build on the blinking LED exercise to create a simple persistence of vision wand consisting of 8 individually addressable color LEDs using the WS2811/WS2812B serial protocol.

Much more elaborate versions of this wand (and some beautiful pictures and movies) can be found in these links:
- https://www.instructables.com/Persistence-of-Vision-LED-Staff/
- https://povstaff.readthedocs.io/en/latest/
- https://learn.adafruit.com/pov-dotstar-double-staff

## WS2811 and WS2812B individually addressable color LEDs
We will be using this color LED stick
- https://protosupplies.com/product/ws2812-addressable-rgb-led-stick-module/

Here is the image from https://protosupplies.com:

<img src="https://protosupplies.com/wp-content/uploads/2020/09/WS2812-RGB-8-LED-Stick-Module.jpg" width="640" height="480">

Note: the WS in WS2811 and WS2812B stands for Worldsemi. Search this page for WS2812B and see the chip that implements all the magic in this project.
- http://www.world-semi.com/
- http://www.world-semi.com/ws2812-family/

There is a serial data protocol used to control this string of 8 LEDs.
- 3 8-bit bytes per LED are sent to control Red/Green/Blue.
  - The actual color order can vary; I determine it by experimentation.
  - This allows 256 levels (0-255 for an unsigned 8-bit byte) for each of the colors Red/Green/Blue.
- The order of 3-byte RGB commands sent starts with data for the first LED in the string, then the second, etc.
- Each LED "consumes" its 3-byte RGB command from the data and then passes all the rest of the data down the line until there is a stopage.
- If there is a stopage of data for a certain specified amount of time, the string resets and the each LED will consume a new 3-byte value for its next RGB command.
- That is it! There are some more details on this protocol in [Resources](#resources "Resources") for the curious. 

I typically use the FastLED library to control these LEDs. It is a powerful library, but simple things are simple.

Because we are already using the USB serial port for debugging, we will dedicate a Digital pin as the "software" serial data line. FastLED will take care of using the Digital pin to send a serial data stream.

## The Circuit

The circuit is simple; it is almost just a replacement of the LED from the previous [01_BlinkingLED](https://github.com/Mark-MDO47/ArduinoClass/tree/master/01_BlinkingLED "01_BlinkingLED") with the data pin from the RGB LED stick. There are also power and ground connections to the LED stick.
- https://github.com/Mark-MDO47/ArduinoClass/blob/master/02_PersistenceOfVision/02_PersistenceOfVision.pdf

Note that the connections from one LED to another are internal to the LED stick, so we only need to connect to the first LED. This is a good thing to try to do when using these individually addressable RGB LEDs. If you get close to 400 LEDs in one project (as I have) then you really do not want to solder all those connections between LEDs.

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/02_PersistenceOfVision.png" width="501" height="265">

These LEDs use power that adds up. We can use this to estimate the power
- http://fastled.io/docs/3.1/group___power.html<br>
  - calculate_max_brightness_for_power_vmA(lots of parameters)
     
 | https://github.com/FastLED/FastLED/blob/master/power_mgt.cpp |
 | --- |
| static const uint8_t gRed_mW   = 16 * 5; // 16mA @ 5v = 80mW |
| static const uint8_t gGreen_mW = 11 * 5; // 11mA @ 5v = 55mW |
| static const uint8_t gBlue_mW  = 15 * 5; // 15mA @ 5v = 75mW |
| static const uint8_t gDark_mW  =  1 * 5; //  1mA @ 5v =  5mW |
  
This calculates to about 42 milliamps per LED at max brightness WHITE.

With just 8 RGB LEDs the current draw of 336 milliamps (power 1.68 watts) worst case through the Arduino Nano should be OK. If it got to be many more than that I would use a separate power source for the LEDs. Also, you will find that we set a parameter to limit the total power for each LED in the FastLED library.

## The Code
Now our code discussion section is going to get a little more involved.

### The Code - Timing Without Delays
Open another Example program - Blink Without Delay - and lets compare it with Blink.

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/IDE_LoadBlinkWithoutDelay.png "Arduino IDE loading Blink Without Delay example program")

The **setup()** code is essentially the same - just setting up the LED pin as OUTPUT.

There are some new "state" variables, defined before (and outside) of **setup()** and **loop()** - this means that the values will remain unchanged between calls to **loop()**.
```C
// Variables will change:
int ledState = LOW;             // ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 50;           // interval at which to blink (milliseconds)
```

When we look at the new **loop()** code, we don't see any calls to **delay()** - it just runs straight through and uses the **millis()** clock to decide if it should set the LED pin HIGH or LOW. Usually it just passes through the loop with almost no delay and no change to the LED state. What is the advantage of this?
```C
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }
```

This code design doesn't prevent the Arduino from doing other things (reading other sensors, controlling other devices) during the time we are waiting for the next **interval** to expire.
- In the Blink code inside the **loop()** routine, the two **delay()** calls take almost 100% of the time. This is time during which the Arduino cannot be doing anything else.
- In the "Blink Without Delay" code, the **loop()** code completes rapidly and is called again and again with only a few milliseconds in between loops. If there are other devices to handle and if the code for those devices is written in a similar manner, the Arduino can handle those also. It can do more than just Blink!

All this is caused because we are using the standard architecture for Arduino code, in which there are two routines **setup()** and **loop()** and no interrupts. If the system was multi-tasking either based on real-time interrupts or time slicing and if one task does a delay it doesn't prevent another task from running.

It is possible to enable and use interrupts in the Arduino, but this introduces complexities that sometimes cause trouble for the worlds best programmers - issues of code re-entrancy, software synchronization (i.e. semaphores), prioritization, non-deterministic latency, etc. The people who designed the Arduino chose to use this simpler architecture since the expected audience included many hobbyist and first-time programmers. This simpler architecture avoids many of the complexities mentioned above and thus helps to "keep us out of trouble". If you are more advanced, they do not prevent you from going further.
- See attachInterrupt(), detachInterrupt(), interrupts(), and noInterrupts() in https://reference.arduino.cc/reference/en/.

In all my Arduino projects, I have not needed to use interrupts; I have always stayed with the standard Arduino code architecture. Even for my latest Arduino Nano project I stuck with this architecture: the Rubber Band Gun which includes multiple buttons, multiple strings of WS2812B RGB LEDs, sound generation, bluetooth sound transfer, voice menus for reconfiguration, and motor control.
- https://github.com/Mark-MDO47/RubberBandGun

In our subsequent code, we will be using this "Blink Without Delay" style of coding, since we will be adding other devices that need to be handled.

### The Code - FastLED
Kudos to Daniel Garcia and Mark Kriegsman for the FANTASTIC Arduino FastLED library and examples!!! Unfortunately Daniel Garcia passed away in a tragic accident a few years ago but the library is still being actively maintained.
- https://github.com/FastLED/FastLED
- https://github.com/FastLED/FastLED/blob/master/examples

As mentioned, these WS2811/WS2812B LEDs use just power/ground/serialdata. Other LEDs use power/ground/serialdata/clock. There are some differences in the exact approach for those other LEDs compared to ours.

Here is what we do in **setup()**
- We include the FastLED file (**#include <FastLED.h>**)
- We tell it what pin is to be used for serial communication
  - We are not using the built-in USB serial port for FastLED; FastLED will take care of sending the serial data on a digital I/O pin for us.
- We tell it how many LEDs are in the string attached to that pin
- We tell it what order the three bytes go onto the data line: RGB, RBG, GBR, etc.
- We use the typedef (a C-language construct for an activity-specific data type) **CRGB** to create an array for data storage when the data is sent to the LEDs. We will call this array fastled_array, but the name is arbitrary.
- We use **FastLED.addLeds(...)** to point at fastled_array and give it the information about pin, number of LEDs, and color order.

Here is what we do in **loop()**
- If it is time for the next data pattern:
  - We fill fastled_array with the RGB colors we want for each LED
  - We call **FastLED.show()** to send the color commands to the LED strip
  - We calculate what time the next data pattern should be sent

A preview - look here to see what our first attempt at using the LED strip will look like. I know, we just cannot get away from Blink; it is the "Hello World" of Arduinos.
- https://github.com/FastLED/FastLED/blob/master/examples/Blink/Blink.ino

### The Code - What are we Doing
Now we understand
- the basics of persistance of vision
- how to organize our code using timers so we can respond rapidly to many sensors and devices
- how to detect the state of the button
- how to talk to the LED strip

Now the question is: what are we trying to do?

The ultimate goal is to have a wand we can wave that makes our eyes see patterns. We will use the button to stop and restart the patterns. Although much more elaborate possibilities could be pursued, the plan for this project is to implement a few different patterns depending on how much time we want to spend on it
- Blink - talk to just the first LED, make sure we know the color order https://github.com/FastLED/FastLED/blob/master/examples/Blink/Blink.ino
- Sawtooth - a triangular wave bouncing from top to bottom and back
- Oval - a pattern that appears to be a set of ovals; maybe even appear to be a bubble-blower
- DemoReel - Mark Kriegsman's classic DemoReel100.ino https://github.com/FastLED/FastLED/tree/master/examples/DemoReel100

The LED pattern code for Sawtooth and Oval will pretty much done from scratch using the FastLED library. The LED pattern code for Blink and DemoReel will be derived from example FastLED code. DemoReel will show some of the incredible capabilities of the FastLED library for generating beautiful patterns with little code.

So I will split this into four projects:
| Part | Title | Link |
| --- | --- | --- |
| Part A | Blink | https://github.com/Mark-MDO47/ArduinoClass/blob/master/02_PersistenceOfVision/Part_A/README.md |
| Part B | Sawtooth | https://github.com/Mark-MDO47/ArduinoClass/blob/master/02_PersistenceOfVision/Part_B/README.md |
| Part C | Oval | https://github.com/Mark-MDO47/ArduinoClass/blob/master/02_PersistenceOfVision/Part_C/README.md |
| Part D | DemoReel | https://github.com/Mark-MDO47/ArduinoClass/blob/master/02_PersistenceOfVision/Part_D/README.md |

## Resources

### WS2812B Protocol
The WS2812B protocol can be found in this spec:
* https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf

A higher level depiction of this output protocol in action (taken from the spec) is shown here. First is the serial head-to-tail cascade architecture of the LEDs:

![alt text](https://github.com/Mark-MDO47/FPGA_RBG_2_RBGW/blob/master/images/CascadeLED_SerialProtocol_arch.png "WS2812b RGB serial cascade architecture (from spec)")

Then the high-level serial output protocol as seen by each of the LEDs in the architecture diagram. Note how each LED "consumes" the first set of bytes and passes on the rest.

![alt text](https://github.com/Mark-MDO47/FPGA_RBG_2_RBGW/blob/master/images/WS2812B_RGB_SerialProtocol.png "WS2812b RGB serial output protocol (from spec)")

In summary, there is a serial data protocol used to control strings of WS2811/WS2812B RGB LEDs.
- 3 8-bit bytes per LED are sent to control Red/Green/Blue.
  - The actual color order can vary; I determine it by experimentation.
  - This allows 256 levels (0-255) for each of the colors Red/Green/Blue.
- The order of 3-byte RGB commands sent starts with data for the first LED in the string, then the second, etc.
- Each LED "consumes" its 3-byte RGB command from the data and then sends all the rest of the data down the line.
- If there is a stopage of data for a certain specified amount of time, the string resets and the first LED will consume the next RGB command.

