# NOTES

## Connect the Arduino Nano to the USB cable
![alt text](https://www.circuitstoday.com/wp-content/uploads/2018/02/Arduino-Nano-Pinout.jpg "CircuitsToday.com picture of Arduino Nano")

I will provide four Arduino Nano clones and some supporting hardware for use during the class.

The Arduino Nano uses a USB Mini-B female and thus needs a cord from your laptop with a USB Mini-B Male connector. If your laptop has a USB A connection then I have cords you can use; otherwise please provide your own method to connect to either Mini-B directly or to bridge the gap to the USB A connector on the cord I can provide. This USB connection provides both a serial port (for uploading and communication) and power/ground.
- https://www.technicalcable.com/usb-cable-assemblies/

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

```
void setup() {
 // put your setup code here, to run once:
}
void loop() {
 // put your main code here, to run repeatedly:
}
```

## Start with example program
In the Arduino IDE, use menu **File** -> **Examples** -> **01.Basics** -> **Blink**. This will bring up the starting point for our Blink exercise.

In the **setup()** function you will find a "pinMode" call. LED_BUILTIN is a symbol for the "pin" number that controls the builtin LED on any Arduino; this will be set to OUTPUT mode so we can turn the LED on and off. The **setup()** function is called only once, before ever calling the **loop()** function.

In the **loop()** function you will find that it delays 1000 milliseconds, turns the LED **ON**, delays 1000 milliseconds, and turns the LED **OFF**. Because the **loop()** function is called over and over, this will continue until you stop it by reprogramming or powering off the Arduino Nano.

**CONGRATULATIONS!** You have executed your first Arduino program!

## Part A - Add an external LED
As you undoubtedly know, LEDs are designed to be connected with positive voltage on the + side and ground or negative voltage on the - side. If this rule is not followed, the LED will either not work or burn up. Also you will need a 300 or 220 ohm resistor in series to prevent burning out the LED and prevent damaging the Arduino Nano.
- https://makecode.adafruit.com/learnsystem/pins-tutorial/devices/led-connections

![alt text](https://pxt.azureedge.net/blob/03fec9ac9dbaee9f745ae2beda43fc15119c1c20/static/cp/learn/pins-tutorial/devices/led-polarity.jpg "Adafruit.com polarity of LED")

![alt text](https://pxt.azureedge.net/blob/2ebeedcf4108aa2a5ecc9b8b232cbb5960b2dfb6/static/cp/learn/pins-tutorial/devices/led-connection.jpg 
"Adafruit.com Resistor and LED in circuit")

We will use the breadboard and connectors I supply to create the following circuit. **Remember** to put the **"+"** side of the LED towards the resistor which connects to Digital I/O pin 3 (hereafter I would refer to this as D3).
- https://github.com/Mark-MDO47/ArduinoClass/blob/master/01_BlinkingLED/01_Blinking_LED_part_A_Schematic.pdf

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/01_BlinkingLED_part_A_Schematic.png "Circuit Diagram of 01-Part-A: our external LED connections")

Here are the changes we will make to the standard Blink program; first in (or before) **setup()**:

```
#define DPIN_LED_OUT 3 // in case we want to move it, only need to change this

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  // initialize our new pins
  pinMode(DPIN_LED_OUT, OUTPUT);      // digital OUTPUT means we control voltage on pin, HIGH or LOW
}
```

And now the changes for **loop()**:

```
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(DPIN_LED_OUT, LOW);   // turn the external LED off
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(DPIN_LED_OUT, HIGH);  // turn the external LED on
  delay(1000);                       // wait for a second
}
```

## Part B - Add loop counter and Button; display messages on serial port
Now we will add a push button for digital input and start using the USB serial port for diagnostic output - a fantastically useful diagnostic tool. Note that this USB serial port can also be used for input.
- https://github.com/Mark-MDO47/ArduinoClass/blob/master/01_BlinkingLED/01_Blinking_LED_part_B_Schematic.pdf

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/01_BlinkingLED_part_B_Schematic.png "Circuit Diagram of 01-Part-B: add button")

We will configure the input pin D05 as **INPUT_PULLUP**; this means that the Arduino Nano will connect it internally to the +5V "rail" using a resistance that minimizes power loss, probably about 5,000 or 10,000 ohms. This could be written as 5Kohm or 10Kohm.
- When the switch is OPEN (disconnected or not pushed) then the voltage on the pin is HIGH (close to +5V) and will be sensed as HIGH.
- When the switch is CLOSED (connected or pushed) the pin is grounded by a low-resistance path; therefore the voltage on the pin is LOW (close to GND) and will be sensed as LOW.
In reality, I don't often rely on this internal pullup because I use a lot of inexpensive Arduino Nano clones that can be sensitive to heat and a bit fragile, so I usually have an external resistor for the pullup as can be seen in the upper left-hand side of this schematic:
- https://github.com/Mark-MDO47/RubberBandGun/blob/master/RubberBandGun_Wiring.pdf

We will use some **Serial.*"" routines: Serial.begin(), Serial.print(), and Serial.println(). These are documented starting in this area:
- https://www.arduino.cc/reference/en/language/functions/communication/serial/

For instance, the various ways to use Serial.print() are documented here
- https://www.arduino.cc/reference/en/language/functions/communication/serial/print/

Now our one-time setup() code is starting to be more complex; see if you can spot the new code and figure out what it does.
```
#define DPIN_LED_OUT 3 // in case we want to move it, only need to change this
#define DPIN_BTN_IN  5 // in case we want to move it, only need to change this

void setup() {
  static int loop_count = 0;
  pinMode(DPIN_LED_OUT, OUTPUT);      // digital OUTPUT means we control voltage on pin, HIGH or LOW
  pinMode(DPIN_BTN_IN, INPUT_PULLUP); // digital INPUT_PULLUP means voltage HIGH unless grounded

  Serial.begin(115200);         // this is for general debug

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println();
  Serial.println(F("ArduinoClass init..."));
}
```



## Resources
### Arduino Nano and ATMEGA 328P
We will be using Arduino Nano clones in our projects. You can ignore the following for our class; this is for follow-up by interested persons.

Lots of info on the Arduino Nano is found here (diagrams, not schematics)
* https://www.circuitstoday.com/arduino-nano-tutorial-pinout-schematics

The ATMEGA 328P chip used in the Arduino Nano is described here
* http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf

Mapping the ports to the internal registers is described here
* https://www.arduino.cc/en/Reference/PortManipulation

### "F" macro to save RAM

### My favorite Arduino clone - ESP32
