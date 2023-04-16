# NOTES

**Table of Contents**
* [Top](#notes "Top")
* [Demo](#demo "Demo")
* [Serial Port Commands](#serial-port-commands "Serial Port Commands")
* [Reminder](#reminder "Reminder")

We will continue with our modified FastLED example program from **Part_C** to perform our **Demo** pattern.

## Demo
[Top](#notes "Top")<br>
The idea is to use Mark Kriegsman's classic DemoReel100.ino with our LED Stick.<br>
- https://github.com/FastLED/FastLED/tree/master/examples/DemoReel100

Here is where all our work organizing the code for Part B Sawtooth pays off. Except for changing Sawtooth to Oval, there are very few changes to make.

Copy the Oval.ino file into a directory named Demo with filename Demo.ino, then open it in the Arduino IDE.

Now do global replaces with case sensitivity on as shown below:
| Replace this | With this |
| --- | --- |
| oval_ | ptrn_ |

Now for the actual changes. 

## Serial Port Commands
[Top](#notes "Top")<br>

## Reminder
[Top](#notes "Top")<br>
The connections do not change; this is just here for a reminder.

Remember:
- red wire is for 5 Volts from Arduino to LED stick (4-7VDC)
- black wire is for Ground between Arduino and LED stick (GND)
- white wire is for serial_data output from Arduino to LED stick (IN)

Here is a protosupplies.com image of the LED stick detail showing labels

![alt text](https://protosupplies.com/wp-content/uploads/2020/09/WS2812-RGB-8-LED-Stick-Module-With-Right-Angle-Header.jpg "protosupplies.com image LED stick detail showing labels")

Here is a reminder of our desired wiring

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/02_PersistenceOfVision.png" width="1002" height="530" alt="Image of wiring diagram for Persistence of Vision">
