# Notes

**Table of Contents**
- [Top](#notes "Top")
- [The Idea](#the-idea "The Idea")
- [The Circuit](#the-circuit "The Circuit")
  - [YX5200 Sound Module](#yx5200-sound-module "YX5200 Sound Module")
  - [KCX_BT_EMITTER Bluetooth Sound Transmitter](#kcx_bt_emitter-bluetooth-sound-transmitter "KCX_BT_EMITTER Bluetooth Sound Transmitter")
- [The Code](#the-code "The Code")
  - [Code Outline](#code-outline "Code Outline")
  - [Code Details](#code-details "Code Details")

## The Idea
[Top](#notes "Top")<br>
Our Theremin, especially with the large LED disks, is pretty impressive. It can be a little dicey to hold your hand in the right place to see the pattern play out, but the USB Monitor will tell which pattern it is showing.

In this project we will add a circuit to send sound to a Bluetooth speaker to tell us which pattern we are on. When the system powers on it will announce the project, state the pattern being displayed, and then provide background sound collected from Saturn's electromagnetic field by the Cassini mission. If the HC-SR04 detects that a different pattern has been selected, the sound will state the new pattern and then return to the Cassini sound.

## The Circuit
[Top](#notes "Top")<br>
The plan is that the circuit to implement the sound to the bluetooth will be on a different breadboard than the one containing the Theremin circuit. There will only be one of these so I will bring it around to the different stations so everyone can try it. In order to use it we will need the setup for the large LED disks including its separate power supply, so I will bring that around too.

The wiring schematic can be found here; an image is given below.
- https://github.com/Mark-MDO47/ArduinoClass/blob/master/04_TheFinale/04_TheFinale_ThereminSound.pdf

![alt text](https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/04_TheFinale_DemoReelSound.png "Circuit for 04 The Finale - Theremin with Sound")

In the image above, everything below the red line is on the new breadboard that I will bring along. The schematic includes the "Programming Arduino" page but we will not be using that in the class as I will already have paired the bluetooth speaker with our circuit.

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
- The way the files are stored on the SD card must be exactly right. If there was ever any file or directory placed on the SD card, it must first be FAT-formatted again before storing or changing files on the card. My GitHub page on this module includes a Python program copyem.py that helps with this.
- There is a 1 KOhm resistor between the Arduino and the YX5200 RX pin. This is not optional. If this is left out then the commands sent on this line will be heard in the sound from the speaker.
- When using the line-level outputs to the Bluetooth module, the correct ground must be used. There are two ground pins on the YX5200 and the documentation does not distinguish between them, but one works far better as audio-ground or analog-ground than the other.
- The card can play MP3 files but there is a delay to start playing. It is much faster starting with WAV files.
- There are many clones of this chip and it is hard to know when you order one which one you will get. Some of the more elaborate features don't work on some of the clones.
- The BUSY line will not change to busy status immediately; it takes some milliseconds. My measurements are that it might take as few as 40 milliseconds, but that may depend on which YX5200 clone you are using. After starting a sound, I make the software pretend that the BUSY line is in busy status for 250 milliseconds before actually using the state of the line.

### KCX_BT_EMITTER Bluetooth Sound Transmitter
[Top](#notes "Top")<br>
The KCX_BT_EMITTER Bluetooth Sound Transmitter module takes its line-level inputs and sends them to a Bluetooth receiver. It uses an earlier version of Bluetooth than the latest 5.3. Depending on what documentation you read, it uses either version 4.1 or 4.2. This works well with my Bluetooth speaker but has not worked with any earphones I have tried.

I have a separate GitHub project describing how to use this module:
- https://github.com/Mark-MDO47/BluetoothAudioTransmitter_KCX_BT_EMITTER

Some of the things to keep in mind:
- When it is freshly initialized, it will try to connect to the first Bluetooth audio receiver (speaker or earbuds or headphones) it finds. It can be paired with a specific device so it doesn't connect to some random speaker; to do that I use the "Programming Arduino" which allows me to see what Bluetooth devices it sees and to choose among them. It also allows removing devices from the list.
- Once the KCX_BT_EMITTER has been paired with one or more devices, it will not connect to a random device but will wait to connect to one of the devices on its list.
- It does take a few seconds to pair up with a device.
- Unlike the YX5200, the KCX_BT_EMITTER has a power-ground (or digital-ground) and an audio-ground (or analog-ground) clearly distinguished in its documentation.

## The Code
[Top](#notes "Top")<br>
We start from the final Theremin code from section 3 https://github.com/Mark-MDO47/ArduinoClass/tree/master/03_SonarRangeDetector and name it ThereminSound.ino

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
  - start playing the intro sound

In **loop()** we will:
- Set gPatternNumberChanged non-zero whenever the pattern number changes
- Call our **DFcheckSoundDone()** routine to
  - if the pattern changed, interrupt the current sound and announce the new pattern
  - otherwise:
    - handle the delay in believing the BUSY signal from YX5200 (see above in discussion on YX5200)
    - if BUSY signal says sound completed, play the Cassini sound

### Code Details
[Top](#notes "Top")<br>

After **#include <FastLED.h>** and **#include <Ultrasonic.h>** add
```C
#include "Arduino.h"
#include "SoftwareSerial.h"                  // to talk to myDFPlayer without using up debug serial port
#include "DFRobotDFPlayerMini.h"             // to communicate with the YX5200 audio player

#define DPIN_SWSRL_TX    8  // serial out - talk to DFPlayer audio player (YX5200)
#define DPIN_SWSRL_RX    9  // serial in  - talk to DFPlayer audio player (YX5200)
#define DPIN_AUDIO_BUSY 10  // digital input - signals when audio finishes

SoftwareSerial mySoftwareSerial(DPIN_SWSRL_RX, DPIN_SWSRL_TX); // to talk to YX5200 audio player
DFRobotDFPlayerMini myDFPlayer;                                // to talk to YX5200 audio player
void DFsetup();                                                // how to initialize myDFPlayer

#define SOUNDNUM_INTRO   7 // our introduction
#define SOUNDNUM_CASSINI 8 // Cassini Saturn sound - SPACE!!!
#define SOUND_DEFAULT_VOL     25  // default volume - 25 is pretty good
#define SOUND_BKGRND_VOL      20  // background volume
#define SOUND_ACTIVE_PROTECT 250  // milliseconds to keep SW twiddled sound active after doing myDFPlayer.play(mySound)
 uint32_t state_timerForceSoundActv = 0;  // end timer for enforcing SOUND_ACTIVE_PROTECT
```

To get the timing delay for BUSY and get intro to play and then pattern to be announced once and then Cassini to play until a new pattern, we use the following state table.<br>
NOTE: the myBusy column is "not busy" if LOW==DPIN_AUDIO_BUSY **and** the forceBusy timer has expired; otherwise it is "BUSY".<br>
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
