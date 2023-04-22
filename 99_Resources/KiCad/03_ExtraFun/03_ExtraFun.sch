EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 1 1
Title "03 Sonar Range Detector - Extra Fun"
Date "2023-04-22"
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
P 3950 4600
F 0 "R?" H 4018 4646 50  0000 L CNN
F 1 "220 to 300 Ohm" H 4018 4555 50  0000 L CNN
F 2 "" H 3950 4600 50  0001 C CNN
F 3 "~" H 3950 4600 50  0001 C CNN
	1    3950 4600
	1    0    0    -1  
$EndComp
$Comp
L mdoLibrary:Arduino_USB A?
U 1 1 6438ED98
P 6250 5250
F 0 "A?" H 6250 6237 60  0000 C CNN
F 1 "Arduino_USB" H 6250 6131 60  0000 C CNN
F 2 "" H 6250 5250 60  0000 C CNN
F 3 "" H 6250 5250 60  0000 C CNN
	1    6250 5250
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 64388E02
P 5200 4850
F 0 "SW?" H 5200 5135 50  0000 C CNN
F 1 "SW_Push" H 5200 5044 50  0000 C CNN
F 2 "" H 5200 5050 50  0001 C CNN
F 3 "~" H 5200 5050 50  0001 C CNN
	1    5200 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 5050 4850 5050
Wire Wire Line
	5000 4850 4850 4850
Wire Wire Line
	4850 4850 4850 5050
Wire Wire Line
	5650 4850 5400 4850
Wire Wire Line
	6850 4850 7050 4850
$Comp
L mdoLibrary:HC-SR04 M?
U 1 1 643F7E0B
P 4000 5650
F 0 "M?" H 4158 5765 50  0000 C CNN
F 1 "HC-SR04" H 4158 5674 50  0000 C CNN
F 2 "" H 4150 5650 50  0001 C CNN
F 3 "" H 4150 5650 50  0001 C CNN
	1    4000 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 5950 4400 5950
Wire Wire Line
	4950 5850 4400 5850
Wire Wire Line
	5650 5750 4950 5750
Wire Wire Line
	4950 5750 4950 5850
Wire Wire Line
	5400 4850 5400 5600
Wire Wire Line
	5400 5600 4550 5600
Wire Wire Line
	4550 5600 4550 5750
Wire Wire Line
	4550 5750 4400 5750
Connection ~ 5400 4850
Wire Wire Line
	7050 4850 7050 6550
Wire Wire Line
	7050 6550 4400 6550
Wire Wire Line
	4400 6550 4400 6050
$Comp
L mdoLibrary:UBEC J?
U 1 1 6440393A
P 2850 3550
F 0 "J?" H 2950 4237 60  0000 C CNN
F 1 "UBEC" H 2950 4131 60  0000 C CNN
F 2 "" H 2850 3550 60  0001 C CNN
F 3 "" H 2850 3550 60  0001 C CNN
	1    2850 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 3700 3550 3700
Wire Wire Line
	3350 3300 3550 3300
$Comp
L Device:Battery_Cell BT?
U 1 1 6440ACA4
P 2000 3550
F 0 "BT?" H 2118 3646 50  0000 L CNN
F 1 "Battery_Cell" H 2118 3555 50  0000 L CNN
F 2 "" V 2000 3610 50  0001 C CNN
F 3 "~" V 2000 3610 50  0001 C CNN
	1    2000 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 3700 2000 3700
Wire Wire Line
	2000 3700 2000 3650
Wire Wire Line
	2000 3350 2000 3300
Wire Wire Line
	2000 3300 2350 3300
Text Notes 1900 3200 0    50   ~ 0
9V Battery
$Comp
L mdoLibrary:LEDring_big Z?
U 1 1 64448FEE
P 4700 2100
F 0 "Z?" H 5728 2095 60  0000 L CNN
F 1 "LEDring_big" H 5728 1989 60  0000 L CNN
F 2 "" H 4700 2250 60  0001 C CNN
F 3 "" H 4700 2250 60  0001 C CNN
	1    4700 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 3200 4750 3300
Wire Wire Line
	3550 3300 4750 3300
Connection ~ 3550 3300
Wire Wire Line
	3550 3700 4650 3700
Wire Wire Line
	4650 3700 4650 3200
Connection ~ 3550 3700
Wire Wire Line
	3950 4700 3950 5350
Wire Wire Line
	3950 4100 4850 4100
Wire Wire Line
	3950 4100 3950 4500
Wire Wire Line
	4850 3200 4850 4100
Wire Wire Line
	3950 5350 5650 5350
Wire Wire Line
	7200 4650 7200 6650
Wire Wire Line
	7200 6650 3550 6650
Wire Wire Line
	3550 6650 3550 3700
Wire Wire Line
	6850 4650 7200 4650
$EndSCHEMATC
