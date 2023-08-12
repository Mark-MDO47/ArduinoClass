# NOTES

## Back to Root of Class
Click this link to back to go back to the root of the Arduino class
- https://github.com/Mark-MDO47/ArduinoClass/tree/master


## Table of Contents
* [Top](#notes "Top")
* [Arduino IDE](#arduino-ide "Arduino IDE")
* [C and C++ Languages used in Arduino IDE](#c-and-cplusplus-languages-used-in-arduino-ide "C and C++ Languages used in Arduino IDE")
* [Schematics and Fritzing](#schematics-and-fritzing "Schematics and Fritzing")
  * [KiCad - optional](#kicad-\--optional "KiCad - optional")
  * [Fritzing - optional](#fritzing-\--optional "Fritzing - optional")

## Arduino IDE
[Top](#notes "Top")<br>
**It will be helpful to install the Arduino IDE on your laptop before the start of the class if you are planning to use your laptop to connect to the test systems during the class.**<br>At this time the latest version is 2.04 and can be installed on Windows, Macintosh, and Linux.
- https://www.arduino.cc/en/software

If you have a Chromebook I have not found a way to install the latest version, but the older version 1.8.19 can be installed on modern Chromebooks and will work fine for this class. Search for "Legacy IDE (1.8.X)" in the above link. The following YouTube video describes this installation. NOTE: to play youtube and keep this tab open you must right-click the link and select to play in a new tab.
- https://www.youtube.com/watch?v=2cve6n4LZqI

It is possible to use the "Arduino Cloud". This method is not used in this class.

## C and Cplusplus Languages used in Arduino IDE
[Top](#notes "Top")<br>
The Arduino IDE uses a variant of the C++ language. You can program in a C++ style or a C style. The code that we will use in this course will be quite straighforward and should be understandable if you know any computer language. One thing to note about C/C++: array indices start with zero.
- https://reference.arduino.cc/reference/en/

## Schematics and Fritzing
[Top](#notes "Top")<br>

### Schematics
[Top](#notes "Top")<br>
Simple schematic diagrams are used throughout this course. These use special symbols to represent parts of an electrical circuit - such as resistors and LEDs - and lines to represent the connections.

Example schematic wiring diagram showing a physical representation of an Arduino Nano, a resistor, and a Light Emitting Diode or LED:<br>
<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/01_BlinkingLED_part_A_Schematic.png" width="150" alt="Example KiCad schematic">

 I sometimes call my schematics "schematic wiring diagrams" because I don't quite follow the rules of the standards organizations, although I reserve the right to just call them schematics.
- I often show all power and ground connections as wires rather than going to standard voltage and ground symbols. I do this to make these connections more visible, because when assembling or soldering together a circuit, one of my most common errors is to forget to connect a power or ground pin.
- I don't always follow the "rules" about placement of all inputs on one side and all outputs on the other side; instead I make my own symbols for such things as Arduinos and other chips and modules that show the physical placement of the pins on the part. I do this because I often wire directly from the schematic and find it bewildering to have to figure out the physical placement somewhere other than the schematic.

### Fritzing
[Top](#notes "Top")<br>
I have included Fritzing images for most of the projects in this course. These give a more physical view of how to wire an electrical circuit than a schematic. They are commonly used to illustrate breadboard projects and can even show the breadboard itself.

Example Fritzing with the same components as the above schematic and with the addition of the breadboard:<br>
<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/01_BlinkingLED_part_A_Fritzing.png" width="150" alt="Example Fritzing Image">

Fritzing is the name of the organization that produces the Fritzing tool that produces these images. This leads to some linguistic confusion as I often refer to these images using the noun Fritzing, the activity I do to generate the image using the verb Fritzing, the saved file for the Fritzing tool using the noun Fritzing, and the saved generated special part for the tool using the adjective Fritzing: a Fritzing part (which sort of sounds like cursing). In my defense I offer the following quote from today's Wikipedia entry on "-ing":
- "-ing" is a suffix used to make one of the inflected forms of English verbs. This verb form is used as a present participle, as a gerund, and sometimes as an independent noun or adjective.

## KiCad - optional
[Top](#notes "Top")<br>
I use the free schematic editor KiCad for capturing "schematic wiring diagrams". It can also do Spice simulations, PCB board layout, Gerber File generation, Bill of Materials --- the whole works!
- https://www.kicad.org/

This is not needed for the class but is a fantastic tool for those that are interested. See the larger KiCad discussion in the resources section for more details.
- https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/README.md

## Fritzing - optional
[Top](#notes "Top")<br>
I use the Fritzing tool **(costs about $10)** to generate depictions of our breadboard projects. This tool can also do simulations and can have a PCB board made with your breadboard project.
- https://fritzing.org/

This is not needed for the class but is a fun tool for those that are interested. See the larger Fritzing and InkScape discussion in the resources section for more details.
- https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/README.md
