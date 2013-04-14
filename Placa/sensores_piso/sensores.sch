EESchema Schematic File Version 2  date Sun 14 Apr 2013 01:33:47 AM ART
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
EELAYER 43  0
EELAYER END
$Descr A4 11700 8267
Sheet 1 1
Title ""
Date "14 apr 2013"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Connection ~ 2750 1700
Wire Wire Line
	2750 1500 2750 2050
Wire Wire Line
	2750 1700 2600 1700
Wire Wire Line
	2750 2250 2750 2100
Wire Wire Line
	2750 2100 3000 2100
Wire Wire Line
	2100 1700 1950 1700
Wire Wire Line
	1950 1700 1950 2050
Wire Wire Line
	1950 2050 2050 2050
Wire Wire Line
	2050 2250 1950 2250
Wire Wire Line
	1950 2250 1950 2400
Wire Wire Line
	3750 2450 3750 2250
$Comp
L +5V #PWR?
U 1 1 516A2BA2
P 2750 1500
F 0 "#PWR?" H 2750 1590 20  0001 C CNN
F 1 "+5V" H 2750 1590 30  0000 C CNN
	1    2750 1500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 516A2B65
P 3750 2450
F 0 "#PWR?" H 3750 2450 30  0001 C CNN
F 1 "GND" H 3750 2380 30  0001 C CNN
	1    3750 2450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 516A2B56
P 1950 2400
F 0 "#PWR?" H 1950 2400 30  0001 C CNN
F 1 "GND" H 1950 2330 30  0001 C CNN
	1    1950 2400
	1    0    0    -1  
$EndComp
$Comp
L POT RV?
U 1 1 516A2B00
P 3000 2250
F 0 "RV?" H 3000 2150 50  0000 C CNN
F 1 "POT" H 3000 2250 50  0000 C CNN
	1    3000 2250
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 516A2AD5
P 3500 2250
F 0 "R2" V 3600 2250 50  0000 C CNN
F 1 "100" V 3500 2250 50  0000 C CNN
	1    3500 2250
	0    1    1    0   
$EndComp
$Comp
L R R_sens
U 1 1 516A2AC6
P 2350 1700
F 0 "R_sens" V 2430 1700 50  0000 C CNN
F 1 "200" V 2350 1700 50  0000 C CNN
	1    2350 1700
	0    -1   -1   0   
$EndComp
$Comp
L CNY70 ???
U 1 1 516A2AAF
P 2450 2150
F 0 "???" H 2450 2150 60  0000 C CNN
F 1 "CNY70" H 2450 2150 60  0000 C CNN
	1    2450 2150
	1    0    0    -1  
$EndComp
$EndSCHEMATC
