# NOTES

## Back to Root of Class
Click this link to back to go back to the root of the Arduino class
- https://github.com/Mark-MDO47/ArduinoClass/tree/master


**Table Of Contents**
* [Top](#notes "Top")
* [Back to Root of Class](#back-to-root-of-class "Back to Root of Class")
* [HC-SR04 Ultrasonic Range Finder](#hc\-sr04-ultrasonic-range-finder "HC-SR04 Ultrasonic Range Finder")
* [Speed of Sound](#speed-of-sound "Speed of Sound")
* [Pros and Cons of HC-SR04](#pros-and-cons-of-hc\-sr04 "Pros and Cons of HC-SR04")
* [Theremin](#theremin "Theremin")
* [Circuit](#circuit "Circuit")
* [Code](#code "Code")
  * [Cleanup First](#cleanup-first "Cleanup First")
  * [Ultrasonic Range Finder Code](#ultrasonic-range-finder-code "Ultrasonic Range Finder Code")
* [Extra Fun](#extra-fun "Extra Fun")

## HC-SR04 Ultrasonic Range Finder
[Top](#notes "Top")<br>
The Student Kit for this class contains an HC-SR04 for use in this class.

If you want one for your home, the HC-SR04 can be found here (for example) for less than $2:
- https://protosupplies.com/product/hc-sr04-ultrasonic-range-finder-module/
- https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf
- https://www.tutorialspoint.com/arduino/arduino_ultrasonic_sensor.htm

This is typically used to determine ranges of objects from 2cm - 400cm non-contact.

Below is a picture of one of these detectors from our Kit:

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/HC-SR04_Image.png" width="640" alt="HC-SR04 Ultrasonic Range Finder image">

This description comes from the protosupplies.com website:
```
The way the HC-SR04 Ultrasonic Range Finder Module works is as follows:

1. The module is normally idle.
2. A 10 uSec or wider pulse is sent to the TRIG pin on the module, usually by a microcontroller.
   This will cause the module to start a detection cycle.
3. The module emits eight bursts of 40KHz sound and sets it’s ECHO pin output HIGH.
4. When the signal is reflected back from an object and is detected by the module, the ECHO pin is set back to LOW.
5.By measuring the amount of time that the ECHO pin is held HIGH, the distance to the object can be calculated
  using the basic formula  (Time that ECHO is held HIGH * Speed of sound / 2)
  The divide by 2 is because the sound has to travel in both directions (both out and back)
  and we want to know just the out distance.

If an echo is not returned (no object detected), the module will still lower the ECHO pin after a fixed delay.
This delay may vary, but is about 200mSec on the modules that I have measured.
This is required to prevent the module from hanging if there is no return echo.
```

This sequence is illustrated by the timing diagram below from the sparkfun.com HC-SR04 spec. Note that the top line represents the Trigger signal from the Arduino, the middle line represents the ultrasonic sound emitted, and the bottom pulse represents the Echo signal returning to the Arduino. The top and bottom pulses are at TTL (Transistor to Transistor) voltage levels. The bottom pulse has text that says "TTL lever" but that is just a typo; it should say "TTL Level". Where it says "range in proportion" it means that the time (width) of the HIGH pulse on the Echo signal when multiplied by a constant related to the speed of sound in air is the distance of the target from the HC-SR04. Our job will include measuring the time of the HIGH pulse and getting it multiplyied by that constant.<br>
![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/HC-SR04_Timing.png "sparkfun.com Image of HC-SR04 timing diagram")


## Speed of Sound
[Top](#notes "Top")<br>
From https://www.nde-ed.org/Physics/Sound/tempandspeed.xhtml 
```
Molecules at higher temperatures have more energy, thus they can vibrate faster. 
Since the molecules vibrate faster, sound waves can travel more quickly.
```

Data from https://www.nde-ed.org/Physics/Sound/tempandspeed.xhtml

| Temp degC | Temp DegF | Speed Meter/Sec | Speed Inch/Sec | Speed Ft/Sec |
| --- | --- | --- | --- | --- |
| 45 | 113 | 358.0 | 14,095 | 1,175 |
| 21 | 69.8 | 343.6 | 13,528 | 1,127 |
| -1 | 30.2 | 330.4 | 13,008 | 1,084 |

## Pros and Cons of HC-SR04
[Top](#notes "Top")<br>
Many people have noted pros and cons of the HC-SR04, such as
- https://github.com/shurik179/DualSonar

```
HC-SR04 are cheap and reliable ultrasonic sensors, used in many robotics projects
with Arduino or similar microcontrollers. However, they have two drawbacks:

1. The standard method of reading the sensor in Arduino, using PulseIn() function,
   ties up the microcontroller for up to 30ms and interferes with tasks which need
   to be run frequently such as WiFi communication using Blynk or reading input
   from other sensors over serial interface.
2. Each sensor requires 2 pins, so if you have several ultrasonic senors, you run out of pins quickly.

There are some ways to mitigate these probems, such as using interrupts instead of PulseIn
or using NewPing library which allows one to use only one pin per sensor.
```

Fortunately, the delay from the HC-SR04 gets shorter as the distance of the detected object gets closer. In this project we will use the HC-SR04 for short distances, and the long 200 millisecond timeout if there is no detected object won't bother us too much since we won't have time critical tasks when that happens. Thus we can use the standard PulseIn() function or equivalent.

In fact we will use the Ultrasonic library to work with this sensor:
- https://www.arduinolibraries.info/libraries/ultrasonic

This code does the typical single-threaded wait for the return ECHO as seen in this code snippet:
```C
  previousMicros = micros();
  while(!digitalRead(echo) && (micros() - previousMicros) <= timeout); // wait for the echo pin HIGH or timeout
  previousMicros = micros();
  while(digitalRead(echo)  && (micros() - previousMicros) <= timeout); // wait for the echo pin LOW or timeout
```

This code does have a **setTimeout()** function if we want to prevent extremely long delays. The manual seems to imply that we would not want to sense the HC-SR04 more often than once every 60 milliseconds.

## Theremin
[Top](#notes "Top")<br>
We will use the HC-SR04 to detect the position of our hand and use that to control the light displays on our LED strip. This use of hand position is similar to the way the musical intrument Theremin controls the sound by detecting hand position. Theremin was the English spelling of the last name of the inventor of the musical instrument.
- https://en.wikipedia.org/wiki/Theremin

Here is a picture from that Wikipedia article of Alexandra Stepanoff playing the theremin on NBC Radio in 1930.

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/Theramin-Alexandra-Stepanoff-1930_from_wikimedia.org.jpg "from wikimedia.org an image of Alexandra Stepanoff playing the theremin on NBC Radio in 1930")

Essentially, we will start with the DemoReel.ino file from 02 Part D and replace the USB serial commands with detection of hand position by the HC-SR04.

## Circuit
[Top](#notes "Top")<br>
Here is the circuit for the Theremin project.
- https://github.com/Mark-MDO47/ArduinoClass/blob/master/03_SonarRangeDetector/03_SonarRangeDetector.pdf

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/03_SonarRangeDetector.png" width="750" alt="Image of wiring diagram for Theremin (Sonar Range Detector)">

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/03_SonarRangeDetector_Fritzing.png" width="750" alt="Fritzing image of wiring diagram for the Sonar Range Detector">

I think you can figure out how I decided to connect the Arduino pins to the HC-SR04. If you have any questions please ask them in class to make sure everyone understands the rationale.

I left the button circuit in. We will not use it, so if you wish you can remove it. If you leave it in then the only changes in the circuit will be four wires to connect to the HC-SR04.

Here is an image showing how to connect to the HC-SR04 to the jumper wires.

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/03_SonarRangeDetector_connections.png "Image of connections to HC-SR04 Ultrasonic Range Detector")

Here is an image of the setup for the Sonar Range Detector project.

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/03_SonarRangeDetector_8LED_setup.png "Image of setup for 03 Sonar Range Detector with the 8-LED strip")

## Code
[Top](#notes "Top")<br>
Below we modify the code to act as our "Theremin" for lights.

### Cleanup First
[Top](#notes "Top")<br>
This time we will delete the old code first, then add the new code.

Copy 02 Part-D DemoReel.ino into a directory named Theremin and name the file Theremin.ino.

We delete all the code relating to the USB serial port input; we will leave the code that prints in case we need it for debugging.<br>
Delete these lines
```C
#define SERIAL_MAX_INPUT_LEN 5 // maximum number of characters to accept in one command; otherwise flush to next newline and process what we have
#define SERIAL_INPUT_BUF_LEN (SERIAL_MAX_INPUT_LEN + 5) // size of our actual buffer; room for terminating '\0' and a little extra

static char serial_input_buf[SERIAL_INPUT_BUF_LEN]; // one character for terminating '\0'
```

Delete everything for the following routines
- handle_serial_input_command()
- handle_serial_input()

Delete these lines in **setup()**
```C
  while (Serial.available()) Serial.read(); // clear any startup junk from the serial queue
  memset((void *)serial_input_buf, 0, SERIAL_INPUT_BUF_LEN); // clear buffer; good idea for zero-terminated strings

  Serial.println("Commands:");
  Serial.println("0: rainbow");
  Serial.println("1: rainbowWithGlitter");
  Serial.println("2: confetti");
  Serial.println("3: sinelon");
  Serial.println("4: juggle");
  Serial.println("5: bpm");
  Serial.println("");
```

Delete these lines in **loop()**
```C
  // process USB serial command characters if present
  if (Serial.available()) handle_serial_input();
```

### Ultrasonic Range Finder Code
[Top](#notes "Top")<br>
First we ensure that the Ultrasonic library is installed in the Arduino IDE

Picture of Arduino IDE starting Library Manager<br>
![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/IDE_ManageLibraries.png "Image of IDE starting Library Manager")

Picture of Arduino IDE Library Manager showing Ultrasonic library is NOT installed<br>
![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/IDE_Ultrasonic.png "Image of Library Manager showing Ultrasonic is not installed")

Picture of Arduino IDE Library Manager showing Ultrasonic library IS installed<br>
![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/IDE_Ultrasonic_installed.png "Image of Library Manager showing Ultrasonic is installed")

Then put the following immediately either before or after the **#include "FastLED.h"**
```C
#include "Ultrasonic.h"
```

Near the other pin definitions place the following
```C
#define ULTRA_TRIG_PIN 12 // HC-SR04 Trigger digital pin
#define ULTRA_ECHO_PIN 10 // HC-SR04 Trigger echo pin
#define ULTRA_CM_PER_REGION 9 // HC-SR04 every this many CM is a different pattern
#define ULTRA_IGNORE_INITIAL_CM 3 // HC-SR04 ignore the first 3 CM since valid range starts at 2 CM

// instantiate my HC-SR04 data object
Ultrasonic my_ultra = Ultrasonic(ULTRA_TRIG_PIN, ULTRA_ECHO_PIN); // default timeout is 20 milliseconds

```

After the line **SimplePatternList gPatterns = { rainbow, ... };**
```C
char * gPatternStrings[1+PATTERN_MAX_NUM] = { "0 rainbow", "1 rainbowWithGlitter", "2 confetti", "3 sinelon", "4 juggle", "5 bpm" };
int gPrevPattern = -1;
```

Before **setup()**
```C
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// handle_ultra() - process HC-SR04 data.
//    returns: pattern number 0 <= num <= PATTERN_MAX_NUM
//

int handle_ultra() {
  int pattern; // integer pattern number from 0 thru 5 inclusive
  // get the range reading from the Ultrasonic sensor in centimeters
  int ultra_dist=(my_ultra.read(CM));
  
  ultra_dist -= ULTRA_IGNORE_INITIAL_CM;
  if (ultra_dist < 0) ultra_dist = 0;
  pattern = ultra_dist / ULTRA_CM_PER_REGION;
  if (pattern > 5) pattern = 5;

  return(pattern);
} // end handle_ultra()

```

Insert this at the start of **loop()** before the line that says **gPatterns\[gCurrentPatternNumber\]();**
```C
  EVERY_N_MILLISECONDS( 200 ) { gCurrentPatternNumber = handle_ultra(); }
  if (gPrevPattern != gCurrentPatternNumber) {
    gPrevPattern = gCurrentPatternNumber;
    Serial.println(gPatternStrings[gCurrentPatternNumber]);
  }

```

Now compile, load and run the code. As you move your hand closer and farther away from the HC-SR04 you should see the patterns displayed change. The first and last ranges are bigger, but in the middle the width of the range for a particular pattern is about 9 cm or a little bigger than 3 inches. You can start the serial monitor and it will tell you which pattern is displaying.

## Extra Fun
[Top](#notes "Top")<br>
I will bring to the class one or two large WS2812B disks such as this 241 LED WS2812B disk or maybe some 93 LED WS2812B disks. There will not be enough for each station but everyone will be able to modify NUM_LEDS in Theremin.ino and try it out, based on the number of LEDs in the disk. It really looks spectacular!

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/241LED_WS2812B.png "Image of 241 LED WS2812B disk")

However, this will definitely exceed the amount of power we want to pass through the Arduino Nano so we will need to modify the circuit so power to the LEDs does not come from the Arduino.<br>
For this purpose I often use a UBEC (Universal Battery Eliminator Circuit). This device will typically take as input something in the range of about 6V to 28V DC and usually has selectable output voltage of either 5V or 6V. If we attach a 9V battery to the UBEC, it will be able to power the LED Disk.<br>
![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/UBEC.png "Image of typical UBEC")

FYI at this time a 93 LED WS2812B disk is about $20 and a 241 LED WS2812B disk is about $28. A 5V 3A output UBEC is about $13 in a 5-pack.

Here is a wiring diagram for the LED Strip circuit with the UBEC supplying power to the LED Disk. The color scheme of the unmodified 241-LED ring is red/white/green not red/black/green; I put this indication on the image. Note also that I connect the UBEC and Arduino ground but do not connect the power between them; I don't want the Arduino power from the USB to "fight" against a slight difference with the UBEC power.
- https://github.com/Mark-MDO47/ArduinoClass/blob/master/03_SonarRangeDetector/03_SonarRangeDetector_ExtraFun.pdf<br>
<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/03_SonarRangeDetector_ExtraFun.png" width="501" alt="Image of wiring diagram for 03 Sonar Extra Fun">

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/03_SonarRangeDetector_ExtraFun_Fritzing.png" width="750" alt="Fritzing image of wiring diagram for the Sonar Range Detector">

It is often good practice to put some capacitors in the power circuit to smooth out the power when the load varies, but for this experiment we won't do that.

Here is an image of the setup for the 241-LED disk

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/03_SonarRangeDetector_241LED_setup.png "Image of setup for 03 Sonar Range Detector with the 241-LED disk")

A YouTube of this in operation on a 241 LED SW2812B disk can be seen here:
- https://youtu.be/0KehSIJmKcs
