# VC_ChristmasTree

## Back to Root of Class
Click this link to back to go back to the root of the Arduino class
- https://github.com/Mark-MDO47/ArduinoClass/tree/master

## Introduction
This code is used for one Arduino Nano in a set of two Arduino Nanos in one build - the Christmas Tree with WS2812B LEDs.

The code for the WS2812B LEDs is pointed to below. It receives its voice commands from the other Arduino Nano.
* https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/ChristmasTree/VC_ChristmasTree

The code for the other Arduino Nano is connected to the DFRobot DF2301Q (SKU SEN0539-EN, https://www.dfrobot.com/product-2665.html). This device allows us to enter voice commands. It does not require nor use an internet connection; the processing is done locally. It transfers the voice-command pattern number to the other Arduino. This will be the **I2C** version:
* https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/ChristmasTree/VoiceCommands_I2C

## Parts List
| Qty | Part | Notes |
| --- | --- | --- |
| 1 | Knife Switch | Always good to have a Frankenstein touch to your projects! |
| 1 | Battery | Anything from 7 to 22 V |
| 1 | UBEC | Using a 3-Amp version |
| 2 | Arduino Nano | Using inexpensive clones |
| 1 | DF2301Q Voice Recognition Sensor | See above for ordering details |
| 3 | WS2812B 8-LED Rings | Leftovers from 93-LED disks |
| 1 | WS2812B 16-LED Ring | Leftovers from 93-LED disk |
| 1 | Cardboard Cutout Christmas Tree | Extremely simple |
| 1 | Cardboard Cutout Star | Extremely simple |
| 1 | Stand with support for tree | Extremely simple |

