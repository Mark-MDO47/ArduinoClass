# It is a wide world out there

I hope that this sparks your interest in doing fun electronics hobby projects! I may teach some classes on other parts of the hobby electronics and software world if there is interest. I am hoping to meet folks with interests in some of the hobbies I have.

Before getting into some of the boards, modules and systems that I enjoy using, I want to remind you to check out the Resources page for this class. It has pointers to information and also a list of intriguing project possibilities.
- https://github.com/Mark-MDO47/ArduinoClass/tree/master/99_Resources

There are many types of Arduinos and many sensors that can connect to Arduinos and even other types of boards that serve similar purposes.

**Table of Contents**
* [Top](#it-is-a-wide-world-out-there "Top")
* [Favorite Boards](#favorite-boards "Favorite Boards")
* [Favorite Devices](#favorite-devices "Favorite Devices")
* [Projects I want to Restart](#projects-i-want-to-restart "Projects I want to Restart")
* [Non-Electronics Non-Software](#non\-electronics-non\-software "Non-Electronics Non-Software")
* [Arduino Park the Car Helper](#arduino-park-the-car-helper "Arduino Park the Car Helper")

## Favorite Boards
[Top](#it-is-a-wide-world-out-there "Top")<br>
Here are a few of my favorite boards
- I have already mentioned that my current favorite Arduino is the ESP32 series. These include WiFi and Bluetooth on board plus lots more RAM and Program memory and even dual CPUs for the brave! You can also update your program over WiFi and even debug over WiFi.
- There are boards with similar capabilities to the Arduino that contain small FPGAs (Field Programmable Gate Arrays) that can be programmed to do fast things such as video controllers.
- There are boards similar to the Raspberry Pi that can run real versions of Linux or the stripped down versions such as the Raspberry Pi version of Linux
- One of the things that really excites me is the Nvidia Jetson Nano series of boards, with a CPU of the approximate power of the Raspberry Pi plus the addition of a powerful Nvidia Cuda engine similar to the Nvidia graphics boards that can be used for graphics processing or for Artificial Intelligence. Even the original version of the lowest-end Jetson card has an astonishing 472 MegaFlops of 16-bit floating point!

## Favorite Devices
[Top](#it-is-a-wide-world-out-there "Top")<br>
These are just a few of the devices I have used or will be using in my next projects
- The YX5200 Audio Player which can drive speakers or headphones from sound files you place on its SD card slot. https://github.com/Mark-MDO47/AudioPlayer-YX5200
- The KCX_BT_EMITTER Bluetooth Audio Transmitter that can take the audio from the YX5200 and send it to a bluetooth speaker. https://github.com/Mark-MDO47/BluetoothAudioTransmitter_KCX_BT_EMITTER
- UBEC (Universal Battery Eliminator  Circuit) https://github.com/Mark-MDO47/ArduinoClass/tree/master/03_SonarRangeDetector
- RGB LEDs especially WS2812B and the FastLED library https://github.com/Mark-MDO47/ArduinoClass/tree/master/02_PersistenceOfVision

## Projects I want to Restart
[Top](#it-is-a-wide-world-out-there "Top")<br>
Some of the projects I have started but have placed on hold the last two years when I was very busy are listed below. Maybe some of you would be interested in participating in one of these?
- https://github.com/Mark-MDO47/FPGA_RBG_2_RBGW - use a low-cost Lattice iCE40 Verilog FPGA to convert the FastLED WS2812b **RGB** serial stream to drive an SK6812 **RGBW** strip
- https://github.com/Mark-MDO47/FastLED - alternatively, hack the FastLED library to use the hardware features of the ESP32 (normally used on infrared controllers) so it can drive an SK6812 **RGBW** strip
- https://github.com/Mark-MDO47/Cartoonify - use an Nvidia Jetson Nano to make a camera that uses AI to identify objects in the picture, match that with a hand-drawn cartoon from the Google quickdraw dataset, and print that cartoon on a thermal printer instead of the original picture
- https://github.com/Mark-MDO47/MyThinkstOpenCanary - use a Raspberry Pi to implement the open-source version of the Thinkst Canary and put a honey-pot on the home network to detect if bad guys are in there
- Automate the updates and backups on the home network using Ansible
- Learn pfSense and upgrade my home network's implementation of Steve Gibson's "Three Dumb Routers" to use my Netgate SG3100 router appliance

## Non-Electronics Non-Software
[Top](#it-is-a-wide-world-out-there "Top")<br>
One project I will be tackling soon is the renovation of my harpsichord, which is a keyboard instrument that plucks the strings instead of hammering them. This instrument was popular in Mozart's time.<br>
- I got my low-end harpsichord in about 1979 by trading my MGB for it (interesting story - ask me sometime) and it was already second or third-hand when I got it. I estimate its age as about 70-80 years.
- The felts that damp out the sound when the key is dropped need to be replaced. I finally found a felt wholesaler (!) and got some felt of the correct thickness so I can start on this.

Another project of interest is "fake" radio tubes - look something like vacuum tubes and glow, probably by using a single WS2812B RGB LED.
- https://www.instructables.com/LED-Vacuum-Tubes/
- Also I have been gifted a few real vacuum tubes and will put LEDs on the bottom of them

## Arduino Park the Car Helper
[Top](#it-is-a-wide-world-out-there "Top")<br>
Now just for a laugh - many years ago I saw a post from someone that said they were trying to use an Arduino to help park the car in the right position.  That post included pictures similar to but much better than the ones below.

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/ArduinoParkingHelper_1.jpg "Image 1 of Arduino project to help park the car")

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/ArduinoParkingHelper_2.jpg "Image 1 of Arduino project to help park the car")

Thank you and Enjoy!<br>
Mark
