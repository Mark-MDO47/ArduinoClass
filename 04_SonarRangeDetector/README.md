# NOTES

## Speed of Sound

## HC-SR04 Ultrasonic Sensor
I will be providing the parts to be used in this class for four workstations.

The HC-SR04 can be found here (for example) for less than $2:
- https://protosupplies.com/product/hc-sr04-ultrasonic-range-finder-module/

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
Since the molecules vibrate faster, sound waves can travel more quickly.
The speed of sound in room temperature air is 346 meters per second.
This is faster than 331 meters per second, which is the speed of sound in air at freezing temperatures.
```

Data from https://www.nde-ed.org/Physics/Sound/tempandspeed.xhtml

| Temp degC | Temp DegF | Speed Meter/Sec | Speed Inch/Sec |
| --- | --- | --- | --- | --- |
| 45 | xx | 358.0 | yy |


## Theremin controller

## Resources

- Wikipedia - Speed of Sound
- Wikipedia - Theremin
- HC-SR04 - specifications
