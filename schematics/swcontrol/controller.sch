EESchema Schematic File Version 2
LIBS:msp430
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:controller-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L C C1
U 1 1 54F2F845
P 3000 1400
F 0 "C1" H 3050 1500 50  0000 L CNN
F 1 "100n" H 3050 1300 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 3038 1250 30  0001 C CNN
F 3 "" H 3000 1400 60  0000 C CNN
	1    3000 1400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 54F2F9B4
P 3000 1750
F 0 "#PWR05" H 3000 1500 60  0001 C CNN
F 1 "GND" H 3000 1600 60  0000 C CNN
F 2 "" H 3000 1750 60  0000 C CNN
F 3 "" H 3000 1750 60  0000 C CNN
	1    3000 1750
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR06
U 1 1 54F2F9DA
P 3000 1100
F 0 "#PWR06" H 3000 950 60  0001 C CNN
F 1 "+3V3" H 3000 1240 60  0000 C CNN
F 2 "" H 3000 1100 60  0000 C CNN
F 3 "" H 3000 1100 60  0000 C CNN
	1    3000 1100
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 54F2FA6B
P 1550 1200
F 0 "R1" V 1630 1200 50  0000 C CNN
F 1 "47k" V 1557 1201 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 1480 1200 30  0001 C CNN
F 3 "" H 1550 1200 30  0000 C CNN
	1    1550 1200
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR07
U 1 1 54F2FACC
P 1550 850
F 0 "#PWR07" H 1550 700 60  0001 C CNN
F 1 "+3V3" H 1550 990 60  0000 C CNN
F 2 "" H 1550 850 60  0000 C CNN
F 3 "" H 1550 850 60  0000 C CNN
	1    1550 850 
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 54F2FB00
P 1550 1600
F 0 "C2" H 1600 1700 50  0000 L CNN
F 1 "1n" H 1600 1500 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 1588 1450 30  0001 C CNN
F 3 "" H 1550 1600 60  0000 C CNN
	1    1550 1600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 54F2FBBE
P 1550 1850
F 0 "#PWR08" H 1550 1600 60  0001 C CNN
F 1 "GND" H 1550 1700 60  0000 C CNN
F 2 "" H 1550 1850 60  0000 C CNN
F 3 "" H 1550 1850 60  0000 C CNN
	1    1550 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 1100 3000 1250
Wire Wire Line
	3000 1550 3000 1750
Wire Wire Line
	1550 850  1550 1050
Wire Wire Line
	1550 1750 1550 1850
Wire Wire Line
	1550 1400 1750 1400
$Comp
L MSP430G2533IPW20 U?
U 1 1 55485339
P 3300 3350
F 0 "U?" H 2050 3950 40  0000 C CNN
F 1 "MSP430G2533IPW20" H 4300 2800 40  0000 C CNN
F 2 "20PW" H 2050 2800 35  0000 C CIN
F 3 "" H 3300 2950 60  0000 C CNN
	1    3300 3350
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR?
U 1 1 554854B0
P 3300 2600
F 0 "#PWR?" H 3300 2450 60  0001 C CNN
F 1 "+3V3" H 3300 2740 60  0000 C CNN
F 2 "" H 3300 2600 60  0000 C CNN
F 3 "" H 3300 2600 60  0000 C CNN
	1    3300 2600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 554854C9
P 3300 4100
F 0 "#PWR?" H 3300 3850 60  0001 C CNN
F 1 "GND" H 3300 3950 60  0000 C CNN
F 2 "" H 3300 4100 60  0000 C CNN
F 3 "" H 3300 4100 60  0000 C CNN
	1    3300 4100
	1    0    0    -1  
$EndComp
Text GLabel 1750 1400 2    60   Input ~ 0
RST
Text GLabel 1700 2900 0    60   Input ~ 0
RST
Text GLabel 4850 3150 2    60   Input ~ 0
ZERO
Wire Wire Line
	4850 3150 4750 3150
Text GLabel 4850 3550 2    60   Input ~ 0
SCK
Text GLabel 4900 3350 2    60   Input ~ 0
CE
Text GLabel 4850 3450 2    60   Input ~ 0
CSN
Text GLabel 1700 3650 0    60   Input ~ 0
TRIAC
Wire Wire Line
	1850 3650 1700 3650
