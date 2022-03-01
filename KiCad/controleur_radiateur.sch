EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Contrôleur radiateur fil pilote par GSM"
Date "2022-02-09"
Rev "2"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Module:Arduino_Nano_v3.x A1
U 1 1 60266AA4
P 5800 3600
F 0 "A1" H 5800 2511 50  0000 C CNN
F 1 "Arduino_Nano_v3.x" H 5800 2420 50  0000 C CNN
F 2 "perso:Arduino_Nano_step" H 5800 3600 50  0001 C CIN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 5800 3600 50  0001 C CNN
	1    5800 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 4600 5900 4600
$Comp
L Device:R R2
U 1 1 60269F2F
P 5050 2900
F 0 "R2" H 4800 2900 50  0000 L CNN
F 1 "1k" H 4800 2800 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4980 2900 50  0001 C CNN
F 3 "~" H 5050 2900 50  0001 C CNN
	1    5050 2900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 6026ADAA
P 5050 2400
F 0 "R3" H 4800 2450 50  0000 L CNN
F 1 "1.8k" H 4800 2350 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4980 2400 50  0001 C CNN
F 3 "~" H 5050 2400 50  0001 C CNN
	1    5050 2400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 6026B5A9
P 5050 2250
F 0 "#PWR03" H 5050 2000 50  0001 C CNN
F 1 "GND" H 5150 2050 50  0000 R CNN
F 2 "" H 5050 2250 50  0001 C CNN
F 3 "" H 5050 2250 50  0001 C CNN
	1    5050 2250
	-1   0    0    1   
$EndComp
Wire Wire Line
	5050 2550 5050 2700
Wire Wire Line
	5700 2600 5700 2550
$Comp
L perso:SIM800L U1
U 1 1 602A2A1B
P 2650 4300
F 0 "U1" H 2650 5215 50  0000 C CNN
F 1 "SIM800L" H 2650 5124 50  0000 C CNN
F 2 "perso:SIM800L_module" H 2750 4100 50  0001 C CNN
F 3 "" H 2750 4100 50  0001 C CNN
	1    2650 4300
	1    0    0    1   
$EndComp
Wire Wire Line
	4600 2700 5050 2700
Connection ~ 5050 2700
Wire Wire Line
	5050 2700 5050 2750
NoConn ~ 2150 4450
NoConn ~ 2150 4550
NoConn ~ 2150 4650
NoConn ~ 2150 4750
NoConn ~ 2150 4950
$Comp
L power:GND #PWR02
U 1 1 602B0A67
P 3150 4450
F 0 "#PWR02" H 3150 4200 50  0001 C CNN
F 1 "GND" V 3200 4350 50  0000 R CNN
F 2 "" H 3150 4450 50  0001 C CNN
F 3 "" H 3150 4450 50  0001 C CNN
	1    3150 4450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3150 4650 3450 4650
$Comp
L power:GND #PWR04
U 1 1 602B8794
P 5950 4600
F 0 "#PWR04" H 5950 4350 50  0001 C CNN
F 1 "GND" V 5955 4472 50  0000 R CNN
F 2 "" H 5950 4600 50  0001 C CNN
F 3 "" H 5950 4600 50  0001 C CNN
	1    5950 4600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5950 4600 5900 4600
Connection ~ 5900 4600
Wire Wire Line
	3650 4250 3650 4150
Wire Wire Line
	3650 4550 3650 4750
NoConn ~ 3150 4950
$Comp
L Device:R R8
U 1 1 6027A8EB
P 7200 4200
F 0 "R8" V 7000 4100 50  0000 L CNN
F 1 "680" V 7100 4100 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 7130 4200 50  0001 C CNN
F 3 "~" H 7200 4200 50  0001 C CNN
	1    7200 4200
	0    1    1    0   
$EndComp
$Comp
L Device:R R7
U 1 1 6027ADD3
P 7200 3600
F 0 "R7" V 7000 3500 50  0000 L CNN
F 1 "680" V 7100 3500 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 7130 3600 50  0001 C CNN
F 3 "~" H 7200 3600 50  0001 C CNN
	1    7200 3600
	0    1    1    0   
$EndComp
Wire Wire Line
	7350 4200 7550 4200
