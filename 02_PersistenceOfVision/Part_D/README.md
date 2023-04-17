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
#define SERIAL_MAX_INPUT_LEN 250 // maximum number of characters to accept prior to calling it quits
#define SERIAL_INPUT_BUF_LEN 255 // size of our actual buffer; room for terminating '\0' and a little extra
static char serial_input_buf[SERIAL_INPUT_BUF_LEN]; // one character for terminating '\0'
static int pattern_num = 0; // this is the result of handling commands - to change this number
```

Before **setup()** we add these lines:

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
#define SERIAL_MAX_INPUT_INPUT_EACH_CALL 5 // maximum number of characters to read each call

void handle_serial_input() {
  static int serial_input_flushing = 0;
  static long int serial_input_next_char_idx = 0; // where to store the next character
  char inchar;
  long int inchar_count = 0;

  while (Serial.available()) {
    inchar = (char) Serial.read();
    inchar_count += 1;
    if (inChar == '\n') {
      handle_serial_input_command(serial_input_buf);
      memset((void *)serial_input_buf, 0, SERIAL_INPUT_BUF_LEN); // clear buffer
      serial_input_next_char_idx = 0; // where to store the next character
      serial_input_flushing = 0; // no longer flushing
      break;
    } else if (serial_input_flushing) {
      if (SERIAL_MAX_INPUT_INPUT_EACH_CALL <= inchar_count) break;
    } else {
      if SERIAL_MAX_INPUT_LEN <= (serial_input_next_char_idx+1)) {
        serial_input_flushing = 1;
      } else {
        serial_input_buf[serial_input_next_char_idx++] = inchar;
      }
      if (SERIAL_MAX_INPUT_INPUT_EACH_CALL <= inchar_count) break;
    } // end either process or flush characters
  } // end while serial input data available
} // end handle_serial_input()
```

In **setup()** we add these lines near the start:

```C
  Serial.begin(115200);         // this serial communication is for general debug; set the USB serial port to 115,200 baud

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  while (Serial.available()) Serial.read(); // clear any startup junk from the serial queue
  memset((void *)serial_input_buf, 0, SERIAL_INPUT_BUF_LEN); // clear buffer; good idea for zero-terminated strings
  Serial.println(""); // print a blank line in case there is some junk from power-on
  Serial.println(F("ArduinoClass init..."));
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
