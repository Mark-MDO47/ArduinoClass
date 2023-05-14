EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 1 1
Title "02 Persistence of Vision - Stick"
Date "2023-05-07"
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
P 6900 3050
F 0 "R?" V 6968 3096 50  0000 L CNN
F 1 "220 to 300 Ohm" V 7050 2850 50  0000 L CNN
F 2 "" H 6900 3050 50  0001 C CNN
F 3 "~" H 6900 3050 50  0001 C CNN
	1    6900 3050
	0    1    1    0   
$EndComp
$Comp
L mdoLibrary:Arduino_USB A?
U 1 1 6438ED98
P 5400 5150
F 0 "A?" H 5400 6137 60  0000 C CNN
F 1 "Arduino_USB" H 5400 6031 60  0000 C CNN
F 2 "" H 5400 5150 60  0000 C CNN
F 3 "" H 5400 5150 60  0000 C CNN
	1    5400 5150
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D?
U 1 1 6439D7A1
P 7750 3050
F 0 "D?" H 8094 3096 50  0000 L CNN
F 1 "WS2812B" H 8094 3005 50  0000 L CNN
F 2 "LED_SMD:LED_WS2812B_PLCC4_5.0x5.0mm_P3.2mm" H 7800 2750 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 7850 2675 50  0001 L TNN
	1    7750 3050
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D?
U 1 1 643A2FD8
P 8800 3050
F 0 "D?" H 9144 3096 50  0000 L CNN
F 1 "WS2812B" H 9144 3005 50  0000 L CNN
F 2 "LED_SMD:LED_WS2812B_PLCC4_5.0x5.0mm_P3.2mm" H 8850 2750 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 8900 2675 50  0001 L TNN
	1    8800 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	9950 2300 8800 2300
Wire Wire Line
	9950 2300 9950 4750
Wire Wire Line
	4800 5350 4600 5350
Wire Wire Line
	6000 4550 6200 4550
Wire Wire Line
	6200 4550 6200 3700
Wire Wire Line
	6000 4750 9950 4750
$Comp
L mdoLibrary:UBEC J?
U 1 1 64587F3E
P 3650 2550
F 0 "J?" H 3750 3237 60  0000 C CNN
F 1 "UBEC" H 3750 3131 60  0000 C CNN
F 2 "" H 3650 2550 60  0001 C CNN
F 3 "" H 3650 2550 60  0001 C CNN
	1    3650 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery BT?
U 1 1 645894A4
P 1550 2500
F 0 "BT?" H 1658 2546 50  0000 L CNN
F 1 "Battery" H 1658 2455 50  0000 L CNN
F 2 "" V 1550 2560 50  0001 C CNN
F 3 "~" V 1550 2560 50  0001 C CNN
	1    1550 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 2750 7750 2300
Wire Wire Line
	8800 2750 8800 2300
Connection ~ 8800 2300
Wire Wire Line
	8800 2300 7750 2300
Wire Wire Line
	7750 3350 7750 3700
Wire Wire Line
	7750 3700 6200 3700
Wire Wire Line
	6800 3050 4600 3050
Wire Wire Line
	4600 3050 4600 5350
Wire Wire Line
	7000 3050 7450 3050
Connection ~ 7750 2300
Wire Wire Line
	4350 2300 6000 2300
Wire Wire Line
	6200 3700 6200 2700
Wire Wire Line
	6200 2700 4350 2700
Connection ~ 6200 3700
Wire Wire Line
	7750 3700 8800 3700
Wire Wire Line
	8800 3700 8800 3350
Connection ~ 7750 3700
Text Notes 7100 1700 0    197  ~ 39
8 LED WS2821B Stick
Wire Wire Line
	3150 2700 1550 2700
$Comp
L mdoLibrary:SW_SPST SW?
U 1 1 64596855
P 2600 2300
F 0 "SW?" H 2600 2535 50  0000 C CNN
F 1 "SW_SPST" H 2600 2444 50  0000 C CNN
F 2 "" H 2600 2300 50  0001 C CNN
F 3 "" H 2600 2300 50  0001 C CNN
	1    2600 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 2300 2800 2300
Wire Wire Line
	2400 2300 1550 2300
Wire Wire Line
	6000 4450 6000 2300
Connection ~ 6000 2300
Wire Wire Line
	6000 2300 7750 2300
Text Notes 6500 2950 0    118  ~ 0
Optional
$EndSCHEMATC