$Comp
L Diode:1N4007 D6
U 1 1 6028700B
P 8850 3800
F 0 "D6" H 8850 4017 50  0000 C CNN
F 1 "1N4007" H 8850 3926 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 8850 3625 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 8850 3800 50  0001 C CNN
	1    8850 3800
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4007 D7
U 1 1 60287E55
P 8850 4400
F 0 "D7" H 8850 4617 50  0000 C CNN
F 1 "1N4007" H 8850 4526 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 8850 4225 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 8850 4400 50  0001 C CNN
	1    8850 4400
	-1   0    0    1   
$EndComp
Wire Wire Line
	8150 4400 8700 4400
Wire Wire Line
	8700 3800 8150 3800
Wire Wire Line
	9000 4400 9200 4400
Wire Wire Line
	9200 3800 9000 3800
$Comp
L Relay_SolidState:MOC3023M U2
U 1 1 602D77CA
P 7850 3700
F 0 "U2" H 7850 4025 50  0000 C CNN
F 1 "MOC3023M" H 7850 3934 50  0000 C CNN
F 2 "perso:MOC3023M" H 7650 3500 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/MOC3023M-D.PDF" H 7850 3700 50  0001 L CNN
	1    7850 3700
	1    0    0    -1  
$EndComp
$Comp
L Relay_SolidState:MOC3023M U3
U 1 1 602DBB81
P 7850 4300
F 0 "U3" H 7850 4625 50  0000 C CNN
F 1 "MOC3023M" H 7850 4534 50  0000 C CNN
F 2 "perso:MOC3023M" H 7650 4100 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/MOC3023M-D.PDF" H 7850 4300 50  0001 L CNN
	1    7850 4300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR012
U 1 1 602F0469
P 7550 4400
F 0 "#PWR012" H 7550 4150 50  0001 C CNN
F 1 "GND" V 7550 4250 50  0000 R CNN
F 2 "" H 7550 4400 50  0001 C CNN
F 3 "" H 7550 4400 50  0001 C CNN
	1    7550 4400
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR011
U 1 1 602F15B7
P 7550 3800
F 0 "#PWR011" H 7550 3550 50  0001 C CNN
F 1 "GND" V 7550 3650 50  0000 R CNN
F 2 "" H 7550 3800 50  0001 C CNN
F 3 "" H 7550 3800 50  0001 C CNN
	1    7550 3800
	0    1    1    0   
$EndComp
Wire Wire Line
	7550 3600 7350 3600
Wire Wire Line
	9200 3800 9200 4400
Text Notes 9200 3000 0    50   ~ 0
Pilote
Text Notes 9200 2650 0    50   ~ 0
Phase
$Comp
L Sensor_Temperature:DS18B20 U4
U 1 1 60301FDF
P 3400 2600
F 0 "U4" V 3125 2600 50  0000 C CNN
F 1 "DS18B20" V 3034 2600 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline_Wide" H 2400 2350 50  0001 C CNN
F 3 "http://datasheets.maximintegrated.com/en/ds/DS18B20.pdf" H 3250 2850 50  0001 C CNN
	1    3400 2600
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR013
U 1 1 603082C6
P 3100 2600
F 0 "#PWR013" H 3100 2350 50  0001 C CNN
F 1 "GND" V 3100 2450 50  0000 R CNN
F 2 "" H 3100 2600 50  0001 C CNN
F 3 "" H 3100 2600 50  0001 C CNN
	1    3100 2600
	0    1    1    0   
$EndComp
$Comp
L Device:R R9
U 1 1 6030AEFD
P 3650 3100
F 0 "R9" V 3450 3000 50  0000 L CNN
F 1 "4.7k" V 3550 3000 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3580 3100 50  0001 C CNN
F 3 "~" H 3650 3100 50  0001 C CNN
	1    3650 3100
	0    1    1    0   
$EndComp
$Comp
L Device:C C1
U 1 1 6044D551
P 3650 5000
F 0 "C1" H 3765 5046 50  0000 L CNN
F 1 "470µ 6.3V" H 3765 4955 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 3688 4850 50  0001 C CNN
F 3 "~" H 3650 5000 50  0001 C CNN
F 4 "2805615" H 3650 5000 50  0001 C CNN "Farnell"
	1    3650 5000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR014
U 1 1 6044DEFC
P 3650 5150
F 0 "#PWR014" H 3650 4900 50  0001 C CNN
F 1 "GND" H 3700 5000 50  0000 R CNN
F 2 "" H 3650 5150 50  0001 C CNN
F 3 "" H 3650 5150 50  0001 C CNN
	1    3650 5150
	1    0    0    -1  
$EndComp
Connection ~ 3650 4850
Wire Wire Line
	3150 4850 3650 4850
