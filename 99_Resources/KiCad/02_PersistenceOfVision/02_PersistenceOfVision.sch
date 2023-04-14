EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 1 1
Title "02 Persistence of Vision"
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
P 1500 4000
F 0 "R?" H 1568 4046 50  0000 L CNN
F 1 "220 to 300 Ohm" H 1568 3955 50  0000 L CNN
F 2 "" H 1500 4000 50  0001 C CNN
F 3 "~" H 1500 4000 50  0001 C CNN
	1    1500 4000
	1    0    0    -1  
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
L Switch:SW_Push SW?
U 1 1 64388E02
P 4350 4750
F 0 "SW?" H 4350 5035 50  0000 C CNN
F 1 "SW_Push" H 4350 4944 50  0000 C CNN
F 2 "" H 4350 4950 50  0001 C CNN
F 3 "~" H 4350 4950 50  0001 C CNN
	1    4350 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 4950 4000 4950
Wire Wire Line
	4150 4750 4000 4750
Wire Wire Line
	4000 4750 4000 4950
$Comp
L LED:WS2812B D?
U 1 1 6439D7A1
P 2150 3050
F 0 "D?" H 2494 3096 50  0000 L CNN
F 1 "WS2812B" H 2494 3005 50  0000 L CNN
F 2 "LED_SMD:LED_WS2812B_PLCC4_5.0x5.0mm_P3.2mm" H 2200 2750 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 2250 2675 50  0001 L TNN
	1    2150 3050
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D?
U 1 1 6439F025
P 3100 3050
F 0 "D?" H 3444 3096 50  0000 L CNN
F 1 "WS2812B" H 3444 3005 50  0000 L CNN
F 2 "LED_SMD:LED_WS2812B_PLCC4_5.0x5.0mm_P3.2mm" H 3150 2750 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 3200 2675 50  0001 L TNN
	1    3100 3050
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D?
U 1 1 643A1A23
P 4050 3050
F 0 "D?" H 4394 3096 50  0000 L CNN
F 1 "WS2812B" H 4394 3005 50  0000 L CNN
F 2 "LED_SMD:LED_WS2812B_PLCC4_5.0x5.0mm_P3.2mm" H 4100 2750 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 4150 2675 50  0001 L TNN
	1    4050 3050
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D?
U 1 1 643A1E95
P 5000 3050
F 0 "D?" H 5344 3096 50  0000 L CNN
F 1 "WS2812B" H 5344 3005 50  0000 L CNN
F 2 "LED_SMD:LED_WS2812B_PLCC4_5.0x5.0mm_P3.2mm" H 5050 2750 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 5100 2675 50  0001 L TNN
	1    5000 3050
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D?
U 1 1 643A29C1
P 5950 3050
F 0 "D?" H 6294 3096 50  0000 L CNN
F 1 "WS2812B" H 6294 3005 50  0000 L CNN
F 2 "LED_SMD:LED_WS2812B_PLCC4_5.0x5.0mm_P3.2mm" H 6000 2750 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 6050 2675 50  0001 L TNN
	1    5950 3050
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D?
U 1 1 643A2BA5
P 6900 3050
F 0 "D?" H 7244 3096 50  0000 L CNN
F 1 "WS2812B" H 7244 3005 50  0000 L CNN
F 2 "LED_SMD:LED_WS2812B_PLCC4_5.0x5.0mm_P3.2mm" H 6950 2750 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 7000 2675 50  0001 L TNN
	1    6900 3050
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D?
U 1 1 643A2DB0
P 7850 3050
F 0 "D?" H 8194 3096 50  0000 L CNN
F 1 "WS2812B" H 8194 3005 50  0000 L CNN
F 2 "LED_SMD:LED_WS2812B_PLCC4_5.0x5.0mm_P3.2mm" H 7900 2750 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 7950 2675 50  0001 L TNN
	1    7850 3050
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
	1850 3050 1500 3050
Wire Wire Line
	1500 3050 1500 3900
Wire Wire Line
	2450 3050 2800 3050
Wire Wire Line
	3400 3050 3750 3050
Wire Wire Line
	4350 3050 4700 3050
Wire Wire Line
	5300 3050 5650 3050
Wire Wire Line
	6250 3050 6600 3050
Wire Wire Line
	7200 3050 7550 3050
Wire Wire Line
	8150 3050 8500 3050
Wire Wire Line
	4800 4750 4550 4750
Wire Wire Line
	8800 3350 7850 3350
Wire Wire Line
	7850 3350 6900 3350
Connection ~ 7850 3350
Wire Wire Line
	6900 3350 5950 3350
Connection ~ 6900 3350
Wire Wire Line
	5950 3350 5000 3350
Connection ~ 5950 3350
Wire Wire Line
	5000 3350 4050 3350
Connection ~ 5000 3350
Wire Wire Line
	4050 3350 3100 3350
Connection ~ 4050 3350
Wire Wire Line
	3100 3350 2150 3350
Connection ~ 3100 3350
Connection ~ 2150 3350
Wire Wire Line
	6200 3700 2150 3700
Wire Wire Line
	2150 3350 2150 3700
Wire Wire Line
	9950 2300 2150 2300
Wire Wire Line
	2150 2300 2150 2750
Wire Wire Line
	9950 2300 9950 4750
Wire Wire Line
	8800 2750 7850 2750
Wire Wire Line
	7850 2750 6900 2750
Connection ~ 7850 2750
Wire Wire Line
	6900 2750 5950 2750
Connection ~ 6900 2750
Wire Wire Line
	5950 2750 5000 2750
Connection ~ 5950 2750
Wire Wire Line
	5000 2750 4050 2750
Connection ~ 5000 2750
Wire Wire Line
	4050 2750 3100 2750
Connection ~ 4050 2750
Wire Wire Line
	3100 2750 2150 2750
Connection ~ 3100 2750
Connection ~ 2150 2750
Text Notes 1650 2000 0    118  ~ 24
NOTE: connections needed only to leftmost LED; daisy chain is within the LED Stick
Wire Wire Line
	4800 5350 1500 5350
Wire Wire Line
	1500 5350 1500 4100
Wire Wire Line
	6000 4550 6200 4550
Wire Wire Line
	6200 4550 6200 3700
Wire Wire Line
	6000 4750 9950 4750
$EndSCHEMATC
