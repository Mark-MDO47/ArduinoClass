EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 1 1
Title "03 Sonar Range Detector - Extra Fun"
Date "2023-04-18"
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
P 2550 4100
F 0 "R?" H 2618 4146 50  0000 L CNN
F 1 "220 to 300 Ohm" H 2618 4055 50  0000 L CNN
F 2 "" H 2550 4100 50  0001 C CNN
F 3 "~" H 2550 4100 50  0001 C CNN
	1    2550 4100
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
$Comp
L LED:WS2812B D?
U 1 1 6439D7A1
P 3000 3150
F 0 "D?" H 3344 3196 50  0000 L CNN
F 1 "WS2812B" H 3344 3105 50  0000 L CNN
F 2 "LED_SMD:LED_WS2812B_PLCC4_5.0x5.0mm_P3.2mm" H 3050 2850 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 3100 2775 50  0001 L TNN
	1    3000 3150
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D?
U 1 1 6439F025
P 3950 3150
F 0 "D?" H 4294 3196 50  0000 L CNN
F 1 "WS2812B" H 4294 3105 50  0000 L CNN
F 2 "LED_SMD:LED_WS2812B_PLCC4_5.0x5.0mm_P3.2mm" H 4000 2850 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 4050 2775 50  0001 L TNN
	1    3950 3150
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D?
U 1 1 643A1A23
P 4900 3150
F 0 "D?" H 5244 3196 50  0000 L CNN
F 1 "WS2812B" H 5244 3105 50  0000 L CNN
F 2 "LED_SMD:LED_WS2812B_PLCC4_5.0x5.0mm_P3.2mm" H 4950 2850 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 5000 2775 50  0001 L TNN
	1    4900 3150
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D?
U 1 1 643A1E95
P 5850 3150
F 0 "D?" H 6194 3196 50  0000 L CNN
F 1 "WS2812B" H 6194 3105 50  0000 L CNN
F 2 "LED_SMD:LED_WS2812B_PLCC4_5.0x5.0mm_P3.2mm" H 5900 2850 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 5950 2775 50  0001 L TNN
	1    5850 3150
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D?
U 1 1 643A29C1
P 6800 3150
F 0 "D?" H 7144 3196 50  0000 L CNN
F 1 "WS2812B" H 7144 3105 50  0000 L CNN
F 2 "LED_SMD:LED_WS2812B_PLCC4_5.0x5.0mm_P3.2mm" H 6850 2850 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 6900 2775 50  0001 L TNN
	1    6800 3150
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D?
U 1 1 643A2BA5
P 7750 3150
F 0 "D?" H 8094 3196 50  0000 L CNN
F 1 "WS2812B" H 8094 3105 50  0000 L CNN
F 2 "LED_SMD:LED_WS2812B_PLCC4_5.0x5.0mm_P3.2mm" H 7800 2850 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 7850 2775 50  0001 L TNN
	1    7750 3150
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D?
U 1 1 643A2DB0
P 8700 3150
F 0 "D?" H 9044 3196 50  0000 L CNN
F 1 "WS2812B" H 9044 3105 50  0000 L CNN
F 2 "LED_SMD:LED_WS2812B_PLCC4_5.0x5.0mm_P3.2mm" H 8750 2850 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 8800 2775 50  0001 L TNN
	1    8700 3150
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D?
U 1 1 643A2FD8
P 9650 3150
F 0 "D?" H 9994 3196 50  0000 L CNN
F 1 "WS2812B" H 9994 3105 50  0000 L CNN
F 2 "LED_SMD:LED_WS2812B_PLCC4_5.0x5.0mm_P3.2mm" H 9700 2850 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 9750 2775 50  0001 L TNN
	1    9650 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 3150 2550 3150
Wire Wire Line
	3300 3150 3650 3150
Wire Wire Line
	4250 3150 4600 3150
Wire Wire Line
	5200 3150 5550 3150
Wire Wire Line
	6150 3150 6500 3150
Wire Wire Line
	7100 3150 7450 3150
Wire Wire Line
	8050 3150 8400 3150
Wire Wire Line
	9000 3150 9350 3150
Wire Wire Line
	5650 4850 5400 4850
Wire Wire Line
	9650 3450 8700 3450
Wire Wire Line
	8700 3450 7750 3450
Connection ~ 8700 3450
Wire Wire Line
	7750 3450 6800 3450
Connection ~ 7750 3450
Wire Wire Line
	6800 3450 5850 3450
Connection ~ 6800 3450
Wire Wire Line
	5850 3450 4900 3450
Connection ~ 5850 3450
Wire Wire Line
	4900 3450 3950 3450
Connection ~ 4900 3450
Wire Wire Line
	3950 3450 3000 3450
Connection ~ 3950 3450
Connection ~ 3000 3450
Wire Wire Line
	7050 3800 3000 3800
Wire Wire Line
	3000 3450 3000 3800
Wire Wire Line
	9650 2850 8700 2850
Wire Wire Line
	8700 2850 7750 2850
Connection ~ 8700 2850
Wire Wire Line
	7750 2850 6800 2850
Connection ~ 7750 2850
Wire Wire Line
	6800 2850 5850 2850
Connection ~ 6800 2850
Wire Wire Line
	5850 2850 4900 2850
Connection ~ 5850 2850
Wire Wire Line
	4900 2850 3950 2850
Connection ~ 4900 2850
Wire Wire Line
	3950 2850 3000 2850
Connection ~ 3950 2850
Text Notes 2500 2100 0    118  ~ 24
NOTE: connections needed only to leftmost LED; daisy chain is within the LED Stick
Wire Wire Line
	5650 5450 2550 5450
Wire Wire Line
	6850 4650 7050 4650
Wire Wire Line
	7050 4650 7050 3800
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
P 1700 3300
F 0 "J?" H 1800 3987 60  0000 C CNN
F 1 "UBEC" H 1800 3881 60  0000 C CNN
F 2 "" H 1700 3300 60  0001 C CNN
F 3 "" H 1700 3300 60  0001 C CNN
	1    1700 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 4200 2550 5450
Wire Wire Line
	2550 4000 2550 3150
Wire Wire Line
	2200 3450 2400 3450
Wire Wire Line
	2450 2850 3000 2850
Wire Wire Line
	2200 3050 2400 3050
Connection ~ 3000 2850
Wire Wire Line
	2400 3050 2450 3050
Wire Wire Line
	2450 3050 2450 2850
Connection ~ 2400 3050
Wire Wire Line
	2400 3450 3000 3450
Connection ~ 2400 3450
$Comp
L Device:Battery_Cell BT?
U 1 1 6440ACA4
P 850 3300
F 0 "BT?" H 968 3396 50  0000 L CNN
F 1 "Battery_Cell" H 968 3305 50  0000 L CNN
F 2 "" V 850 3360 50  0001 C CNN
F 3 "~" V 850 3360 50  0001 C CNN
	1    850  3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 3450 850  3450
Wire Wire Line
	850  3450 850  3400
Wire Wire Line
	850  3100 850  3050
Wire Wire Line
	850  3050 1200 3050
Text Notes 750  2950 0    50   ~ 0
9V Battery
$EndSCHEMATC