$Comp
L IRM-10-5:IRM-10-5 U5
U 1 1 607260CE
P 7900 2150
F 0 "U5" H 7900 1783 50  0000 C CNN
F 1 "IRM-10-5" H 7900 1874 50  0000 C CNN
F 2 "perso:IRM-10-5" H 7900 2150 50  0001 L BNN
F 3 "" H 7900 2150 50  0001 L BNN
F 4 "MEANWELL" H 7900 2150 50  0001 L BNN "MANUFACTURER"
F 5 "IPC7251" H 7900 2150 50  0001 L BNN "STANDARD"
	1    7900 2150
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 60729C72
P 7400 2050
F 0 "#PWR0101" H 7400 1800 50  0001 C CNN
F 1 "GND" V 7400 1900 50  0000 R CNN
F 2 "" H 7400 2050 50  0001 C CNN
F 3 "" H 7400 2050 50  0001 C CNN
	1    7400 2050
	0    1    1    0   
$EndComp
Wire Wire Line
	9450 2700 8600 2700
Wire Wire Line
	8600 2700 8600 2250
Wire Wire Line
	8600 2250 8400 2250
Wire Wire Line
	9450 2800 8850 2800
Wire Wire Line
	8850 2800 8850 2050
Wire Wire Line
	8850 2050 8400 2050
Wire Wire Line
	9450 2900 9200 2900
Wire Wire Line
	8600 2700 8600 3600
Connection ~ 8600 2700
Wire Wire Line
	8150 3600 8600 3600
Wire Wire Line
	8150 4200 8600 4200
Connection ~ 9200 3800
$Comp
L zfkds_3:ZFKDS_3 J1
U 1 1 60731CC7
P 9650 2700
F 0 "J1" H 9678 2626 50  0000 L CNN
F 1 "ZFKDS_3" H 9678 2535 50  0000 L CNN
F 2 "perso:ZFKDS_3" H 9650 2700 50  0001 C CNN
F 3 "~" H 9650 2700 50  0001 C CNN
	1    9650 2700
	1    0    0    -1  
$EndComp
Text Notes 9200 2800 0    50   ~ 0
Neutre
Wire Wire Line
	5300 3500 5050 3500
Wire Wire Line
	3150 4550 3450 4550
Wire Wire Line
	4600 3600 5300 3600
NoConn ~ 5300 3000
NoConn ~ 5300 3100
NoConn ~ 5300 3300
NoConn ~ 5300 3700
NoConn ~ 5300 3800
NoConn ~ 5300 3900
NoConn ~ 5300 4000
NoConn ~ 5300 4100
NoConn ~ 6300 4300
NoConn ~ 6300 4200
NoConn ~ 6300 4100
NoConn ~ 6300 4000
NoConn ~ 6300 3900
NoConn ~ 6300 3800
NoConn ~ 6300 3700
NoConn ~ 6300 3400
NoConn ~ 6300 3100
NoConn ~ 6300 3000
NoConn ~ 5900 2600
$Comp
L Diode:1N4007 D1
U 1 1 6097D9D0
P 3650 4400
F 0 "D1" V 3750 4250 50  0000 C CNN
F 1 "1N4007" V 3650 4200 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 3650 4225 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 3650 4400 50  0001 C CNN
	1    3650 4400
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R4
U 1 1 61B902C4
P 3400 4750
F 0 "R4" V 3550 4700 50  0000 L CNN
F 1 "4.7k" V 3650 4700 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3330 4750 50  0001 C CNN
F 3 "~" H 3400 4750 50  0001 C CNN
	1    3400 4750
	0    1    1    0   
$EndComp
Wire Wire Line
	3250 4750 3150 4750
Wire Wire Line
	3550 4750 3650 4750
Connection ~ 3650 4750
Wire Wire Line
	3650 4750 3650 4850
$Comp
L power:GND #PWR01
U 1 1 61B9D747
P 1750 4850
F 0 "#PWR01" H 1750 4600 50  0001 C CNN
F 1 "GND" V 1850 4900 50  0000 R CNN
F 2 "" H 1750 4850 50  0001 C CNN
F 3 "" H 1750 4850 50  0001 C CNN
	1    1750 4850
	0    1    1    0   
$EndComp
$Comp
L Device:R R1
U 1 1 61B9F29E
P 1950 4850
F 0 "R1" V 1750 4800 50  0000 L CNN
F 1 "4.7k" V 1850 4750 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 1880 4850 50  0001 C CNN
F 3 "~" H 1950 4850 50  0001 C CNN
	1    1950 4850
	0    1    1    0   
