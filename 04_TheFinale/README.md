# Notes

**Table of Contents**
* [Top](#notes "Top")
* [The ThereminSound Idea](#the-thereminsound-idea "The ThereminSound Idea")
  * [The Circuit](#the-circuit "The Circuit")
    * [TLDR UART Serial Interface](#tldr-uart-serial-interface "TLDR UART Serial Interface")
    * [YX5200 Sound Module](#yx5200-sound-module "YX5200 Sound Module")
    * [KCX_BT_EMITTER Bluetooth Sound Transmitter](#kcx_bt_emitter-bluetooth-sound-transmitter "KCX_BT_EMITTER Bluetooth Sound Transmitter")
  * [The ThereminSound Code](#the-thereminsound-code "The ThereminSound Code")
    * [Code Outline](#code-outline "Code Outline")
    * [Hysteresis](#hysteresis "Hysteresis")
    * [Code Details](#code-details "Code Details")
* [The VoiceCommands and VC_DemoReel Idea](#the-voicecommands-and-vc_demoreel-idea "The VoiceCommands and VC_DemoReel Idea")
  * [TLDR I2C Interface](#tldr-i2c-interface "TLDR I2C Interface")
  * [The Circuit - Two Arduinos](#the-circuit-\--two-arduinos "The Circuit - Two Arduinos")
  * [The VoiceCommands and VC_DemoReel Code](#the-voicecommands-and-vc_demoreel-code "The VoiceCommands and VC_DemoReel Code")
    * [Modified DFRobot code for DF2301QG](#modified-dfrobot-code-for-df2301qg "Modified DFRobot code for DF2301QG")
    * [DF2301QG code](#df2301qg-code "DF2301QG code")
  * [Parallel Arduino-to-Arduino Interface](#parallel-arduino\-to\-arduino-interface "Parallel Arduino-to-Arduino Interface")
    * [Parallel Interface Interesting Part](#parallel-interface-interesting-part "Parallel Interface Interesting Part")
  * [VC_DemoReel Sound Code](#vc_demoreel-sound-code "VC_DemoReel Sound Code")

There are two projects or builds in this section (Finale and Encore?) - **ThereminSound** and **VoiceCommands and VC_DemoReel**.

## The ThereminSound Idea
[Top](#notes "Top")<br>
Our Theremin, especially with the large LED disks, is pretty impressive. It can be a little dicey to hold your hand in the right place to see the pattern play out, but the USB Monitor will tell which pattern it is showing.

In this project we will add a circuit to send sound to a Bluetooth speaker to tell us which pattern we are on. When the system powers on it will announce the project, state the pattern being displayed, and then provide background sound collected from Saturn's electromagnetic field by the Cassini mission. If the HC-SR04 detects that a different pattern has been selected, the sound will state the new pattern and then return to the Cassini sound.

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/04_TheFinale_DemoReelSound_setup.jpg" width="750" alt="Image of Theremin with Speech Sound">

Here is a video of this circuit in operation:
- https://youtu.be/G7ARC0xHXRg

### The Circuit
[Top](#notes "Top")<br>
The plan is that the circuit to implement the sound to the bluetooth will be on a different breadboard than the one containing the Theremin circuit. There will only be one of these so I will bring it around to the different stations so everyone can try it. In order to use it we will need the setup for the large LED disks including its separate power supply, so I will bring that around too.

The wiring schematic can be found here; an image is given below.
- https://github.com/Mark-MDO47/ArduinoClass/blob/master/04_TheFinale/04_TheFinale_ThereminSound.pdf

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/04_TheFinale_DemoReelSound.png "Circuit for 04 The Finale - Theremin with Sound")

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/04_TheFinale_DemoReelSound_Fritzing.png" width="750" alt="Fritzing image of wiring diagram for for 04 The Finale - Theremin with Sound">

In the schematic wiring diagram above, everything below the red line is on the new breadboard that I will bring along. The schematic includes the "Programming Arduino" page but we will not be using that in the class as I will already have paired the bluetooth speaker with our circuit.  In the Fritzing image above, this portion of the circuit is inside the red dotted-line rectangle and is labeled "Bluetooth and Sound Circuitry.

The interface between the two circuits consists of five wires on the new breadboard:
| Color | Purpose |
| --- | --- |
| Red | 5V power from the battery circuit |
| Black | Common Ground (digital) for all circuitry |
| Green | YX5200 RX - used for Arduino to send serial commands to YX5200 |
| Blue | YX5200 TX - used for Arduino to receive serial status from YX5200 |
| Yellow | YX5200 Busy - used for Arduino to detect if current sound still being played |

#### TLDR UART Serial Interface
[Top](#notes "Top")<br>
To communicate with the YX5200 we use a serial data protocol named Universal Asynchronous Receiver Transmitter or UART for short.
- We previously saw a serial data protocol for sending color information to the WS2812B LEDs; that one used a single wire to transmit data in just one direction.
- The UART protocol used on the Arduinos is also one wire, but a second wire can be used to transmit in the other direction. The UART protocol itself can actually get more complicated than that, but for us this description is adequate.
- UART interaces can be used to program the Arduino Nano; the USB port on the Arduino actually connects up to a hardware UART implementation.
- Arduino UART interfaces to other devices are quite common; we will use a special library SoftwareSerial to connect to the YX5200 using ordinary digital I/O pins.

Here is an excellent description of how the UART interface works:
- https://www.seeedstudio.com/blog/2022/09/08/uart-communication-protocol-and-how-it-works/

Below is an illustration from that tutorial showing the high/low sequences on the line for a UART byte transfer:<br>
<img src="https://www.seeedstudio.com/blog/wp-content/uploads/2022/09/uart1.png" width="600" alt="seeedstudio.com image of UART byte transfer"><br>

Note that the detection of the first high-to-low transition is used to set the time used to (hopefully) sample the other bits in the middle of the bit. The timing of the bits on the transmitting side and the timing of the detection of the bits on the receiving side need to remain in sync throughout or there can be a receive error. We will see how that can affect us in the **VoiceCommands and VC_DemoReel** project that follows this one.

#### YX5200 Sound Module
[Top](#notes "Top")<br>
The YX5200 Sound Module uses a FAT-formatted SD (a.k.a. TF) card of up to 32 GByte to store numbered sound files to play. It outputs the sound on both speaker-level (less than 3 Watts) and line-level outputs. For this circuit we will use the line level outputs.

I have a separate GitHub project describing how to use this module:
- https://github.com/Mark-MDO47/AudioPlayer-YX5200

Some of the things to keep in mind:
- The library I use to control the YX5200 is written by dfrobot.com. I copied a version from their github page and put it directly in the directory with the *.ino file.
  - https://github.com/DFRobot/DFRobotDFPlayerMini - the library
  - https://wiki.dfrobot.com/DFPlayer_Mini_SKU_DFR0299 - the DFRobot version of the part
  - https://www.dfrobot.com/product-1121.html - includes some samples and projects for the part
  - The dfrobot.com DFPlayer library is also available in the Arduino IDE Library Manager as seen below. There are other libraries available for controlling these parts but I don't have much experience with the others.<br>
<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/04_TheFinale_DemoReelSound_DFRobotLib.png" width="600" alt="Library Manager image of DFRobot library to control YX5200"><br>
- The way the files are stored on the SD (or TF) card must be exactly right. If there was ever any file or directory placed on the SD card, the SD card must first be FAT-formatted again before storing or changing files on the card. My YX5200 GitHub page (see above) on this module includes a Python program copyem.py that helps with this.
- There is a 1 KOhm resistor between the Arduino and the YX5200 RX pin. This is not optional. If this is left out then the commands sent on this line will be heard in the sound from the speaker.
- When using the YX5200 line-level outputs to the Bluetooth module, the correct ground must be used. There are two ground pins on the YX5200 and the documentation does not distinguish between them, but one works far better as audio-ground or analog-ground than the other. Again, you can refer to my YX5200 GitHub page (see above).
- The card can play MP3 files but there is a delay to start playing. It is much faster starting with WAV files.
- There are many clones of this chip and it is hard to know when you order one (unless you order from dfrobot.com) which clone you will get. Some of the more elaborate features don't work on some of the clones.
- The BUSY line will not change to busy status immediately; it takes some milliseconds. My measurements are that it might take as few as 40 milliseconds, but that may depend on which YX5200 clone you are using. After starting a sound, I make the software pretend that the BUSY line is in busy status for 250 milliseconds before actually using the state of the line.

#### KCX_BT_EMITTER Bluetooth Sound Transmitter
[Top](#notes "Top")<br>
The KCX_BT_EMITTER Bluetooth Sound Transmitter module takes its line-level inputs and sends them to a Bluetooth receiver.The KCX_BT_EMITTER Version 1.1 (and 1.2) used here conforms to an earlier version of Bluetooth than the latest Bluetooth 5.3. Depending on what documentation you read, it uses either version 4.1 or 4.2. This works well with my Bluetooth speaker but has not worked with any Bluetooth earphones I have tried. This version of the KCX_BT_EMITTER is the one I am familiar with. There is an updated Version 1.7 supporting some more advanced features but I have much more experience with these 1.1 versions.

I have a separate GitHub project describing how to use this module:
- https://github.com/Mark-MDO47/BluetoothAudioTransmitter_KCX_BT_EMITTER/tree/KCX_BT_EMITTER_V1.1 (branch for the V1.1 and V1.2 versions used here)
- https://github.com/Mark-MDO47/BluetoothAudioTransmitter_KCX_BT_EMITTER (master branch, points to branches KCX_BT_EMITTER_V1.1 and KCX_BT_EMITTER_V1.7)

Some of the things to keep in mind:
- When the KCX_BT_EMITTER is freshly initialized, it will try to connect to the first Bluetooth audio receiver (speaker or earbuds or headphones) it finds. It can be paired with a specific device so it doesn't connect to some random speaker; to do that I use the "Programming Arduino" which allows me to see what Bluetooth devices it sees and to select among them for ones it will be allowed to connect with. The "Programming Arduino" can also remove devices from the allowed list.
- Once the KCX_BT_EMITTER has been programmed to allow pairing with one or more devices, it will not connect to a random device but will wait to connect to one of the devices on its list.
- It does take a few seconds to pair up with a device.
- Unlike the YX5200, the KCX_BT_EMITTER has a power-ground (or digital-ground) and an audio-ground (or analog-ground) clearly distinguished in its documentation.

### The ThereminSound Code
[Top](#notes "Top")<br>
We start from the final Theremin code from section 3 https://github.com/Mark-MDO47/ArduinoClass/tree/master/03_SonarRangeDetector and name it ThereminSound.ino

As mentioned above, I have directly copied the dfrobot.com DFPlayer library into the code area in the Arduino code section of this class GitHub page but alternatively the library is available in the library manager. I tend to keep my own copy of the library since I initially had to do significant debugging to learn how to communicate not just with the dfrobot.com version of the part but also with several of the different clones. It was convenient to be able to put debugging statements directly in the library to do that debugging, and I have continued the practice of having the library available for me to modify as desired. Note that there are also several alternative libraries for communicating with YX5200 parts.
- https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/ThereminSound

#### Code Outline
[Top](#notes "Top")<br>
Below is an outline of the changes we will make

Before **setup()** we will:
- Create the global object mySoftwareSerial to talk on our YX5200 RX and TX pins.
- Create the global object myDFPlayer to handle YX5200 communications using the above pins.

In **setup()** we will:
- Initialize the pin used to sense when the sound has completed.
- Call our **DFsetup()** routine to
  - connect to mySoftwareSerial
  - initialize the YX5200 and set some parameters
  - delay 3 seconds to allow the Bluetooth speaker to connect
  - start playing the intro sound; this sound is protected to play completely

In **loop()** we will:
- Set gPatternNumberChanged non-zero whenever the pattern number changes
- Call our **DFcheckSoundDone()** routine to
  - if the intro sound is still playing, let it finish and return
  - if the pattern changed, interrupt the current sound and start playing the  announcement for the new pattern
  - otherwise:
    - handle the delay in believing the BUSY signal from YX5200 (see above in discussion on YX5200)
    - if BUSY signal says sound completed, play the Cassini sound

To get the timing delay for BUSY and get intro to play and then pattern to be announced once and then Cassini to play until a new pattern, we use the following state table.<br>
NOTE: the myBusy column is "not busy" if HIGH==DPIN_AUDIO_BUSY **and** the forceBusy timer has expired; otherwise it is "BUSY".<br>
| gPatternNumberChanged | state_introSoundPlaying | myBusy | Action | Reason |
| --- | --- | --- | --- | --- |
| 0 | 1 | BUSY | no change | still playing intro |
| 1 | 1 | BUSY | no change | still playing intro |
| 0 | 1 | not busy | start Cassini | intro done, no new pattern |
| 1 | 1 | not busy | start pattern | intro done, new pattern |
| 0 | 0 | BUSY | no change | sound still playing, no new pattern |
| 1 | 0 | BUSY | start pattern | pattern changed, interrupt |
| 0 | 0 | not busy | start Cassini | no sound playing, intro done, no new pattern |
| 1 | 0 | not busy | start pattern | no sound playing, pattern changed |

#### Hysteresis
One aspect of the Sonar Range Finder is that it is easy to get your hand near the region separating two distinct patterns and have it waver back and forth between the two patterns.

One approach to making this easier would be to add "hysteresis" in the changing between patterns. The general definition of this is "the value of a physical property lags behind changes in the effect causing it" but I am using it as it is seen in electronics, in which once a decision is made the threshold is moved such that going back to the previous decision is harder.
- An example might be a 12 volt relay coil. If the voltage is raised slowly the relay may turn on at perhaps 11 volts, but it will remain turned on as you drop the voltage below 11 volts to perhaps 9 volts before it turns off.
- Another way of thinking about the example above is that the output of the relay depends on both the voltage and the history. If the voltage is 10 volts and the history is that it was previously on, the output is that the relay is on. If the voltage is 10 volts and the history is that it was previously off, the output is that the relay is off. The history could also be stated in terms of the voltage history instead of the relay output history, but it would be a more complicated statement.
- I experimented with simulating a similar effect in software using the HC-SR04 in my "Park the Car" project (https://github.com/Mark-MDO47/KnowHow_ParkTheCar) but was never happy with the result.

For this project I took a different approach. Each sound file that states the name of a pattern starts with a short silent period, giving the hand a chance to find a region where the new pattern is stable without having the speaker go back and forth rapidly speaking different patterns.

#### Code Details
[Top](#notes "Top")<br>

Replace everything between the following two lines with the below code and comments<br>
```
 * https://github.com/Mark-MDO47/ArduinoClass/tree/master/03_SonarRangeDetector
<<< several lines here >>>
#define NUM_LEDS 8 // Mark-MDO47 number of WS2812B LEDs
```

```
 * https://github.com/Mark-MDO47/ArduinoClass/tree/master/04_TheFinale
 * 
 * Theremin with sound
 */

 // connections:
// 
// Nano pin 5V      LEDstick VCC
// Nano pin GND     LEDstick GND
// Nano pin D-7     LEDstick DIN
//
// Nano pin 5V      SR04 VCC
// Nano pin GND     SR04 GND
// Nano pin D-12    SR04 Trig
// Nano pin D-10    SR04 Echo
//
// Nano pin D-8     YX5200 TX; Arduino RX
// Nano pin D-9     YX5200 RX; Arduino TX
// Nano pin D-11    YX5200 BUSY; HIGH when audio finishes

#include <FastLED.h>
#include <Ultrasonic.h>

#include "Arduino.h"
#include "SoftwareSerial.h"                  // to talk to myDFPlayer without using up debug serial port
#include "DFRobotDFPlayerMini.h"             // to communicate with the YX5200 audio player

#define DPIN_SWSRL_TX    9  // serial out - talk to DFPlayer audio player (YX5200)
#define DPIN_SWSRL_RX    8  // serial in  - talk to DFPlayer audio player (YX5200)
#define DPIN_AUDIO_BUSY 11  // digital input - HIGH when audio finishes

SoftwareSerial mySoftwareSerial(/*rx =*/DPIN_SWSRL_RX, /*tx =*/DPIN_SWSRL_TX); // to talk to YX5200 audio player
              // SoftwareSerial(rxPin,         txPin,       inverse_logic)
DFRobotDFPlayerMini myDFPlayer;                                // to talk to YX5200 audio player
void DFsetup();                                                // how to initialize myDFPlayer

#define SOUNDNUM_INTRO   7 // our introduction
#define SOUNDNUM_CASSINI 8 // Cassini Saturn sound - SPACE!!!
#define SOUND_DEFAULT_VOL     25  // default volume - 25 is pretty good
#define SOUND_BKGRND_VOL      20  // background volume
#define SOUND_ACTIVE_PROTECT 250  // milliseconds to keep SW twiddled sound active after doing myDFPlayer.play(mySound)
uint32_t state_timerForceSoundActv = 0;  // end timer for enforcing SOUND_ACTIVE_PROTECT
uint8_t state_introSoundPlaying = 1; // we start with the intro sound
 
// How many leds in your strip?
#define NUM_LEDS 241 // number of WS2812B LEDs
```

Replace everything between the following lines with the below code and comments<br>
```
// constants won't change:

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current

void rainbow() 
```

```C
// our current pattern number, from 0 thru 5 inclusive
uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gLatestTruePatternNumber = 0; // latest true pattern (not psuedo-pattern)
uint8_t gPrevPattern = 99; // previous pattern number
uint8_t gPatternNumberChanged = 0; // non-zero if need to announce pattern number

#define DFCHANGEVOLUME 0 // zero does not change sound
// #define DFPRINTDETAIL 1 // if need detailed status from myDFPlayer (YX5200 communications)
#define DFPRINTDETAIL 0  // will not print detailed status from myDFPlayer
#if DFPRINTDETAIL // routine to do detailed debugging
  void DFprintDetail(uint8_t type, int value); // definition of call
#else  // no DFPRINTDETAIL
  #define DFprintDetail(type, value) // nothing at all
#endif // #if DFPRINTDETAIL

/////////////////////////////////////////////////////////////////////////////////////////////////////////
#if DFPRINTDETAIL
void DFprintDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerUSBInserted:
      Serial.println("USB Inserted!");
      break;
    case DFPlayerUSBRemoved:
      Serial.println("USB Removed!");
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      } // end switch (value)
      break;
    default:
      break;
  }  // end switch (type)
} // end DFprintDetail()
#endif // DFPRINTDETAIL

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// DFstartSound(tmpSoundNum, tmpVolume) - start tmpSoundNum if it is valid
//
// tmpSoundNum is the sound file number. For our Arduino Class this is 1 through 8 inclusive
//
// Had lots of trouble with reliable operation using playMp3Folder. Came to conclusion
//    that it is best to use the most primitive of YX5200 commands.
// Also saw strong correlation of using YX5200 ACK and having even more unreliable
//    operation, so turned that off in DFinit.
// The code checking DPIN_AUDIO_BUSY still needs the delay but 250 millisec is probably overkill.
// There is code checking myDFPlayer.available() that can maybe also be removed now
//    that the dubugging for above is finished. Now that I am using myDFPlayer.play(),
//    it only seems to trigger when I interrupt a playing sound by starting another.
//    It is sort of interesting but not needed.
//
void  DFstartSound(uint16_t tmpSoundNum, uint16_t tmpVolume) {
  uint16_t idx;
  bool prevHI;
  uint16_t mySound = tmpSoundNum;
  static uint8_t init_minmax = 2;
  static uint32_t prev_msec;
  static uint32_t max_msec = 0;
  static uint32_t min_msec = 999999;
  uint32_t diff_msec = 0;
  uint32_t now_msec = millis();


#if DFCHANGEVOLUME
  myDFPlayer.volume(tmpVolume);  // Set volume value. From 0 to 30 - FIXME 25 is good
#if DFPRINTDETAIL
  if (myDFPlayer.available()) {
    Serial.print(F(" DFstartSound ln ")); Serial.print((uint16_t) __LINE__); Serial.println(F(" myDFPlayer problem after volume"));
    DFprintDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
  }
#endif // DFPRINTDETAIL
#endif // DFCHANGEVOLUME

  myDFPlayer.play(mySound); //play specific mp3 in SD: root directory ###.mp3; number played is physical copy order; first one copied is 1
  // Serial.print(F("DEBUG DFstartSound myDFPlayer.play(")); Serial.print((uint16_t) mySound); Serial.println(F(")"));
  state_timerForceSoundActv = millis() + SOUND_ACTIVE_PROTECT; // handle YX5200 problem with interrupting play

  if (init_minmax) {
    init_minmax -= 1;
  }  else {
    diff_msec = now_msec - prev_msec;
    if (diff_msec > max_msec) {
      max_msec = diff_msec;
      // Serial.print(F("max_msec ")); Serial.println(max_msec);
    } else if (diff_msec < min_msec) {
      min_msec = diff_msec;
      // Serial.print(F("min_msec ")); Serial.println(min_msec);
    }
  }
  prev_msec = now_msec;
} // end DFstartSound()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// DFcheckSoundDone()
//
// notBusy means (HIGH == digitalRead(DPIN_AUDIO_BUSY)) && (millis() >= state_timerForceSoundActv)
//    DPIN_AUDIO_BUSY goes HIGH when sound finished, but may take a while to start
//    state_timerForceSoundActv is millisec count we have to wait for to before checking DPIN_AUDIO_BUSY
//
void DFcheckSoundDone() {
  uint8_t myBusy = (HIGH != digitalRead(DPIN_AUDIO_BUSY)) || (millis() < state_timerForceSoundActv);
  uint8_t playNumber = 99; // this means don't change

  if (0 != state_introSoundPlaying) { // intro still playing
    if (0 == myBusy) { // can play a non-intro sound
      if (0 != gPatternNumberChanged) { // start pattern sound
        playNumber = gCurrentPatternNumber+1; // sound numbers start at 1
      } else { // start Cassini sound
        playNumber = SOUNDNUM_CASSINI; // this should never execute, we start with gPatternNumberChanged=1
      } // end start a sound
    } // end if can play a non-intro sound
  } else { // intro done
    if (0 != gPatternNumberChanged) { // always start new pattern number sound
      playNumber = gCurrentPatternNumber+1; // sound numbers start at 1
    } else if (0 == myBusy) { // sound finished and no new pattern, start Cassini
      playNumber = SOUNDNUM_CASSINI;
    }
  } // end if intro done

  if (99 != playNumber) { // there is a new sound to play
    gPatternNumberChanged = 0;
    state_introSoundPlaying = 0;
    if (SOUNDNUM_CASSINI == playNumber) {
      DFstartSound(SOUNDNUM_CASSINI, SOUND_BKGRND_VOL);
    } else {
      DFstartSound(gCurrentPatternNumber+1, SOUND_DEFAULT_VOL);
    }
  } // end if there is a new sound to play
} // end DFcheckSoundDone()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// DFsetup()
void DFsetup() {
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial, false, true)) {  // Use softwareSerial to communicate with mp3 player
    Serial.println(F("Unable to begin DFPlayer:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(1);
    }
  }
  myDFPlayer.EQ(DFPLAYER_EQ_BASS); // our speaker is quite small
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD); // device is SD card
  myDFPlayer.volume(SOUND_DEFAULT_VOL);  // Set volume value. From 0 to 30 - FIXME 25 is good
  delay(3); // allow bluetooth connection to complete
  Serial.println(F("DFPlayer Mini online."));

  DFstartSound(SOUNDNUM_INTRO, SOUND_DEFAULT_VOL);
} // end DFsetup()

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// The brilliant (no pun intended) Demo Reel 100 patterns!
void rainbow() 
```

In the **setup()** routine before the following lines, add the new code below it.<br>
```C
  Serial.println(""); // print a blank line in case there is some junk from power-on
  Serial.println("ArduinoClass init...");
```

```C
  pinMode(DPIN_AUDIO_BUSY,  INPUT_PULLUP); // HIGH when audio stops

  mySoftwareSerial.begin(9600); // this is control to YX5200 DFPlayer audio player

  // initialize the DFPlayer audio player
  DFsetup();
```
In the **loop()** routine, replace the following lines with the lines below. Notice the addition of **gPatternNumberChanged = 1;** and **DFcheckSoundDone();**<br>
```C
  EVERY_N_MILLISECONDS( 200 ) { gCurrentPatternNumber = handle_ultra(); }
  if (gPrevPattern != gCurrentPatternNumber) {
    gPrevPattern = gCurrentPatternNumber;
    Serial.print(gPatternStrings[gCurrentPatternNumber]); Serial.println(gUltraDistance);
  }
```

```C
  EVERY_N_MILLISECONDS( 200 ) { gCurrentPatternNumber = handle_ultra(); }
  if (gPrevPattern != gCurrentPatternNumber) {
    gPrevPattern = gCurrentPatternNumber;
    gPatternNumberChanged = 1; // alerts the announcement of the pattern
    Serial.print(gPatternStrings[gCurrentPatternNumber]); Serial.println(gUltraDistance);
  }

  // whenever current sound is done, go back to Cassini
  DFcheckSoundDone();
```

## The VoiceCommands and VC_DemoReel Idea
[Top](#notes "Top")<br>
The Theremin with pattern announcements over Bluetooth speaker is very cool; but if we could control it by voice commands that would be even cooler!

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/04_smileyface.png" width="500" alt="Image of Voice Command Demo Reel with Smiley Face displayed">

Here is a YouTube of this project in operation:
- https://youtu.be/M8Xc4aVh5Hc

In this project we will add a circuit to listen to voice commands for which pattern to display ("Display number zero" through "Display number five") and send an identifying code to the Arduino. This will cause us to display the associated DemoReel100 pattern on the LEDs and announce the pattern name on the Bluetooth speaker. We will disconnect the HC-SR04 Ultrasonic Range Detector to avoid confusion in commanding of patterns.

| Voice Command | Pattern |
| --- | --- |
| Display number zero | rainbow |
| Display number one | rainbowWithGlitter |
| Display number two | confetti |
| Display number three | sinelon |
| Display number four | juggle |
| Display number five | bpm |
| Display smiley face | toggle smiley face and merge into pattern |
| --- | --- |
| Volume up | change volume |
| Volume down | change volume |
| Change volume to maximum | change volume |
| Change volume to minimum | change volume |
| Change volume to medium | change volume |


The device we will use to accept voice commands is the DFRobot DF2301QG SKU SEN0539-EN from the Gravity product line. I will bring this circuit around to the stations so everyone can try it on their system.
- https://www.dfrobot.com/product-2665.html
- https://wiki.dfrobot.com/SKU_SEN0539-EN_Gravity_Voice_Recognition_Module_I2C_UART

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/SEN0539-EN-1_from_dfrobot.com.jpg" width="500" alt="Image of DF2301QG voice command module from dfrobot.com">

One interesting thing about this device is that it doesn't depend on any Internet connection or giant tech company voice-to-text service; it does the voice recognition locally.

Another thing I noticed is that the documentation for UART calls to set volume give a range of 1 through 7 but the I2C code to set the volume seems to imply via commented-out code a range of 0 through 20. The module at power-on has a higher volume than a volume setting of 7.<br>
**Documentation:**<br>
```
$ git remote -v
origin  https://github.com/DFRobot/DFRobot_DF2301Q.git (fetch)
origin  https://github.com/DFRobot/DFRobot_DF2301Q.git (push)
$ grep -in "volume" *.* examples/*/*.* | grep -i "range\|DF2301Q_"
$ grep -in "volume" *.* examples/*/*.* | grep -i "range\|[@]"
DFRobot_DF2301Q.h:171:   * @fn setVolume
DFRobot_DF2301Q.h:172:   * @brief Set volume
DFRobot_DF2301Q.h:173:   * @param vol - Volume range(1-7)
DFRobot_DF2301Q.h:302:   * @n       DF2301Q_UART_MSG_CMD_SET_VOLUME : Set volume, the set value range 1-7
README.md:106:   * @fn setVolume
README.md:107:   * @brief Set volume
README.md:108:   * @param vol - Volume range(1-7)
README.md:173:   * @n       DF2301Q_UART_MSG_CMD_SET_VOLUME : Set volume, the set value range 1-7
README_CN.md:106:   * @fn setVolume
README_CN.md:173:   * @n       DF2301Q_UART_MSG_CMD_SET_VOLUME : ????, ?????1~7
examples/i2c/i2c.ino:5: * @n  Get and set the wake-up state duration, set mute mode, set volume, and enter the wake-up state
examples/i2c/i2c.ino:30:   * @brief Set voice volume
examples/i2c/i2c.ino:31:   * @param voc - Volume value(1~7)
examples/uart/uart.ino:5: * @n  Set the wake-up state duration, set mute mode, set volume, enter the wake-up state, and reset the module
examples/uart/uart.ino:49:   * @n       DF2301Q_UART_MSG_CMD_SET_VOLUME : Set volume, the set value range 1-7
```

**I2C Code:**<br>
```C
void DFRobot_DF2301Q_I2C::setVolume(uint8_t vol)
{
  // if (vol < 0)
  //   vol = 0;
  // else if (vol > 20)
  //   vol = 20;
  writeReg(DF2301Q_I2C_REG_SET_VOLUME, &vol);
}
```

After some experimentation I decided that the I2C interface provided a more reliable communication between Arduino to DF2301QG than the UART interface.

### TLDR I2C Interface
[Top](#notes "Top")<br>
The I2C (Inter-Integrated Circuit) interface is a serial protocol using a **bus** structure; this is different than the WS2812B serial protocol and the UART serial protocol that are **point-to-point**. It also differs in that it is a **clocked** or **synchronous** serial interface and thus requires two lines (one clock one data), instead of the **asynchronous** serial interfaces that we have seen before.<br>
- https://docs.arduino.cc/learn/communication/wire
- https://howtomechatronics.com/tutorials/arduino/how-i2c-communication-works-and-how-to-use-it-with-arduino/
- https://www.geeksforgeeks.org/i2c-communication-protocol/

The image below from howtomechatronics.com shows what a typical I2C bus might look like. Note that there are multiple devices attached to the bus, so there must be a part of the I2C protocol for deciding which device gets to talk on the bus next. The protocol used is one example of the **so-called master/slave** protocol, in which the bus master (in this case an Arduino) decides who talks on the bus at any time. The master also generates the clock. The other devices all have an address (example 0x34 for one of the devices below) that allows the master to specifically talk with it. In our case we will use the default I2C address for the DF2301QG: 0x50.<br>
<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/I2C-Communication-How-It-Works_from_howtomechatronics.com.png" width="750" alt="howtomechatronics.com image of I2C bus">

Most Arduinos have I2C communication hardware built in. Curiously, that I2C hardware can be accessed by using the analog pins A4 and A5; that is what we will do with the Arduino Nano. Some Arduinos have other pins that can also access the I2C hardware.

I will leave the references above to explain the details of how the I2C interface works.

### The Circuit - Two Arduinos
[Top](#notes "Top")<br>
The communication with the LEDs and with the YX5200 sound module use "software serial" communications on general purpose I/O pins. The Arduino Nano must set these pins HIGH or LOW at fairly precise times to send the information to the device. In my code I turn off the reply from the YX5200 because that seemed to be too high a computational and timing burden on the poor Arduino Nano - the commands would go out OK but when it tried to read the acknowledgement it couldn't get the correct data so it generated error messages. I ultimately decided to just assume the command went out OK so I disabled reading the acknowledgement.

The addition of the DF2301QG to this mix caused similar problems. This time there was no way to avoid doing serial read operations - we need to get the numeric code telling us what the voice command is! This worked pretty well (not perfect, maybe problem with my code) if I used an Arduino Nano to talk to the DF2301QG and not also talk to the LEDs or YX5200, so I split it into two Arduinos as you can see here:
- https://github.com/Mark-MDO47/ArduinoClass/blob/master/04_TheFinale/04_TheFinale_DemoReelVoiceCommand_I2C.pdf<br>

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/04_VC_schematic_I2C.png" width="750" alt="Image of schematic of Voice Command circuit showing use of two Arduino Nanos">

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/04_TheFinale_DemoReelVoiceCommand_Fritzing_I2C.png" width="750" alt="Image of Fritzing of circuit showing use of two Arduino Nanos">

The Arduino Nano and its circuit on the left is pretty similar to the ThereminSound circuit - I just removed the HC-SR04 Ultrasonic Range Detector and an extraneous button.

The new Arduino Nano and its circuit on the right is very simple. Power and ground are distributed with the traditional black and red wires. Green and Blue I2C wires go to the DF2301QG (be sure to select the I2C communication mode with the slide switch).  The wire color scheme is set by the cable included with the DF2301QG.

There are a different four wires (blue, yellow, orange, and white) connecting the two Arduino Nanos providing a very simple parallel interface (as opposed to serial) to transfer the pattern number across. I used this parallel interface to minimize computational and timing burden on the left Arduino Nano.

Below is an image of the setup of the complete Voice Command circuit showing use of two Arduino Nanos. I had to make a power source with more oomph than the 9V battery; the 241 LEDs really use up the power. We said before that we were approaching the limit of practical complexity wiring up with breadboards; this really pushes that limit!<br>
<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/04_VC_setup_I2C.jpg" width="600" alt="Image of setup of Voice Command circuit showing use of two Arduino Nanos">

Below is a closeup image just the Voice Command part of the circuit. You can see the green and blue lines for the I2C connection to the DF2301QG and also see the white/orange/yellow/blue lines for the parallel Arduino-to-Arduino connection.<br>
<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/04_VC_closeup_I2C.png" width="600" alt="Image of closeup of just the Voice Command part of the circuit">


### The VoiceCommands and VC_DemoReel Code
[Top](#notes "Top")<br>
I won't go into much detail for the VC_DemoReel.ino for the Arduino on the left - it is very similar to the ThereminSound.ino code except I stripped out the code for the HC-SR04 Ultrasonic range detector. I did add the parallel Arduino-to-Arduino interface, and I will discuss the code on both sides of this below. Take a look here and see the discussions below for how it handles receiving the pattern commands and how it handles the "smiley face" psuedo-pattern.
- https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/VC_DemoReel

The VoiceCommands_I2C.ino code for the Arduino on the right is very simple, thanks to the DFRobot library code (even my hacked up version). It is not very similar to our other code, so probably best to copy it from here and read through the description below.
- https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/VoiceCommands

#### Modified DFRobot code for DF2301QG
[Top](#notes "Top")<br>
The library for communicating with the DF2301QG supplied by DFRobot didn't succesfully compile for the **UART** interface with an Arduino Nano. Looking at their code, it compiled for certain Arduinos but not all Arduinos.

I don't know but I would guess that they set up their code to only compile with models of Arduino that they had tested with the code. There is evidence that the order of operations needed to be different for certain Arduino models. As a result I hacked up the DFRobot code a bit to make it compile for the Arduino Nano.

The DF2301QG has two slide-switch-selectable communication modes: UART and I2C. These are both pretty standard serial communication protocols; I2C is often used with Arduino projects.<br>
The DF2301QG also has slide-switch-selectable internal or external speakers; we set it to internal.<br>
Be sure the slide switches are in the right position before use.


I had to hack up the DFRobot library to work with Arduino Nano and the **UART** method; you can find this code here:<br>
- https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/VoiceCommands_UART

The original DFRobot library did work with Arduino Nano and the **I2C** method, and some experiments I did suggest that I2C communication is more solid than the UART communication with this device (fewer voice commands that the DF2301QG tried to send to Nano but Nano did not receive). Because of this I used the I2C method. As I usually do with devices that I had to experiment with, I put the library code (in this case unmodified) directly in place with my code.
- https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/VoiceCommands_I2C

The unmodified DFRobot code can be found here:
- https://github.com/DFRobot/DFRobot_DF2301Q
It can alternatively be loaded with the Arduino IDE library manager as seen below:

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/Library_DF2301Q.png" width="600" alt="Image of Arduino IDE selection for DFRobot DF2301Q library">

#### DF2301QG code
[Top](#notes "Top")<br>
The concept for this code is very simple. After setup we periodically check to see if the DF2301QG has sent us a message. If so we check to see if it is one of the commands we will respond to (see table above) and if so calculate and return the corresponding new pattern number. If there was no message or if it was not a command we respond to, we return the unchanged current pattern number.

For talking with the DF2301QG in I2C mode, here is the code prior to **setup**<br>
```C
// DFRobot SKU DF2301QG-EN communications
#include "DFRobot_DF2301Q.h"
#include "DF2301QG_cmds.h" // my list of command ID codes

// DF2301QG voice command module definitions
//    no definitions; pins A4 and A5 are automatically chosen for I2C
//I2C communication
DFRobot_DF2301Q_I2C asr;

#define DF2301QG_VOLUME_MIN   1
#define DF2301QG_VOLUME_MAX   15 // I2C indicates 20 might be possible
int8_t gDFvolume = DF2301QG_VOLUME_MAX; // signed so that could always detect "-= 1", even if MIN changes to 0


#define PATTERN_MAX_NUM 5 // 0-5 are patterns
#define SMILE_OFF 0
#define SMILE_ON  1
#define PTRN_SMILE_ON 6
#define PTRN_SMILE_OFF 7
uint8_t gSmileyFaceOn = SMILE_OFF; // non-zero to turn on smiley face

// List of patterns to cycle through.
char * gPatternStrings[8 /*1+PATTERN_MAX_NUM+2*/] = { "0 rainbow", "1 rainbowWithGlitter", "2 confetti", "3 sinelon", "4 juggle", "5 bpm", "6 SMILEY ON", "7 SMILEY OFF" };
uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gPrevPattern = 255; // previous pattern number - will always start with a "change" in pattern
```

Here is the DF2301QG **setup** code<br>
```C
  // Init the DF2301QG voice command module
  while (!(asr.begin())) {
    DEBUG_DO_PRINTLN("Communication with device failed, please check connection");
    delay(3000);
  }


  delay(5000); // let DF2301QG finish reset
  // here if want to reset the DF2301QG voice command module
  // asr.resetModule();

  asr.setMuteMode(0);
  // asr.setVolume(gDFvolume);
  asr.setWakeTime(20);

  // tell that DF2301QG voice command module is ready
  asr.playByCMDID(DF2301QG_Retreat);
```

Here is the DF2301QG **loop** code<br>
```C
#define WAIT_FOR 50 // wait this many milliseconds between checking for voice commands
void loop() {
  static uint32_t prev_millisec = 0;
  static uint32_t now_millisec = 0;
  if ((now_millisec = millis()) >= (prev_millisec + WAIT_FOR)) {
    prev_millisec = now_millisec;
    gCurrentPatternNumber = handle_DF2301QG();
  }
  if (gPrevPattern != gCurrentPatternNumber) {
    gPrevPattern = gCurrentPatternNumber;
    // Call the transfer pattern function, sending pattern to other Arduino
    xfr_pattern(gCurrentPatternNumber);
    // DEBUG_DO_PRINTLN(gPatternStrings[gCurrentPatternNumber]);
  }
} // end loop()
```

And here is the DF2301QG handler **handle_DF2301QG**. We handle three sets of commands. The two "pattern cases" will change the value of the pattern being sent to the VC_DemoReel Arduino Nano. The "non-pattern case" does not change the value of the pattern being sent but does send a command to the DF2301QG device to change the volume. Otherwise we ignore the case 0 and for all remaining values we print the numerical code received but do nothing.
- pattern case: we send a pattern number to companion Arduino Nano
- pattern case: we send a "psuedo-pattern" number to companion Arduino Nano
- non-pattern case - just change the volume

Note that the "psuedo-pattern" is a toggle on the smiley face. We keep track internally on whether smiley face is ON or OFF and each time we see the Display_smiley_face code we toggle it and send the "psuedo-pattern" of the current state of SMILE_OFF or SMILE_ON.
```C
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// handle_DF2301QG() - process DF2301QG voice command module data.
//    returns: pattern number 0 <= num <= PATTERN_MAX_NUM
//
uint8_t handle_DF2301QG() {
  uint8_t pattern = gCurrentPatternNumber; // integer pattern number from 0 thru 5 inclusive
  uint8_t vol_tmp;
  uint8_t CMDID; // command code received from DFRobot DF2301QG

  CMDID = asr.getCMDID(); // Get the ID for spoken command word; 0 means no command

  switch (CMDID) {
    case DF2301QG_Display_number_zero: case DF2301QG_Display_number_one: case DF2301QG_Display_number_two:
    case DF2301QG_Display_number_three: case DF2301QG_Display_number_four: case DF2301QG_Display_number_five:
      // pattern case: we send a pattern number to companion Arduino Nano
      pattern = CMDID - DF2301QG_Display_number_zero;
      DEBUG_DO_PRINT(F("Set pattern ")); DEBUG_DO_PRINTLN(pattern);
      break;
    case DF2301QG_Display_smiley_face:
      // pattern case: we send a "psuedo-pattern" number to companion Arduino Nano
      if (SMILE_OFF != gSmileyFaceOn)  { pattern = PTRN_SMILE_OFF; gSmileyFaceOn = SMILE_OFF; }
      else                             { pattern = PTRN_SMILE_ON;  gSmileyFaceOn = SMILE_ON; }
      DEBUG_DO_PRINT(F("Set pattern ")); DEBUG_DO_PRINTLN(pattern);
      break;
    case DF2301QG_Volume_up: case DF2301QG_Volume_down: case DF2301QG_Change_volume_to_maximum:
    case DF2301QG_Change_volume_to_minimum: case DF2301QG_Change_volume_to_medium:
      // non-pattern case - just change the volume
      if (DF2301QG_Volume_up == CMDID) gDFvolume += 1;
      else if (DF2301QG_Volume_down == CMDID) gDFvolume -= 1;
      else if (DF2301QG_Change_volume_to_maximum == CMDID) gDFvolume = DF2301QG_VOLUME_MAX;
      else if (DF2301QG_Change_volume_to_minimum == CMDID) gDFvolume = DF2301QG_VOLUME_MIN;
      else if (DF2301QG_Change_volume_to_medium == CMDID) gDFvolume = (DF2301QG_VOLUME_MAX + DF2301QG_VOLUME_MIN) / 2;
      // now check that we are still in range
      if (gDFvolume > DF2301QG_VOLUME_MAX) gDFvolume = DF2301QG_VOLUME_MAX;
      if (gDFvolume < DF2301QG_VOLUME_MIN) gDFvolume = DF2301QG_VOLUME_MIN;
      asr.setVolume(gDFvolume);
      DEBUG_DO_PRINT(F("Set volume ")); DEBUG_DO_PRINTLN(gDFvolume);
      break;
    case 0:
      // just ignore it
      break;
    default:
      // command ID we do not handle; just print it
      DEBUG_DO_PRINT(F("DF2301QG cmd ID ")); DEBUG_DO_PRINTLN(CMDID);
      break;
  } // end switch (CMDID)

  return(pattern);
} // end handle_DF2301QG()
```

### Parallel Arduino-to-Arduino Interface
[Top](#notes "Top")<br>
The concept for this interface is to make it very simple and avoid placing a computational or timing burden on the left Arduino Nano running VC_DemoReel.ino. The use of a "valid" signal and some timing in the VoiceCommands_I2C.ino achieves this.

Both VC_DemoReel.ino and VoiceCommands_I2C.ino use the same pins.<br>
```C
#define XFR_PIN_WHITE_VALID 2 // set to HIGH for others valid
#define XFR_PIN_ORANGE_1    3 // power 2^0 - part of 3-bit pattern number
#define XFR_PIN_YELLOW_2    4 // power 2^1 - part of 3-bit pattern number
#define XFR_PIN_BLUE_4      5 // power 2^2 - part of 3-bit pattern number
```

VoiceCommands_I2C.ino uses the pins in output mode. It sets the interface "invalid" as soon as possible in **setup**<br>
```C
  pinMode(XFR_PIN_WHITE_VALID, OUTPUT);
  digitalWrite(XFR_PIN_WHITE_VALID, LOW);   // set valid off
  pinMode(XFR_PIN_ORANGE_1, OUTPUT);
  pinMode(XFR_PIN_YELLOW_2, OUTPUT);
  pinMode(XFR_PIN_BLUE_4, OUTPUT);
```

VC_DemoReel.ino sets the pins in input mode in **setup**<br>
```C
  pinMode(XFR_PIN_WHITE_VALID, INPUT);
  pinMode(XFR_PIN_ORANGE_1,    INPUT);
  pinMode(XFR_PIN_YELLOW_2,    INPUT);
  pinMode(XFR_PIN_BLUE_4,      INPUT);
```

VC_DemoReel.ino does a fair bit of fancy footwork to handle the smiley face psuedo-pattern, and this gets mixed into the transfer code. First some definitions<br>
```C
#ifdef SMILEY_COLOR_ALL_ONE
static const CRGB all_one_loop_array[] = {CRGB::Red, CRGB::White, CRGB::Blue, CRGB::Green };
#endif // SMILEY_COLOR_ALL_ONE
#ifdef SMILEY_COLOR_RAINBOW
static CRGB rainbow_array[FASTLED_RAINBOWPTRNLEN]; // rainbow pattern colors
#endif // SMILEY_COLOR_RAINBOW
static uint8_t gHue = 0; // rotating "base color"
static uint16_t gHue_rotate_countdown = FASTLED_RAINBOWHUEROTATE;
static uint16_t next_rainbow = 0;

// with three bits for pattern numbers, we can only go from 0 through 7 inclusive
#define PATTERN_MAX_NUM 5 // 0-5 are patterns
#define PATTERN_SMILEY_ONLY 98 // pattern if just toggled smiley on
#define PSUEDO_PATTERN_SMILEY_ON  (PATTERN_MAX_NUM+1)   // 6 to turn smiley face on
#define PSUEDO_PATTERN_SMILEY_OFF (PSUEDO_PATTERN_SMILEY_ON+1) // 7 to turn smiley face on
```

VoiceCommands_I2C.ino in **loop** checks every time to see if the pattern has changed (it is preset to be changed on startup) and if so, calls the routine to transfer the pattern number.<br>
```C
  if (gPrevPattern != gCurrentPatternNumber) {
    gPrevPattern = gCurrentPatternNumber;
    // Call the transfer pattern function, sending pattern to other Arduino
    xfr_pattern(gCurrentPatternNumber);
    // DEBUG_DO_PRINTLN(gPatternStrings[gCurrentPatternNumber]);
  }
```

VC_DemoReel.ino in **loop** periodically looks to see if there is a pattern to receive. Normally there is a valid pattern and it is only occasionally a different pattern than the previous pattern. VC_DemoReel.ino borrows the EVERY_N_MILLISECONDS macro since it includes the FastLED library.
```C
  EVERY_N_MILLISECONDS( 200 ) {
    gCurrentPatternNumber = rcv_pattern();
  }
```

#### Parallel Interface Interesting Part
[Top](#notes "Top")<br>
Now we get to the interesting part - how do the two Arduino Nanos actually communicate?

VoiceCommands_I2C.ino routine **xfr_pattern()** will put the pattern number (0 through 5) on the interface. As we saw above, this routine is only called when the pattern changes.<br>
As we have seen before, we use masking to obtain the binary bits of the pattern number and put them on appropriate pins representing those binary bits. This bit pattern will persist in a valid state until there is a new pattern number.<br>
Pay special attention to the two delay(1) lines.<br>
VoiceCommands_I2C.ino<br>
```C
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// xfr_pattern(pat_num) - transfer pattern number to other Arduino
//    returns: none
//
void xfr_pattern(uint8_t pat_num) {
  digitalWrite(XFR_PIN_WHITE_VALID, LOW);   // set valid off
  delay(1); // make sure no timing issue with other Arduino

  if (0 == (pat_num & 0x01)) digitalWrite(XFR_PIN_ORANGE_1, LOW);
  else                       digitalWrite(XFR_PIN_ORANGE_1, HIGH);

  if (0 == (pat_num & 0x02)) digitalWrite(XFR_PIN_YELLOW_2, LOW);
  else                       digitalWrite(XFR_PIN_YELLOW_2, HIGH);

  if (0 == (pat_num & 0x04)) digitalWrite(XFR_PIN_BLUE_4, LOW);
  else                       digitalWrite(XFR_PIN_BLUE_4, HIGH);

  delay(1); // probably doesn't need delay here, but belt and suspenders
  digitalWrite(XFR_PIN_WHITE_VALID, HIGH);   // set valid ON
} // end xfr_pattern()
```

VC_DemoReel.ino periodically monitors the valid line to see if there is a valid pattern number being sent. Normally there is an unchanging valid pattern number being sent, only occasionally does it change.<br>
Because of the delay statements above near the changes of value of the valid state, we know that we have at least a millisecond to read a valid number if we detect the valid pin HIGH, so we proceed as fast as possible.<br>
For each of the bits in the binary number we add in its numerical value only if the pin is HIGH.

This gets mixed up with the smiley face code since it reacts differently if we are commanding the smiley psuedo-pattern ON from being OFF (need CRGB:Black background pattern) or doing other pattern commands. Also when we command the  smiley psuedo-pattern OFF from being ON we try to return to the last commanded true pattern<br>
VC_DemoReel.ino<br>
```C
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// rcv_pattern() - receive pattern number from other Arduino
//    returns: uint8_t pattern number 0 <= num <= PATTERN_MAX_NUM
//
// PSUEDO_PATTERN_SMILEY_ON or PSUEDO_PATTERN_SMILEY_OFF will affect the smiley face
//   but will not change the pattern number EXCEPT for the first time it toggles on
//   and (possibly) the first time it toggles off.
//
uint8_t rcv_pattern() {
  uint8_t the_pattern = gCurrentPatternNumber; // if new pattern not valid, we return this
  uint8_t the_pattern_before_smiley = 0;
  if (HIGH == digitalRead(XFR_PIN_WHITE_VALID)) { // we have at least 1 millisec to do read
    the_pattern = 0;
    if (HIGH == digitalRead(XFR_PIN_ORANGE_1)) the_pattern += 1;
    if (HIGH == digitalRead(XFR_PIN_YELLOW_2)) the_pattern += 2;
    if (HIGH == digitalRead(XFR_PIN_BLUE_4)) the_pattern += 4;
    // handle smiley
    if (PSUEDO_PATTERN_SMILEY_ON == the_pattern) {
      if (0 == gSmileyFaceOn) {
        the_pattern = PATTERN_SMILEY_ONLY; // first time we toggle on
      } else { // this really should not happen
        the_pattern = gCurrentPatternNumber;
      }
      gSmileyFaceOn = 1;
    } else if (PSUEDO_PATTERN_SMILEY_OFF == the_pattern) {
      the_pattern = gLatestTruePatternNumber; // return to last true pattern
      gSmileyFaceOn = 0;
    } else { // it is a true pattern not a psuedo-pattern
      gLatestTruePatternNumber = the_pattern;
    }
  } // end if valid pattern number to read
  return(the_pattern);
} // end rcv_pattern()
```
### VC_DemoReel Sound Code
Even the sound code gets involved with smiley face, since the psuedo-pattern doesn't have a sound file (just shows how lazy I am).

VC_DemoReel.ino previous code
```C
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// DFcheckSoundDone()
//
// notBusy means (HIGH == digitalRead(DPIN_AUDIO_BUSY)) && (millis() >= state_timerForceSoundActv)
//    DPIN_AUDIO_BUSY goes HIGH when sound finished, but may take a while to start
//    state_timerForceSoundActv is millisec count we have to wait for to before checking DPIN_AUDIO_BUSY
//
void DFcheckSoundDone() {
  uint8_t myBusy = (HIGH != digitalRead(DPIN_AUDIO_BUSY)) || (millis() < state_timerForceSoundActv);
  uint8_t playNumber = 99; // this means don't change

  if (0 != state_introSoundPlaying) { // intro still playing
    if (0 == myBusy) { // can play a non-intro sound
      if (0 != gPatternNumberChanged) { // start pattern sound
        playNumber = gCurrentPatternNumber+1; // sound numbers start at 1
      } else { // start Cassini sound
        playNumber = SOUNDNUM_CASSINI; // this should never execute, we start with gPatternNumberChanged=1
      } // end start a sound
    } // end if can play a non-intro sound
  } else { // intro done
    if (0 != gPatternNumberChanged) { // always start new pattern number sound
      playNumber = gCurrentPatternNumber+1; // sound numbers start at 1
    } else if (0 == myBusy) { // sound finished and no new pattern, start Cassini
      playNumber = SOUNDNUM_CASSINI;
    }
  } // end if intro done

  if (99 != playNumber) { // there is a new sound to play
    gPatternNumberChanged = 0;
    state_introSoundPlaying = 0;
    if (SOUNDNUM_CASSINI == playNumber) {
      DFstartSound(SOUNDNUM_CASSINI, SOUND_BKGRND_VOL);
    } else {
      DFstartSound(gCurrentPatternNumber+1, SOUND_DEFAULT_VOL);
    }
  } // end if there is a new sound to play
} // end DFcheckSoundDone()
```

VC_DemoReel.ino smiley face code
```C
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// DFcheckSoundDone()
//
// notBusy means (HIGH == digitalRead(DPIN_AUDIO_BUSY)) && (millis() >= state_timerForceSoundActv)
//    DPIN_AUDIO_BUSY goes HIGH when sound finished, but may take a while to start
//    state_timerForceSoundActv is millisec count we have to wait for to before checking DPIN_AUDIO_BUSY
//
void DFcheckSoundDone() {
  uint8_t myBusy = (HIGH != digitalRead(DPIN_AUDIO_BUSY)) || (millis() < state_timerForceSoundActv);
  uint8_t playNumber = 99; // this means don't change

  if (0 != state_introSoundPlaying) { // intro still playing
    if (0 == myBusy) { // can play a non-intro sound
      if (0 != gPatternNumberChanged) { // start pattern sound
        if (PATTERN_SMILEY_ONLY == gCurrentPatternNumber) {
          playNumber = SOUNDNUM_CASSINI; // we don't have a sound for smiley face
        } else {
          playNumber = gCurrentPatternNumber+1; // sound numbers start at 1
        }
      } else { // start Cassini sound
        playNumber = SOUNDNUM_CASSINI; // this should never execute, we start with gPatternNumberChanged=1
      } // end start a sound
    } // end if can play a non-intro sound
  } else { // intro done
    if (0 != gPatternNumberChanged) { // always start new pattern number sound
      if (PATTERN_SMILEY_ONLY == gCurrentPatternNumber) {
        playNumber = SOUNDNUM_CASSINI; // we don't have a sound for smiley face
      } else {
        playNumber = gCurrentPatternNumber+1; // sound numbers start at 1
      }
    } else if (0 == myBusy) { // sound finished and no new pattern, start Cassini
      playNumber = SOUNDNUM_CASSINI;
    }
  } // end if intro done

  if ((99 != playNumber) && (PATTERN_SMILEY_ONLY != gCurrentPatternNumber)) { // there is a new sound to play
    gPatternNumberChanged = 0;
    state_introSoundPlaying = 0;
    if (SOUNDNUM_CASSINI == playNumber) {
      DFstartSound(SOUNDNUM_CASSINI, SOUND_BKGRND_VOL);
    } else {
      DFstartSound(gCurrentPatternNumber+1, SOUND_DEFAULT_VOL);
    }
  } // end if there is a new sound to play
} // end DFcheckSoundDone()
```

Odds and Ends - we also want to have a background of LEDs all OFF (CRGB::Black) when the smiley face appears until a pattern is commanded.<br>
VC_DemoReel.ino smiley face background.<br>
```C
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// do_smiley_background() - background all-black if just toggled to smiley face
//
void do_smiley_background() {
  for (uint16_t i=0; i < NUM_LEDS; i++) leds[i] = CRGB::Black;
} // do_smiley_background
```
