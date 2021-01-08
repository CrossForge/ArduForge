EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr User 6299 4724
encoding utf-8
Sheet 1 1
Title "CC1101 examplary wiring schematic."
Date "2021-01-08"
Rev ""
Comp "ArduForge"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 "Wiring schematic compatible with default values of the ArduForge::CC1101 class."
$EndDescr
Wire Wire Line
	5050 750  5050 700 
$Comp
L Device:R_Small R1
U 1 1 5FF8FA7C
P 4050 1650
F 0 "R1" V 3854 1650 50  0000 C CNN
F 1 "220" V 3945 1650 50  0000 C CNN
F 2 "" H 4050 1650 50  0001 C CNN
F 3 "~" H 4050 1650 50  0001 C CNN
	1    4050 1650
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R2
U 1 1 5FF90B07
P 3750 1650
F 0 "R2" V 3554 1650 50  0000 C CNN
F 1 "470" V 3645 1650 50  0000 C CNN
F 2 "" H 3750 1650 50  0001 C CNN
F 3 "~" H 3750 1650 50  0001 C CNN
	1    3750 1650
	0    1    1    0   
$EndComp
Wire Wire Line
	3950 1650 3900 1650
$Comp
L Device:R_Small R1
U 1 1 5FF93F1E
P 4050 2100
F 0 "R1" V 3854 2100 50  0000 C CNN
F 1 "220" V 3945 2100 50  0000 C CNN
F 2 "" H 4050 2100 50  0001 C CNN
F 3 "~" H 4050 2100 50  0001 C CNN
	1    4050 2100
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R2
U 1 1 5FF93F24
P 3750 2100
F 0 "R2" V 3554 2100 50  0000 C CNN
F 1 "470" V 3645 2100 50  0000 C CNN
F 2 "" H 3750 2100 50  0001 C CNN
F 3 "~" H 3750 2100 50  0001 C CNN
	1    3750 2100
	0    1    1    0   
$EndComp
Wire Wire Line
	3950 2100 3900 2100
$Comp
L Device:R_Small R1
U 1 1 5FF96042
P 4050 2600
F 0 "R1" V 3854 2600 50  0000 C CNN
F 1 "220" V 3945 2600 50  0000 C CNN
F 2 "" H 4050 2600 50  0001 C CNN
F 3 "~" H 4050 2600 50  0001 C CNN
	1    4050 2600
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FF9AB41
P 3550 1650
F 0 "#PWR?" H 3550 1400 50  0001 C CNN
F 1 "GND" V 3555 1522 50  0000 R CNN
F 2 "" H 3550 1650 50  0001 C CNN
F 3 "" H 3550 1650 50  0001 C CNN
	1    3550 1650
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FF9B04A
P 3550 2100
F 0 "#PWR?" H 3550 1850 50  0001 C CNN
F 1 "GND" V 3555 1972 50  0000 R CNN
F 2 "" H 3550 2100 50  0001 C CNN
F 3 "" H 3550 2100 50  0001 C CNN
	1    3550 2100
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FF99537
P 3550 2600
F 0 "#PWR?" H 3550 2350 50  0001 C CNN
F 1 "GND" V 3555 2472 50  0000 R CNN
F 2 "" H 3550 2600 50  0001 C CNN
F 3 "" H 3550 2600 50  0001 C CNN
	1    3550 2600
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R2
U 1 1 5FF96048
P 3750 2600
F 0 "R2" V 3554 2600 50  0000 C CNN
F 1 "470" V 3645 2600 50  0000 C CNN
F 2 "" H 3750 2600 50  0001 C CNN
F 3 "~" H 3750 2600 50  0001 C CNN
	1    3750 2600
	0    1    1    0   
$EndComp
Wire Wire Line
	3650 2600 3550 2600
Wire Wire Line
	3650 1650 3550 1650
Wire Wire Line
	3650 2100 3550 2100
Wire Wire Line
	3900 2100 3900 2250
Connection ~ 3900 2100
Wire Wire Line
	3900 2100 3850 2100
Wire Wire Line
	2400 2050 2400 2350
Wire Wire Line
	3900 1650 3900 1850
Connection ~ 3900 1650
Wire Wire Line
	3900 1650 3850 1650
$Comp
L MCU_Module:Arduino_Nano_v3.x A1
U 1 1 5FF8593B
P 4950 1750
F 0 "A1" H 4950 661 50  0000 C CNN
F 1 "Arduino Nano" H 4950 570 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 4950 1750 50  0001 C CIN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 4950 1750 50  0001 C CNN
	1    4950 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 2350 4450 2350
Wire Wire Line
	4150 2100 4300 2100
Wire Wire Line
	4300 2250 4450 2250
Wire Wire Line
	4950 2750 4950 2800
Wire Wire Line
	4950 2800 2100 2800
Wire Wire Line
	3850 2600 3900 2600
Wire Wire Line
	4150 2600 4450 2600
Wire Wire Line
	3900 2700 3900 2600
Connection ~ 3900 2600
Wire Wire Line
	3900 2600 3950 2600
Wire Wire Line
	3900 2250 2500 2250
Wire Wire Line
	2500 2250 2500 1950
Wire Wire Line
	3900 1850 2250 1850
Wire Wire Line
	4150 1650 4400 1650
Wire Wire Line
	4400 2150 4450 2150
$Comp
L RF:CC1101 U?
U 1 1 5FF840AC
P 1650 1950
F 0 "U?" H 1850 1950 50  0001 C CNN
F 1 "CC1101" H 1700 2150 50  0000 C CNN
F 2 "" H 1850 1950 50  0001 C CNN
F 3 "" H 1850 1950 50  0001 C CNN
	1    1650 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 1950 2100 1950
Wire Wire Line
	2100 2050 2400 2050
Wire Wire Line
	2250 2150 2100 2150
Wire Wire Line
	1100 2150 1300 2150
Wire Wire Line
	1100 1350 1100 2150
Wire Wire Line
	4450 1350 1100 1350
Wire Wire Line
	1200 2700 3900 2700
Wire Wire Line
	1200 1950 1300 1950
Wire Wire Line
	1200 2700 1200 1950
Wire Wire Line
	1300 700  5050 700 
Wire Wire Line
	1300 700  1300 1850
Wire Wire Line
	2100 2250 2100 2800
Wire Wire Line
	4450 2600 4450 2450
Wire Wire Line
	4300 2100 4300 2250
Wire Wire Line
	2250 1850 2250 2150
Wire Wire Line
	4400 1650 4400 2150
$EndSCHEMATC
