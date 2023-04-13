EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A 11000 8500
encoding utf-8
Sheet 1 1
Title "01 Blinking LED part A"
Date "2023-04-13"
Rev ""
Comp "Author: https://github.com/Mark-MDO47/ArduinoClass/tree/master"
Comment1 "NOTE: Chips & Modules shown top view, notch at top"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:R_Small_US R?
U 1 1 64387B62
P 3600 2850
F 0 "R?" H 3668 2896 50  0000 L CNN
F 1 "220 to 300 Ohm" H 3668 2805 50  0000 L CNN
F 2 "" H 3600 2850 50  0001 C CNN
F 3 "~" H 3600 2850 50  0001 C CNN
	1    3600 2850
	1    0    0    -1  
$EndComp
$Comp
L mdoLibrary:Arduino_USB A?
U 1 1 6438ED98
P 5350 4300
F 0 "A?" H 5350 5287 60  0000 C CNN
F 1 "Arduino_USB" H 5350 5181 60  0000 C CNN
F 2 "" H 5350 4300 60  0000 C CNN
F 3 "" H 5350 4300 60  0000 C CNN
	1    5350 4300
	1    0    0    -1  
$EndComp
$Comp
L Device:LED_ALT D?
U 1 1 6438566F
P 4050 2050
F 0 "D?" H 4043 2266 50  0000 C CNN
F 1 "LED_ALT" H 4043 2175 50  0000 C CNN
F 2 "" H 4050 2050 50  0001 C CNN
F 3 "~" H 4050 2050 50  0001 C CNN
	1    4050 2050
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4750 4100 3600 4100
Wire Wire Line
	3600 4100 3600 2950
Wire Wire Line
	3600 2750 3600 2050
Wire Wire Line
	4050 2050 4200 2050
Wire Wire Line
	4550 2050 4550 3900
Wire Wire Line
	4550 3900 4750 3900
Wire Wire Line
	3600 2050 3900 2050
Wire Wire Line
	4200 2050 4550 2050
Connection ~ 4200 2050
$EndSCHEMATC
