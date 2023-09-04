# Resources

## Back to Root of Class
Click this link to back to go back to the root of the Arduino class
- https://github.com/Mark-MDO47/ArduinoClass/tree/master


**Table of Contents**
* [Top](#resources "Top")
* [Arduino IDE](#arduino-ide "Arduino IDE")
* [The Computer Language used in the Arduino IDE](#the-computer-language-used-in-the-arduino-ide "The Computer Language used in the Arduino IDE")
* [Arduino Nano and ATMEGA 328P](#arduino-nano-and-atmega-328p "Arduino Nano and ATMEGA 328P")
* [My favorite Arduino variant - ESP32](#my-favorite-arduino-variant-\--esp32 "My favorite Arduino variant - ESP32")
* [EEPROM to save configuration](#eeprom-to-save-configuration "EEPROM to save configuration")
* [PROGMEM and F macro to save RAM](#progmem-and-f-macro-to-save-ram "PROGMEM and F macro to save RAM")
* [Solderless Breadboard](#solderless-breadboard "Solderless Breadboard")
* [YX5200 Audio Player](#yx5200-audio-player "YX5200 Audio Player")
  * [Saturn Sounds from Cassini](#saturn-sounds-from-cassini "Saturn Sounds from Cassini")
  * [Text-to-Speech Robotic Sounds](#text\-to\-speech-robotic-sounds "Text-to-Speech Robotic Sounds")
* [KCX_BT_EMITTER Bluetooth Audio Transmitter](#kcx_bt_emitter-bluetooth-audio-transmitter "KCX_BT_EMITTER Bluetooth Audio Transmitter")
* [DF2301QG Voice Recognizer and Command Module](#df2301qg-voice-recognizer-and-command-module "DF2301QG Voice Recognizer and Command Module")
* [UBEC Universal Battery Eliminator Circuit](#ubec-universal-battery-eliminator-circuit "UBEC Universal Battery Eliminator Circuit")
* [9 10K Ohm resistors one package](#9-10k-ohm-resistors-one-package "9 10K Ohm resistors one package")
* [SN74HCT125N 3-state Buffer](#sn74hct125n-3\-state-buffer "SN74HCT125N 3-state Buffer")
* [Schematics KiCad and Fritzing](#schematics-kicad-and-fritzing "Schematics KiCad and Fritzing")
  * [Schematics](#schematics "Schematics")
  * [KiCad](#kicad "KiCad")
  * [Fritzing](#fritzing "Fritzing")
* [Projects on the Web](#projects-on-the-web "Projects on the Web")
* [TLDR Decimal and Binary and Hexadecimal](#tldr-decimal-and-binary-and-hexadecimal "TLDR Decimal and Binary and Hexadecimal")
* [TLDR Power and Wires](#tldr-power-and-wires "TLDR Power and Wires")
* [TLDR WS2812B Serial Protocol](#tldr-ws2812b-serial-protocol "TLDR WS2812B Serial Protocol")
* [TLDR UART Serial Interface](#tldr-uart-serial-interface "TLDR UART Serial Interface")
* [TLDR I2C Interface](#tldr-i2c-interface "TLDR I2C Interface")

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
We will be using Arduino Nano clones in our projects. You can ignore the following for our class; this is for follow-up by interested persons. Below is an image of an Arduino Nano from www.circuitstoday.com.

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/Arduino-Nano-Pinout_from_circuitstoday.com.png "CircuitsToday.com picture of Arduino Nano")

Lots of info on the Arduino Nano is found here (diagrams, not schematics)
* https://www.circuitstoday.com/arduino-nano-tutorial-pinout-schematics

The ATMEGA 328P chip used in the Arduino Nano is described here
* http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf

Mapping the ports to the internal registers is described here
* https://www.arduino.cc/en/Reference/PortManipulation

## My favorite Arduino variant - ESP32
[Top](#resources "Top")<br>
Here is some documentation from the maker of the chipset and many modules for ESP32; also some other tutorials on installing the ESP32 into the board manager for the Arduino IDE and installing the USB Serial Driver into Windows 10
* https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html
* https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/
* https://randomnerdtutorials.com/esp32-troubleshooting-guide
* https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads
* https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=documentation

A few quotes from above:
- ESP32 is a single 2.4 GHz Wi-Fi-and-Bluetooth SoC (System On a Chip) designed by Espressif Systems.
- The ESP32 series is available as a chip or module.

Some of the ESP32 modules that I use are currently less than $30 for quantity 5:
- https://www.amazon.com/gp/product/B08DQQ8CBP

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/ESP32.png" width="475" height="476">

Here is an article about how to choose which ESP32 module you want to use:
- https://makeradvisor.com/esp32-development-boards-review-comparison/

An ESP32 module has MUCH more RAM and program storage than the original Arduinos, is much faster, and comes complete with easy-to-use on-board WIFI and Bluetooth. Many ESP32 boards including the ESP32 and the ESP32-S3 have dual-core CPUs for expert users.

On the other hand, ESP32 modules typically work with 3.5V I/O instead of 5V so you need to be prepared to handle that. For instance I use the **[SN74HCT125N 3-state Buffer](#sn74hct125n-3\-state-buffer "SN74HCT125N 3-state Buffer")** quadruple bus buffer and voltage translator to convert from 3.5 Volt outputs to 5 Volt outputs.

One thing to keep in mind is that not all GPIO pins on an ESP32 are usable for every purpose. This article will take you through the basics. Don't worry - there are probably plenty of GPIO pins available for your project; just use the right ones!
- https://randomnerdtutorials.com/esp32-pinout-reference-gpios/

In particular, the following pins affect the way the ESP32 boots, so unless you want to affect booting don't attach them to peripherals that would pull them up or down. 
- MTDI
- GPIO0
- GPIO2
- MTDO
- GPIO5

ESP32 boards are typically physically wider than the Arduino Nano and they don't fit well on a standard solderless breadboard. I use two small breadboards to mount an ESP32 as shown below.

| Top View | Side View |
| --- | --- |
| <img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/ESP32_Breadboard_1.png" width="150" alt="Overhead View of ESP32 on two breadboards"> | <img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/ESP32_Breadboard_2.png" width="150" alt="Side View of ESP32 on two breadboards"> |

Here are some repositories and YouTubes showing off some of the advantages of the ESP32 over older Arduino modules such as the Nano:
- https://github.com/RalphBacon/228-Wireless-Over-the-Air-OTA-ESP32-updates - Elegant OTA (Over The Air) update can have username and password
  - https://youtu.be/OaHzlBTUrRQ
- https://github.com/RalphBacon/258-ESP32-Web-Enabled-with-OTA
  - https://www.youtube.com/watch?v=6yiuImbqKYY
- https://github.com/RalphBacon/260-ESP32-Web-Pages-Part-2
  - https://youtu.be/7cfeWTsJxcE
- https://github.com/garyexplains/examples/blob/master/ESP-NOW_on_Arduino_Nano_ESP32.md
  - https://www.youtube.com/watch?v=MRgAeg2i5Qg
- https://github.com/RalphBacon/ESP32-Dual-Core-Programming
  - https://youtu.be/jpVcCmh8sig
- https://github.com/garyexplains/examples/tree/master/Dual_Core_for_RP2040_ESP32_ESP32-S3
  - https://www.youtube.com/watch?v=w5YigjvSaF4
- https://www.youtube.com/watch?v=k_D_Qu0cgu8  ESP32 Dual Core on Arduino IDE
  - https://github.com/SensorsIot/ESP32-Dual-Core

For ESP32 I personally use Microsoft Visual Studio Community with the extension "VSIX Arduino IDE (Vx.x) for Visual Studio (xxxx)" https://www.visualmicro.com/; this includes an Over-The-Air WiFi debugger that works with my ESP32 modules with built-in Wifi. The debugger isn't perfect but being able to connect over WiFi is great. This extension does cost; Hobby/Personal one-PC is about $25/year at this time (2023); other licensing options are available.

## EEPROM to save configuration
[Top](#resources "Top")<br>
These Arduino Nanos have 32Kbyte of FLASH memory (program storage), 2Kbyte of SRAM, and 1Kbyte of EEPROM.
- FLASH memory (no acronym) was an offshoot of EEPROM. For the Arduino Nano it is erasable and writeable in blocks of many consecutive bytes.
- EEPROM (Electrically Eraseable Programmable Read-Only Memory) is, for the Arduino Nano, erasable and writeable in blocks of one byte. The Read-Only part seems strange, but the idea is that we can erase it and then program (write) it but we cannot write it in one step.
- SRAM (Static Random Access Memory) is, for the Arduino Nano, readable and writeable in blocks of one byte. There is typically no published limit on the number of times it can be read or written. Note that there is a difference between RAM, SRAM, DRAM, and other variants but in this class I will refer to them as either SRAM or RAM.

Note: 1Kbyte (capital K) typically means 1,024 bytes; 1,024 is considered to be the "binary thousand" since it is 2 to the power 10 and 1,000 is 10 to the power 3. 1kbyte (lower case k) is often decimal 1,000. Sometimes, however, the person writing these numbers has a typo so be forewarned.

In Arduino practice:
- FLASH memory is used to store the program code. It can also be used to store constant strings and other data (see section on **[PROGMEM and F macro to save RAM](#progmem-and-f-macro-to-save-ram "PROGMEM and F macro to save RAM")**).
- SRAM is used for variables that change often during program execution. If you write **static int xxx = 5;** or **int func(int a) { int xxx; xxx = a+1; return(xxx); };**, then **xxx** will be in SRAM.
- EEPROM is used to save things that are changed during program execution and that the changed state needs to be remembered the next time the Arduino powers-on.

The Arduino EEPROM interface is simplicity itself:
- early in the *.ino file put the line **#include <EEPROM.h>**
- when you want to read a byte from EEPROM, call **readValue = EEPROM.read(address);**
- when you want to write a byte to EEPROM, call **EEPROM.update(address, byteValue);**
- for other possibilities including dealing with data that is not just one byte in length, read https://docs.arduino.cc/learn/programming/eeprom-guide

Given that FLASH is written only when we change the program and EEPROM would be written while the program is running, it is likely that EEPROM will use up all its erase/write cycles before FLASH will. In Arduino, EEPROM **reads** are unlimited. The Arduino EEPROM is specified to handle 100,000 **erase/write** cycles for each position (byte). However, the Arduino Nanos I use are cheap $2 clones instead of the official Arduino Nano at close to $25; therefore I don't want to push the limits. Also, writes to EEPROM take a few milliseconds which can slow down operation. Because of this I use **EEPROM.update(address, byteValue)** instead of **EEPROM.write(address, byteValue)**. The difference is that EEPROM.update() first reads the EEPROM (fast and doesn't use up erase/write cycles) and only does the write if the EEPROM byte is not already the desired value.

When the Arduino powers up, how will it know if the parameters stored in EEPROM are valid or if it is a new Arduino out of the bag and the values are random? To handle this I store a simple checksum along with the parameters in EEPROM. If the EEPROM checksum doesn't match the EEPROM configuration data then I store a fresh set of configuration data in EEPROM. Doing this also makes it easy to provide a "factory reset" capability.

Because I use a one-byte checksum (you could use a more elaborate checksum if you want) there is a one in 256 chance that random data will have a checksum that matches it. Because I am lazy, I accept that chance: if the first time I program an Arduino it acts crazy then I can either write something to the configuration value or I can one-time change the expected value of the checksum to be different (for example; 1 + the normal checksum) and then it will put good power-on configuration data in EEPROM. Later I can either leave the checksum expectation at this new value or change it back.

## PROGMEM and F macro to save RAM
[Top](#resources "Top")<br>
The following references show how to save constant values such as strings in program memory instead of using precious Arduino RAM:
- https://reference.arduino.cc/reference/en/language/variables/utilities/progmem/
- https://www.instructables.com/Arduino-String-Manipulation-Using-Minimal-Ram/

Here is a simple example of usage PROGMEM and "F" macro for Serial.print*():

```C
#include "Arduino.h"

#define USE_PROGMEM 1                     // set non-zero to keep big const items in FLASH (PROGMEM keyword)


// somewhere in your code 
#if USE_PROGMEM
  Serial.println(F("My strings are stored in PROGMEM"));
#else // not USE_PROGMEM
  Serial.println("My strings are stored in RAM");
#endif // USE_PROGMEM
```

Using PROGMEM for data storage of large tables is possible but a little more complex. Read the docs or talk to me.

## Solderless Breadboard
[Top](#resources "Top")<br>
We will be using a solderless breadboard to rapidly implement parts of our circuit. Connections are made by plugging wires or components into the holes in the board. A youtube video of connecting LEDs to a solderless breadboard can be found at this link.  NOTE: to play youtube and keep this tab open you must right-click the link and select to play in a new tab.
- https://www.youtube.com/watch?v=UvS9Wf2BoyE

A good guide to solderless breadboards can be found at this link:
- https://protosupplies.com/guide-to-solderless-breadboards/

Here from the above link is an image of a typical solderless breadboard.

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/Breadboard-Details_from_protosupplies.com.jpg "Image of typical solderless breadboard from protosupplies.com")

It might be worthwhile to look the above image over in detail; we will be using this breadboard in this class. Try to find which pins distribute power and ground vertically (the long way on the breadboard), which pins distribute signals side-to-side, and how far the signals get distributed in these directions.

Something that may help, again from that protosupplies.com article about breadboards, is the following image of a breadboard from the inside, showing the metal that connects the pins on the top of the breadboard.

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/Breadboard-Contacts-Back-Side-2_from_protosupplies.com.jpg "Image of typical solderless breadboard from protosupplies.com")

Be aware that a circuit laid out on such a solderless breadboard can then be transferred to a solderable breadboard PCB board fairly easily. See the comparison between these two below.

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/Breadboard_Solderboard.png "Image of a solderless breadboard and a solderable breadboard PCB board")

## YX5200 Audio Player
[Top](#resources "Top")<br>
The YX5200 Audio Player can drive speakers or headphones from sound files you place on its SD card slot. About $2 each in packs of 5.<br>
Placing the audio files onto the SD card requires special care. Also there are many clone versions with different chips and different firmware levels. The following link shows the method I used to get reliable performance.
- https://github.com/Mark-MDO47/AudioPlayer-YX5200

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/YX5200_MP3player.png "Image of YX5200 Audio Player")

### Saturn Sounds from Cassini
[Top](#resources "Top")<br>
Sounds from SPACE!!! Saturn is SO COOL!

Some great science-fictiony sounds came from the Cassini space mission. Here is where you can get audio from the Cassini mission representing radio emissions from Saturn:
- http://www-pw.physics.uiowa.edu/space-audio/cassini/SKR1/
- http://www-pw.physics.uiowa.edu/space-audio/cassini/SKR1/SKR-03-324.wav

You can find more about the Cassini mission here
- https://solarsystem.nasa.gov/missions/cassini/overview/

Attribution of external sounds found (in whole or in part, possibly altered) used in this class (see https://github.com/Mark-MDO47/ArduinoClass/tree/master/99_Resources/Sounds):<br><br>
<table border cellspacing="1" cellpadding="9">
<tr><td><b>Tag</b></td><td><b>File Name</b></td><td><b>URL</b></td><td><b>Who</b></td></tr>
<tr><td>N/A</td><td>SKR-03-324.wav</td><td>http://www-pw.physics.uiowa.edu/space-audio/cassini/SKR1/</td><td>NASA Cassini mission Radio and Plasma Wave Science</td></tr>
</table>
<br><br>
<table border cellspacing="1" cellpadding="9">
<tr><td><b>Tag</b></td><td><b>Name</b></td><td><b>URL</b></td>
<tr><td>zero/1.0/</td><td>Creative Commons 0 License</td><td>https://creativecommons.org/publicdomain/zero/1.0/</td></tr>
<tr><td>by/3.0/</td><td>Creative Commons Attribution License</td><td>https://creativecommons.org/licenses/by/3.0/</td></tr>
<tr><td>by-nc/3.0/</td><td>Creative Commons Attribution Noncommercial License</td><td>https://creativecommons.org/licenses/by-nc/3.0/</td></tr>
</table>

### Text-to-Speech Robotic Sounds
[Top](#resources "Top")<br>
The final project "Theremin with Sound" speaks to you when you change patterns.<br>
I used the "original" **eSpeak** text-to-speech program version 1.48.04 to produce the speaking sounds with a robotic flavor, which I wanted.

To complete the robotic flavor I used **Audacity** which can be found at https://www.audacityteam.org/

The original eSpeak text to speech code and compiled versions can be found at http://espeak.sourceforge.net/
- Kudos to (email) jonsd at users dot sourceforge dot net for creating eSpeak

Note that eSpeak project is inactive since disappearance of Jonathan Duddington.

Active development and support now happens in eSpeak NG project https://github.com/espeak-ng/espeak-ng, maintained by Reece H. Dunn.
- Kudos to Reece H. Dunn for continuing the good work

A web implementation of eSpeak can be found as below; it is great fun, and just one of many text-to-text and text-to-speech engines on the site. https://lingojam.com/RobotVoiceGenerator

If you are interested in more details on Text-to-Speech Robotic Sounds and the processing involved see:
- https://github.com/Mark-MDO47/AudioPlayer-YX5200

## KCX_BT_EMITTER Bluetooth Audio Transmitter
[Top](#resources "Top")<br>
The KCX_BT_EMITTER can take the audio from the YX5200 and send it to a bluetooth speaker. The KCX_BT_EMITTER Version 1.1 (and 1.2) supports Bluetooth 4.1 and is about $3.50 on Ebay or $1.50 on aliexpress.com. This is the one I am familiar with. I have heard rumors of an updated Version 1.7 supporting stereo and/or Bluetooth 5.x but have no experience with these, although I have ordered some and will be experimenting with them.<br>
The information on commanding the KCX_BT_EMITTER to auto-pair to a specific speaker is in Chinese. Also there is a trick to getting a low-noise connection between this and the YX5200. I have pointers to these details and some utilities I wrote to help with commanding/pairing in the following link.
- https://github.com/Mark-MDO47/BluetoothAudioTransmitter_KCX_BT_EMITTER

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/KCX_BT_Board_IMG_1351.png "Image of KCX_BT_EMITTER Bluetooth Audio Transmitter")

## DF2301QG Voice Recognizer and Command Module
[Top](#resources "Top")<br>
The DFRobot DF2301QG SKU SEN0539-EN recognizes voice commands and sends a numerical code to the Arduino. I have only been using this for a few weeks but it looks like fun! One interesting thing about this device is that it doesn't depend on any Internet connection or giant tech company voice-to-text service; it does the voice recognition locally.
- https://www.dfrobot.com/product-2665.html
- https://wiki.dfrobot.com/SKU_SEN0539-EN_Gravity_Voice_Recognition_Module_I2C_UART

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/SEN0539-EN-1_from_dfrobot.com.jpg" width="500" alt="Image of DF2301QG voice command module from dfrobot.com">

## UBEC Universal Battery Eliminator Circuit
[Top](#resources "Top")<br>
A UBEC (Universal Battery Eliminator Circuit - not Union of Banana Exporting Countries) is often used to power an Arduino and perhaps some of its other circuits as well. This switching power supply will typically take as input something in the range of about 6V to 28V DC and usually has selectable output voltage of either 5V or 6V. I often connect a 9V battery as input to a UBEC or two or more 18650 batteries. If there is a heavy draw somewhere in your circuit that is far from the batteries, you can increase the voltage of your source battery and put the UBEC close to the circuit drawing the power and thus reduce the current in the wires between.<br>
![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/UBEC.png "Image of typical UBEC")

## 9 10K Ohm resistors one package
[Top](#resources "Top")<br>
This handy device allows the use of one component to give 10 individual pullups. This is useful for instance if your project has a lot of buttons.
- https://www.digikey.com/en/products/detail/bourns-inc/4610X-AP1-103LF/3741070

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/4610X_SERIES_from_digikey.com.jpg" width="150" alt="digikey.com image of 9 10K Ohm resistors one package">

## SN74HCT125N 3-state Buffer
[Top](#resources "Top")<br>
This chip can be used to provide fan-out for Arduino outputs. I also abuse it to use it to convert 3.5V outputs from an ESP32 into 5V outputs, especially when driving moderately fast serial interfaces such as a string of WS2812B LEDs. It is not really designed for voltage conversion but it seems to work for me with the ESP32 outputs.
- https://www.digikey.com/en/products/detail/texas-instruments/SN74HCT125N/376860

The version I use is a Dual In-Line Package (DIP) chip; the following is an image from www.amazon.com. I find these DIP chips easier to work with than some of the surface-mount chip packages.<br>
![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/SN74HCT125N.jpg "Image from www.amazon.com of the SN74HCT125N")

## Schematics KiCad and Fritzing
[Top](resources "Top")<br>

### Schematics
[Top](resources "Top")<br>
Simple schematic diagrams are used throughout this course. These use special symbols to represent parts of an electrical circuit - such as resistors and LEDs - and lines to represent the connections.

Example schematic wiring diagram showing a physical representation of an Arduino Nano, a resistor, and a Light Emitting Diode or LED:<br>
<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/01_BlinkingLED_part_A_Schematic.png" width="150" alt="Example KiCad schematic">

Some tutorials to help you recognize common schematic symbols:
- https://www.youtube.com/watch?v=Y3s6uY4oO5w "How to Identify Common Schematic Symbols - Another Teaching Moment | Digi-Key Electronics" - the basics, maybe all you need for this class
- https://www.youtube.com/watch?v=-dzHDgJVJh4 "How to Read a Schematic - Another Teaching Moment | Digi-Key Electronics" - more in depth

I sometimes call my schematics "schematic wiring diagrams" because I don't quite follow the rules of the standards organizations, although I reserve the right to just call them schematics.
- I often show all power and ground connections as wires rather than going to standard voltage and ground symbols. I do this to make these connections more visible. When assembling or soldering together a circuit, one of my most common errors is to forget to connect a power or ground pin, so this format of schematic is helpful to me.
- I don't always follow the "rules" about placement of all chip input pins on one side and all chip output pins on the other side; instead I make my own symbols for such things as Arduinos and other chips and modules that show the physical placement of the pins on the part. I do this because I often wire directly from the schematic and find it annoying to have to figure out the physical pin placement somewhere other than the schematic.

## KiCad
[Top](#resources "Top")<br>
I use the free schematic editor KiCad for capturing schematics (what I do might better be called wiring diagrams; see above). KiCad can also do Spice simulations, PCB board layout, Gerber File generation, Bill of Materials --- the whole works!
- https://www.kicad.org/

If you don't want to use KiCad, don't worry - all the schematic wiring diagrams for the class are in PDF form in the various directories, and also in images in the description of each project.

There are many YouTube videos describing the basics of KiCad usage. I recommend viewing a few of them if you want to start with KiCad. Most are quite good; I didn't really have a favorite. Be aware that KiCad version 6.0 was the start of some bit changes, so try to find videos using that or later. KiCad is currently (2023) at version 7.0.5.

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/KiCad_screen.png" width="300" alt="Image of KiCad Schematic Capture screen">

The official KiCad curated libraries can be found here:
- https://kicad.github.io/
- https://gitlab.com/kicad

I also have a tendency to use some third-party KiCad symbol libraries, especially the DigiKey library. You can see all the "official" KiCad libraries available at this location:
- https://www.kicad.org/libraries/third_party/

Even all that is not enough for me! I have some of my own hand-generated schematic symbols in my KiCad 7.0.2 library mdoLibrary.kicad_sym. These are in this repository so you can find them to view the KiCad files included with this class.
- https://github.com/Mark-MDO47/ArduinoClass/tree/master/99_Resources/KiCad

SnapEDA also has libraries with schematic symbols and footprints. If you start making PCB boards this might be a useful addition.
- https://www.snapeda.com/
- https://www.snapeda.com/kicad/

There is a SnapEDA Chrome extension to help search. Unfortunately the SnapEDA KiCad plugin is for earlier versions of KiCad, but the symbols and footprints still work.

If you want to use KiCad to edit the schematic wiring diagrams for this class, I would recommend adding mdoLibrary.kicad_sym to your global libraries so you don't have to add it as a project-specific library for each of the schematics. To do this you may want to copy that small library to some permanent place on your disk drive so you don't need to worry why KiCad is complaining once you delete the class repository. I created a directory **C:\KiCad\V7\LocalLibraries** and put mdoLibrary.kicad_sym there. Then I added it into the global library using **Preferences** -> **Manage Symbol Libraries...** as seen below

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/99_Preferences_ManageSymbolLibraries.png "Image of KiCad selecting Preferences - Manage Symbol Libraries")

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/99_Preferences_AddSymbolLibraries.png "Image of KiCad after adding mdoLibrary.kicad_sym to global libraries")

### Fritzing
[Top](resources "Top")<br>
I have included Fritzing images for most of the projects in this course. These give a more physical view of how to wire an electrical circuit than a schematic. They are commonly used to illustrate breadboard projects and can even show the breadboard itself.

Example Schematic and corresponding Fritzing with the same components and with the addition of the breadboard:<br>
<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/01_BlinkingLED_part_A_Schematic.png" width="150" alt="Example KiCad schematic">
<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/01_BlinkingLED_part_A_Fritzing.png" width="150" alt="Example Fritzing Image">

Fritzing does cost about $10 and can be found here:
- https://fritzing.org

If you are like me, even though Fritzing comes with a lot of parts in its library I need other parts that I cannot find there nor in public libraries. Thus it is handy to know how to create new parts. Admittedly, I only create the "Breadboard" version of the part and do not create the Fritzing PCB footprint or worry about the schematic symbol. Because you will probably want to use a vector drawing program to create the image, even if starting from a picture, here are some good places to look to see how to create parts.
- https://www.youtube.com/watch?v=0RDrw8WvYNQ "Fritzing Part Creation - Chapter9 - Using Photo and PDF" - my favorite Fritzing/InkScape parts tutorial
- https://inkscape.org/ - where to get the free vector drawing program InkScape
- https://fritzing.org/learning/tutorials/creating-custom-parts - the official source, though not completely up to date

There is a **FritzingCheckPart.py** python program. Be aware that it can make changes to your part, not just report issues! Make a copy of your part and check the copy, then choose the one you like better. Maybe it should be called **FritzingFixPart.py** as one wag said in the forum.
- https://forum.fritzing.org/t/fritzingcheckpart-nitpicking/11096
- https://github.com/vanepp/FritzingCheckPart

If you get deep into creating your own Fritzing parts, it might be worth looking over some of the parts of this tool. For instance, glancing through **FritzingTools.py** I found this comment.
- Some part of Fritzing (probably the script to produce the gerber output) can't deal with inheritance. The case that drove this change (and the only translation currently being done) is to save the svg in Inkscape as optimized svg (rather than plain) at which point the stroke-width attribute is optimized in to copper0 or copper1 top level and inherited. The output geber missing the stroke-width parameter outputs an oversize nonplated through hole. To fix that we copy the stroke length in to the leaf nodes of all elements of copper0 or copper1 which should fix the problem and allow us to use optimised svg in Inkscape.

Fritzing is the name of the organization that produces the Fritzing tool that produces these images. This leads to some linguistic confusion as I often refer to these images using the noun Fritzing, the activity I do to generate the image using the verb Fritzing, the saved file for the Fritzing tool using the noun Fritzing, and the saved generated special part for the tool using the adjective Fritzing: a Fritzing part (which sort of sounds like cursing). In my defense I offer the following quote from today's Wikipedia entry on "-ing":
- "-ing" is a suffix used to make one of the inflected forms of English verbs. This verb form is used as a present participle, as a gerund, and sometimes as an independent noun or adjective.

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
- https://thepi.io/how-to-use-your-raspberry-pi-as-a-wireless-access-point/
- https://randomnerdtutorials.com/esp32-wireless-communication-protocols/#lora
- https://randomnerdtutorials.com/esp32-bluetooth-classic-arduino-ide/
- https://www.instructables.com/The-Process-of-Designing-and-Ordering-a-PCB-Signal/
- https://www.instructables.com/How-to-Assemble-a-PCB-With-Tiny-SMD-Parts/

## TLDR Decimal and Binary and Hexadecimal
[Top](#resources "Top")<br>
When programming it eventually becomes necessary to understand decimal, binary, and hexadecimal arithmetic. It is not hard to understand but it does take some time to be proficient in it. Fortunately in this class we don't really need to be quick at it, we just need to be able to figure it out.

We all are used to decimal arithmetic and the notation system based on powers of 10. If you see the decimal number 123 you know, starting from the right and moving left, that it is (3 times ten-to-the-power-zero) + (2 times ten-to-the-power-one) + (1 times ten-to-the-power-two). Since anything (let's ignore infinity and zero at this point) to the power zero is one, that means 123 is three plus twenty plus one hundred.

The same principle applies to binary but every digit is either one or zero and every position is a power of two instead of a power of ten. Again, hexadecimal is the same principle but every digit is from zero to nine then a, b, c, d, e, or f representing 10, 11, 12, 13, 14 or 15; and every position is a power of sixteen instead of ten or two. It is pretty easy to convert binary to hexadecimal and back and hexadecimal has one fourth as many digits and binary.

The following short document goes over this in just a little more detail.
- http://www.eecs.umich.edu/courses/eecs270/270lab/270_docs/HexNumSys.pdf

And now a caution about octal. Octal arithmetic is similar to the above systems with digits confined to 0,1,2,3,4,5,6,7 and the positions based on powers of eight. The difficulty arises from the method the C language uses to flag that the digits should be interpreted as octal: if the number has all decimal digits and starts with zero, it is assumed to be octal.

This means that in C language, 10 is ten decimal but 010 is eight decimal. In fact if you try to use 09, it will be flagged as an error because 9 is not an octal digit. Having compiler errors tell us when the compiler is misinterpretting our numbers is one thing, having it silently accept 010 as eight is quite another - so **programmor emptor**!

So how do we specify integer constants in the various number systems?
- decimal - just use decimal digits but do not start with zero. If you want the value zero, 0 octal = 0 decimal = 0.
- octal - use octal digits and start with a zero
- hexadecimal - use 0x followed by hexadecimal digits; OK to use either upper or lower case hex letters
- binary - us 0b followed by binary digits

The following statements cause identical values to be stored in "i":
```C
i =       47;
i =      057;
i =     0x2f;
i = 0b101111;
```

There is more to learn, for instance negative numbers in twos-complement or ones-complement and how they behave, but the above will pretty much cover this class.

## TLDR Power and Wires
[Top](#resources "Top")<br>
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

With just 8 RGB LEDs the current draw of 336 milliamps (power 1.68 watts) worst case through the Arduino Nano should be OK. If it got to be much more than that I would use a separate power source for the LEDs. At first in our projects I only use one color at a time on each LED and so limit power draw. Later, you will find that we set a parameter to limit the total power for each LED in the FastLED library. My plan is to use various software means to limit power to less than 168 milliamps or 0.84 watts, probably significantly less.

Calculating wire size (Google for instance wire gauge ampacity 5v dc): the following link leads to information about power that can be safely passed through wire of different types and guages.
- https://www.powerstream.com/Wire_Size.htm

Looking up in the table referenced above, an AWG30 single strand wire meeting the specs of the site could carry 860 milliamps. We are using multi stranded AWG30 so we would not expect the full 5X safety margin. Even so, I suspect that our AWG30 would be adequate. In fact I have used silicon coated multi stranded AWG30 to power two WS2812B 32 LED strands just due to ignorance of the issue. The margin of safety you want depends on other things too, such as the voltage drop you can tolerate (the table gives resistance data) and whether the electronics comes in contact with someone.

 An AWG24 single strand wire meeting the specs of the site could carry 3,500 milliamps. Obviously AWG24 multi strand is overkill, even though we are using multi stranded.

For my Graduation Cap project with 372 WS2812B LEDs I used AWG20 multi stranded wire for power and ground because it came in contact with my daughters when operating the caps and I wasn't willing to chance any possibility of discomfort.

## TLDR WS2812B Serial Protocol
[Top](#resources "Top")<br>
There is a serial data protocol used to control this string of 8 WS2812B LEDs.
- 3 8-bit bytes per LED are sent to control Red/Green/Blue.
  - The actual color order can vary; we will determine it by experimentation.
  - This allows 256 levels (0-255 for an unsigned 8-bit byte) for each of the colors Red/Green/Blue.
- The order of 3-byte RGB commands sent starts with data for the first LED in the string, then the second, etc.
- Each LED "consumes" its 3-byte RGB command from the data and then passes all the rest of the data down the line until the data stream stops for at least 50 microseconds
  - After this 50 microsecond stop, the string resets and the each LED including the first LED will be ready to start again, consuming a new 3-byte value for its next RGB command and passing the commands after the consumed one down the line of the string.

The WS2812B protocol can be found in this spec:
* https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf

A higher level depiction of this output protocol in action (taken from the spec) is shown here. First is the serial head-to-tail cascade architecture of the LEDs:

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/CascadeLED_SerialProtocol_arch.png "WS2812b RGB serial cascade architecture (from spec)")

Then the high-level serial output protocol as seen by each of the LEDs in the architecture diagram. Note how each LED "consumes" the first set of bytes and passes on the rest.

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/WS2812B_RGB_SerialProtocol.png "WS2812b RGB serial output protocol (from spec)")

## TLDR UART Serial Interface
[Top](#notes "Top")<br>
To communicate with the YX5200 we use a serial data protocol named Universal Asynchronous Receiver Transmitter or UART for short.
- We previously saw a serial data protocol for sending color information to the WS2812B LEDs; that one used a single wire to transmit data in just one direction.
- The UART protocol used on the Arduinos is also one wire, but a second wire can be used to transmit in the other direction. The UART protocol itself can actually get more complicated than that, but for us this description is adequate.
- UART interaces can be used to program the Arduino Nano; the USB port on the Arduino actually connects up to a hardware UART implementation.
- Arduino UART interfaces to other devices are quite common; we will use a special library SoftwareSerial to connect to the YX5200 using ordinary digital I/O pins.

Here is an excellent description of how the UART interface works:
- https://www.seeedstudio.com/blog/2022/09/08/uart-communication-protocol-and-how-it-works/

Below is an illustration from that tutorial showing the high/low sequences on the line for a UART byte transfer:<br>
<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/uart1_from_seeedstudio.com.png" width="600" alt="seeedstudio.com image of UART byte transfer"><br>

Note that the detection of the first high-to-low transition is used to set the time used to (hopefully) sample the other bits in the middle of the bit. The timing of the bits on the transmitting side and the timing of the detection of the bits on the receiving side need to remain in sync throughout or there can be a receive error. That caused us to use two Arduino Nanos in the **VoiceCommands and VC_DemoReel** project.<br>
- https://github.com/Mark-MDO47/ArduinoClass/tree/master/04_TheFinale

### TLDR I2C Interface
[Top](#notes "Top")<br>
The **I2C** (Inter-Integrated Circuit) interface is a serial protocol using a **bus** structure; in the Arduino world this is also known as the **Two Wire Interface**. This **bus** structure is different than the WS2812B serial protocol and the UART serial protocol that are **point-to-point**. It also differs in that it is a **clocked** or **synchronous** serial interface and thus requires two lines (one clock one data), instead of the **asynchronous** serial interfaces that we have seen before.<br>
- https://docs.arduino.cc/learn/communication/wire
- https://learn.sparkfun.com/tutorials/i2c/introduction
- https://howtomechatronics.com/tutorials/arduino/how-i2c-communication-works-and-how-to-use-it-with-arduino/
- https://www.geeksforgeeks.org/i2c-communication-protocol/
- https://www.nxp.com/docs/en/user-guide/UM10204.pdf - UM10204 I2C-bus specification and user manual Rev. 7.0 — 1 October 2021
- https://i2c.info/i2c-bus-specification - I2C Bus Specification

The image below from howtomechatronics.com shows what a typical I2C bus might look like. Note that there are multiple devices attached to the bus, so there must be a part of the I2C protocol for deciding which device gets to talk on the bus next. The protocol used is one example of the **so-called master/slave** protocol, in which the bus master or controller (in this case an Arduino) decides who talks on the bus at any time. The master also generates the clock. The other devices all have an address (example 0x34 for one of the devices in the image below) that allows the master to specifically talk with it. In our case we will use the default I2C address for the DF2301QG: 0x64.<br>
<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/I2C-Communication-How-It-Works_from_howtomechatronics.com.png" width="750" alt="howtomechatronics.com image of I2C bus">

Curiously, most Arduinos have I2C communication hardware built in that can be accessed by using the analog pins A4 and A5. That is what we will do with the Arduino Nano.

Also, I have seen examples in the Arduino documentation with and without the pullup resistors near the right side of the above diagram. I think it is safe to have the pullup resistors, but for some applications they may not be absolutely necessary. I would expect that having the pullup resistors in the circuit would make the communications a bit more reliable.

Our usage is a simple one: just one bus controller, standard 7-bit addresses.

The description below is mostly drawn from the references here; see the references for the full description.

#### Truly TLDR - the I2C Interface
In I2C there are two active lines: SDA (Serial Data) and SCL (Serial Clock). Notice that in the UART interface and the WS2812B interface there is no clock line; that is what makes them Asynchronous and I2C Synchronous.
- Some descriptions speak of 8-bit data words or packets, each word/packet followed by an ACK bit, surrounded by START/STOP condition bits; others speak of 9-bit data packets or frames including the ACK bit surrounded by START/STOP condition bits.
  - I will describe it as 8-bit data words followed by an ACK bit surrounded by START/STOP conditions. To me, the 8-bits is data and the START/STOP conditions and ACK bits are protocol.
- The serial data line can change only when the serial clock line is low. It can not change when the serial clock line is high.<br>
- After each 8-bit data word is sent, the receiver of the data (controller or target) sends an ACK bit that says either the word was received correctly or not.
  - I will not go into what is done if the ACK bit says not received; read the references for that information.
- An entire group of 8-bit data word transfers is surrounded by a START condition and a STOP condition.
  - There is also a START repeat but I will not cover that here;  read the references for that information.

Here is a graph from i2c.info/i2c-bus-specification showing the Rule of Change of Serial Data on the I2C bus.<br>
<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/I2C_RuleChangeOfData_from_i2c.info_i2c-bus-specification.png" width="750" alt="i2c.info/i2c-bus-specification graph of Rule of Change of Serial Data on I2C bus">

Here is a graph from i2c.info/i2c-bus-specification showing the Start and Stop Condition of Serial Data on the I2C bus.<br>
<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/I2C_StartAndStopCondition_from_i2c.info_i2c-bus-specification.png" width="750" alt="i2c.info/i2c-bus-specification graph of Start and Stop Condition of Serial Data on I2C bus">

Here is a graph from i2c.info/i2c-bus-specification showing a Sample Transaction on the I2C bus. Note that data is transmitted Most Significant Bit (MSB) first.<br>
<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/I2C_SampleTransaction_from_i2c.info_i2c-bus-specification.png" width="750" alt="i2c.info/i2c-bus-specification graph of Sample Transaction on I2C bus">

The concept for our simple one bus controller, standard 7-bit addresses case goes somewhat as follows:
- When the controller (Arduino) wants to talk to the target (DF2301QG), it causes a START condition and then sends the 7-bit address of the DF2301QG and then sends one bit that tells whether the Arduino wants to write or read a register
- The DF2301QG sends an ACK bit saying that it saw that and is ready to proceed
- The Arduino sends eight bits of the register address for the DF2301QG register it wants to write or read
- The DF2301QG sends an ACK bit saying that it saw that and is ready to proceed
- If the Arduino is writing data to the DF2301QG register:
  - The Arduino sends the eight-bit value to write into the DF2301QG register
  - The DF2301QG sends an ACK bit saying that it saw that and is ready to proceed (it will store the data into the DF2301QG register internally)
- Or else if the Arduino is reading data from the DF2301QG register:
  - The DF2301QG sends the eight-bit value that was read from the DF2301QG register
  - The Arduino sends an ACK bit saying that it saw that and is ready to proceed
- The Arduino causes a STOP condition

There are possible variations on the above to speed operations for multiple consecutive register reads or writes, but once again you can read about these in the references above.

Here is an example from our 04_TheFinale Voice Commands project as captured on an Oscilloscope. The horizontal direction is time, increasing as we go from left to right. The vertical direction is voltage, increasing as we go from bottom to top. Each of the traces has its own point on the vertical direction that corresponds to zero volts. I placed the two traces close together to make it easier to see the timing.
- Yellow (on top) corresponds to SCL (Serial Clock)
- Blue (on bottom) corresponds to SDA (Serial Data)

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/I2C_OscopeCloseup.jpg" width="750" alt="Oscilloscope capture of Serial Clock and Serial Data on I2C bus">
