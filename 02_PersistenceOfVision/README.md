# NOTES

**Table of Contents**
* [Top](#notes "Top")
* [Human Vision Persistence](#human-vision-persistence "Human Vision Persistence")
* [WS2811 and WS2812B individually addressable color LEDs](#ws2811-and-ws2812b-individually-addressable-color-leds "WS2811 and WS2812B individually addressable color LEDs")
* [The Circuit](#the-circuit "The Circuit")
* [The Code](#the-code "The Code")
* [Resources](#resources "Resources")

## Human Vision Persistence
Louis Le Prince is generally credited to be the first person to record and show moving pictures.
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

There is a serial data protocol used to control this string of 8 LEDs.
- 3 8-bit bytes per LED are sent to control Red/Green/Blue.
  - The actual color order can vary; I determine it by experimentation.
  - This allows 256 levels (0-255) for each of the colors Red/Green/Blue.
- The order of 3-byte RGB commands sent starts with data for the first LED in the string, then the second, etc.
- Each LED "consumes" its 3-byte RGB command from the data and then sends all the rest of the data down the line.
- If there is a stopage of data for a certain specified amount of time, the string resets and the first LED will consume the next RGB command.

I typically use the FastLED library to control these LEDs. It is a powerful library, but simple things are simple.

Because we are already using the USB serial port for debugging, we will dedicate a Digital pin as the "software" serial data line.

## The Circuit

The circuit is simple; it is almost just a replacement of the LED from the previous [01_BlinkingLED](https://github.com/Mark-MDO47/ArduinoClass/tree/master/01_BlinkingLED "01_BlinkingLED") with the data pin from the RGB LED stick. There are also power and ground connections to the LED stick.
- https://github.com/Mark-MDO47/ArduinoClass/blob/master/02_PersistenceOfVision/02_PersistenceOfVision.pdf

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/02_PersistenceOfVision.png" width="501" height="265">

With just 8 RGB LEDs the power draw through the Arduino Nano should be OK. If it got to be many more than that I would use a separate power source for the LEDs.

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

This code design doesn't prevent the code from doing other things (reading other sensors, controlling other devices) during the time we are waiting for the next **interval** to expire.
- In the Blink code inside the **loop()** routine, the two **delay()** calls take almost 100% of the time. This is time during which the Arduino cannot be doing anything else.
- In the "Blink Without Delay" code, the **loop()** code completes rapidly and is called again and again with only a few milliseconds in between loops. If there are other devices to handle and if the code for those devices is written in a similar manner, the Arduino can handle those also. It can do more than just Blink!

All this is caused because we are using the standard architecture for Arduino code, in which there are two routines **setup()** and **loop()** and no interrupts. If the system was multi-tasking either based on real-time interrupts or time slicing and if one task does a delay it doesn't prevent another task from running.

It is possible to enable and use interrupts in the Arduino, but this introduces complexities that sometimes cause trouble for the worlds best programmers - issues of code re-entrancy, software synchronization (i.e. semaphores), prioritization, variable latency, etc. The people who designed the Arduino chose to use this simpler architecture since the expected audience included many hobbyist and first-time programmers. This simpler architecture avoids many of the complexities mentioned above and thus helps to "keep us out of trouble".
- See attachInterrupt(), detachInterrupt(), interrupts(), and noInterrupts() in https://reference.arduino.cc/reference/en/.

In our subsequent code, we will be using this "Blink Without Delay" style of coding, since we will be adding other devices that need to be handled.

### The Code - FastLED

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

