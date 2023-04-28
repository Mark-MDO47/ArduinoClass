# ArduinoClass
For a Maker-Space Arduino class 2023<br>
Author: Mark Olson

Below is the lesson plan for the class.

| Lesson | Description | Image |
| --- | --- | --- |
| [00_InstallArduinoIDE](https://github.com/Mark-MDO47/ArduinoClass/tree/master/00_InstallArduinoIDE "00_InstallArduinoIDE") | Install the tools, discuss the venerable C/C++ language.<br>**If possible, please read this lesson and install the Arduino IDE before class!** | <img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/IDE_Blink.png" width="142" alt="Image of Arduino IDE"> |
| [01_BlinkingLED](https://github.com/Mark-MDO47/ArduinoClass/tree/master/01_BlinkingLED "01_BlinkingLED") | Blink some simple LEDs, control blinking using a button, display diagnostic messages using USB serial port.<br>Discusses ways to power Arduino, program persistence, and use of PROGMEM to lower usage of RAM. | <img src="https://www.circuitstoday.com/wp-content/uploads/2018/02/Arduino-Nano-Pinout.jpg" width="142" alt="CircuitsToday.com picture of Arduino Nano"> |
| [02_PersistenceOfVision](https://github.com/Mark-MDO47/ArduinoClass/tree/master/02_PersistenceOfVision "02_PersistenceOfVision") | Fool your vision system with RGB LEDs, control with button and with keyboard via USB serial port. Consists of setup and four projects, plus "extra credit".<br>Discusses WS2812B addressable RGB LEDs, the FastLED library, power consumption and wire guage considerations, and storage of configuration information in EEPROM.<br>TLDR discusses the serial protocol for WS2812B. | ![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/FastLEDblink.png "Image of 02_PersistanceOfVision PartA: LED Stick Blinking") |
| [03_SonarRangeDetector](https://github.com/Mark-MDO47/ArduinoClass/tree/master/03_SonarRangeDetector "03_SonarRangeDetector") | Measure distances with ultrasonic waves to control a zillion LEDs. Consists of one project plus "Extra Fun" using really large collections of RGB LEDs.<br>Discusses HC-SR04 Ultrasonic Range Finder, the ULTRASONIC library, and the famous DemoReel100 RGB LED demonstration program.<br>TLDR discusses speed of sound in air at different temperatures and also the Theremin musical instrument. | <img src="https://protosupplies.com/wp-content/uploads/2019/08/HC-SR04-Ultrasonic-Range-Finder.jpg" width="150" alt="picture of HC-SR04 from protosupplies.com"> |
| [04_ThatIsNotAll](https://github.com/Mark-MDO47/ArduinoClass/tree/master/04_ThatIsNotAll "04_ThatIsNotAll") | These are a few of my favorite things... | <img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/MadScience_400.png" width="150" alt="Image of Mark with Mad Scientist Goggles"> |
| [99_Resources](https://github.com/Mark-MDO47/ArduinoClass/tree/master/99_Resources "99_Resources") | Repository of class information. | <img src="https://lh3.googleusercontent.com/p/AF1QipNOe-jdALOFjO_PwiTpwXQfhZ7P1iPFawCwV-7A=s680-w680-h510" width="150" alt="Image of Long Room Library at Trinity College"> |

For this class I will provide a "kit" for each student station. I have labeled them "Kit 1" through "Kit 6"; Kit 1 is intended for me and the others are available for the class. Each kit includes all the major components for all the projects of our class except the "Extra Fun" section of the 03_SonarRangeDetector, for which we will share some equipment that I will bring. The parts are still in the wrappers (except for the RGB LED Strips; I needed to solder on some wires) so if some do not work we will need to double up; maybe I would sacrifice my kit.

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/Kits_Class.png" width="300" alt="Image of Kits for Arduino Class">

Each of these kits costs about $8 today and I think you will experience that there are many exciting Arduino projects that can be performed inexpensively!

| Part | Cost on March 2023 | Source used |
| --- | --- | --- |
| Arduino Nano | $2.35 | aliexpress.com |
| Solderless Breadboard | < $2 | protosupplies.com |
| WS2812B RGB 8-LED Strip | < $2 | protosupplies.com |
| HC-SR04 Sonar Range Detector | < $2 | protosupplies.com |

Please try to bring a USB cable from your laptop to the Arduino Nano. The Nano has a USB Mini-B female so your cable should end in USB Mini-B male; for more information see the references in lesson 01_BlinkingLED. I will have at least enough USB-A to USB Mini-B cables available for the 5 student stations, but if your laptop uses USB-C or anything but USB-A you will need to cover the gap.

You should then be able to do all of the projects as I will bring all the following for our use.
- connectors, clips, harnesses, and wires
- old style simple LED
- push button
- 200 Ohm resistor
- large RGB Color LED Disks (93 LEDs and 241 LEDs) plus 9V battery and UBEC power convertor (I will provide some to share between student stations)

By the way, Kudos to my son Carl for Alpha-Testing this class. You will see some images and videos of his work and may even catch a glimpse of him or me in the videos.
