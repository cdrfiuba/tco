EESchema Schematic File Version 2
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
LIBS:cny70
LIBS:sensores-cache
LIBS:sensores-cache
EELAYER 24 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "25 may 2013"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 2150 2350 0    60   ~ 0
Sensor_Piso_Izq
$Comp
L POT RV1
U 1 1 516A2B00
P 2300 3300
F 0 "RV1" H 2300 3200 50  0000 C CNN
F 1 "POT" H 2300 3300 50  0000 C CNN
F 2 "" H 2300 3300 60  0001 C CNN
F 3 "" H 2300 3300 60  0001 C CNN
	1    2300 3300
	1    0    0    -1  
$EndComp
$Comp
L R R_sens1
U 1 1 516A2AC6
P 1250 2700
F 0 "R_sens1" V 1330 2700 50  0000 C CNN
F 1 "200" V 1250 2700 50  0000 C CNN
F 2 "" H 1250 2700 60  0001 C CNN
F 3 "" H 1250 2700 60  0001 C CNN
	1    1250 2700
	-1   0    0    1   
$EndComp
$Comp
L CNY70 ??1
U 1 1 516A2AAF
P 1750 3200
F 0 "??1" H 1750 3200 60  0000 C CNN
F 1 "CNY70" H 1750 3200 60  0000 C CNN
F 2 "" H 1750 3200 60  0001 C CNN
F 3 "" H 1750 3200 60  0001 C CNN
	1    1750 3200
	1    0    0    -1  
$EndComp
$Comp
L CONN_8X2 P1
U 1 1 51A1369E
P 4000 1300
F 0 "P1" H 4000 1750 60  0000 C CNN
F 1 "CONN_8X2" V 4000 1300 50  0000 C CNN
F 2 "~" H 4000 1300 60  0000 C CNN
F 3 "~" H 4000 1300 60  0000 C CNN
	1    4000 1300
	1    0    0    -1  
$EndComp
Text Label 2850 950  0    60   ~ 0
Sensor_Piso_Cen
Text Label 2850 1050 0    60   ~ 0
S1+
Text Label 2850 1150 0    60   ~ 0
Sensor_Piso_Izq
Text Label 2850 1350 0    60   ~ 0
Sensor_Piso_Der
Text Label 2850 1650 0    60   ~ 0
S-
Text Label 2850 1250 0    60   ~ 0
S2+
Text Label 2850 1450 0    60   ~ 0
S3+
NoConn ~ 3600 1550
NoConn ~ 4400 950 
NoConn ~ 4400 1050
NoConn ~ 4400 1150
NoConn ~ 4400 1250
NoConn ~ 4400 1350
NoConn ~ 4400 1450
NoConn ~ 4400 1550
$Comp
L GND #PWR5
U 1 1 51A1397D
P 4700 1800
F 0 "#PWR5" H 4700 1800 30  0001 C CNN
F 1 "GND" H 4700 1730 30  0001 C CNN
F 2 "" H 4700 1800 60  0000 C CNN
F 3 "" H 4700 1800 60  0000 C CNN
	1    4700 1800
	1    0    0    -1  
$EndComp
Text Label 3950 2350 0    60   ~ 0
Sensor_Piso_Cen
$Comp
L POT RV2
U 1 1 51A13AE0
P 4100 3300
F 0 "RV2" H 4100 3200 50  0000 C CNN
F 1 "POT" H 4100 3300 50  0000 C CNN
F 2 "" H 4100 3300 60  0001 C CNN
F 3 "" H 4100 3300 60  0001 C CNN
	1    4100 3300
	1    0    0    -1  
$EndComp
$Comp
L R R_sens2
U 1 1 51A13AE6
P 3450 2650
F 0 "R_sens2" V 3530 2650 50  0000 C CNN
F 1 "200" V 3450 2650 50  0000 C CNN
F 2 "" H 3450 2650 60  0001 C CNN
F 3 "" H 3450 2650 60  0001 C CNN
	1    3450 2650
	0    -1   -1   0   
$EndComp
$Comp
L CNY70 U1
U 1 1 51A13AEC
P 3550 3200
F 0 "U1" H 3550 3200 60  0000 C CNN
F 1 "CNY70" H 3550 3200 60  0000 C CNN
F 2 "" H 3550 3200 60  0001 C CNN
F 3 "" H 3550 3200 60  0001 C CNN
	1    3550 3200
	1    0    0    -1  
