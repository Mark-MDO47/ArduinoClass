# Notes

**Table of Contents**
* [Top](#notes "Top")
* [The Idea](#the-idea "The Idea")
* [The Circuit](#the-circuit "The Circuit")
  * [YX5200 Sound Module](#yx5200-sound-module "YX5200 Sound Module")
  * [KCX_BT_EMITTER Bluetooth Sound Transmitter](#kcx_bt_emitter-bluetooth-sound-transmitter "KCX_BT_EMITTER Bluetooth Sound Transmitter")
* [The Code](#the-code "The Code")
  * [Code Outline](#code-outline "Code Outline")
  * [Hysteresis](#hysteresis "Hysteresis")
  * [Code Details](#code-details "Code Details")

## The Idea
[Top](#notes "Top")<br>
Our Theremin, especially with the large LED disks, is pretty impressive. It can be a little dicey to hold your hand in the right place to see the pattern play out, but the USB Monitor will tell which pattern it is showing.

In this project we will add a circuit to send sound to a Bluetooth speaker to tell us which pattern we are on. When the system powers on it will announce the project, state the pattern being displayed, and then provide background sound collected from Saturn's electromagnetic field by the Cassini mission. If the HC-SR04 detects that a different pattern has been selected, the sound will state the new pattern and then return to the Cassini sound.

<img src="https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/04_TheFinale_DemoReelSound_setup.jpg" width="750" alt="Image of Theremin with Speech Sound">

Here is a video of this circuit in operation:
- https://youtu.be/G7ARC0xHXRg

## The Circuit
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

### YX5200 Sound Module
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
- The way the files are stored on the SD card must be exactly right. If there was ever any file or directory placed on the SD card, it must first be FAT-formatted again before storing or changing files on the card. My YX5200 GitHub page (see above) on this module includes a Python program copyem.py that helps with this.
- There is a 1 KOhm resistor between the Arduino and the YX5200 RX pin. This is not optional. If this is left out then the commands sent on this line will be heard in the sound from the speaker.
- When using the line-level outputs to the Bluetooth module, the correct ground must be used. There are two ground pins on the YX5200 and the documentation does not distinguish between them, but one works far better as audio-ground or analog-ground than the other. Again, you can refer to my YX5200 GitHub page (see above).
- The card can play MP3 files but there is a delay to start playing. It is much faster starting with WAV files.
- There are many clones of this chip and it is hard to know when you order one which one you will get. Some of the more elaborate features don't work on some of the clones.
- The BUSY line will not change to busy status immediately; it takes some milliseconds. My measurements are that it might take as few as 40 milliseconds, but that may depend on which YX5200 clone you are using. After starting a sound, I make the software pretend that the BUSY line is in busy status for 250 milliseconds before actually using the state of the line.

### KCX_BT_EMITTER Bluetooth Sound Transmitter
[Top](#notes "Top")<br>
The KCX_BT_EMITTER Bluetooth Sound Transmitter module takes its line-level inputs and sends them to a Bluetooth receiver.The KCX_BT_EMITTER Version 1.1 (and 1.2) used here conforms to an earlier version of Bluetooth than the latest Bluetooth 5.3. Depending on what documentation you read, it uses either version 4.1 or 4.2. This works well with my Bluetooth speaker but has not worked with any Bluetooth earphones I have tried. This version of the KCX_BT_EMITTER is the one I am familiar with. I have heard rumors of an updated Version 1.7 supporting stereo and/or Bluetooth 5.x but have no experience with these, although I have ordered some and will be experimenting with them.

I have a separate GitHub project describing how to use this module:
- https://github.com/Mark-MDO47/BluetoothAudioTransmitter_KCX_BT_EMITTER

Some of the things to keep in mind:
- When it is freshly initialized, it will try to connect to the first Bluetooth audio receiver (speaker or earbuds or headphones) it finds. It can be paired with a specific device so it doesn't connect to some random speaker; to do that I use the "Programming Arduino" which allows me to see what Bluetooth devices it sees and to select among them for ones it will be allowed to connect with. The "Programming Arduino" can also remove devices from the allowed list.
- Once the KCX_BT_EMITTER has been programmed to allow pairing with one or more devices, it will not connect to a random device but will wait to connect to one of the devices on its list.
- It does take a few seconds to pair up with a device.
- Unlike the YX5200, the KCX_BT_EMITTER has a power-ground (or digital-ground) and an audio-ground (or analog-ground) clearly distinguished in its documentation.

## The Code
[Top](#notes "Top")<br>
We start from the final Theremin code from section 3 https://github.com/Mark-MDO47/ArduinoClass/tree/master/03_SonarRangeDetector and name it ThereminSound.ino

As mentioned above, I have directly copied the dfrobot.com DFPlayer library into the code area in the Arduino code section of this class GitHub page but alternatively the library is available in the library manager. I tend to keep my own copy of the library since I initially had to do significant debugging to learn how to communicate not just with the dfrobot.com version of the part but also with several of the different clones. It was convenient to be able to put debugging statements directly in the library to do that debugging, and I have continued the practice of having the library available for me to modify as desired. Note that there are also several alternative libraries for communicating with YX5200 parts.
- https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/ThereminSound

### Code Outline
[Top](#notes "Top")<br>
Below is an outline of the changes we will make

Curiously, before **setup()** we will:
- Create the global object mySoftwareSerial to talk on our KCX_BT_EMITTER RX and TX pins.
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

### Hysteresis
One aspect of the Sonar Range Finder is that it is easy to get your hand near the region separating two distinct patterns and have it waver back and forth between the two patterns.

One approach to making this easier would be to add "hysteresis" in the changing between patterns. The general definition of this is "the value of a physical property lags behind changes in the effect causing it" but I am using it as it is seen in electronics, in which once a decision is made the threshold is moved such that going back to the previous decision is harder.
- An example might be a 12 volt relay coil. If the voltage is raised slowly the relay may turn on at perhaps 11 volts, but it will remain turned on as you drop the voltage below 11 volts to perhaps 9 volts before it turns off.
- Another way of thinking about the example above is that the output of the relay depends on both the voltage and the history. If the voltage is 10 volts and the history is that it was previously on, the output is that the relay is on. If the voltage is 10 volts and the history is that it was previously off, the output is that the relay is off. The history could also be stated in terms of the voltage history instead of the relay output history, but it would be a more complicated statement.
- I experimented with simulating a similar effect in software using the HC-SR04 in my "Park the Car" project (https://github.com/Mark-MDO47/KnowHow_ParkTheCar) but was never happy with the result.

For this project I took a different approach. Each sound file that states the name of a pattern starts with a short silent period, giving the hand a chance to find a region where the new pattern is stable without having the speaker go back and forth rapidly speaking different patterns.

### Code Details
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
