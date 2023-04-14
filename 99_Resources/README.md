# Resources

## Arduino IDE
It will be helpful to install the Arduino IDE on your laptop before the start of the class if you are planning to use your laptop to connect to the test systems during the class. At this time the latest version is 2.04 and can be installed on Windows, Macintosh, and Linux.
- https://www.arduino.cc/en/software

If you have a Chromebook I have not found a way to install the latest version, but the older version 1.8.19 can be installed on modern Chromebooks and will work fine for this class. Search for "Legacy IDE (1.8.X)" in the above link. The following YouTube describes this installation.
- https://www.youtube.com/watch?v=2cve6n4LZqI

It is possible to use the "Arduino Cloud". This method is not used in this class.

## The C/C++ Language used in the Arduino IDE

The Arduino IDE uses a variant of the C++ language. You can program in a C++ style or a C style. The code that we will use in this course will be quite straighforward and should be understandable if you know any computer language. One thing to note about C/C++: array indices start with zero.
- https://reference.arduino.cc/reference/en/

## KiCad (optional)
I use the free schematic editor KiCad for capturing schematics. It can also do Spice simulations, PCB board layout, Gerber File generation, Bill of Materials --- the whole works!
- https://www.kicad.org/

This is not needed for the class but is a fantastic tool for those that are interested.

## Arduino Nano and ATMEGA 328P
We will be using Arduino Nano clones in our projects. You can ignore the following for our class; this is for follow-up by interested persons.

Lots of info on the Arduino Nano is found here (diagrams, not schematics)
* https://www.circuitstoday.com/arduino-nano-tutorial-pinout-schematics

The ATMEGA 328P chip used in the Arduino Nano is described here
* http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf

Mapping the ports to the internal registers is described here
* https://www.arduino.cc/en/Reference/PortManipulation

## My favorite Arduino clone - ESP32
* https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html

A few quotes from above:
- ESP32 is a single 2.4 GHz Wi-Fi-and-Bluetooth SoC (System On a Chip) designed by Espressif Systems.
- The ESP32 series is available as a chip or module.

Some of the ESP32 modules that I use are currently less than $30 for quantity 5:
- https://www.amazon.com/gp/product/B08DQQ8CBP

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/ESP32.png "ESP32 module from above")

An ESP32 module has MUCH more RAM and program storage than the original Arduinos, is much faster, and comes complete with easy-to-use on-board WIFI and Bluetooth. It has dual-CPUs for expert users.

On the other hand, ESP32 modules work with 3.5V instead of 5V so you need to be prepared to handle that. For instance I use the SN74HCT125N quadruple bus buffer and voltage translator to convert from 3.5 Volt outputs to 5 Volt outputs.

Also, ESP32 modules are larger than an Arduino Nano and don't fit well on typical breadboards. I sometimes use two breadboards with space in between and put the ESP32 in the middle.

## PROGMEM and "F" macro to save RAM
The following references show how to save constant values such as strings in program memory instead of using precious Arduino RAM:
- https://reference.arduino.cc/reference/en/language/variables/utilities/progmem/
- https://www.instructables.com/Arduino-String-Manipulation-Using-Minimal-Ram/
