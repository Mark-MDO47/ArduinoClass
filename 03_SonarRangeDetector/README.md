# NOTES

## Speed of Sound

## HC-SR04 Ultrasonic Sensor
I will be providing the parts to be used in this class for four workstations.

The HC-SR04 can be found here (for example) for less than $2:
- https://protosupplies.com/product/hc-sr04-ultrasonic-range-finder-module/
- https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf
- https://www.tutorialspoint.com/arduino/arduino_ultrasonic_sensor.htm

This is typically used to determine ranges of objects from 2cm - 400cm non-contact.

Below is a picture of this detector from the protosupplies.com website:

<img src="https://protosupplies.com/wp-content/uploads/2019/08/HC-SR04-Ultrasonic-Range-Finder.jpg" width="640" height="480">

This description also comes from the protosupplies.com website:
```
The way the HC-SR04 Ultrasonic Range Finder Module works is as follows:

1. The module is normally idle.
2. A 10 uSec or wider pulse is sent to the TRIG pin on the module, usually by a microcontroller.
   This will cause the module to start a detection cycle.
3. The module emits eight bursts of 40KHz sound and sets it’s ECHO pin output HIGH.
4. When the signal is reflected back from an object and is detected by the module, the ECHO pin is set back to LOW.
5.By measuring the amount of time that the ECHO pin is held HIGH, the distance to the object can be calculated
  using the basic formula  (Time that ECHO is held HIGH * Speed of sound / 2)
  The divide by 2 is because the sound has to travel in both directions (both out and back)
  and we want to know just the out distance.

If an echo is not returned (no object detected), the module will still lower the ECHO pin after a fixed delay.
This delay may vary, but is about 200mSec on the modules that I have measured.
This is required to prevent the module from hanging if there is no return echo.
```

From https://www.nde-ed.org/Physics/Sound/tempandspeed.xhtml 
```
Molecules at higher temperatures have more energy, thus they can vibrate faster. 
Since the molecules vibrate faster, sound waves can travel more quickly.
```

Data from https://www.nde-ed.org/Physics/Sound/tempandspeed.xhtml

| Temp degC | Temp DegF | Speed Meter/Sec | Speed Inch/Sec | Speed Ft/Sec |
| --- | --- | --- | --- | --- |
| 45 | 113 | 358.0 | 14,095 | 1,175 |
| 21 | 69.8 | 343.6 | 13,528 | 1,127 |
| -1 | 30.2 | 330.4 | 13,008 | 1,084 |

### Pros and Cons of HC-SR04

Many people have noted pros and cons of the HC-SR04, such as
- https://github.com/shurik179/DualSonar

```
HC-SR04 are cheap and reliable ultrasonic sensors, used in many robotics projects
with Arduino or similar microcontrollers. However, they have two drawbacks:

1. The standard method of reading the sensor in Arduino, using PulseIn() function,
   ties up the microcontroller for up to 30ms and interferes with tasks which need
   to be run frequently such as WiFi communication using Blynk or reading input
   from other sensors over serial interface.
2. Each sensor requires 2 pins, so if you have several ultrasonic senors, you run out of pins quickly.

There are some ways to mitigate these probems, such as using interrupts instead of PulseIn
or using NewPing library which allows one to use only one pin per sensor.
```

Fortunately, the delay from the HC-SR04 gets shorter as the distance of the detected object gets closer. In this project we will use the HC-SR04 for short distances, and the long 200 millisecond timeout if there is no detected object won't bother us too much since we won't have time critical tasks when that happens. Thus we can use the standard PulseIn() function or equivalent.

In fact we will use the Ultrasonic library to work with this sensor:
- https://www.arduinolibraries.info/libraries/ultrasonic

This code does the typical single-threaded wait for the return ECHO as seen in this code snippet:
```C
  previousMicros = micros();
  while(!digitalRead(echo) && (micros() - previousMicros) <= timeout); // wait for the echo pin HIGH or timeout
  previousMicros = micros();
  while(digitalRead(echo)  && (micros() - previousMicros) <= timeout); // wait for the echo pin LOW or timeout
```

This code does have a **setTimeout()** function if we want to prevent extremely long delays. The manual seems to imply that we would not want to sense the HC-SR04 more often than once every 60 milliseconds.

## Theremin controller
We will use the HC-SR04 to detect the position of our hand and use that to control the light displays on our LED strip. This use of hand position is similar to the way the musical intrument Theremin controls the sound by detecting hand position.
- https://en.wikipedia.org/wiki/Theremin

Here is a picture from that Wikipedia article of Alexandra Stepanoff playing the theremin on NBC Radio in 1930.

![alt text](https://upload.wikimedia.org/wikipedia/commons/thumb/1/11/Theramin-Alexandra-Stepanoff-1930.jpg/220px-Theramin-Alexandra-Stepanoff-1930.jpg "from wikimedia.org an image of Alexandra Stepanoff playing the theremin on NBC Radio in 1930")

Essentially, we will start with 02 Part D and replace the USB serial commands with detection of hand position by the HC-SR04.

## Resources


