#define Pin_Pilote_High 13 /*D13 */ 
#define Pin_Pilote_Low 12 /*D12 */ 
#define Pin_Temperature 4 /*D4  */

#include "OneWire.h"	// capteur température
#include "SoftwareSerial.h"	// SIM800L
#include <EEPROM.h>
#include <avr/wdt.h >	// watchdog pour reset

SoftwareSerial Serial_Sim(6, 5);	// pin6 =  D6 = RX, pin5 =  D5 = TX  Arduino Nano
OneWire Temperature(Pin_Temperature);

// structure contenant les infos liées au capteur de température  
struct st_Data_Temp
{
	byte type_s;
	byte data[12];
	byte addr[8];
	byte present;
	float celsius;
};
st_Data_Temp data_temp;

#define CONFORT 1
#define ECO 2
#define HORS_GEL 3
#define ARRET 4
// structure contenant les infos liées au module SIM800L  
struct st_Data_Sim
{
	char received;	// caractère reçu
	String sms_data;	// concaténation des caractères reçus
	String phone_number;	// numéro de téléphone (figé pour le moment)
	int mode;	// mode du fil pilote (confort, etc)
};
st_Data_Sim data_sim;

int EE_addr = 0;	// adresse EEPROM mode du fil pilote  

void setup()
{
	pinMode(Pin_Pilote_High, OUTPUT);	// controle MOC haut 
	pinMode(Pin_Pilote_Low, OUTPUT);	// controle MOC bas

	data_sim.phone_number = "+33xxxxxxxxx";	// numéro de téléphone 

	Serial.begin(9600);
	Serial_Sim.begin(9600);

	delay(1000);
	Serial_Sim.println("AT");	// répond OK 
	updateSerial();

	Serial_Sim.println("AT+CMGF=1");	// configure mode TEXT
	updateSerial();
	Serial_Sim.println("AT+CNMI=1,2,0,0,0");	// paramètrage réception sms
	updateSerial();

	Serial.println("GSM OK");
	updateSerial();

	if (!Temperature.search(data_temp.addr))
	{
		Serial.println("Plus d'adresses.");
		Serial.println();
		Temperature.reset_search();
		delay(250);
		return;
	}

	if (OneWire::crc8(data_temp.addr, 7) != data_temp.addr[7])
	{
		Serial.println("CRC invalide!");
		return;
	}

	Serial.println();

	// octet 1 : version du composant 
	switch (data_temp.addr[0])
	{
		case 0x10:
			//Serial.println("  Chip = DS18S20"); 	// or old DS1820
			data_temp.type_s = 1;
			break;
		case 0x28:
			//Serial.println("  Chip = DS18B20");
			data_temp.type_s = 0;
			break;
		case 0x22:
			//Serial.println("  Chip = DS1822");
			data_temp.type_s = 0;
			break;
		default:
			Serial.println("Composant non reconnu : pas un DS18x20.");
			return;
	}

	Temperature.reset();
	Temperature.select(data_temp.addr);
	Temperature.write(0x44, 1);	// début conversion, parasite power on 
	delay(1000);
	data_temp.present = Temperature.reset();

	Serial.println("Temperature OK");

	data_sim.mode = EEPROM.read(EE_addr);	// recharge le mode du fil pilote depuis l'eeprom

	Serial.println("Initialisation terminée");
	updateSerial();
}
#define set_Confort() set_Pilote(0, 0)
#define set_Eco() set_Pilote(1, 1)
#define set_HorsGel() set_Pilote(0, 1)
#define set_Arret() set_Pilote(1, 0)

/*
 *positionne les 2 sorties qui controlent les optocoupleurs
 */
void set_Pilote(char h, char l)
{
	digitalWrite(Pin_Pilote_High, h);
	digitalWrite(Pin_Pilote_Low, l);
}

/*
 *acquisition et ecriture de la température dans la variable situé dans la structure
 */
void read_Celsius()
{
	int i;
	Temperature.reset();
	Temperature.select(data_temp.addr);
	Temperature.write(0x44, 1);	// début conversion, parasite power on 
	delay(1000);

	data_temp.present = Temperature.reset();
	Temperature.select(data_temp.addr);
	Temperature.write(0xBE);	// Lire Scratchpad

	Serial.print("  Data = ");
	Serial.print(data_temp.present, HEX);
	Serial.print(" ");
	for (i = 0; i < 9; i++) // 9 octets
	{
		data_temp.data[i] = Temperature.read();
		Serial.print(data_temp.data[i], HEX);
		Serial.print(" ");
	}

	Serial.print(" CRC=");
	Serial.print(OneWire::crc8(data_temp.data, 8), HEX);
	Serial.println();

	// Convertir les données en température
	// résultat 16 bits signées
	int16_t raw = (data_temp.data[1] << 8) | data_temp.data[0];
	if (data_temp.type_s)
	{
		raw = raw << 3;	// resolution 9 bits par défault
		if (data_temp.data[7] == 0x10)
		{
			// "count remain" résolution 12 bit 
			raw = (raw & 0xFFF0) + 12 - data_temp.data[6];
		}
	}
	else
	{
		byte cfg = (data_temp.data[4] &0x60);
		// en résolution basse les lsd sont non définie donc on les mets à zéro
		if (cfg == 0x00) raw = raw &~7;	// 9 bits, 93.75 ms
		else if (cfg == 0x20) raw = raw &~3;	// 10 bits, 187.5 ms
		else if (cfg == 0x40) raw = raw &~1;	// 11 bits, 375 ms
		//// defaut resolution 12 bit, 750 ms 
	}

	data_temp.celsius = (float) raw / 16.0;
	Serial.print("  Temperature = ");
	Serial.print(data_temp.celsius);
	Serial.print(" Celsius, ");
	Serial.println("");
}

