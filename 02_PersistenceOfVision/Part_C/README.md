# NOTES

**Table of Contents**
* [Top](#notes "Top")
* [Sawtooth](#sawtooth "Sawtooth")
* [Reminder](#reminder "Reminder")

We will use a slightly modified FastLED example program **Sawtooth** to make sure we are talking to the LED stick correctly and check that the order of colors to send matches what we need.

## Sawtooth
Copy the file from Part-A and put it in a directoy named Sawtooth, rename it to Sawtooth.ino, and open it with the Arduino IDE

We want to make it so that the first blink we light up only the first LED, the second blink light up only the second LED, and so on until the eighth blink light up only the eighth LED.
Then we turn around. On the next blink we light up only the 7th LED, then the 6th, and so on until we light up the 2nd.
At this point we repeat.

There are many ways to code this, some of them elegant. I have gradually come to the point of view that I want to make my code blindingly obvious. If someone other than myself is the next one to work on the code, then obviously they should be aware of every nook and cranny of the C- and C++- language specifications and be able to figure out how it works even if my variable names are named from characters of a Humphrey Bogart movie. On the other hand, if I am the poor schlub who has to look at the code again, I know I won't remember in 6 months what the *** I was doing so I want to be able to figure it out as quickly as possible.

Here is a method I might use to do this. First, definitions of variables that must remain the same value between calls to **loop()**; these are placed prior to either **setup()** or **loop()**.

I will use some of the variables from BlinkWithoutDelay to handle the timing

```C
// Variables will change:
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 50;           // interval at which to blink (milliseconds)
```

Then, also prior to either **setup()** or **loop()**, some definitions and variables to control our code.
```C
#define NUM_CALLS_THEN_REPEAT 14 // the pattern does 14 calls then repeats
const int led_on_array_per_call[NUM_CALLS_THEN_REPEAT] = { 0, 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1 };
```
## Reminder
The connections do not change; this is just here for a reminder.

Remember:
- red wire is for 5 Volts from Arduino to LED stick (4-7VDC)
- black wire is for Ground between Arduino and LED stick (GND)
- white wire is for serial_data output from Arduino to LED stick (IN)

Here is a protosupplies.com image of the LED stick detail showing labels

![alt text](https://protosupplies.com/wp-content/uploads/2020/09/WS2812-RGB-8-LED-Stick-Module-With-Right-Angle-Header.jpg "protosupplies.com image LED stick detail showing labels")

Here is a reminder of our desired wiring

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/02_PersistenceOfVision.png" width="1002" height="530" alt="Image of wiring diagram for Persistence of Vision">