$EndComp
Wire Wire Line
	1750 4850 1800 4850
Wire Wire Line
	2100 4850 2150 4850
Wire Wire Line
	9200 2900 9200 3800
Wire Wire Line
	8600 3600 8600 4200
Connection ~ 8600 3600
Wire Notes Line
	7800 1200 7800 1700
Wire Notes Line
	7800 2450 7800 3300
Text Notes 7950 1600 0    354  ~ 0
AC
Text Notes 7050 1600 0    354  ~ 0
DC
Wire Notes Line
	7800 4600 7800 5450
Wire Wire Line
	6850 4200 7050 4200
NoConn ~ 6300 3600
NoConn ~ 5300 3200
$Comp
L power:+5V #PWR0102
U 1 1 61BE8D00
P 7400 2250
F 0 "#PWR0102" H 7400 2100 50  0001 C CNN
F 1 "+5V" V 7400 2500 50  0000 C CNN
F 2 "" H 7400 2250 50  0001 C CNN
F 3 "" H 7400 2250 50  0001 C CNN
	1    7400 2250
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR0103
U 1 1 61BEE4AE
P 3650 4150
F 0 "#PWR0103" H 3650 4000 50  0001 C CNN
F 1 "+5V" H 3665 4323 50  0000 C CNN
F 2 "" H 3650 4150 50  0001 C CNN
F 3 "" H 3650 4150 50  0001 C CNN
	1    3650 4150
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0104
U 1 1 61BEF7A1
P 5700 2550
F 0 "#PWR0104" H 5700 2400 50  0001 C CNN
F 1 "+5V" H 5715 2723 50  0000 C CNN
F 2 "" H 5700 2550 50  0001 C CNN
F 3 "" H 5700 2550 50  0001 C CNN
	1    5700 2550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0105
U 1 1 61BF46C1
P 3850 2600
F 0 "#PWR0105" H 3850 2450 50  0001 C CNN
F 1 "+5V" V 3850 2800 50  0000 C CNN
F 2 "" H 3850 2600 50  0001 C CNN
F 3 "" H 3850 2600 50  0001 C CNN
	1    3850 2600
	0    1    1    0   
$EndComp
Wire Wire Line
	3700 2600 3850 2600
$Comp
L power:+5V #PWR0106
U 1 1 61C03066
P 3850 3100
F 0 "#PWR0106" H 3850 2950 50  0001 C CNN
F 1 "+5V" V 3850 3300 50  0000 C CNN
F 2 "" H 3850 3100 50  0001 C CNN
F 3 "" H 3850 3100 50  0001 C CNN
	1    3850 3100
	0    1    1    0   
$EndComp
Wire Wire Line
	3800 3100 3850 3100
Text Label 3400 3500 1    39   ~ 0
Temp_Data
Text Label 4600 3400 0    39   ~ 0
Temp_Data
Wire Wire Line
	4600 3400 5300 3400
Wire Wire Line
	3400 2900 3400 3100
Wire Wire Line
	3500 3100 3400 3100
Connection ~ 3400 3100
Wire Wire Line
	3400 3100 3400 3500
NoConn ~ 6000 2600
Text Label 3450 4550 2    39   ~ 0
TX_GSM
Text Label 3450 4650 2    39   ~ 0
RX_GSM
Text Label 4600 2700 0    39   ~ 0
RX_GSM
Text Label 4600 3600 0    39   ~ 0
TX_GSM
Wire Wire Line
	5050 3050 5050 3500
Text Label 4600 4200 0    39   ~ 0
D12
Text Label 6850 4200 0    39   ~ 0
D12
Wire Wire Line
	6850 3600 7050 3600
Wire Wire Line
	4600 4200 5300 4200
Wire Wire Line
	5300 4300 4600 4300
Text Label 4600 4300 0    39   ~ 0
D13
Text Label 6850 3600 0    39   ~ 0
D13
Text Notes 4600 3700 0    39   ~ 0
A RX µC
Text Notes 4600 2800 0    39   ~ 0
De TX µC
Text Notes 3700 4600 0    50   ~ 0
Tension de chute +5V à +4.4V
Text Notes 8950 7000 0    79   ~ 0
Rev 2 :\n[-] LED alimentation\n[-] LED ON/OFF optocoupleurs\n[+] DTR -> GND\n[+] RST -> +V\nRemise en forme schéma
$EndSCHEMATC
