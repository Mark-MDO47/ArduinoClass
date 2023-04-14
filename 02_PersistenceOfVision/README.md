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

