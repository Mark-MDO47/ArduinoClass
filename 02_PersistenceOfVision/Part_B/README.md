# NOTES

**Table of Contents**
* [Top](#notes "Top")
* [Cleanup](#cleanup "Cleanup")
* [Button](#button "Button")
* [LEDs](#leds "LEDs")
* [Sawtooth](#sawtooth "Sawtooth")
* [Reminder](#reminder "Reminder")

We will continue with our modified FastLED example program from **Part_A** to perform our **Sawtooth** pattern.

## Cleanup
[Top](#notes "Top")<br>
Copy the file from Part-A and put it in a directory named Sawtooth, rename it to Sawtooth.ino, and open it with the Arduino IDE.

The first thing we should do is get rid of the commented-out unused calls to **FastLED.addLeds** in the **setup()** routine. These are good documentation of how to make the calls for lots of different types of RGB LEDs, but they just clutter up our code.

Next we should use some of the variables from BlinkWithoutDelay to handle the timing. These can go prior to **setup()**.

```C
// Variables will change:
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 40;           // interval at which to blink (milliseconds); 25 blinks per second
```
I adjusted the value of **interval** to give 25 blinks per second; a little faster than the 24 frames per second required to make movies appear to move.

Now we adjust the **loop()** code to use the BlinkWithoutDelay method.
```C
void loop() {
  // check to see if it's time to "blink" the LED strip; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();

  // TODO - handle the button input

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // TODO - blink the LEDs
  }
} // end loop()
```

## Button
[Top](#notes "Top")<br>
We create the routine to handle the button.<br>
This is an extremely simple routine and could actually be placed inline, but it is good practice to modularize your code and compartmentalize the knowledge needed. It could help in the future: if there are multiple inputs including more buttons and possibly other digital inputs we could return a bitmask with the status of all the inputs.<br>
I just couldn't bring myself to do the modularization for the simple **setup()** routine, but will do it for **loop()**.<br>
Our plan is that when the button is pressed the LED sawtooth pattern goes back to the start and waits for button release. The button routine merely returns the status of the button; the LED routines will do what they want with that status.

I should mention that there is such a thing as contact bounce, which we could handle in the button routine. I chose not to pay attention to this for our simple project. If you want to see more on that topic look in the Arduino IDE under
- **File** -> **Examples** -> **02.Digital** -> **Debounce**

Here is the definition of our button pin; it goes with the other definitions before the **setup()** routine
```C
const int button_pin = 3;     // the number of the pushbutton pin
```
Here is code to add in the setup routine
```C
  // initialize the pushbutton pin as an input with pullup:
  pinMode(button_pin, INPUT_PULLUP);
```

Here is our routine to handle button input. Place it before **setup()** so that **loop()** will see 

```C
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// handle_button(btn_pin) - determine the state of a single button or any digital input, HIGH or LOW
//    returns: int with either value HIGH or LOW
//
// btn_pin is the pin number of the digital pin we sense for the button, range 1-13 inclusive

int handle_button(int btn_pin) {
  return(digitalRead(btn_pin)); // the pushbutton status; pressed==LOW, not-pressed==HIGH
} // end handle_button()
```

Finally in **loop()** we replace **// TODO - handle the button input** with this

```C
  // the pushbutton status; pressed==LOW, not-pressed==HIGH
  int button_up = handle_button(button_pin);
```

## LEDs
[Top](#notes "Top")<br>
We create the routine to handle the LED Stick.<br>
This is a more complex routine, since we want it to be able to handle the Sawtooth pattern and the other patterns in Part-C and Part-D.

```C
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// handle_leds_phase(...) - determine the state of a single button, HIGH or LOW
//    returns: long int with either value >= 0 phase to blink or value < 0 paused
//
// btn_pressed - the pushbutton status; pressed==LOW, not-pressed==HIGH

long int handle_leds_phase(int btn_pressed) {
  // TODO
} // end handle_leds_phase()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// handle_leds(...) - determine the state of a single button, HIGH or LOW
//    returns: int with either value HIGH==blinked the LEDs or LOW==did not blink
//
// btn_pressed - the pushbutton status; pressed==LOW, not-pressed==HIGH

int handle_leds(int btn_pressed) {
  long int blink_phase = handle_leds_phase(btn_pressed);
} // end handle_leds()
```


## Sawtooth
[Top](#notes "Top")<br>
We want to make it so that the first blink we light up only the first LED, the second blink light up only the second LED, and so on until the eighth blink light up only the eighth LED.
Then we turn around. On the next blink we light up only the 7th LED, then the 6th, and so on until we light up the 2nd.
At this point we repeat.

There are many ways to code this, some of them elegant. I have gradually come to the point of view that I want to make my code blindingly obvious. If someone other than myself is the next one to work on the code, then obviously they should be aware of every nook and cranny of the C- and C++- language specifications and be able to figure out how it works even if my variable names are named from characters of a Humphrey Bogart movie. On the other hand, if I am the poor schlub who has to look at the code again, I know I won't remember in 6 months what the *** I was doing so I want to be able to figure it out as quickly as possible.

Here is a method I might use to do this. First, definitions of variables that must remain the same value between calls to **loop()**; these are placed prior to either **setup()** or **loop()**.

**FIXME use static, put in LED routine** Then, also prior to either **setup()** or **loop()**, some definitions and variables to control our code.
```C
#define NUM_CALLS_THEN_REPEAT 14 // the pattern does 14 calls then repeats
const int led_on_array_per_call[NUM_CALLS_THEN_REPEAT] = { 0, 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1 };
```
## TO DO
To Do
- add call to routine to handle LEDs
  - modularize with reset_pattern() and next_pattern()

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
