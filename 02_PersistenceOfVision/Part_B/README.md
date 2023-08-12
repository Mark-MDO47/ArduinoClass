# NOTES

## Back to Root of Class
Click this link to back to go back to the root of the Arduino class
- https://github.com/Mark-MDO47/ArduinoClass/tree/master


**Table of Contents**
* [Top](#notes "Top")
* [Smoke and Mirrors](#smoke-and-mirrors "Smoke and Mirrors")
* [Code Cleanup](#code-cleanup "Code Cleanup")
* [Code for Button](#code-for-button "Code for Button")
* [Code for LEDs](#code-for-leds "Code for LEDs")
* [Code for Sawtooth](#code-for-sawtooth "Code for Sawtooth")
* [Reminder](#reminder "Reminder")

We will continue with our modified FastLED example program from **Part_A** to perform our **Sawtooth** pattern.

## Smoke and Mirrors
[Top](#notes "Top")<br>
I have found that if you are waving the LED Stick and also trying to see the pattern, looking in a mirror helps. I will bring a mirror for the class.

## Code Cleanup
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
const long interval = 1;           // interval at which to blink (milliseconds); 500 blinks per second so our arm doesn't get tired
```
I adjusted the value of **interval** to give 500 "ON" blinks per second (every other blink is dark). This is much faster than the 24 frames per second required to make movies appear to move.<br>
The effect we are trying for is a little different than movies, since our lights are moving. By having the blinks very rapid it means that we don't have to be so precise in our arm movement.

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

The definition **#define CLOCK_PIN 13** is expected to be unused in our code since our LED Strip does not use a clock; you can comment it out or delete it.

Finally, we change the LED array name from leds to fastled_array.<br>
Partially I just want you to be aware that the name is arbitrary. Also I want you to see you could have multiple fastled_array data structures to build the patterns; we just need to remember that for any I/O pin the data will always come from the array passed in the **FastLED.addLeds** call. Thus if other arrays are used to build the pattern, it is necessary to copy the final pattern into that array associated with the I/O pin.

We can do a global search and replace in the Arduino IDE with one restriction. The IDE does allow the search/replace to be case sensitive but it does not allow it to replace only whole words or complete matches. If desired another editor could be used for this step, or else the "Find" and "Replace and Find" buttons can be used to ensure only desired changes are made.

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/IDE_Replace_leds_w_fastled_array.png "Image of replace dialog to change leds to fastled_array")

## Code for Button
[Top](#notes "Top")<br>
We create the routine to handle the button.<br>
This is an extremely simple routine and could actually be placed inline, but it is good practice to modularize your code and compartmentalize the knowledge needed. It could help in the future: if there are multiple inputs including more buttons and possibly other digital inputs; we could return a bitmask with the status of all the inputs.<br>
I just couldn't bring myself to do the modularization for the simple **setup()** routine, but will do it for **loop()**.<br>
Our plan is that when the button is pressed the LED sawtooth pattern goes back to the start and waits for button release. The button routine merely returns the status of the button; the LED routines will do what they want with that status.

I should mention that there is such a thing as contact bounce, which we could handle in the button routine. I chose not to pay attention to this for our simple project. If you want to see more on that topic look in the Arduino IDE under
- **File** -> **Examples** -> **02.Digital** -> **Debounce**

Here is the definition of our button pin; it goes with the other definitions before the **setup()** routine
```C
#define BUTTON_PIN 3 // the number of the pushbutton pin
```
Here is code to add in the setup routine
```C
  // initialize the pushbutton pin as an input with pullup:
  pinMode(BUTTON_PIN, INPUT_PULLUP);
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
  int button_up = handle_button(BUTTON_PIN);
```

## Code for LEDs
[Top](#notes "Top")<br>
We create the routine to handle the LED Stick.<br>
We want this routine to be able to handle the Sawtooth pattern and the other patterns in Part-C and Part-D.

Put this routine just prior to **handle_button()**

```C
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// handle_leds(...) - get the pattern and then display on LEDs
//    returns: int with either value HIGH==blinked the LEDs or LOW==did not blink
//
// btn_pressed - the pushbutton status; pressed==LOW, not-pressed==HIGH
//       note that this routine does not know what to do with btn_pressed;
//       the pattern routines (in this case Sawtooth) know what to do with btn_pressed

int handle_leds(int btn_pressed) {
  int did_blink = sawtooth_fill_pattern(btn_pressed, fastled_array); // fill the pattern into RAM

  FastLED.show(); // show the pattern on LEDs

  return(did_blink); // HIGH if blink, LOW if pause
} // end handle_leds()
```
NOTE: we will define sawtooth_fill_pattern() when we get to the Sawtooth pattern.

Finally in **loop()** we replace **// TODO - blink the LEDs** with this
```C
  handle_leds(button_up); // generate pattern to display and display it
```

## Code for Sawtooth
[Top](#notes "Top")<br>
We want to make it so that the first blink we light up only the first LED, the second blink light up only the second LED, and so on until the eighth blink light up only the eighth LED.
Then we turn around. On the next blink we light up only the 7th LED, then the 6th, and so on until we light up the 2nd.
At this point we repeat.

There are many ways to code this, some of them elegant. I have gradually come to the point of view that I want to make my code blindingly obvious. If someone other than myself is the next one to work on my code then obviously they should be qualified to work on it before they touch my code; they should be aware of every nook and cranny of the C and C++ language specifications and be able to figure out how it works even if there are no comments and my variable names are characters from a Humphrey Bogart movie mixed with Goldilocks and the three bears. On the other hand, if I am the poor schlub who has to look at the code again, I know I won't remember in 6 months what the *** I was doing so I want to make it easy to figure it out as quickly as possible.

Here is a method I might use to do this. 

Prior to either **setup()** or **loop()**, some definitions to control our code.
```C
#define SAWTOOTH_CALLS_THEN_REPEAT 14 // the Sawtooth pattern does this many calls then repeats
```

Just prior to **handle_leds()**, add the new routines for the Sawtooth pattern.

```C
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// sawtooth_phase(btn_pressed) - determine the state of what the phase of pattern generation is
//    returns: long int with either value >= 0 phase to blink or value < 0 paused
//
// btn_pressed - the pushbutton status; pressed==LOW, not-pressed==HIGH
//       btn_pressed LOW means reset to start of pattern and wait for btn_pressed HIGH
//       note that ONLY this routine interprets btn_pressed

long int sawtooth_phase(int btn_pressed) {
  static long int current_phase = -1;

  if (LOW == btn_pressed) {
    current_phase = -1; // reset pattern and pause
  } else {
    current_phase += 1;
    current_phase %= SAWTOOTH_CALLS_THEN_REPEAT; // loop through the number of calls before repeat
  }
  
  return(current_phase);
} // end sawtooth_phase()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// sawtooth_pause_pattern(blink_phase, ptrn_leds) - 
//    fills ptrn_leds with all CRGB::Black
//    returns: none
//
// blink_phase - ignored
// ptrn_leds   - where to store the pattern

void sawtooth_pause_pattern(long int blink_phase, CRGB * ptrn_leds) {

  // pause pattern - all CRGB::Black
  for (long int i = 0; i < NUM_LEDS; i++) {
    ptrn_leds[i] = CRGB::Black;
  }

} // end sawtooth_pause_pattern()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// sawtooth_blink_pattern(blink_phase, ptrn_leds) - 
//    fills ptrn_leds with next pattern based on blink_phase
//    returns: none
//
// blink_phase - long int, range 0-13
// ptrn_leds   - where to store the pattern

void sawtooth_blink_pattern(long int blink_phase, CRGB * ptrn_leds) {
  static const int led_on_array_per_call[SAWTOOTH_CALLS_THEN_REPEAT] = { 0, 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1 };

  // blink pattern - all CRGB::Black except one CRGB::Red
  for (long int i = 0; i < NUM_LEDS; i++) {
    ptrn_leds[i] = CRGB::Black;
  }
  ptrn_leds[led_on_array_per_call[blink_phase]] = CRGB::Red;

} // end sawtooth_blink_pattern()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// sawtooth_fill_pattern(btn_pressed, ptrn_leds) - 
//    returns: int with either value HIGH==blinked the LEDs or LOW==did not blink
//
// btn_pressed - the pushbutton status; pressed==LOW, not-pressed==HIGH
// ptrn_leds   - where to store the pattern

int sawtooth_fill_pattern(int btn_pressed, CRGB * ptrn_leds) {
  int did_blink = LOW;
  long int blink_phase = sawtooth_phase(btn_pressed);

  if (blink_phase < 0) {
    sawtooth_pause_pattern(blink_phase, ptrn_leds);
    did_blink = LOW;
  } else {
    sawtooth_blink_pattern(blink_phase, ptrn_leds);
    did_blink = HIGH;
  }

  return(did_blink);
} // end sawtooth_fill_pattern
```

For discussion - I am unsure if I want to pass fastled_array into handle_leds() or not, even though I am passing it into the Sawtooth pattern routines. Typically in FastLED programming such items are global. For the pattern routines I felt it would be nice to be able to generate into areas that were temporary storage so we could do more pattern manipulation.

What do you think about this and why?

When running these persistence of vision projects, you will be waving your hand around with some electronics tied to the breadboard and the Arduino. You don't want the breadboard and Arduino to be waving around. I have found it to be a good practice to connect all the leads of the LED Stick to the breadboard and then, when waving it, use the other hand to hold down both the breadboard and the last few inches of the LED Stick leads where they are just about to connect to the breadboards.

This is a video showing the sawtooth pattern in action followed by an image that somewhat captured the effect.  My son (college graduate) Alpha-Tested the class for me and appears in this material by permission.<br>
The sawtooth pattern appears better in person than in this video. I think there are at least these two main reasons:
- the camera does not have the persistence of vision that humans do
- the camera frame rate is less than the blink rate

https://youtu.be/UdA5ehl802k

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/02_PersistanceOfVision_PartB_Sawtooth.png" width="411" alt="Image that somewhat captures the persistence of vision effect">

## Reminder
[Top](#notes "Top")<br>
The connections do not change; this is just here for a reminder.

| Wire Color | Schematic | LED Stick | Purpose |
| --- | --- | --- | --- |
| Black | VSS | GND | Ground |
| Red | VDD | VCC | +5 Volts |
| White | DIN | IN | Serial Data |

Here is a reminder of our desired wiring

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/02_PersistenceOfVision.png" width="1002" height="530" alt="Image of wiring diagram for Persistence of Vision">

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/02_PersistenceOfVision_Fritzing.png" width="750" alt="Fritzing image of wiring diagram for Persistence of Vision">