/*
 *SIM800L mode réception
 */
void ReceiveMode()
{
	Serial_Sim.println("AT");	//répond "OK"
	updateSerial();
	Serial_Sim.println("AT+CMGF=1");	// Configurer mode TEXT 
	updateSerial();
	Serial_Sim.println("AT+CNMI=2,2,0,0,0");	// paramètrage réception sms
	updateSerial();
}

/*
 *Envoie la chaine situé dans data_sim.sms_data au numéro data_sim.phone_number
 */
void Send_Data()
{
	Serial.println("Envoie des données sms ...");
	Serial_Sim.print("AT+CMGF=1\r");	// mode SMS
	delay(100);
	Serial_Sim.print("AT+CMGS=\"" + data_sim.phone_number + "\"\r");
	delay(500);
	Serial_Sim.print(data_sim.sms_data);	// envoie le contenu de la variable 
	delay(500);
	Serial_Sim.print((char) 26);	// requis pour confirmer l'envoie
	delay(500);
	Serial_Sim.println();
	Serial.println("Données envoyés.");
	delay(500);

}

void updateSerial()
{
	while (Serial.available())
	{
		Serial_Sim.write(Serial.read());	//Renvoie ce qui est lu sur la liaison série GSM vers la console
	}

	while (Serial_Sim.available())
	{
		Serial.write(Serial_Sim.read());	//Renvoie ce qui est lu sur la liaison série PC vers le GSM (non utilisé)
	}
}

void loop()
{
	String rx_full;	// concaténation des caractères lus par la liaison série
	while (Serial_Sim.available() > 0)
	{
		data_sim.received = Serial_Sim.read();	//1 caractère
		Serial.print(data_sim.received);
		rx_full.concat(data_sim.received);	//on concatène le char au string
		if (rx_full.indexOf("Temp") != -1)	// le message contient Temp -> on renvoie la température
		{
			read_Celsius();
			data_sim.sms_data = "Temperature : " + String(data_temp.celsius) + " C";
			Send_Data();
			ReceiveMode();
		}
		else
		{
			if (rx_full.indexOf("Confort") != -1)	//  on positionne les optocoupleurs et en renvoie ok
			{
				set_Confort();
				data_sim.mode = CONFORT;
				EEPROM.write(EE_addr, data_sim.mode);
				data_sim.sms_data = "OK Confort";
				Send_Data();
				ReceiveMode();
			}
			else
			{
				if (rx_full.indexOf("Arret") != -1)	// on positionne les optocoupleurs et en renvoie ok
				{
					set_Arret();
					data_sim.mode = ARRET;
					EEPROM.write(EE_addr, data_sim.mode);
					data_sim.sms_data = "OK Arret";
					Send_Data();
					ReceiveMode();
				}
				else
				{
					if (rx_full.indexOf("Eco") != -1)	// on positionne les optocoupleurs et en renvoie ok
					{
						set_Eco();
						data_sim.mode = ECO;
						EEPROM.write(EE_addr, data_sim.mode);
						data_sim.sms_data = "OK Eco";
						Send_Data();
						ReceiveMode();
					}
					else
					{
						if (rx_full.indexOf("Hors") != -1)	// on positionne les optocoupleurs et en renvoie ok
						{
							set_HorsGel();
							data_sim.mode = HORS_GEL;
							EEPROM.write(EE_addr, data_sim.mode);
							data_sim.sms_data = "OK Hors gel";
							Send_Data();
							ReceiveMode();
						}
						else
						{
							if (rx_full.indexOf("Mode") != -1)	// on répond à la requete et on envoie le mode actuel
							{
								switch (data_sim.mode)
								{
									case ARRET:
										data_sim.sms_data = "Mode arret";
										break;
									case CONFORT:
										data_sim.sms_data = "Mode confort";
										break;
									case ECO:
										data_sim.sms_data = "Mode eco";
										break;
									case HORS_GEL:
										data_sim.sms_data = "Mode hors gel";
										break;
								}

								Send_Data();
								ReceiveMode();
							}
							else
							{
								if (rx_full.indexOf("Reset") != -1)	// on force le reset de l'arduino
								{
									wdt_enable(WDTO_15MS);
									while (1) {}

									Serial.println("Jamais atteint");
								}
								else
								{
									// pas reconnu on ne fait rien !!!  (si tel surtaxé envoie sms ???)
								}
							}
						}
					}
				}
			}
		}
	}
}
