# NOTES

**Table of Contents**
* [Top](#notes "Top")
* [Human Vision Persistence](#human-vision-persistence "Human Vision Persistence")
* [The Circuit and the Code](#the-circuit-and-the-code "The Circuit and the Code")
* [Resources](#resources "Resources")

## Human Vision Persistence
Louis Le Prince is the first person to record and show moving pictures.
- https://en.wikipedia.org/wiki/Louis_Le_Prince

The effect is known as the persistence of vision: the human eye continues to "see" light for a short time after the light stops. You can try this by simply closing your eyes. Over time it was discovered that a playback speed of 24 frames per second was fast enough to make the pictures "move".

In this exercise we will build on the blinking LED exercise to create a simple persistence of vision wand consisting of 8 individually addressable color LEDs using the WS2811 serial protocol.

Much more elaborate versions of this wand (and some beautiful pictures and movies) can be found in these links:
- https://www.instructables.com/Persistence-of-Vision-LED-Staff/
- https://povstaff.readthedocs.io/en/latest/
- https://learn.adafruit.com/pov-dotstar-double-staff

## The Circuit and the Code

- Four LEDs are outputs
  - Polarity of LEDs
  - Current limiting resistor
- Counter to sequence light patterns
  - Sawtooth
  - Oval

## Resources

- Wikipedia - Thomas Edison and Movies
- KiCad
