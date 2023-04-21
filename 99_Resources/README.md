# Resources

**Table of Contents**
* [Top](#resources "Top")
* [Arduino IDE](#arduino-ide "Arduino IDE")
* [The Computer Language used in the Arduino IDE](#the-computer-language-used-in-the-arduino-ide "The Computer Language used in the Arduino IDE")
* [Arduino Nano and ATMEGA 328P](#arduino-nano-and-atmega-328p "Arduino Nano and ATMEGA 328P")
* [My favorite Arduino variant - ESP32](#my-favorite-arduino-variant-\--esp32 "My favorite Arduino variant - ESP32")
* [PROGMEM and F macro to save RAM](#progmem-and-f-macro-to-save-ram "PROGMEM and F macro to save RAM")
* [KiCad](#kicad "KiCad")
* [Projects on the Web](#projects-on-the-web "Projects on the Web")
* [TLDR Power and Wires](#tldr-power-and-wires "TLDR Power and Wires")

## Arduino IDE
[Top](#resources "Top")<br>
It will be helpful to install the Arduino IDE on your laptop before the start of the class if you are planning to use your laptop to connect to the test systems during the class. At this time the latest version is 2.04 and can be installed on Windows, Macintosh, and Linux.
- https://www.arduino.cc/en/software

If you have a Chromebook I have not found a way to install the latest version, but the older version 1.8.19 can be installed on modern Chromebooks and will work fine for this class. Search for "Legacy IDE (1.8.X)" in the above link. The following YouTube describes this installation. NOTE: to play youtube and keep this tab open you must right-click the link and select to play in a new tab.
- https://www.youtube.com/watch?v=2cve6n4LZqI

It is possible to use the "Arduino Cloud". This method is not used in this class.

## The Computer Language used in the Arduino IDE
[Top](#resources "Top")<br>
The Arduino IDE uses a variant of the C++ language. You can program in a C++ style or a C style. The code that we will use in this course will be quite straighforward and should be understandable if you know any computer language. One thing to note about C/C++: array indices start with zero.
- https://reference.arduino.cc/reference/en/

## Arduino Nano and ATMEGA 328P
[Top](#resources "Top")<br>
We will be using Arduino Nano clones in our projects. You can ignore the following for our class; this is for follow-up by interested persons.

Lots of info on the Arduino Nano is found here (diagrams, not schematics)
* https://www.circuitstoday.com/arduino-nano-tutorial-pinout-schematics

The ATMEGA 328P chip used in the Arduino Nano is described here
* http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf

Mapping the ports to the internal registers is described here
* https://www.arduino.cc/en/Reference/PortManipulation

## My favorite Arduino variant - ESP32
[Top](#resources "Top")<br>
Here is some documentation from the maker of the chipset and many modules for ESP32
* https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html

A few quotes from above:
- ESP32 is a single 2.4 GHz Wi-Fi-and-Bluetooth SoC (System On a Chip) designed by Espressif Systems.
- The ESP32 series is available as a chip or module.

Some of the ESP32 modules that I use are currently less than $30 for quantity 5:
- https://www.amazon.com/gp/product/B08DQQ8CBP

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/ESP32.png" width="475" height="476">

An ESP32 module has MUCH more RAM and program storage than the original Arduinos, is much faster, and comes complete with easy-to-use on-board WIFI and Bluetooth. It has dual-CPUs for expert users.

On the other hand, ESP32 modules work with 3.5V instead of 5V so you need to be prepared to handle that. For instance I use the SN74HCT125N quadruple bus buffer and voltage translator to convert from 3.5 Volt outputs to 5 Volt outputs.

The ESP32 is also physically wider than the Arduino Nano and doesn't fit well on a standard solderless breadboard. I use two small breadboards to mount an ESP32 as shown below.

| Top View | Side View |
| --- | --- |
| <img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/ESP32_Breadboard_1.png" width="150" alt="Overhead View of ESP32 on two breadboards"> | <img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/ESP32_Breadboard_2.png" width="150" alt="Side View of ESP32 on two breadboards"> |

## PROGMEM and F macro to save RAM
[Top](#resources "Top")<br>
The following references show how to save constant values such as strings in program memory instead of using precious Arduino RAM:
- https://reference.arduino.cc/reference/en/language/variables/utilities/progmem/
- https://www.instructables.com/Arduino-String-Manipulation-Using-Minimal-Ram/

Here is a simple example of usage PROGMEM and "F" macro for Serial.print*():

```C
#include "Arduino.h"

#define USE_PROGMEM true                     // set true to keep big const items in FLASH (PROGMEM keyword)


// somewhere in your code 
#if USE_PROGMEM
  Serial.println(F("My strings are stored in PROGMEM"));
#else // not USE_PROGMEM
  Serial.println("My strings are stored in RAM");
#endif // USE_PROGMEM
```

Using PROGMEM for data storage of large tables is possible but a little more complex. Read the docs or talk to me.

## KiCad
[Top](#resources "Top")<br>
I use the free schematic editor KiCad for capturing schematics (actually what I do might better be called wiring diagrams). KiCad can also do Spice simulations, PCB board layout, Gerber File generation, Bill of Materials --- the whole works!
- https://www.kicad.org/

This is not needed for the class but is a fantastic tool for those that are interested.

## Projects on the Web
[Top](#resources "Top")<br>
Here are a few potential projects on the web that have caught my eye
- https://hackaday.io/discover
- https://all3dp.com/2/arduino-projects-best-sites/
- https://all3dp.com/2/most-useful-arduino-projects/
- https://all3dp.com/2/best-arduino-alternatives/
- https://www.instructables.com/DIY-Tinfoil-Ribbon-Speaker/
- https://www.instructables.com/Galaxy-Mood-Lamp/
- https://blog.arduino.cc/2022/04/06/the-o-clock-is-a-fun-way-to-check-the-current-time/
- https://www.instructables.com/O-Clock/
- https://www.instructables.com/Persistence-of-Vision-LED-Staff/
- https://povstaff.readthedocs.io/en/latest/
- https://learn.adafruit.com/pov-dotstar-double-staff
- https://www.instructables.com/LED-Kaleidoscope-1/
- https://www.instructables.com/The-Neopixel-LED-Vase/
- https://www.instructables.com/How-to-Make-an-Old-school-Neon-Street-Sign/
- https://blog.arduino.cc/2023/01/27/the-cwvox-is-a-simple-device-that-converts-voice-commands-into-morse-code-keying/
- https://blog.arduino.cc/
- https://shop.m5stack.com/collections/m5-controllers/products/esp32-basic-core-iot-development-kit-v2-6
- https://randomnerdtutorials.com/esp32-over-the-air-ota-programming/
- https://randomnerdtutorials.com/esp32-esp8266--https-ssl-tls/
- https://randomnerdtutorials.com/esp32-wireless-communication-protocols/#lora
- https://randomnerdtutorials.com/esp32-bluetooth-classic-arduino-ide/
- https://rntlab.com/module-1/welcome-build-web-servers/
- https://randomnerdtutorials.com/esp32-wireless-communication-protocols/#lora
- https://randomnerdtutorials.com/esp32-bluetooth-classic-arduino-ide/
- https://www.instructables.com/The-Process-of-Designing-and-Ordering-a-PCB-Signal/
- https://www.instructables.com/How-to-Assemble-a-PCB-With-Tiny-SMD-Parts/

## TLDR Power and Wires
The LED Sticks I ordered did not have pins on them for me to connect my jumpers to; I had to solder wires to them. I chose to use AWG24 wire for power and ground and AWG30 wire for the "serialdata" signal.<br>
The silicon coated multi stranded AWG30 is my go-to for wiring up my projects. It carries enough current for most of the projects I do, is extremely flexible, and the silicon insulation doesn't melt or burn when I am soldering. It is available in an astonishing variety of colors and not too expensive.<br>
The silicon coated multi stranded AWG24 wire for power and ground is in fact overkill for these projects, but it reminds me to discuss a little more about how to decide what guage of wire to use.


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

With just 8 RGB LEDs the current draw of 336 milliamps (power 1.68 watts) worst case through the Arduino Nano should be OK. If it got to be many more than that I would use a separate power source for the LEDs. At first in our projects I only use one color at a time on each LED and so limit power draw. Later, you will find that we set a parameter to limit the total power for each LED in the FastLED library.

Calculating wire size (Google for instance wire gauge ampacity 5v dc): the following link leads to information about power that can be safely passed through wire of different types and guages.
- https://www.powerstream.com/Wire_Size.htm

My plan is to use various software means to limit power to less than 21 milliamps or 0.85 watts. Looking up in the table referenced above, an AWG30 single-strand wire meeting the specs of the site could carry 142 milliamps. We are using multi stranded AWG30 but even so, I suspect that would be adequate. In fact I have used silicon coated multi stranded AWG30 to power an Arduino Nano plus two WS2812B 32 LED strands. The margin of safety you want depends on other things too, such as the voltage drop you can tolerate and whether the electronics comes in contact with someone.

For my Graduation Cap project with 372 WS2812B LEDs I used AWG20 wire for power and ground because it came in contact with my daughters when operating the caps.