Wire Wire Line
	1850 2900 1700 2900
Wire Wire Line
	4900 3350 4750 3350
Wire Wire Line
	4850 3450 4750 3450
Wire Wire Line
	4850 3550 4750 3550
$Comp
L CONN_02X04 P?
U 1 1 55485A01
P 8600 1200
F 0 "P?" H 8600 1450 50  0000 C CNN
F 1 "BK24x1" H 8600 950 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x04" H 8600 0   60  0001 C CNN
F 3 "" H 8600 0   60  0000 C CNN
	1    8600 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 1350 1550 1450
Connection ~ 1550 1400
Text GLabel 4850 3650 2    60   Input ~ 0
MISO
Text GLabel 4850 3750 2    60   Input ~ 0
MOSI
Wire Wire Line
	4850 3650 4750 3650
Wire Wire Line
	4750 3750 4850 3750
Wire Wire Line
	3300 4000 3300 4100
Wire Wire Line
	3300 2600 3300 2650
$Comp
L +3V3 #PWR?
U 1 1 55485E7A
P 8100 1350
F 0 "#PWR?" H 8100 1200 60  0001 C CNN
F 1 "+3V3" H 8100 1490 60  0000 C CNN
F 2 "" H 8100 1350 60  0000 C CNN
F 3 "" H 8100 1350 60  0000 C CNN
	1    8100 1350
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR?
U 1 1 55485E95
P 9050 1350
F 0 "#PWR?" H 9050 1100 60  0001 C CNN
F 1 "GND" H 9050 1200 60  0000 C CNN
F 2 "" H 9050 1350 60  0000 C CNN
F 3 "" H 9050 1350 60  0000 C CNN
	1    9050 1350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9050 1350 8850 1350
Wire Wire Line
	8350 1350 8100 1350
Text Notes 5250 3050 0    60   ~ 0
Prestavi TRIAC na P1.0\n
$Comp
L CP C?
U 1 1 55485FFA
P 2450 1400
F 0 "C?" H 2475 1500 50  0000 L CNN
F 1 "CP" H 2475 1300 50  0000 L CNN
F 2 "" H 2488 1250 30  0000 C CNN
F 3 "" H 2450 1400 60  0000 C CNN
	1    2450 1400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 55486049
P 2450 1750
F 0 "#PWR?" H 2450 1500 60  0001 C CNN
F 1 "GND" H 2450 1600 60  0000 C CNN
F 2 "" H 2450 1750 60  0000 C CNN
F 3 "" H 2450 1750 60  0000 C CNN
	1    2450 1750
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR?
U 1 1 55486066
P 2450 1100
F 0 "#PWR?" H 2450 950 60  0001 C CNN
F 1 "+3V3" H 2450 1240 60  0000 C CNN
F 2 "" H 2450 1100 60  0000 C CNN
F 3 "" H 2450 1100 60  0000 C CNN
	1    2450 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 1550 2450 1750
Wire Wire Line
	2450 1100 2450 1250
$Comp
L C C?
U 1 1 55486120
P 3450 1550
F 0 "C?" H 3500 1650 50  0000 L CNN
F 1 "100n" H 3500 1450 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 3488 1400 30  0001 C CNN
F 3 "" H 3450 1550 60  0000 C CNN
	1    3450 1550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 554861F0
P 3450 1750
F 0 "#PWR?" H 3450 1500 60  0001 C CNN
F 1 "GND" H 3450 1600 60  0000 C CNN
F 2 "" H 3450 1750 60  0000 C CNN
F 3 "" H 3450 1750 60  0000 C CNN
	1    3450 1750
	1    0    0    -1  
$EndComp
Text GLabel 3450 1200 1    60   Input ~ 0
ZERO
Wire Wire Line
	3450 1200 3450 1400
Wire Wire Line
	3450 1700 3450 1750
$Comp
L CONN_01X04 P?
U 1 1 55486476
P 8850 2000
F 0 "P?" H 8850 2250 50  0000 C CNN
F 1 "BiWire" V 8950 2000 50  0000 C CNN
F 2 "" H 8850 2000 60  0000 C CNN
F 3 "" H 8850 2000 60  0000 C CNN
	1    8850 2000
	1    0    0    -1  
