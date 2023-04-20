# NOTES

**Table of Contents**
* [Top](#notes "Top")
* [Connect the Arduino Nano to the USB cable](#connect-the-arduino-nano-to-the-usb-cable "Connect the Arduino Nano to the USB cable")
* [Run the example Blink program](#run-the-example-blink-program "Run the example Blink program")
* [Part A - Add an external LED](#part-a-\--add-an-external-led "Part A - Add an external LED")
* [Part B - Add Button and Display Messages on USB Serial Port](#part-b-\--add-button-and-display-messages-on-usb-serial-port "Part B - Add Button and Display Messages on USB Serial Port")
* [Resources](#resources "Resources")

## Connect the Arduino Nano to the USB cable
[Back to Top](#notes "Back to Top")

![alt text](https://www.circuitstoday.com/wp-content/uploads/2018/02/Arduino-Nano-Pinout.jpg "CircuitsToday.com picture of Arduino Nano")

I will provide four Arduino Nano clones and some supporting hardware for use during the class.

The Arduino Nano uses a USB Mini-B female and thus needs a cord from your laptop with a USB Mini-B Male connector. If your laptop has a USB A connection then I have cords you can use; otherwise please provide your own method to connect to either Mini-B directly or to bridge the gap to the USB A connector on the cord I can provide (for instance, if you only have USB C connectors). This USB connection provides both a serial port (for uploading and communication) and power/ground. The link below shows what many USB cables and sockets look like.
- https://en.wikipedia.org/wiki/USB

To connect your computer to the Arduino Nano
- Connect the Arduino Nano to a USB port on your computer.
- Start the Arduino IDE and in the menu **Tools** -> **Board: ...** select **Arduino Nano**.

These are relatively old Arduino Nanos.
- In the Arduino IDE menu **Tools** -> **Processor** -> **ATmega328P** select **Old Bootloader**.
- **Programmer** should then automatically be selected as **AVRISP mkll**.

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/ConfigUSB.png "Configure USB port for old Arduino Nano")

## View an Empty Sketch (Arduino program)
The Arduino IDE uses a variant of the C++ language. You can program in a C++ style or a C style. The code that we will use in this course will be quite straighforward and should be understandable if you know any computer language. One thing to note about C/C++: array indices start with zero.

An Arduino program (called a "sketch" in Arduino-speak) is typically stored with extension ".ino". If you save your program as fred.ino, you will find that it is saved in a directory named fred.

When opening the Arduino IDE you will initially see the empty sketch (program) as shown below. This is the standard architecture for Arduino code. It is possible to extend this to use interrupts, go to low power modes, and other special-purpose things. For our class we will just use the standard architecture as seen below.

```C
void setup() {
 // put your setup code here, to run once:
}
void loop() {
 // put your main code here, to run repeatedly:
}
```

## Run the example Blink program
[Back to Top](#notes "Back to Top")

In the Arduino IDE, choose menu **File** -> **Examples** -> **01.Basics** -> **Blink**. This will bring up the starting point for our Blink exercise.

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/IDE_LoadBlink.png "Arduino IDE loading Blink example program")

In the **setup()** function you will find a "pinMode" call; this sets the internal "pin" to OUTPUT mode so we can turn the internal LED on and off.
- LED_BUILTIN is a symbol for the "pin" number that controls the builtin LED; this symbol will automaticall be correct on any Arduino.

The **setup()** function is called only once, before ever calling the **loop()** function.

In the **loop()** function you will find that it delays 1000 milliseconds, turns the LED **ON**, delays 1000 milliseconds, and turns the LED **OFF**.

Because the **loop()** function is called over and over, this will continue until you stop it by reprogramming or powering off the Arduino Nano.

With the Arduino connected to the USB port on your computer, use the button circled in red below to compile, load, and run the Blink example program. The on-board LED should blink.

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/IDE_CompileAndRun.png "Arduino IDE compile-load-run button")

**CONGRATULATIONS!** You have executed your first Arduino program!

## Part A - Add an external LED
[Back to Top](#notes "Back to Top")

We will be using a solderless breadboard to implement parts of our circuit. Connections are made by plugging wires or components into the holes in the board. A youtube of connecting LEDs to a solderless breadboard can be found at this link:
- https://www.youtube.com/watch?v=UvS9Wf2BoyE

A good guide to solderless breadboards can be found at this link:
- https://protosupplies.com/guide-to-solderless-breadboards/

Here from the above link is an image of a typical solderless breadboard.

![alt text](https://protosupplies.com/wp-content/uploads/2018/12/Breadboard-Details.jpg "Image of typical solderless breadboard from protosupplies.com")

Be aware that a circuit laid out on such a solderless breadboard can then be transferred to a solderable breadboard PCB board fairly easily. See the comparison between these two below.

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/Breadboard_Solderboard.png "Image of a solderless breadboard and a solderable breadboard PCB board")

As you undoubtedly know, LEDs are designed to be connected with positive voltage on the + side and ground or negative voltage on the - side. If this rule is not followed, the LED will either not work or burn up. Also you will need a 300 or 220 ohm resistor in series to prevent burning out the LED and prevent damaging the Arduino Nano.
- https://makecode.adafruit.com/learnsystem/pins-tutorial/devices/led-connections

Here from the above link is a diagram showing how to identify the polarity (+ and - pins) of an LED:

![alt text](https://pxt.azureedge.net/blob/03fec9ac9dbaee9f745ae2beda43fc15119c1c20/static/cp/learn/pins-tutorial/devices/led-polarity.jpg "Adafruit.com polarity of LED")

Here from the above link is a diagram showing a simple battery circuit to light up an LED. Note the resistor to prevent burning out the LED. This is NOT our Arduini circuit; it just shows how to make an LED light up with a battery.
![alt text](https://pxt.azureedge.net/blob/2ebeedcf4108aa2a5ecc9b8b232cbb5960b2dfb6/static/cp/learn/pins-tutorial/devices/led-connection.jpg 
"Adafruit.com Resistor and LED in circuit")

We will use the breadboard and connectors I supply to implement the following circuit. **Remember** to put the **"+"** side of the LED towards the resistor which connects to Digital I/O pin 3 (hereafter I would refer to this as D3 or D03). The schematic symbol for the Light Emitting Diode (or any diode) has the arrow pointing from the positive side to the negative side.
- https://github.com/Mark-MDO47/ArduinoClass/blob/master/01_BlinkingLED/01_Blinking_LED_part_A_Schematic.pdf

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/01_BlinkingLED_part_A_Schematic.png "Circuit Diagram of 01-Part-A: our external LED connections")

Here are the changes we will make to the standard Blink program; first in (or before) **setup()**:

```C
#define DPIN_LED_OUT 3 // in case we want to move it, only need to change this

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  // initialize our new pin for external LED
  pinMode(DPIN_LED_OUT, OUTPUT);      // digital OUTPUT means we control voltage on pin, HIGH or LOW
}
```

And now the changes for **loop()**:

```C
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(DPIN_LED_OUT, LOW);   // turn the external LED off
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(DPIN_LED_OUT, HIGH);  // turn the external LED on
  delay(1000);                       // wait for a second
}
```

When we execute this program, the internal LED and the external LED blink; one is off when the other is on.

## Part B - Add Button and Display Messages on USB Serial Port
[Back to Top](#notes "Back to Top")

Now we will add a push button for digital input. We will also start using the USB serial port for diagnostic output - a fantastically useful diagnostic tool. Note that this USB serial port can also be used for input.

Here is what our new circuit looks like:
- https://github.com/Mark-MDO47/ArduinoClass/blob/master/01_BlinkingLED/01_Blinking_LED_part_B_Schematic.pdf

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/01_BlinkingLED_part_B_Schematic.png "Circuit Diagram of 01-Part-B: add button")

We will configure the input pin D05 as **INPUT_PULLUP**; this means that the Arduino Nano will connect it internally to the +5V "rail" using a resistance that minimizes power loss, probably about 5,000 or 10,000 ohms. This could be written as 5Kohm or 10Kohm.
- When the switch is OPEN (disconnected or not pushed) then the voltage on the pin is HIGH (close to +5V) and will be sensed as HIGH.
- When the switch is CLOSED (connected or pushed) the pin is grounded by a low-resistance path; therefore the voltage on the pin is LOW (close to GND) and will be sensed as LOW.

In reality, I don't often rely on this internal pullup because I use a lot of inexpensive Arduino Nano clones that can be sensitive to heat and a bit fragile, so I usually have an external resistor for the pullup as can be seen in the upper left-hand side of this schematic for one of my recent projects:
- https://github.com/Mark-MDO47/RubberBandGun/blob/master/RubberBandGun_Wiring.pdf

For our USB Serial communications we will use some **Serial.*()** routines such as Serial.begin(), Serial.print(), and Serial.println(). These are documented starting in this area:
- https://www.arduino.cc/reference/en/language/functions/communication/serial/

For instance, the various ways to use Serial.print() are documented here
- https://www.arduino.cc/reference/en/language/functions/communication/serial/print/

When using the USB serial port, the Arduino IDE "Serial Monitor" needs to be started as seen here:

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/Config_USB_SerialMonitor.png "Start Arduino IDE Serial Monitor")

The screen itself looks like this:

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/Config_USB_SerialMonitor_screen.png "Arduino IDE Serial Monitor Screen")

Now our one-time **setup()** code is starting to be a little more complex. I am sure you can figure out what the new code does even if some techniques are unfamiliar to you.
```C
#define DPIN_LED_OUT 3 // this pin drives the external LED
#define DPIN_BTN_IN  5 // this pin is used to sense the external button
static int loop_count = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // initialize digital pin LED_BUILTIN as an output.
  pinMode(DPIN_LED_OUT, OUTPUT);      // digital OUTPUT means we control voltage on pin, HIGH or LOW
  pinMode(DPIN_BTN_IN, INPUT_PULLUP); // digital INPUT_PULLUP means voltage HIGH unless grounded

  Serial.begin(115200);         // this serial communication is for general debug; set the USB serial port to 115,200 baud

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println(""); // print a blank line in case there is some junk from power-on
  Serial.println(F("ArduinoClass init..."));
}
```

The **loop()** code is also more complex. I tried to write it in a simple style; we will discuss it in the class.
```C
void loop() {
  int btn_val = digitalRead(DPIN_BTN_IN);

  if (HIGH == btn_val) { // push button to STOP light blinking
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(DPIN_LED_OUT, LOW);   // turn the external LED off
  } // end if btn_val HIGH
  delay(1000);                       // wait for a second
  if (HIGH == btn_val) {
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(DPIN_LED_OUT, HIGH);  // turn the external LED on
  } // end if btn_val HIGH
  delay(1000);                       // wait for a second

  loop_count += 1;    // instead of loop_count = loop_count + 1
  Serial.print("Button ");
  if (HIGH == btn_val) {
    Serial.print("UP   (GO)  ");
  } else {
    Serial.print("DOWN (STOP)");
  } // end if statement on btn_val
  Serial.print(" loop_count: "); Serial.println(loop_count);
}
```

### Some Arduino and C-language features not used above
[Back to Top](#notes "Back to Top")

C-language has some useful but perhaps obscure features; I will just mention one here for those that want to explore further. It is possible to compress the code above a little using the **?:** operator. This takes a **Condition** and chooses one of two results separated by the **:**. For instance:
- Condition?X:Y

If Condition is true then the resulting value is X : otherwise the resulting value is Y.

To use this to print either UP or DOWN we could say
```C
  Serial.print((HIGH == btn_val) ? "Button UP   (GO)  " : "Button DOWN (STOP)");
```

There are many other ways we could re-arrange the printing to minimize calls to the Serial.*() routines, or to minimize RAM usage, etc. One of these is use of the "F" macro to put strings into program memory instead of RAM - RAM can be precious when programming Arduino. If you are interested in some of these, see **PROGMEM and "F" macro** in the **Resources** section and/or talk with me after the class.

## Resources
### Arduino Nano and ATMEGA 328P
We will be using Arduino Nano clones in our projects. You can ignore the following for our class; this is for follow-up by interested persons.

Lots of info on the Arduino Nano is found here (diagrams, not schematics)
* https://www.circuitstoday.com/arduino-nano-tutorial-pinout-schematics

The ATMEGA 328P chip used in the Arduino Nano is described here
* http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf

Mapping the ports to the internal registers is described here
* https://www.arduino.cc/en/Reference/PortManipulation

### My favorite Arduino clone - ESP32
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

### PROGMEM and "F" macro to save RAM
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
