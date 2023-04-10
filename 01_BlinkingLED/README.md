# NOTES

## Connect the Arduino Nano
![alt text](https://www.circuitstoday.com/wp-content/uploads/2018/02/Arduino-Nano-Pinout.jpg "CircuitsToday.com picture of Arduino Nano")

I will provide four Arduino Nano clones and some supporting hardware for use during the class.

The Arduino Nano uses a USB Mini-B female and thus needs a cord from your laptop with a USB Mini-B Male connector. If your laptop has a USB A connection then I have cords you can use; otherwise please provide your own method to connect to either Mini-B directly or to bridge the gap to the USB A connector on the cord I can provide. This USB connection provides both a serial port (for uploading and communication) and power/ground.
- https://www.technicalcable.com/usb-cable-assemblies/

## Empty Sketch
The Arduino IDE uses a variant of the C++ language. You can program in a C++ style or a C style. The code that we will use in this course will be quite straighforward and should be understandable if you know any computer language. One thing to note about C/C++: array indices start with zero.

An Arduino program (called a "sketch" in Arduino-speak) is typically stored with extension ".ino". If you save your program as fred.ino, you will find that it is saved in a directory named fred.

When opening the Arduino IDE you will initially see the empty sketch (program) as shown below. This is the standard architecture for Arduino code. It is possible to extend this to use interrupts, go to low power modes, and other special-purpose things. For our class we will just use the standard architecture as seen below.
- void setup() {
-   // put your setup code here, to run once:
- }
- void loop() {
-   // put your main code here, to run repeatedly:
- }

## Start with example program
In the Arduino IDE, use menu **File** -> **Examples** -> **01.Basics** -> **Blink**. This will bring up the starting point for our Blink exercise.

In the **setup()** function you will find a "pinMode" call. LED_BUILTIN is a symbol number for the builtin "pin" that controls the builtin LED on the Arduino Nano; this will be set to OUTPUT mode so we can turn the LED on and off. The **setup()** function is called only once, before ever calling the **loop()** function.

In the **loop()** function you will find that it delays 1000 milliseconds, turns the LED **ON**, delays 1000 milliseconds, and turns the LED **OFF**. Because the **loop()** function is called over and over, this will continue until you stop it by reprogramming or powering off the Arduino Nano.

**CONGRATULATIONS!** You have executed your first Arduino program!

## Add an external LED
As you undoubtedly know, LEDs are designed to be connected with positive voltage on one side and negative voltage on the other. If this rule is not followed, the LED will either not work or burn up. Also

## Add serial port messages

## Add loop counter and Button; display on serial port

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
