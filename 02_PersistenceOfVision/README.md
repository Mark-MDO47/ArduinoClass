# NOTES

## Back to Root of Class
Click this link to back to go back to the root of the Arduino class
- https://github.com/Mark-MDO47/ArduinoClass/tree/master


**Table Of Contents**
* [Top](#notes "Top")
* [Back to Root of Class](#back-to-root-of-class "Back to Root of Class")
* [Human Vision Persistence](#human-vision-persistence "Human Vision Persistence")
  * [Four Projects](#four-projects "Four Projects")
  * [Why so Fast?](#why-so-fast "Why so Fast?")
* [WS2812B individually addressable color LEDs](#ws2812b-individually-addressable-color-leds "WS2812B individually addressable color LEDs")
* [The Circuit](#the-circuit "The Circuit")
  * [TLDR Power and Wires](#tldr-power-and-wires "TLDR Power and Wires")
* [The Code](#the-code "The Code")
  * [The Code - Timing Without Delays](#the-code-\--timing-without-delays "The Code - Timing Without Delays")
  * [The Code - FastLED](#the-code-\--fastled "The Code - FastLED")
* [The Code - What are we Doing](#the-code-\--what-are-we-doing "The Code - What are we Doing")
* [Resources](#resources "Resources")
  * [WS2812B Protocol](#ws2812b-protocol "WS2812B Protocol")

## Human Vision Persistence
[Top](#notes "Top")<br>
Louis Le Prince is generally credited to be the first person to record and show moving pictures. Yes, there is actually something that Thomas Edison did NOT invent.
- https://en.wikipedia.org/wiki/Louis_Le_Prince

The effect that allows us to enjoy movies is known as the persistence of vision: the human vision system continues to "see" light for a short time after the light stops. You can try this by simply closing your eyes and seeing spots where the light was brightest. Over time it was discovered that a playback speed of 24 frames per second was fast enough to make the pictures appear to move.

In this exercise we will build on the blinking LED exercise to create a simple persistence of vision wand consisting of 8 individually addressable color LEDs using the WS2812B serial protocol. We will then add an Ultrasonic Range Detector to control patterns for the LEDs.

Much more elaborate versions of this wand (and some beautiful pictures and movies) can be found in these links:
- https://www.instructables.com/Persistence-of-Vision-LED-Staff/
- https://povstaff.readthedocs.io/en/latest/
- https://learn.adafruit.com/pov-dotstar-double-staff
- https://learn.adafruit.com/bike-wheel-pov-display
- https://learn.adafruit.com/genesis-poi-dotstar-led-persistence-of-vision-poi

### Four Projects
[Top](#notes "Top")<br>
This Persistence of Vision exercise is split into four projects:
| Part | Title | Link | Image |
| --- | --- | --- | --- |
| Part A | Blink | https://github.com/Mark-MDO47/ArduinoClass/blob/master/02_PersistenceOfVision/Part_A/README.md | <img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/02_PersistanceOfVision_PartA_FastLEDblink_setup.png" width="500" alt="Image of Fast LED Blink with LED Wand"> |
| Part B | Sawtooth | https://github.com/Mark-MDO47/ArduinoClass/blob/master/02_PersistenceOfVision/Part_B/README.md | <img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/02_PersistanceOfVision_PartB_Sawtooth.png" width="500" alt="Image of SawTooth Persistence of Vision"> |
| Part C | Oval and Hello World! plus Spinning Stick! | https://github.com/Mark-MDO47/ArduinoClass/blob/master/02_PersistenceOfVision/Part_C/README.md | <img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/02_PersistenceOfVision_PartC_stick_topView.png" width="500" alt="Image of Spinning Stick Persistence of Vision"><br><img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/WhirlingStick_HelloWorld.jpg" width="500" alt="Image of Spinning Stick Persistence of Vision"> |
| Part D | DemoReel | https://github.com/Mark-MDO47/ArduinoClass/blob/master/02_PersistenceOfVision/Part_D/README.md | <img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/03_SonarRangeDetector_241LED_setup.png" width="500" alt="Image of Sonar Range Detector"> |

### Why so Fast?
[Top](#notes "Top")<br>
For our persistence of vision projects, we will go faster than 24 blinks per second because we are not just trying to blend one complete frame (picture) into the next, we are trying to draw a frame in the eye with at most 8 dots per blink. Our "frame rate" might be 200 blinks per second or more. In Part C of this exercise we will demonstrate a spinning "Persistence of Vision Stick" and will be able to experiment with rates up to 1,000 times per second or as slow as 25 times per second so we can investigate this effect.

## WS2812B individually addressable color LEDs
[Top](#notes "Top")<br>
We will be using this color LED Stick; it is contained in the Student "Kit".
- https://protosupplies.com/product/ws2812-addressable-rgb-led-stick-module/

Here is an image of the LED Stick that we will be using:<br>
![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/02_PersistanceOfVision_PartA_FastLEDblink.png "Image of WS2812B RGB LED Stick")

Note: the WS in WS2812B stands for Worldsemi. Search this page for WS2812B and see the chip that implements all the magic in this project.
- http://www.world-semi.com/
- http://www.world-semi.com/ws2812-family/

There is a serial data protocol used to control this string of 8 WS2812B LEDs.
- 3 8-bit bytes per LED are sent to control Red/Green/Blue.
  - The actual color order can vary; we will determine it by experimentation.
  - This allows 256 levels (0-255 for an unsigned 8-bit byte) for each of the colors Red/Green/Blue.
- The order of 3-byte RGB commands sent starts with data for the first LED in the string, then the second, etc.
- Each LED "consumes" its 3-byte RGB command from the data and then passes all the rest of the data down the line until there is a stopage.
- If there is a stopage of data for a certain specified amount of time, the string resets and the each LED will consume a new 3-byte value for its next RGB command.
- That is it! There are some more details on this protocol in [Resources](#resources "Resources") for the curious. 

I typically use the FastLED library to control these LEDs. It is a powerful library, but simple things are simple.
- One thing to note is that mixing three colors of LEDs (RBG) is baked deeply into the FastLED library. It appears to be quite difficult to adjust it to handle other combinations such as RBGW.

Because we are already using the USB serial port for debugging, we will dedicate a Digital pin as the "software" serial data line. FastLED will take care of using the Digital pin to send a serial data stream.

## The Circuit
[Top](#notes "Top")<br>
The circuit is simple; it is almost just a replacement of the LED from the previous [01_BlinkingLED](https://github.com/Mark-MDO47/ArduinoClass/tree/master/01_BlinkingLED "01_BlinkingLED") with the data pin from the RGB LED stick. There are also power and ground connections to the LED stick. **This circuit will be used in parts A through D of this section.** We will make a variation of the circuit for the "Persistence of Vision Stick" in part C, not to be confused with the "LED stick"
- https://github.com/Mark-MDO47/ArduinoClass/blob/master/02_PersistenceOfVision/02_PersistenceOfVision.pdf

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/02_PersistenceOfVision.png" width="750" alt="Image of wiring diagram for Persistence of Vision">

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/02_PersistenceOfVision_Fritzing.png" width="750" alt="Fritzing image of wiring diagram for Persistence of Vision">


The connections that we will make to the LED Stick are all on the upper left side of the schematic. The labels on the schematic are VSS, VDD, and DIN. However, the labels on our stick are GND, VCC and IN.<br>
![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/02_PersistanceOfVision_PartA_LEDstickSoldering.png "Image of 02_PersistanceOfVision: LED Stick Labeling")

The explanation for this is too complicated for a poor SW hack like myself so I will just point out the relationship:<br>
| Wire Color | Schematic | LED Stick | Purpose |
| --- | --- | --- | --- |
| Black | VSS | GND | Ground |
| Red | VDD | VCC | +5 Volts |
| White | DIN | IN | Serial Data |

OK I looked it up. When NPN transistors were in vogue, Vcc (positive) and Vee (ground) were for the Collector and Emitter, respectively. When FET logic took over, Vdd (positive) and Vss (ground) were for the Drain and and Source. When CMOS took over none of this made sense but apparently nobody was willing to change it again either.
- If you want to be a fanatic about Vss, Vdd, Vcc, and Vee you can look in the 1963 IEEE standard 255-1963 "Letter Symbols for Semiconductor Devices" (IEEE Std 255-1963).

Note that the connections from one LED to another are internal to the LED stick, so we only need to connect to the first LED. This is a good thing to try to do when using these individually addressable RGB LEDs. If you get close to 400 LEDs in one project (as I have) then you really do not want to have to solder all those connections between LEDs!

### TLDR Power and Wires
[Top](#notes "Top")<br>
The LED Sticks I ordered did not have pins on them for me to connect my jumpers to; I had to solder wires to them. I chose to use AWG24 wire for power and ground and AWG30 wire for the "serialdata" signal.<br>
The silicon coated multi stranded AWG30 is my go-to for wiring up my projects. It carries enough current for most of the projects I do, is extremely flexible, and the silicon insulation doesn't melt or burn when I am soldering. It is available in an astonishing variety of colors and not too expensive.<br>
The silicon coated multi stranded AWG24 wire for power and ground is in fact overkill for these class projects, but it reminds me to discuss a little more about how to decide what guage of wire to use.

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

With just 8 RGB LEDs the current draw of 336 milliamps (power 1.68 watts) worst case through the Arduino Nano should be OK, at least for a short time. If it got to be many more LEDs than that I would use a separate power source for the LEDs. At first in our projects I only use one color at a time on each LED and so limit power draw. Later, you will find that we set a parameter to limit the total power for each LED in the FastLED library. My plan is to use various software means to limit power to less than 168 milliamps or 0.84 watts for our 8-LED stick, probably significantly less.

Calculating wire size (Google for instance wire gauge ampacity 5v dc): the following link leads to information about power that can be safely passed through wire of different types and guages.
- https://www.powerstream.com/Wire_Size.htm

Looking up in the table referenced above, an AWG30 single strand wire meeting the specs of the site could carry 860 milliamps. We are using multi stranded AWG30 so we would not expect the full 5X safety margin on our design limit of 168 milliamps. Even so, I suspect that our AWG30 would be adequate. In fact I have used silicon coated multi stranded AWG30 to power two WS2812B 16 LED strands just due to ignorance of the issue. The margin of safety you want depends on other things too, such as the voltage drop you can tolerate (the table gives resistance data) and whether the electronics comes in contact with someone.

 An AWG24 single strand wire meeting the specs of the site could carry 3,500 milliamps. Obviously even multi strand AWG24 is overkill.

For my Graduation Cap project with 372 WS2812B LEDs I used a higher voltage to reduce the current and AWG20 multi stranded wire for power and ground because it came in contact with my daughters when operating the caps and I wasn't willing to chance any possibility of discomfort.

## The Code
[Top](#notes "Top")<br>
Now our code discussion section is going to get a little more involved.

### The Code - Timing Without Delays
[Top](#notes "Top")<br>
Open another Example program - Blink Without Delay - and let's compare it with Blink.

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/IDE_LoadBlinkWithoutDelay.png "Arduino IDE loading Blink Without Delay example program")

If for some reason you do not have access to that you can find a copy (from 2023-08) in this area under _Examples_ArduinoIDE/BlinkWithoutDelay
- https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode

The **setup()** code is essentially the same - just setting up the LED pin as OUTPUT.

There are some new "state" variables, defined before (and outside) of **setup()** and **loop()** - defining them this way means that the values will remain unchanged between calls to **loop()**.
```C
// Variables will change:
int ledState = LOW;             // ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 1;           // interval at which to blink (milliseconds)
```
The rules for C and C++ on scope and persistence actually have a lot more detail to them than I indicated above, but this will do for now.
- One item that I find particularly disturbing is that the definition of the **static** keyword has now diverged between C and C++. This seems like a bad trend; C and C++ had been compatible for many years. It seems to me they could have defined a static_cpp or something if they wanted a variant.

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

In contrast to our previous **loop()** design, this code design doesn't prevent the Arduino from doing other things (reading other sensors, controlling other devices) during the time we are waiting for the next **interval** to expire.
- In the "Blink" example code inside the **loop()** routine, the two **delay()** calls take almost 100% of the time. This is time during which the Arduino cannot be doing anything else.
- In the "Blink Without Delay" example code, the **loop()** code completes rapidly and is called again and again with only a few milliseconds in between loops. If there are other devices to handle and if the code for those devices is written in a similar manner, the Arduino can handle those also. It can do more than just Blink!

All this is caused because we are using the standard architecture for Arduino code, in which there are two routines **setup()** and **loop()** and no interrupts. If the system was multi-tasking either based on real-time interrupts or time slicing, then if one task does a delay it doesn't prevent another task from running. In our Arduino standard architecture, a delay means nothing else in the software world is happening until the delay finishes.

It is possible to enable and use interrupts in the Arduino, but this introduces complexities that sometimes cause trouble for the worlds best programmers - issues of code re-entrancy, software synchronization (i.e. semaphores), prioritization, non-deterministic latency, etc. The people who designed the Arduino chose to use this simpler architecture since the expected audience included many hobbyist and first-time programmers. This simpler architecture avoids many of the complexities mentioned above and thus helps to "keep us out of trouble". If you are more advanced, they do not prevent you from going further.
- See attachInterrupt(), detachInterrupt(), interrupts(), and noInterrupts() in https://reference.arduino.cc/reference/en/.

In all my Arduino projects, I have not needed to use interrupts; I have always stayed with the standard Arduino code architecture. Even for my latest Arduino Nano project I stuck with this architecture: the Rubber Band Gun which includes multiple buttons, multiple strings of WS2812B RGB LEDs, sound generation, bluetooth sound transfer, voice menus for reconfiguration, and motor control.
- https://github.com/Mark-MDO47/RubberBandGun

In our subsequent code, we will be using this "Blink Without Delay" style of coding, since we will be adding other devices that need to be handled.

### The Code - FastLED
[Top](#notes "Top")<br>
Kudos to Daniel Garcia and Mark Kriegsman for the FANTASTIC Arduino FastLED library and examples!!! Unfortunately Daniel Garcia passed away in a tragic accident a few years ago but the library is still being actively maintained.
- https://github.com/FastLED/FastLED
- https://github.com/FastLED/FastLED/blob/master/examples

If you haven't used FastLED with your Arduino IDE before you will probably need to load the library. This is easy! First start the Library Manager<br>
![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/IDE_ManageLibraries.png "Image of IDE starting Library Manager")

If FastLED is not installed, install the library that says "By Daniel Garcia". It is OK if there are several libraries that say something about FastLED, but be sure that the one by Daniel Garcia is installed too.

Below is a picture showing FastLED library **needs to be** installed<br>
![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/IDE_FastLED_needsInstall.png "Image of Library Manager showing FastLED needs to be installed")

Below is a picture of the Arduino IDE Library Manager showing FastLED library **is** installed<br>
![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/IDE_FastLED.png "Image of Library Manager showing FastLED is installed")

As mentioned, these WS2812B RGB LEDs use just power/ground/serialdata. Other RGB LEDs that FastLED controls use power/ground/serialdata/clock. There are some differences in the exact approach for using FastLED for those other LEDs compared to our WS2812B LEDs.

Here is what we do before **setup()**
- We include the FastLED file (**#include <FastLED.h>**)
- Either do or don't include a line that says FASTLED_USING_NAMESPACE
  - NOTE: some of the FastLED examples use the macro FASTLED_USING_NAMESPACE. This is OK to use but does nothing on the Arduino Nano; it only takes effect on spark platforms from sparkfun.com.
  - See https://github.com/FastLED/FastLED/issues/574
- We tell it what pin is to be used for serial communication.
  - We are not using the built-in USB HW serial port for FastLED; FastLED will take care of sending the serial data on a digital I/O pin controlled by software.
- We tell it how many LEDs are in the string attached to that pin
- We tell it what order the three bytes go onto the data line: RGB, RBG, GBR, etc.
- We use the typedef (a C-language construct for an activity-specific data type) **CRGB** to create an array for data storage from which the data is sent to the LEDs. We will call this array fastled_array, but the name is arbitrary.

Here is what we do in **setup()**
- We use **FastLED.addLeds(...)** to point at fastled_array and give it the information about what I/O pin, number of LEDs, and color order.

Here is what we do in **loop()**
- If it is time for the next data pattern:
  - We fill fastled_array with the RGB colors we want for each LED
  - We call **FastLED.show()** to send the color commands to the LED strip
  - We calculate what time the next data pattern should be sent

A preview - look here to see what our first attempt at using the LED strip will look like. I know, we just cannot get away from Blink; it is the "Hello World" of Arduinos.
- https://github.com/FastLED/FastLED/blob/master/examples/Blink/Blink.ino

## The Code - What are we Doing
Now we understand
- the basics of persistance of vision
- how to organize our code using timers so we can respond rapidly to many sensors and devices
- how to detect the state of the button
- how to talk to the LED strip

Now the question is: what are we trying to do?

The ultimate goal is to make a wand that we can wave that makes our eyes see patterns. We will use the button to stop and restart the patterns. Although much more elaborate possibilities could be pursued, the plan for this project is to implement a few different patterns depending on how much time we want to spend on it
- Blink - talk to just the first LED, make sure we know the color order
  - https://github.com/FastLED/FastLED/blob/master/examples/Blink/Blink.ino
- Sawtooth - a triangular wave bouncing from top to bottom and back
- Oval - a pattern that appears to be a set of ovals; maybe even appear to be a bubble-blower
- Hello World! - a late entry but a classic!
- DemoReel - Mark Kriegsman's classic DemoReel100.ino
  - https://github.com/FastLED/FastLED/tree/master/examples/DemoReel100

The LED pattern code for Sawtooth, Oval, and Hello World will pretty much done from scratch using the FastLED library. The LED pattern code for Blink and DemoReel will be derived from example FastLED code. DemoReel will show some of the incredible capabilities of the FastLED library for generating beautiful patterns with little code.

The coding method for Sawtooth and Oval/Hello are different. This is done on purpose to show examples of manipulating the data to produce desired patterns. The final version of Oval.ino will be able to produce any of the patterns Sawtooth, Oval, or Hello World and either use rainbow colors or all red.

## Resources
[Top](#notes "Top")<br>

### WS2812B Protocol
[Top](#notes "Top")<br>
The WS2812B protocol can be found in this spec:
* https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf

A higher level depiction of this output protocol in action (taken from the spec) is shown here. First is the serial head-to-tail cascade architecture of the LEDs:

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/CascadeLED_SerialProtocol_arch.png "WS2812b RGB serial cascade architecture (from spec)")

Then the high-level serial output protocol as seen by each of the LEDs in the architecture diagram. Note how each LED "consumes" the first set of bytes and passes on the rest.

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/WS2812B_RGB_SerialProtocol.png "WS2812b RGB serial output protocol (from spec)")

In summary, there is a serial data protocol used to control strings of WS2812B RGB LEDs.
- 3 8-bit bytes per LED are sent to control Red/Green/Blue.
  - The actual color order can vary; we determine it by experimentation.
  - This allows 256 levels (0-255) for each of the colors Red/Green/Blue.
- The order of 3-byte RGB commands sent starts with data for the first LED in the string, then the second, etc.
- Each LED "consumes" its 3-byte RGB command from the data and then sends all the rest of the data down the line.
- If there is a stopage of data for a certain specified amount of time, the string resets and the first LED will consume the next RGB command.
