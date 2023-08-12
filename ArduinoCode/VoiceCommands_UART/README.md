# Voice Commands UART

## Back to Root of Class
Click this link to back to go back to the root of the Arduino class
- https://github.com/Mark-MDO47/ArduinoClass/tree/master

This is the **UART** version of VoiceCommands. After experimentation I decided to use the **I2C** version; see below
- https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/VoiceCommands_I2C

The main reasons for using the I2C version:
- The DFRobot library for DF2301Q had to be hacked up to make it work in **UART** mode for the Arduino Nano. The unmodified version of the DFRobot library can be used in **I2C** mode.
- Experimentation suggests that the **I2C** version is better at having the DF2301Q detected command message reach the Arduino Nano than the **UART version**.

## Introduction
This code is used for one Arduino Nano in a set of two Arduino Nanos in one build. This build is the second part in section 04.
* https://github.com/Mark-MDO47/ArduinoClass/tree/master/04_TheFinale

This code is used in **UART** mode on the Arduino Nano connected to the DFRobot DF2301Q (SKU SEN0539-EN, https://www.dfrobot.com/product-2665.html). This device allows us to enter voice commands. It does not require nor use an internet connection; the processing is done locally.
* https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/VoiceCommands_UART

The code for the other Arduino Nano in this build receives the choice of pattern to display and generates that pattern on the LEDs and announces the pattern name on the Bluetooth speaker. The patterns are from Mark Kriegsman's classic DemoReel100.ino.
- https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/VC_DemoReel

## Changes in DFRobot code
I hacked the DFRobot code to allow it to run on an Arduino Nano in **UART** mode. I did not do this in a particularly pleasing way, just made it work.
- Thus the DFRobot code here is not exactly the code from DFRobot. Caveat Programmor!
- The unmodified DFRobot code can be found here: https://github.com/DFRobot/DFRobot_DF2301Q
