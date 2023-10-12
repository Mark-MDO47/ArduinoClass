# Arduino Class
For an Arduino class 2023; FabLab will be first<br>
Author: Mark Olson<br>
To all who attended the first Arduino Class at FabLab: thanks and I hope you had fun while learning a few things!

**Table Of Contents**
* [Top](#arduino-class "Top")
* [Lesson Plan](#lesson-plan "Lesson Plan")
* [Parts Kit Provided](#parts-kit-provided "Parts Kit Provided")
* [Some other items used in the extra credit projects](#some-other-items-used-in-the-extra-credit-projects "Some other items used in the extra credit projects")
* [Some other things you might see in the class](#some-other-things-you-might-see-in-the-class "Some other things you might see in the class")
* [Please Bring USB Cable](#please-bring-usb-cable "Please Bring USB Cable")
* [Learning C and Cplusplus](#learning-c-and-cplusplus "Learning C and Cplusplus")
* [Kudos](#kudos "Kudos")

## Lesson Plan
[Top](#arduino-class "Top")<br>
Below is the lesson plan for the class.

| Lesson | Description | Image |
| --- | --- | --- |
| [PleaseKnowSomeC/C++](#learning-c-and-cplusplus "-1_Please Know Some C/C++") | If you have never done any programming, please learn a little about C and C++ before signing up for the Arduino class. Thanks!<br>I plan to add a separate (very) short class on C language for those without programming experience; either programming experience or this class will be a pre-requisite for the Arduino class. | <img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/KandRbook.png" width="142" alt="Image of Kernighan and Ritchie C language book"> |
| [00_InstallArduinoIDE](https://github.com/Mark-MDO47/ArduinoClass/tree/master/00_InstallArduinoIDE "00_InstallArduinoIDE") | Install the Arduino IDE<br>Brief discussion of the venerable C/C++ language<br>Quick introduction to schematics and Fritzing<br>**If possible, please read this lesson and install the Arduino IDE before class!** | <img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/IDE_Blink.png" width="142" alt="Image of Arduino IDE"> |
| [01_BlinkingLED](https://github.com/Mark-MDO47/ArduinoClass/tree/master/01_BlinkingLED "01_BlinkingLED") | Blink some simple LEDs<br>Control blinking using a button<br>Display diagnostic messages using USB serial port<br>YouTube: https://youtu.be/c5UH3J40uWE<br>YouTube: https://youtube.com/shorts/qGxECSMQtAQ<br>Discusses ways to power Arduino, program persistence through power-cycling, and use of PROGMEM to lower usage of RAM.<br><br>External Image of Arduino Nano from CircuitsToday.com | <img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/Arduino-Nano-Pinout_from_circuitstoday.com.png" width="142" alt="CircuitsToday.com picture of Arduino Nano"><br><img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/01_BlinkingLED_part_B_setup.png" width="150" alt="Image of Blinking LED part B"> |
| [02_PersistenceOfVision](https://github.com/Mark-MDO47/ArduinoClass/tree/master/02_PersistenceOfVision "02_PersistenceOfVision") | Fool your vision system with RGB LEDs<br>Control Arduino with button and with keyboard via USB serial port<br>Consists of setup and four projects, plus "extra credit" and "persistence of vision spinning stick"<br>Youtube: https://youtu.be/UdA5ehl802k<br>Discusses WS2812B addressable RGB LEDs, the FastLED library, binary numbers and boolean algebra, power consumption and wire guage considerations, and storage of configuration information in EEPROM.<br>TLDR discusses the serial protocol for WS2812B. | <img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/02_PersistanceOfVision_PartA_FastLEDblink_setup.png" width="150" alt="Image of 02_PersistanceOfVision PartA: setup with LED Stick Blinking"><br><img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/WhirlingStick_HelloWorld.jpg" width="150" alt="Image of spinning LED Stick Blinking Hello World"> |
| [03_SonarRangeDetector](https://github.com/Mark-MDO47/ArduinoClass/tree/master/03_SonarRangeDetector "03_SonarRangeDetector") | Measure distances with ultrasonic waves to control a zillion LEDs<br>Consists of one project plus "Extra Fun" using really large collections of RGB LEDs<br>Youtube: https://youtu.be/0KehSIJmKcs<br>Discusses HC-SR04 Ultrasonic Range Finder, the ULTRASONIC library, and the famous DemoReel100 RGB LED demonstration program.<br>TLDR discusses speed of sound in air at different temperatures and also the Theremin musical instrument. | <img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/HC-SR04_Image.png" width="150" alt="picture of HC-SR04"><br><img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/03_SonarRangeDetector_241LED.png" width="150" alt="picture of 241 LED disk"> |
| [04_TheFinale](https://github.com/Mark-MDO47/ArduinoClass/tree/master/04_TheFinale "04_TheFinale") | Add sound and Bluetooth to our Sonar Range Detector and DemoReel100<br>Also do the same thing with Voice Commanding instead of Sonar Range Detector<br>A "sound add-on" takes this project close to the maximum practical size for breadboarding using this haywire approach. The voice commanding takes it even further, requiring two Arduino Nanos.<br>Youtube: https://youtu.be/G7ARC0xHXRg<br>Youtube: https://youtu.be/M8Xc4aVh5Hc<br>Discusses the YX5200 Sound Module using SD Card with sound files and the KCX_BT_EMITTER Bluetooth Transmitter.<br>Discusses the DF2301QG voice commanding module. | <img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/04_VC_setup_lights_on.jpg" width="150" alt="Image of 04_TheFinale: Voice Commands setup"><br><img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/04_SoundModules.png" width="150" alt="Image of 04_TheFinale: Sound and Bluetooth Modules"><br><img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/DF2301GQ.png" width="150" alt="Image of 04_TheFinale: Voice Command Module"><br><img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/04_smileyface.png" width="150" alt="Image of 04_TheFinale: Voice Command Demo Reel with smiley face"> |
| [05_ThatIsNotAll](https://github.com/Mark-MDO47/ArduinoClass/tree/master/05_ThatIsNotAll "05_ThatIsNotAll") | These are a few of my favorite things...<br>Youtube: https://youtu.be/VJ-WH86G7Pg | <img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/MadScience_400.png" width="150" alt="Image of Mark with Mad Scientist Goggles"> |
| [99_Resources](https://github.com/Mark-MDO47/ArduinoClass/tree/master/99_Resources "99_Resources") | Repository of class information.<br><br>External Image of Long Room Library at Trinity College from lh3.googleusercontent.com  | <img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/2021-10-07_Library_from_googleusercontent.com.jpg" width="150" alt="Image of Long Room Library at Trinity College"> |
| [ArduinoCode](https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/README.md "ArduinoCode") | Repository of code for the class projects.  | <img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/IDE_Blink.png" width="142" alt="Image of Arduino IDE"> |

## Parts Kit Provided
[Top](#arduino-class "Top")<br>
For this class I will provide a "kit" for each student station. I have labeled them "Kit 1" through "Kit 6"; Kit 1 is intended for me and the others are available for the class. Each kit includes all the major components for all the projects of our class except the "Extra Fun" section of the 03_SonarRangeDetector, for which we will share some extra equipment that I will bring. The Kit parts are still in the wrappers (except for the RGB LED Strips; I needed to solder on some wires) so if some do not work we will need to double up; maybe I would sacrifice my kit.

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/Kits_Class.png" width="300" alt="Image of Kits for Arduino Class">

Each of these kits costs about $8 today and I think you will experience that there are many exciting Arduino projects that can be performed inexpensively!

| Part | Cost on March 2023 | Source used |
| --- | --- | --- |
| Arduino Nano | $2.35 | aliexpress.com |
| Solderless Breadboard | < $2 | protosupplies.com |
| WS2812B RGB 8-LED Strip | < $2 | protosupplies.com |
| HC-SR04 Sonar Range Detector | < $2 | protosupplies.com |
| Button | ~ $0.10 | amazon.com |
| 200 Ohm resistor | ~ $0.10 | digikey.com |
| LED | ~ $0.10 | amazon.com |

You should then be able to do all of the standard projects. For the extra credit projects I will bring all the following for our use, to be moved from station to station.
- connectors, clips, harnesses, and wires
- large RGB Color LED Disks (93 LEDs and 241 LEDs) plus battery and UBEC power convertor (I will provide some to share between student stations)
- a breadboard with the sound circuitry (YX5200 sound module and KCX_BT_EMITTER Bluetooth module) for the finale project
- a breadboard with an extra Arduino Nano and a voice recognition and command module (DF2301QG) for the finale project

## Some other items used in the extra credit projects
[Top](#arduino-class "Top")<br>
These will be provide to share between the stations.<br>

| Part | Image |
| --- | --- |
| Mirror | <img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/mirror_from_bedbathandbeyond.com.png" width="100" alt="Image from bedbathandbeyond.com of a mirror for viewing persistence of vision"> |
| Large (93 or 241 LED) WS2812B disk | <img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/241LED_WS2812B.png" width="400" alt="Image of 241 LED WS2812B Disk"> |
| Battery, Universal Battery Eliminator Circuit (UBEC), (Frankenstein) knife switch | <img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/UBEC_PwrSetup.png" width="400" alt="Image of UBEC Power Setup"> |
| "Spinning Stick" Persistence of Vision wand with 8 WS2812B LEDs | <img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/02_PersistenceOfVision_PartC_stick_sideView.png" width="400" alt="Image of Sideview of Spinning Stick"> |
| Bluetooth and Sound Circuitry | <img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/BluetoothAndSoundCircuitry.png" width="800" alt="Image of Bluetooth and Sound Circuitry"> |
| Voice Command module | <img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/DF2301GQ_photo.png" width="800" alt="Image of Voice Command module"> |
| Bluetooth Speaker | <img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/BluetoothSpeaker.png" width="800" alt="Image of Bluetooth Speaker"> |

## Some other things you might see in the class
[Top](#arduino-class "Top")<br>
These will (probably) be present to play with in the class.

| Part | Image |
| --- | --- |
| [Park the Car](https://github.com/Mark-MDO47/KnowHow_ParkTheCar "Park the Car") box with 8 WS2812B LEDs and HC-SR04 Ultrasonic Range Detector | <img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/IMG07763_closed.png" width="400" alt="Image of Park-the-Car box"> |
| [Graduation Cap](https://github.com/Mark-MDO47/GraduationCap2017 "Graduation Cap") with 372 WS2812B LEDs controlled by 4 Arduino Nanos | <img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/IMG_09516_all.png" width="400" alt="Image of Graduation Cap"> |
| [SciFi Rubber Band Gun](https://github.com/Mark-MDO47/RubberBandGun "SciFi Rubber Band Gun") with 144 WS2812B LEDs and Bluetooth sound | <img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/OrangeTop_854_641.jpg" width="400" alt="Image of SciFi Rubber Band Gun"> |
| [SteamPunk Goggles](https://github.com/Mark-MDO47/Know-How-Arduino-SteamPunk-Goggles "SteamPunk Goggles") with 32 WS2812B LEDs | <img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/MarkMadScientistHead.png" width="300" alt="Image of SteamPunk Goggles"> |
| "... neither confirm nor deny" Coaster | <img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/NeitherConfirmNorDeny.png" width="400" alt="Image that can neither be confirmed nor denied"> |

## Please Bring USB Cable
[Top](#arduino-class "Top")<br>
Please try to bring a USB cable to connect from your laptop to the Arduino Nano. The Nano has a USB Mini-B female so your cable should end in USB Mini-B male; for more information see the references in lesson 01_BlinkingLED. I will have at least enough USB-A to USB Mini-B cables available for the 5 student stations, but if your laptop uses USB-C or anything but USB-A you will need to cover the gap.

The link below shows what many USB cables male and female connectors and sockets look like.
- https://en.wikipedia.org/wiki/USB

## Learning C and Cplusplus
[Top](#arduino-class "Top")<br>
One thing I learned when teaching the first class is that things will move much faster if everyone has some basic experience with a text-based programming language.

The Arduino IDE uses C and C++ languages (except for some of the I/O libraries, as explained later).
- If you have experience in any text-based programming language - Python, Java, or other programming languages - you will probably be able to catch on to the parts of C and C++ used in this class quickly.
- If you have never programmed before, I suggest you learn the basics of C before attending this class. You can easily pick up on the few parts of C++ used in this class if you have some knowledge of C (or even Python or Java or other languages)

One factor to consider: Arduino does not implement the standard "printing" etc. functions - not for C (printf and scanf) and not for C++ (IO Streams). Arduino uses relatively simple "Serial" methods such as Serial.begin, Serial.print and Serial.println for output; Serial.available and Serial.read and Serial.read variations for input. See the [Serial Main Page](https://www.arduino.cc/reference/en/language/functions/communication/serial/ "Link to Serial Main Page") for more details.
- If you want to learn the full languages to further your career, you will probably want to learn the standard C and C++ methods at the same time as learning enough C and C++ for this class. There is a lot to learn about C and C++!
- If you want to get started by doing some fun Arduino projects from this class you can skim the standard C and C++ methods, knowing that they are not used for these projects. You can return to the standard methods later.

Here are some web resources for learning the C language:
- https://www.java67.com/2020/07/5-free-courses-to-learn-c-programming.html
- https://medium.com/javarevisited/10-best-c-programming-courses-for-beginners-2c2c1f6bcb12

Here are a few of the highly rated **free** C-language ones from the above lists. I have not taken these classes myself but at a quick glance they seem OK.
- https://www.udemy.com/course/quickstart-guide-c-programming/
- https://www.udemy.com/course/c-programming-2019-master-the-basics/
- https://www.youtube.com/watch?v=KJgsSFOSQv0   C Programming Tutorial for Beginners (about 4 hours)
- https://www.educative.io/courses/learn-c-from-scratch

There are many books on learning the C language. I have no experience with most of them.<br>
The following book is how I learned the C language, back when dinosaurs ruled the earth. I really like its approach of building up knowledge in blocks such that you can use them immediately and they all fit together.<br>
- **The C Programming Language** by Brian W. Kernighan and Dennis M. Ritchie

If you search you might find the "mass-market paperback" at around $20 or maybe a used copy for even less.<br>
If you are going to get a copy, I suggest you try to get the latest edition. Since you will be investing the time, you might as well be close to up-to-date (2nd edition is Copyright 2012).

As an aside: some of the projects will use **binary** arithmetic and **Boolean** logic to implement simple data compression. We will do a quick discussion on how this code works when the time comes. This is another one of those topics that is important but could be skimmed if you just want to enjoy the project and study it later.

There is a quick discussion of binary and other numbering systems in the resources page:
- https://github.com/Mark-MDO47/ArduinoClass/tree/master/99_Resources#tldr-decimal-and-binary-and-hexadecimal

Binary and Boolean are discussed more fully in Wikipedia:
- https://en.wikipedia.org/wiki/Binary_number
- https://en.wikipedia.org/wiki/Boolean_algebra

## Kudos
[Top](#arduino-class "Top")<br>
By the way, Kudos to my son Carl for Alpha-Testing this class. You will see some images and videos of his work and may even catch a glimpse of him or me in the videos.