$EndComp
Text Label 3850 2150 0    60   ~ 0
S1+
Text Label 5700 2350 0    60   ~ 0
Sensor_Piso_Der
$Comp
L POT RV3
U 1 1 51A13B0D
P 5850 3300
F 0 "RV3" H 5850 3200 50  0000 C CNN
F 1 "POT" H 5850 3300 50  0000 C CNN
F 2 "" H 5850 3300 60  0001 C CNN
F 3 "" H 5850 3300 60  0001 C CNN
	1    5850 3300
	1    0    0    -1  
$EndComp
$Comp
L R R_sens3
U 1 1 51A13B13
P 5200 2650
F 0 "R_sens3" V 5280 2650 50  0000 C CNN
F 1 "200" V 5200 2650 50  0000 C CNN
F 2 "" H 5200 2650 60  0001 C CNN
F 3 "" H 5200 2650 60  0001 C CNN
	1    5200 2650
	0    -1   -1   0   
$EndComp
$Comp
L CNY70 U2
U 1 1 51A13B19
P 5300 3200
F 0 "U2" H 5300 3200 60  0000 C CNN
F 1 "CNY70" H 5300 3200 60  0000 C CNN
F 2 "" H 5300 3200 60  0001 C CNN
F 3 "" H 5300 3200 60  0001 C CNN
	1    5300 3200
	1    0    0    -1  
$EndComp
Text Label 5600 2150 0    60   ~ 0
S3+
Text Label 1250 3450 0    60   ~ 0
S-
Text Label 3050 3450 0    60   ~ 0
S-
Text Label 4350 3450 0    60   ~ 0
S-
Text Label 4800 3450 0    60   ~ 0
S-
Text Label 6100 3450 0    60   ~ 0
S-
Text Label 1250 2450 0    60   ~ 0
S2+
Wire Wire Line
	2050 2150 2050 3100
Connection ~ 2150 3150
Wire Wire Line
	2050 3300 2050 3150
Wire Wire Line
	2050 3150 2300 3150
Wire Wire Line
	1250 3100 1350 3100
Wire Wire Line
	1350 3300 1250 3300
Wire Wire Line
	1250 3300 1250 3450
Wire Wire Line
	2550 3450 2550 3300
Wire Wire Line
	3600 950  2850 950 
Wire Wire Line
	3600 1050 2850 1050
Wire Wire Line
	3600 1150 2850 1150
Wire Wire Line
	3600 1250 2850 1250
Wire Wire Line
	3600 1350 2850 1350
Wire Wire Line
	3600 1450 2850 1450
Wire Wire Line
	2850 1650 3600 1650
Wire Wire Line
	4400 1650 4700 1650
Wire Wire Line
	4700 1650 4700 1800
Wire Wire Line
	3850 2150 3850 3100
Wire Wire Line
	3050 2650 3050 3100
Wire Wire Line
	3050 2650 3200 2650
Connection ~ 3950 3150
Wire Wire Line
	3950 2350 3950 3150
Wire Wire Line
	3850 3300 3850 3150
Wire Wire Line
	3850 3150 4100 3150
Wire Wire Line
	3050 3100 3150 3100
Wire Wire Line
	3150 3300 3050 3300
Wire Wire Line
	3050 3300 3050 3450
Wire Wire Line
	3850 2650 3700 2650
Wire Wire Line
	4350 3450 4350 3300
Connection ~ 3850 2650
Wire Wire Line
	5600 2150 5600 3100
Wire Wire Line
	4800 2650 4800 3100
Wire Wire Line
	4800 2650 4950 2650
Connection ~ 5700 3150
Wire Wire Line
	5700 2350 5700 3150
Wire Wire Line
	5600 3300 5600 3150
Wire Wire Line
	5600 3150 5850 3150
Wire Wire Line
	4800 3100 4900 3100
Wire Wire Line
	4900 3300 4800 3300
Wire Wire Line
	4800 3300 4800 3450
Wire Wire Line
	5600 2650 5450 2650
Wire Wire Line
	6100 3450 6100 3300
Connection ~ 5600 2650
Wire Wire Line
	1250 2950 1250 3100
Wire Wire Line
	2150 2350 2150 3150
Text Label 2050 2150 0    60   ~ 0
Vcc
$Comp
L GND #PWR?
U 1 1 51A13F3D
P 2550 3450
F 0 "#PWR?" H 2550 3450 30  0001 C CNN
F 1 "GND" H 2550 3380 30  0001 C CNN
F 2 "" H 2550 3450 60  0000 C CNN
F 3 "" H 2550 3450 60  0000 C CNN
	1    2550 3450
	1    0    0    -1  
$EndComp
$EndSCHEMATC
