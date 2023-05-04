# Resources

**Table of Contents**
* [Top](#resources "Top")
* [Arduino IDE](#arduino-ide "Arduino IDE")
* [The Computer Language used in the Arduino IDE](#the-computer-language-used-in-the-arduino-ide "The Computer Language used in the Arduino IDE")
* [Arduino Nano and ATMEGA 328P](#arduino-nano-and-atmega-328p "Arduino Nano and ATMEGA 328P")
* [My favorite Arduino variant - ESP32](#my-favorite-arduino-variant-\--esp32 "My favorite Arduino variant - ESP32")
* [EEPROM to save configuration](#eeprom-to-save-configuration "EEPROM to save configuration")
* [PROGMEM and F macro to save RAM](#progmem-and-f-macro-to-save-ram "PROGMEM and F macro to save RAM")
* [YX5200 Audio Player](#yx5200-audio-player "YX5200 Audio Player")
* [KCX_BT_EMITTER Bluetooth Audio Transmitter](#kcx_bt_emitter-bluetooth-audio-transmitter "KCX_BT_EMITTER Bluetooth Audio Transmitter")
* [UBEC](#ubec "UBEC")
* [Solderless Breadboard](#solderless-breadboard "Solderless Breadboard")
* [9 10K Ohm resistors one package](#9-10K-ohm-resistors-one-package "9 10K Ohm resistors one package")
* [KiCad](#kicad "KiCad")
* [Projects on the Web](#projects-on-the-web "Projects on the Web")
* [TLDR Power and Wires](#tldr-power-and-wires "TLDR Power and Wires")

## Arduino IDE
[Top](#resources "Top")<br>
It will be helpful to install the Arduino IDE on your laptop before the start of the class if you are planning to use your laptop to connect to the test systems during the class. At this time the latest version is 2.04 and can be installed on Windows, Macintosh, and Linux.
- https://www.arduino.cc/en/software

If you have a Chromebook there doesn't seem to be a way to install the latest IDE version, but the older version 1.8.19 can be installed on modern Chromebooks and will work fine for this class. Search for "Legacy IDE (1.8.X)" in the above link. The following YouTube describes this installation. NOTE: to play youtube and keep this tab open you must right-click the link and select to play in a new tab.
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

## EEPROM to save configuration
These Arduino Nanos have 32Kbyte of FLASH memory (program storage), 2Kbyte of SRAM, and 1Kbyte of EEPROM.
- FLASH memory (no acronym) was an offshoot of EEPROM. For the Arduino Nano it is erasable and writeable in blocks of many consecutive bytes.
- EEPROM (Electrically Eraseable Programmable Read-Only Memory) is, for the Arduino Nano, erasable and writeable in blocks of one byte. The Read-Only part seems strange, but the idea is that we can erase it and then program (write) it but we cannot write it in one step.
- SRAM (Static Random Access Memory) is, for the Arduino Nano, readable and writeable in blocks of one byte. There is typically no published limit on the number of times it can be read or written.

Note: 1Kbyte (capital K) typically means 1,024 bytes; 1,024 is considered to be the "binary thousand) since it is 2 to the power 10 and 1,000 is 10 to the power 3. 1kbyte (lower case k) is often decimal 1,000. Sometimes, however, the person writing these numbers has a typo so be forewarned.

In Arduino practice:
- FLASH memory is used to store the program code. It can also be used to store constant strings and other data (see section on **PROGMEM and F macro** in https://github.com/Mark-MDO47/ArduinoClass/tree/master/99_Resources).
- SRAM is used for variables that change often during program execution. If you write **static int xxx = 5;** or **int func(int a) { int xxx; xxx = a+1; return(xxx); };**, then **xxx** will be in SRAM.
- EEPROM is used to save things that are
  - changed during program execution
  - the changed state needs to be remembered the next time the Arduino powers-on

The Arduino EEPROM interface is simplicity itself:
- early in the *.ino file (maybe after #include <FastLED.h>) put the line **#include <EEPROM.h>**
- when you want to write a byte to EEPROM, call **EEPROM.write(address, byteValue);**
- when you want to read a byte from EEPROM, call **readValue = EEPROM.read(address);**

Given that FLASH is written only when we change the program and EEPROM would be written while the program is running, it is likely that EEPROM will use up all its erase/write cycles before FLASH will. In Arduino, the EEPROM is specified to handle 100,000 erase/write cycles for each position (byte). EEPROM reads are unlimited. However, the Arduino Nanos I use are cheap $2 clones instead of the official Arduino Nano at close to $25; therfore I don't want to push it. As you will see, I use a simple routine I wrote called **eeprom_store_if_change** that first reads the EEPROM byte and if it is the same value we were about to write it skips the write. This is a very simple routine and I am sure you could easily write your own version of it. Otherwise you can use my version in https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/AllThePatterns

When the Arduino powers up, how will it know if the parameters stored in EEPROM are valid or if it is a new Arduino out of the bag and the values are random? To handle this I store a simple checksum along with the parameters in EEPROM. If the EEPROM checksum doesn't match the EEPROM configuration data then I store a fresh set of configuration data in EEPROM.
Because I use a one-byte checksum (you could use a more elaborate checksum if you want) there is a one in 256 chance that random data will have a checksum that matches it. Because I am lazy, I accept that chance: if the first time I program an Arduino it acts crazy then I can either write something to the configuration value or I can one-time change the expected value of the checksum to be different (for example; 1 + the normal checksum) and then it will put good power-on configuration data in EEPROM. Later I can either leave the checksum expectation at this new value or change it back.

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

## YX5200 Audio Player
[Top](#resources "Top")<br>
The YX5200 Audio Player can drive speakers or headphones from sound files you place on its SD card slot. About $2 in packs of 5.<br>
Placing the audio files onto the SD card requires special care. Also there are many clone versions with different chips and different firmware levels. The following link shows the method I used to get reliable performance.
- https://github.com/Mark-MDO47/AudioPlayer-YX5200

![alt text](https://github.com/Mark-MDO47/RubberBandGun/raw/master/PartsInfo/YX5200_MP3player.png "Image of YX5200 Audio Player")

## KCX_BT_EMITTER Bluetooth Audio Transmitter
[Top](#resources "Top")<br>
The KCX_BT_EMITTER can take the audio from the YX5200 and send it to a bluetooth speaker. The KCX_BT_EMITTER supports Bluetooth 4.1 is about $3.50 on Ebay or $1.50 on aliexpress.com. This is the one I am familiar with. I have heard rumors of updated versions supporting stereo and/or Bluetooth 5.x but have no experience with these.<br>
The information on commanding the KCX_BT_EMITTER to auto-pair to a specific speaker is in Chinese. There is a trick to getting a low-noise connection between this and the YX5200. I have pointers to details and a utility I wrote to help with commanding/pairing plus information on the low-noise connection in the following link.
- https://github.com/Mark-MDO47/BluetoothAudioTransmitter_KCX_BT_EMITTER

![alt text](https://github.com/Mark-MDO47/BluetoothAudioTransmitter_KCX_BT_EMITTER/raw/master/images/KCX_BT_Board_IMG_1351.png "Image of KCX_BT_EMITTER Bluetooth Audio Transmitter")

## UBEC
[Top](#resources "Top")<br>
A UBEC (Universal Battery Eliminator Circuit) is often used to power an Arduino and perhaps some of its other circuits as well. This device will typically take as input something in the range of about 6V to 28V DC and usually has selectable output voltage of either 5V or 6V. I often connect a 9V battery as input to a UBEC or two or more 18650 batteries. If there is a heavy draw somewhere in your circuit that is far from the batteries, you can increase the voltage of your source and thus reduce the current in the wires.<br>
![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/UBEC.png "Image of typical UBEC")

## Solderless Breadboard
We will be using a solderless breadboard to rapidly implement parts of our circuit. Connections are made by plugging wires or components into the holes in the board. A youtube video of connecting LEDs to a solderless breadboard can be found at this link.  NOTE: to play youtube and keep this tab open you must right-click the link and select to play in a new tab.
- https://www.youtube.com/watch?v=UvS9Wf2BoyE

A good guide to solderless breadboards can be found at this link:
- https://protosupplies.com/guide-to-solderless-breadboards/

Here from the above link is an image of a typical solderless breadboard.

![alt text](https://protosupplies.com/wp-content/uploads/2018/12/Breadboard-Details.jpg "Image of typical solderless breadboard from protosupplies.com")

It might be worthwhile to look the above image over in detail; we will be using this breadboard in this class. Try to find which pins distribute power and ground vertically (the long way on the breadboard), which pins distribute signals side-to-side, and how far the signals get distributed in these directions.

Something that may help, again from that protosupplies.com article about breadboards, is the following image of a breadboard from the inside, showing the metal that connects the pins on the top of the breadboard.

![alt text](https://protosupplies.com/wp-content/uploads/2018/12/Breadboard-Contacts-Back-Side-2.jpg "Image of typical solderless breadboard from protosupplies.com")

Be aware that a circuit laid out on such a solderless breadboard can then be transferred to a solderable breadboard PCB board fairly easily. See the comparison between these two below.

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/Breadboard_Solderboard.png "Image of a solderless breadboard and a solderable breadboard PCB board")

## 9 10K Ohm resistors one package
[Top](#resources "Top")<br>
This handy device allows the use of one component to give 10 individual pullups. This is handy for instance if your project has a lot of buttons.
- https://www.digikey.com/en/products/detail/bourns-inc/4610X-AP1-103LF/3741070

![alt text](https://media.digikey.com/photos/Bourns%20Photos/4610X%20SERIES.jpg "Image of 9 10K Ohm resistors one package")

## KiCad
[Top](#resources "Top")<br>
I use the free schematic editor KiCad for capturing schematics (actually what I do might better be called wiring diagrams). KiCad can also do Spice simulations, PCB board layout, Gerber File generation, Bill of Materials --- the whole works!
- https://www.kicad.org/

This is not needed for the class but is a fantastic tool for those that are interested. There are many YouTube videos describing the basics of KiCad usage.

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

With just 8 RGB LEDs the current draw of 336 milliamps (power 1.68 watts) worst case through the Arduino Nano should be OK. If it got to be many more than that I would use a separate power source for the LEDs. At first in our projects I only use one color at a time on each LED and so limit power draw. Later, you will find that we set a parameter to limit the total power for each LED in the FastLED library. My plan is to use various software means to limit power to less than 168 milliamps or 0.84 watts, probably significantly less.

Calculating wire size (Google for instance wire gauge ampacity 5v dc): the following link leads to information about power that can be safely passed through wire of different types and guages.
- https://www.powerstream.com/Wire_Size.htm

Looking up in the table referenced above, an AWG30 single strand wire meeting the specs of the site could carry 860 milliamps. We are using multi stranded AWG30 so we would not expect the full 5X safety margin. Even so, I suspect that our AWG30 would be adequate. In fact I have used silicon coated multi stranded AWG30 to power two WS2812B 32 LED strands just due to ignorance of the issue. The margin of safety you want depends on other things too, such as the voltage drop you can tolerate (the table gives resistance data) and whether the electronics comes in contact with someone.

 An AWG24 single strand wire meeting the specs of the site could carry 3,500 milliamps. Obviously AWG24 multi strand is overkill, even though we are using multi stranded.

For my Graduation Cap project with 372 WS2812B LEDs I used AWG20 multi stranded wire for power and ground because it came in contact with my daughters when operating the caps and I wasn't willing to chance any possibility of discomfort.