$EndComp
Text GLabel 4850 2900 2    60   Input ~ 0
TEST
Wire Wire Line
	4850 2900 4750 2900
$Comp
L +3V3 #PWR?
U 1 1 554865AF
P 8500 1850
F 0 "#PWR?" H 8500 1700 60  0001 C CNN
F 1 "+3V3" H 8500 1990 60  0000 C CNN
F 2 "" H 8500 1850 60  0000 C CNN
F 3 "" H 8500 1850 60  0000 C CNN
	1    8500 1850
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR?
U 1 1 554865D0
P 8450 1950
F 0 "#PWR?" H 8450 1700 60  0001 C CNN
F 1 "GND" H 8450 1800 60  0000 C CNN
F 2 "" H 8450 1950 60  0000 C CNN
F 3 "" H 8450 1950 60  0000 C CNN
	1    8450 1950
	0    1    1    0   
$EndComp
Text GLabel 8450 2050 0    60   Input ~ 0
TEST
Text GLabel 8450 2150 0    60   Input ~ 0
RST
Wire Wire Line
	8650 1850 8500 1850
Wire Wire Line
	8650 1950 8450 1950
Wire Wire Line
	8650 2050 8450 2050
Wire Wire Line
	8650 2150 8450 2150
$Comp
L CONN_01X07 P?
U 1 1 554869B1
P 10600 1250
F 0 "P?" H 10600 1650 50  0000 C CNN
F 1 "PWRBRD" V 10700 1250 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x07" H 10600 1250 60  0001 C CNN
F 3 "" H 10600 1250 60  0000 C CNN
	1    10600 1250
	1    0    0    -1  
$EndComp
Text Notes 10750 2600 1    60   ~ 0
Additional Triac Controls\n
$Comp
L GND #PWR?
U 1 1 55486B0D
P 10050 950
F 0 "#PWR?" H 10050 700 60  0001 C CNN
F 1 "GND" H 10050 800 60  0000 C CNN
F 2 "" H 10050 950 60  0000 C CNN
F 3 "" H 10050 950 60  0000 C CNN
	1    10050 950 
	0    1    1    0   
$EndComp
$Comp
L +3V3 #PWR?
U 1 1 55486B3C
P 10050 1350
F 0 "#PWR?" H 10050 1200 60  0001 C CNN
F 1 "+3V3" H 10050 1490 60  0000 C CNN
F 2 "" H 10050 1350 60  0000 C CNN
F 3 "" H 10050 1350 60  0000 C CNN
	1    10050 1350
	0    -1   -1   0   
$EndComp
Text GLabel 10350 1250 0    60   Input ~ 0
TRIAC
Text GLabel 10350 1050 0    60   Input ~ 0
ZERO
Text GLabel 4850 3250 2    60   Input ~ 0
TRIAC2
Wire Wire Line
	4850 3250 4750 3250
Text GLabel 10350 1450 0    60   Input ~ 0
TRIAC2
Wire Wire Line
	10400 950  10050 950 
Wire Wire Line
	10400 1050 10350 1050
Wire Wire Line
	10400 1250 10350 1250
Wire Wire Line
	10400 1350 10050 1350
Wire Wire Line
	10350 1450 10400 1450
Text GLabel 8900 1050 2    60   Input ~ 0
MISO
Text GLabel 8300 1150 0    60   Input ~ 0
MOSI
Text GLabel 8300 1250 0    60   Input ~ 0
CSN
Text GLabel 8900 1250 2    60   Input ~ 0
CE
Text GLabel 8900 1150 2    60   Input ~ 0
SCK
Wire Wire Line
	8900 1250 8850 1250
Wire Wire Line
	8900 1150 8850 1150
Wire Wire Line
	8900 1050 8850 1050
Wire Wire Line
	8300 1250 8350 1250
Wire Wire Line
	8300 1150 8350 1150
Text GLabel 1700 3550 0    60   Input ~ 0
INT
Wire Wire Line
	1850 3550 1700 3550
Text GLabel 8300 1050 0    60   Input ~ 0
INT
Wire Wire Line
	8350 1050 8300 1050
$EndSCHEMATC
