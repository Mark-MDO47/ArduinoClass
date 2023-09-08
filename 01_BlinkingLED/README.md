# NOTES

## Back to Root of Class
Click this link to back to go back to the root of the Arduino class
- https://github.com/Mark-MDO47/ArduinoClass/tree/master


**Table of Contents**
* [Top](#notes "Top")
* [Introducing the Arduino Nano](#introducing-the-arduino-nano "Introducing the Arduino Nano")
* [Connect the Arduino Nano to the USB cable](#connect-the-arduino-nano-to-the-usb-cable "Connect the Arduino Nano to the USB cable")
* [Run the example Blink program](#run-the-example-blink-program "Run the example Blink program")
* [Now It Runs Whenever you Turn On Power](#now-it-runs-whenever-you-turn-on-power "Now It Runs Whenever you Turn On Power")
* [Part A - Add an external LED](#part-a-\--add-an-external-led "Part A - Add an external LED")
  * [TLDR the Arduino delay function](#tldr-the-arduino-delay-function "TLDR the Arduino delay function")
  * [Try it Part A](#try-it-part-a "Try it Part A")
* [Part B - Add Button and Display Messages on USB Serial Port](#part-b-\--add-button-and-display-messages-on-usb-serial-port "Part B - Add Button and Display Messages on USB Serial Port")
  * [Try it Part B](#try-it-part-b "Try it Part B")
* [Resources](#resources "Resources")

## Introducing the Arduino Nano
[Back to Top](#notes "Back to Top")<br>
![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/Arduino-Nano-Pinout_from_circuitstoday.com.png "CircuitsToday.com picture of Arduino Nano")

The Student Kit includes an Arduino Nano clone. I will also bring some additional supporting hardware for use during the class. The above image is from CircuitsToday.com.

The Arduino is one of a class of open-source hardware single-module computers designed by an organization named Arduino. They build the genuine Arduino boards and make the designs avaliable. There are many companies either making clones (such as the ones in our Student Kit) or extending the family (such as the ESP32, currently my favorite Arduino variant).
- https://www.arduino.cc/en/about
- https://www.arduino.cc/en/hardware

These Arduino Nanos have 32Kbyte of FLASH memory (program storage), 2Kbyte of SRAM, and 1Kbyte of EEPROM.
- FLASH memory (no acronym) was an offshoot of EEPROM. For the Arduino Nano it is erasable and writeable in blocks of many bytes. FLASH is found in thumb drives, SD cards, and many other applications.
- EEPROM (Electrically Eraseable Programmable Read-Only Memory) is, for the Arduino Nano, erasable and writeable in blocks of one byte.
- SRAM (Static Random Access Memory) is, for the Arduino Nano, readable and writeable in blocks of one byte. There is typically no published limit on the number of times it can be read or written. It is somewhat faster to read than the FLASH or EEPROM and much much faster to write.

## Connect the Arduino Nano to the USB cable
[Back to Top](#notes "Back to Top")<br>
The Arduino Nano uses a USB Mini-B female and thus needs a cord from your laptop with a USB Mini-B Male connector. If your laptop has a USB A connection then I have cords you can use; otherwise please provide your own method to connect to either Mini-B directly or to bridge the gap to the USB A connector on the cord I can provide (for instance, if you only have USB C connectors). This USB connection provides both a serial port (for uploading and communication) and power/ground. The link below shows what many USB cables male and female connectors and sockets look like.
- https://en.wikipedia.org/wiki/USB

To minimize wear and tear on the Arduino Nano, after connecting the Arduino to the USB cable, one can disconnect at the PC or laptop side instead of the Arduino side.

To connect your computer to the Arduino Nano
- Connect the Arduino Nano to a USB port on your computer.
- Start the Arduino IDE and in the menu **Tools** -> **Board: ...** select **Arduino Nano**.

The Student Kit boards are built from relatively old Arduino Nano designs.
- In the Arduino IDE menu **Tools** -> **Processor** -> **ATmega328P** select **Old Bootloader**.
- **Programmer** should then automatically be selected as **AVRISP mkll**.

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/ConfigUSB.png "Configure USB port for old Arduino Nano")

## View an Empty Sketch (Arduino program)
[Back to Top](#notes "Back to Top")<br>
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
[Back to Top](#notes "Back to Top")<br>
In the Arduino IDE, choose menu **File** -> **Examples** -> **01.Basics** -> **Blink**. This will bring up the starting point for our Blink exercise.

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/IDE_LoadBlink.png "Arduino IDE loading Blink example program")

If for some reason you do not have access to that you can find a copy (from 2023-08) in this area under _Examples_ArduinoIDE/Blink:
- https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode

In the **setup()** function you will find a "pinMode" call; this sets the internal "pin" to OUTPUT mode so we can turn the internal LED on and off.
- LED_BUILTIN is a symbol for the "pin" number that controls the built-in LED on the Arduino. This LED_BUILTIN symbol will automatically be correct when compiling for any Arduino.

The **setup()** function is called only once, before ever calling the **loop()** function.

In the **loop()** function for the example Blink program you will find that it delays 1000 milliseconds, turns the LED **ON**, delays 1000 milliseconds, and turns the LED **OFF**.

Because the **loop()** function is called over and over, this will continue until you stop it by reprogramming, resetting, or powering off the Arduino Nano.

With the Arduino connected to the USB port on your computer, use the button circled in red in the image below to compile, load, and run the Blink example program. The on-board LED should blink.

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/IDE_CompileAndRun.png "Arduino IDE compile-load-run button")

**CONGRATULATIONS!** You have executed your first Arduino program!

## Now It Runs Whenever you Turn On Power
[Back to Top](#notes "Back to Top")<br>
Now that you have loaded a program into the "Program Memory" of the Arduino, it stays there when you power-off or disconnect the Arduino. If you unplug the USB cord, let the Arduino power off completely, and then plug the cord in again you will see that it runs the Blink program again after a short bootup.

This is how you can include an Arduino into your projects. You don't have to connect to a computer and program it each time; it will remember the last program you loaded because the program is stored in FLASH memory which persists across power-cycle.

You also can but don't have to power the Arduino through the USB port. Another way to power the Arduino is to use the Arduino pin marked VIN. If you provide 5 volts on VIN and connect ground to one of the GND pins, the last program will run again. Most Arduinos are able to run with a small range of voltages near 5 volts fed into the VIN pin; always be sure to check the documentation for the correct voltage range before doing this.

## Part A - Add an external LED
[Back to Top](#notes "Back to Top")<br>
We will be using a solderless breadboard to rapidly implement parts of our circuit. Connections are made by plugging wires, jumpers, or components into the holes in the board. A youtube video of connecting LEDs to a solderless breadboard can be found at this link.  NOTE: to play youtube and keep this tab open you must right-click the link and select to play in a new tab.
- https://www.youtube.com/watch?v=UvS9Wf2BoyE

A good guide to solderless breadboards can be found at this link:
- https://protosupplies.com/guide-to-solderless-breadboards/

Here from the above link is an image of a typical solderless breadboard.

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/Breadboard-Details_from_protosupplies.com.jpg "Image of typical solderless breadboard from protosupplies.com")

If you have not worked with a solderless breadboard before, it might be worthwhile to look the above image over in detail. Try to find which pins distribute power and ground vertically (the long way on the breadboard), which pins distribute signals side-to-side, and how far the signals get distributed in these directions.

Something that may help, again from that protosupplies.com article about breadboards, is the following image of a breadboard from the inside, showing the metal that connects the pins on the top of the breadboard.

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/Breadboard-Contacts-Back-Side-2_from_protosupplies.com.jpg "Image of typical solderless breadboard from protosupplies.com")

Be aware that a circuit laid out on such a solderless breadboard can then be transferred to a solderable breadboard PCB board fairly easily. See the comparison between the solderless and solderable breadboards below.

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/Breadboard_Solderboard.png "Image of a solderless breadboard and a solderable breadboard PCB board")

Another way to turn a breadboard circuit into a PCB board is to use the "Fritzing Fab" service provided by their partner Aisler. I have no actual experience with this but it looks intriguing.
- https://aisler.net/partners/fritzing

One thing that will make your life easier (and mine too when I check the circuit) is to try and use some sort of color scheme in the wiring. This is a very common color scheme for wiring in hobbyist electronics and other Direct Current (DC) circuits:
- Wire that is **RED** connects to the positive side or plus side of power; in this class that will be +5 Volts. A memory mnemonic is to remember that RED is HOT.
- Wire that is **BLACK** connects to the ground side or return side of power; in this class that will be 0 Volts. A memory mnemonic is to remember that BLACK is COOL.
- Other colors can be used for different signals. It might be good to use wire colors such as white, green, yellow, blue, etc. for signals (such as Arduino inputs and outputs) and to try to run the wire for a signal through its eventual connection to ground on the breadboard consistently using the same color.

As you undoubtedly know, LEDs are designed to be connected with positive voltage on the + side and ground or negative voltage on the - side. If this rule is not followed, the LED will either not work or burn up. When connected properly, you will need a resistor of about 200 to 300 Ohms in series with the LED to prevent burning out the LED and prevent damaging the Arduino Nano.
- https://makecode.adafruit.com/learnsystem/pins-tutorial/devices/led-connections

Here from the above link is a diagram showing how to identify the polarity (+ and - pins) of an LED:

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/led-polarity_from_adafruit.com_azureedge.net.jpg "Adafruit.com polarity of LED")

Here from the above link is a diagram showing a simple battery circuit to light up an LED. Note the resistor to prevent burning out the LED. This is NOT our Arduini circuit; it just shows how to make an LED light up with a battery.
![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/led-connection_from_adafruit.com_azureedge.net.jpg 
"Adafruit.com Resistor and LED in circuit")

We will use the breadboard and some connectors to implement the following circuit. **Remember** to put the **"+"** side of the LED towards the resistor which connects to Digital I/O pin 3 (hereafter I would refer to this as D3 or D03). The schematic symbol for the Light Emitting Diode (or any diode) has the arrow pointing from the positive side to the negative side. In the diagram below, the left side of the LED is positive and the right side is negative. I have added +/- symbols in red to make it clear which side of the LED is which.
- https://github.com/Mark-MDO47/ArduinoClass/blob/master/01_BlinkingLED/01_Blinking_LED_part_A_Schematic.pdf

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/01_BlinkingLED_part_A_Schematic.png "Circuit Diagram of 01-Part-A: our external LED connections")

Here is an example of the above circuit implemented on a breadboard. Note that the wire fromArduino pin "GND" goes to the horizontal row 19 on the breadboard and is connected by a black wire to one of the "-" rails which runs vertically on the breadboard.
We take advantage of this negative rail by connecting the negative pin of the LED to the negative rail.<br>
Also the resistor connects to Arduino pin "D3" on row 21 and goes to the horizontal row 14 on the breadboard which is not otherwise connected to an Arduino pin,
and that signal runs across to the positive pin of the LED.<br>
![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/01_BlinkingLED_part_A_setup.png "Image of 01_BlinkingLED Part A implementation")

Here is a Fritzing of the above circuit on a breadboard. Note that I did not use the breadboard in exactly the same way for this Fritzing as I did for the actual implementation above. In the implementation I took advantage of the vertical breadboard connection for the ground, but in the Fritzing I just did a straight connection. Also in the implementation I used the 220 Ohm resistor itself to connnect up to a higher horizontal row, but in the Fritzing I put the resistor on the break between horizontal rows. I am using these two versions of the same circuit to illustrate some different styles of breadboard usage and to explore use of the vertical power rails and the horizontal rows.<br>
![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/01_BlinkingLED_part_A_Fritzing.png "Fritzing image of 01_BlinkingLED Part A implementation")

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

### TLDR the Arduino delay function
[Back to Top](#notes "Back to Top")<br>
As an aside, the Arduino delay(n) function does NOT behave similarly to all the sleep(n) functions I have seen in other languages.
- the sleep(n) functions I have seen will sleep **at least as long** as the parameter **n** indicates
- the Arduino delay(n) function will return after **at least as long** as **n-1** milliseconds
- https://forum.arduino.cc/t/problem-with-delay-and-millis/686674

Curiously, this behaviour is not mentioned in the Arduino documentation for the delay() function.
- https://www.arduino.cc/reference/en/language/functions/time/delay/

This doesn't matter to us very much here. If we sleep 999 milliseconds or 1000 milliseconds or even 1001 milliseconds it doesn't cause a traffic accident or other bad effects.

We will see this problem in a place where it does affect us later:
- https://github.com/Mark-MDO47/ArduinoClass/blob/master/04_TheFinale/README.md

### Try it Part A
[Back to Top](#notes "Back to Top")<br>
When we execute this program, the internal LED and the external LED blink; one is off when the other is on. The video at the following link shows what this looks like.
- https://youtu.be/c5UH3J40uWE

## Part B - Add Button and Display Messages on USB Serial Port
[Back to Top](#notes "Back to Top")<br>
Now we will add a push button for digital input. We will also start using the USB serial port for diagnostic output - a fantastically useful diagnostic tool. Note that this USB serial port can also be used for input.

Here is what our new circuit looks like. As before, I have added +/- symbols in red to make it clear which side of the LED is which.
- https://github.com/Mark-MDO47/ArduinoClass/blob/master/01_BlinkingLED/01_Blinking_LED_part_B_Schematic.pdf

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/01_BlinkingLED_part_B_Schematic.png "Circuit Diagram of 01-Part-B: add button")

Below is an image of 01_BlinkingLED Part B setup.
Notice that the button has four pins and is situated with two pins on horizontal
rows 6 & 8 on the left side of the middle split and two on the same horizontal
rows the right side.<br>
I found by experiment that when the button is pushed it connects the pins on opposite corners.
Thus the yellow wire from Arduino pin "D5" goes to horizontal row 6, connects to the upper left corner of the button,
then the lower right corner of the button goes by black wire to the the "-" vertical power rail
and from there all the way to the bottom of the "-" power rail and the black wire connecting to Arduino pin "GND".

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/01_BlinkingLED_part_B_setup.png "Image of 01_BlinkingLED Part B setup")

Here is a Fritzing for the same circuit. Note that once again there are variations between the implementation above and the Fritzing.<br>
![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/01_BlinkingLED_part_B_Fritzing.png "Fritzing image of 01_BlinkingLED Part B implementation")

Here is an image showing the buttons and the four pins on each one.
<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/61yw6SpuXEL._SL1001_.jpg" width="600" alt="Image of the buttons showing the four pins on each one">

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

You may need to set the serial monitor to 115,200 baud to match what our **setup()** routine is going to do.

Now our one-time **setup()** code is starting to be a little more complex. I am sure you can figure out what the new code does even if some techniques are unfamiliar to you. In particular, don't worry about the **F** macro in **Serial.println(F("ArduinoClass init..."));**; it works just as if the **F()** was not there but saves a little RAM. See the section on "PROGMEM and "F" macro to save RAM" for more information.
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

### Try it Part B
[Back to Top](#notes "Back to Top")<br>
When we execute this program, the internal LED and the external LED blink; one is off when the other is on. When we push and hold the button, the blinking stops. When we release the button the blinking restarts. The youtube video (using a different Arduino Nano) at the following link shows what this looks like and the image below that shows the USB serial port messages. NOTE: to play youtube and keep this tab open you must right-click the link and select to play in a new tab.
- https://youtube.com/shorts/qGxECSMQtAQ

Image of 01_BlinkingLED Part B: USB messages Button DOWN<br>
![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/01_BlinkingLED_part_B_USBmsgs_ButtonDOWN.png "Image of 01_BlinkingLED Part B: USB messages Button DOWN")

Image of 01_BlinkingLED Part B: USB messages Button UP<br>
![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/01_BlinkingLED_part_B_USBmsgs_ButtonUP.png "Image of 01_BlinkingLED Part B: USB messages Button UP")

### Some Arduino and C-language features not used above
[Back to Top](#notes "Back to Top")<br>
C-language has some useful but perhaps obscure features; I will just mention one here for those that want to explore further. It is possible to compress the code above a little using the **?:** operator. This takes a **Condition** followed by the question mark **?** and chooses one of two results separated by the **:**. For instance:
- Condition?X:Y

If Condition is true then the resulting value is X : otherwise the resulting value is Y.

To use this to print either UP or DOWN we could say
```C
  Serial.print((HIGH == btn_val) ? "Button UP   (GO)  " : "Button DOWN (STOP)");
```

There are many other ways we could re-arrange the printing to minimize calls to the Serial.*() routines, or to minimize RAM usage, etc. One of these is use of the "F" macro to put strings into program memory instead of RAM - RAM can be precious when programming Arduino. If you are interested in some of these, see **PROGMEM and "F" macro** in the **[Resources](#resources "Resources")** section below or in https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/README.md and/or talk with me after the class.

## Resources
### Arduino Nano and ATMEGA 328P
[Back to Top](#notes "Back to Top")<br>
We will be using Arduino Nano clones in our projects. You can ignore the following for our class; this is for follow-up by interested persons.

Lots of info on the Arduino Nano is found here (diagrams, not schematics)
* https://www.circuitstoday.com/arduino-nano-tutorial-pinout-schematics

The ATMEGA 328P chip used in the Arduino Nano is described here
* http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf

Mapping the ports to the internal registers is described here
* https://www.arduino.cc/en/Reference/PortManipulation

### My favorite Arduino clone - ESP32
[Back to Top](#notes "Back to Top")<br>
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
[Back to Top](#notes "Back to Top")<br>
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
