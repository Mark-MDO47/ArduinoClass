EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A 11000 8500
encoding utf-8
Sheet 1 1
Title "01 Blinking LED part B"
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
P 3600 3650
F 0 "R?" H 3668 3696 50  0000 L CNN
F 1 "220 to 300 Ohm" H 3668 3605 50  0000 L CNN
F 2 "" H 3600 3650 50  0001 C CNN
F 3 "~" H 3600 3650 50  0001 C CNN
	1    3600 3650
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
P 4050 3200
F 0 "D?" H 4043 3416 50  0000 C CNN
F 1 "LED_ALT" H 4043 3325 50  0000 C CNN
F 2 "" H 4050 3200 50  0001 C CNN
F 3 "~" H 4050 3200 50  0001 C CNN
	1    4050 3200
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4750 4100 3600 4100
Wire Wire Line
	3600 4100 3600 3750
Wire Wire Line
	4550 3900 4750 3900
$Comp
L Switch:SW_Push SW?
U 1 1 64388E02
P 4050 2650
F 0 "SW?" H 4050 2935 50  0000 C CNN
F 1 "SW_Push" H 4050 2844 50  0000 C CNN
F 2 "" H 4050 2850 50  0001 C CNN
F 3 "~" H 4050 2850 50  0001 C CNN
	1    4050 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 3550 3600 3200
Wire Wire Line
	3600 3200 3900 3200
Wire Wire Line
	4200 3200 4550 3200
Wire Wire Line
	4550 3200 4550 3900
Wire Wire Line
	4750 4300 3350 4300
Wire Wire Line
	3350 4300 3350 2650
Wire Wire Line
	3350 2650 3850 2650
Wire Wire Line
	4250 2650 4550 2650
Wire Wire Line
	4550 2650 4550 3200
Connection ~ 4550 3200
$EndSCHEMATC
