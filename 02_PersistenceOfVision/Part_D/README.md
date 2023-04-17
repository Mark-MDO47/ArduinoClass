# NOTES

**Table of Contents**
* [Top](#notes "Top")
* [Demo](#demo "Demo")
* [Cleanup](#cleanup "Cleanup")
* [Serial Port Commands](#serial-port-commands "Serial Port Commands")
* [Reminder](#reminder "Reminder")

We will continue with our modified FastLED example program from **Part_C** to perform our **Demo** pattern.

## Demo
[Top](#notes "Top")<br>
The idea is to use Mark Kriegsman's classic DemoReel100.ino with our LED Stick, and use USB Serial commands to choose the pattern.<br>
- https://github.com/FastLED/FastLED/tree/master/examples/DemoReel100

Here is where all our work organizing the code for Part B Sawtooth pays off. Except for changing Sawtooth to Oval, there are very few changes to make.

Copy the Oval.ino file into a directory named Demo with filename Demo.ino, then open it in the Arduino IDE.

Now do global replaces with case sensitivity on as shown below:
| Replace this | With this |
| --- | --- |
| oval_ | ptrn_ |

Now for the actual changes.

Looking at the code for DemoReel100:
- We know we do not need to use the line that says **FASTLED_USING_NAMESPACE** but it is OK to use it
- We want the line **#define FRAMES_PER_SECOND  120**
- We do not need anything from the **setup()** routine
- We copy all the definitions and variables between **setup()** and **loop()** and put them just before our **setup()**
- We copy everything from **void rainbow()** to the end and put it before our **setup()**

In **setup()** we add these lines near the end:
```C
  Serial.begin(115200);         // this serial communication is for general debug; set the USB serial port to 115,200 baud
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println(""); // print a blank line in case there is some junk from power-on
  Serial.println("ArduinoClass init...");
  Serial.println("Commands:");
  Serial.println("0: rainbow");
  Serial.println("1: rainbowWithGlitter");
  Serial.println("2: confetti");
  Serial.println("3: sinelon");
  Serial.println("4: juggle");
  Serial.println("5: bpm");
  Serial.println("");
```

Our new **loop()** now looks like this (everything from DemoReel100 loop() except the last line):
```C
void loop() {
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
}
```

What is this? I thought we would never call **delay()** in the **loop()**?
  - the EVERY_N_MILLISECONDS macro from FastLED uses the millisecond counter behind the scenes
  - **FastLED.delay()** does multiple **FastLED.show()** calls while delaying; it is not **just** a delay()
    - They do that so that FastLED dithering algorithms can generate better looking colors
    - See https://github.com/FastLED/FastLED/issues/1206
    - See https://en.wikipedia.org/wiki/Dither
    - This gave me trouble in my FPGA project https://github.com/Mark-MDO47/FPGA_RBG_2_RBGW

I chose to go ahead with this approach because
- FRAMES_PER_SECOND is 120; the delay won't be very long
- We don't have anything that is super time critical
- Everybody loves beautiful colors
- And besides, rules are made to be broken

In a following project we will be using a sonar range sounder which will throw a monkey wrench into this scheme. But for now, enjoy the show!

## Cleanup
[Top](#notes "Top")<br>
Putting in the code for DemoReel100, it becomes obvious that the structure of our program has changed and there are parts that are no longer needed.
- We will not be using the button
- We will not be using the patterns from Part-C and Part-D
- We will not be using the counters for milliseconds from BlinkWithoutDelay

Remove the following:
```C
#define BUTTON_PIN 3 // Mark-MDO47 we use pin 3 for button
```

Remove the following, along with any other patterns you might have added in Oval.
```C
// #define PATTERN_OVAL 1
#define PATTERN_HELLO 1

#ifdef PATTERN_HELLO
#define PTRN_CALLS_THEN_REPEAT 58 // the HELLO WORLD! pattern does 58 calls then repeats
static unsigned int pattern_bits[PTRN_CALLS_THEN_REPEAT] = { 0xFF, 0x18, 0x18, 0x18, 0xFF, 0x00, 0xFF, 0x89, 0x89, 0x89, 0x00, 0xFF, 0x01, 0x01, 0x01, 0x00, 0xFF, 0x01, 0x01, 0x01, 0x00, 0x7E, 0x81, 0x81, 0x7E, 0x00, 0xE0, 0x1E, 0x01, 0x1E, 0xE0, 0x1E, 0x01, 0x1E, 0xE0, 0x00, 0x7E, 0x81, 0x81, 0x7E, 0x00, 0xFF, 0x98, 0x94, 0x63, 0x00, 0xFF, 0x01, 0x01, 0x01, 0x00, 0xFF, 0x81, 0x42, 0x3C, 0x00, 0xF9, 0x00 };
#else // PATTERN_OVAL
#define PTRN_CALLS_THEN_REPEAT 34 // the Oval pattern does 34 calls then repeats
static unsigned int pattern_bits[PTRN_CALLS_THEN_REPEAT] = { 0x18, 0x24, 0x42, 0x81, 0x81, 0x81, 0x42, 0x24, 0x18, 0x00, 0x40, 0xA0, 0x48, 0x14, 0x08, 0x20, 0x53, 0x23, 0x00, 0x18, 0x24, 0x42, 0x81, 0x81, 0x99, 0xA5, 0xA5, 0x99, 0x81, 0x81, 0x42, 0x24, 0x18, 0x00 };
#endif // PATTERN_HELLO
```

Remove the following:
```C
#define FASTLED_RAINBOWPTRNLEN 64 // number of shades to cycle through
#define FASTLED_RAINBOWHUEROTATE 500 // rotate hues every 500th color pick

static uint16_t gHue_rotate_countdown = FASTLED_RAINBOWHUEROTATE;
static uint16_t next_rainbow = 0;

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 40;           // interval at which to blink (milliseconds); 25 blinks per second
```

Remove the following routines:
- ptrn_phase()
- ptrn_blink_pattern()
- ptrn_fill_pattern()
- handle_leds()
- handle_button()

## Serial Port Commands
[Top](#notes "Top")<br>
It is possible to use the built-in capability **serialEvent()**, which gets called automagically after **loop()** completes. Except the documentation says it doesn't happen for all Arduinos. And the documentation and sample program are really old.

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/IDE_LoadSerialEvent.png "Image of IDE loading SerialEvent example")

Because it is trivially easy to implement a similar capability ourselves, and it does not leave the reader wondering how in the world **serialEvent()** gets called, and I like my code to be blindingly obvious (see my comment in section Sawtooth in https://github.com/Mark-MDO47/ArduinoClass/tree/master/02_PersistenceOfVision/Part_B), I will once again suggest we poke our fingers in the gears.

The goal is to read commands from the USB serial port. To do this and fit within our **setup()/loop()** architecture, we need to meet the following goals
- it should be reasonably encapsulated (because I am lazy)
- if there is nothing to do, we don't waste a lot of time figuring this out and just let **loop()** fall through to handling the next sensor or device
- if there are characters to read, we should read them quickly and put them somewhere and then let **loop()** fall through...
- when we detect end-of-command (linefeed or '\n'), we either notify the **loop()** code or call the processing routine ourselves

For our purposes, we will use **Serial.available()** to detect when character(s) are available to read and **Serial.read()** to read a single character at a time. We do NOT want to use **Serial.readln()** because that would stop Arduino execution until we get a complete line.

The basic flow is as follows. We make some definitions up in the **#define** and **variable definition** sections early in the code.

```C
#define SERIAL_MAX_INPUT_LEN 5 // maximum number of characters to accept in one command; otherwise flush to next newline and process what we have
#define SERIAL_INPUT_BUF_LEN (SERIAL_MAX_INPUT_LEN + 5) // size of our actual buffer; room for terminating '\0' and a little extra
#define PATTERN_MAX_NUM 5 // 0-5 are patterns
static char serial_input_buf[SERIAL_INPUT_BUF_LEN]; // one character for terminating '\0'
```

Before **setup()** we add these lines. (OK: not blindingly obvious but I will try to put in comments. Handling unformatted input from humans is tricky! If you can see how to break it up lets talk about it!)

```C
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// handle_serial_input_command(inbuf) - process serial input command (decimal number).
//    returns: nothing
//
// inbuf - pointer to start of zero-terminated string, no linefeed ('\n')
//         expected to be a decimal number
//
// if input number is valid, store into pattern_num

void handle_serial_input_command(char * inbuf) {
   long int tmp = atoi(inbuf);
   if ((0 <= tmp) && (PATTERN_MAX_NUM >= tmp)) {
     gCurrentPatternNumber = tmp;
   }
} // end handle_serial_input_command()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// handle_serial_input() - process serial input. When a command is received, call handle_serial_input_command() 
//    returns: nothing
//
// Process SERIAL_MAX_INPUT_INPUT_EACH_CALL characters at a time, in case we are reading characters from a machine.
// End of command is signaled by the character '\n'
// Only valid characters in command are decimal digits
//
// serial_input_buf - where to store the serial input command
#define SERIAL_MAX_INPUT_INPUT_EACH_CALL 6 // maximum number of characters to read each call

void handle_serial_input() {
  static int serial_input_flushing = 0;
  static long int serial_input_next_char_idx = 0; // where to store the next character
  char inchar;
  long int inchar_count = 0;

  while (Serial.available()) {
    // whether saving the characters or flushing the input queue, we always read characters.
    inchar = (char) Serial.read();
    inchar_count += 1;
    if (inChar == '\n') {
      // again in either case, we process command if we see end of line
      handle_serial_input_command(serial_input_buf);
      memset((void *)serial_input_buf, 0, SERIAL_INPUT_BUF_LEN); // clear buffer
      serial_input_next_char_idx = 0; // where to store the next character
      serial_input_flushing = 0; // no longer flushing
      break; // process only one command, return back to loop for next command
    } else if (serial_input_flushing) {
      if (SERIAL_MAX_INPUT_INPUT_EACH_CALL <= inchar_count) break; // if flushing and max chars consumed, return back to loop()
    } else {
      // here we are storing characters
      if (SERIAL_MAX_INPUT_LEN <= (serial_input_next_char_idx+1)) {
        // already stored the max number of characters, now we are flushing
        serial_input_flushing = 1;
      } else if (isDigit(inchar)) {
        // room to store character and character is a digit, store it
        serial_input_buf[serial_input_next_char_idx++] = inchar;
      }
      // check if max chars consumed; if so return back to loop(), if more chars allowed, stay in our "while" loop
      if (SERIAL_MAX_INPUT_INPUT_EACH_CALL <= inchar_count) break;
    } // end either process or flush characters
  } // end while serial input data available
} // end handle_serial_input()
```

In **setup()** we add these lines just before the first **Serial.println**
```C
  while (Serial.available()) Serial.read(); // clear any startup junk from the serial queue
  memset((void *)serial_input_buf, 0, SERIAL_INPUT_BUF_LEN); // clear buffer; good idea for zero-terminated strings
```

In **loop()** near the front
```C
  if (Serial.available()) handle_serial_input();
```

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
