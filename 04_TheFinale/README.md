# The Finale - Theremin with Sound

**Table of Contents**
- [Top](#notes "Top")
- [The Idea](#the-idea "The Idea")
- [The Circuit](#the-circuit "The Circuit")
  - [YX5200 Sound Module](#the-circuit "YX5200 Sound Module")
  - [KCX_BT_EMITTER Bluetooth Sound Transmitter](#kcx_bt_emitter-bluetooth-sound-transmitter "KCX_BT_EMITTER Bluetooth Sound Transmitter")
- [The Code](#the-code "The Code")

## The Idea
Our Theremin, especially with the large LED disks, is pretty impressive. It can be a little dicey to hold your hand in the right place to see the pattern play out, but the USB Monitor will tell which pattern it is showing.

In this project we will add a circuit to send sound to a Bluetooth speaker to tell us which pattern we are on. When the system powers on it will announce the project, state the pattern being displayed, and then provide background sound collected from Saturn's electromagnetic field by the Cassini mission. If the HC-SR04 detects that a different pattern has been selected, the sound will state the new pattern and then return to the Cassini sound.

## The Circuit

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

### KCX_BT_EMITTER Bluetooth Sound Transmitter

## The Code
