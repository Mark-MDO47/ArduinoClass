# VC_DemoReel
## Introduction
This code is used for one Arduino Nano in a set of two Arduino Nanos in one build. This build is the second part in section 04.
* https://github.com/Mark-MDO47/ArduinoClass/tree/master/04_TheFinale

This code is used in the Arduino Nano connected to the WS2812B LEDs and the YX5200 Sound Module. It receives the choice of pattern to display and generates that pattern on the LEDs and announces the pattern name on the Bluetooth speaker. The patterns are from Mark Kriegsman's classic DemoReel100.ino.
* https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/VC_DemoReel

The code for the other Arduino Nano is connected to the DFRobot DF2301Q (SKU SEN0539-EN, https://www.dfrobot.com/product-2665.html). This device allows us to enter voice commands. It does not require nor use an internet connection; the processing is done locally. It transfers the voice-command pattern number to the other Arduino. This will be the **I2C** version:
* https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/VoiceCommands_I2C

The **UART** version works OK but the **I2C** version seems to work a little better. Here is the **UART** version:
* https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/VoiceCommands_UART
