#define DEBUG
#define Pin_MOC_Haut 13     // D13  
#define Pin_MOC_Bas 12      // D12 
#define Pin_Temperature 4   // D4

#include "OneWire.h"	    // capteur température
#include "SoftwareSerial.h"	// SIM800L
#include <EEPROM.h>         // EEPROM sauvegarde mode pilote
#include <avr/wdt.h >	    // watchdog pour reset

#define CONFORT 1   // mode sauvegarde en EE
#define ECO 2       // mode sauvegarde en EE
#define HORS_GEL 3  // mode sauvegarde en EE
#define ARRET 4     // mode sauvegarde en EE

#define GSM_CHECK_INTERVAL 60000    // 60s test connection GSM

#define set_Confort() set_Pilote(0, 0)
#define set_Eco()     set_Pilote(1, 1)
#define set_HorsGel() set_Pilote(1, 0)
#define set_Arret()   set_Pilote(0, 1)

SoftwareSerial Serial_Sim(6, 5);	// pin6 =  D6 = RX, pin5 =  D5 = TX  Arduino Nano
OneWire Temperature(Pin_Temperature);
unsigned char u8_EE_addr = 0;	    // adresse EEPROM u8_mode_pilote du fil pilote  
unsigned long u32_tempsPrecedent = 0;

// structure contenant les infos liées au capteur de température  
struct st_Data_Temp
{
	byte u8_type_capteur;
	byte u8_data[12];
	byte u8_addr[8];
	byte u8_present;
	float f_celsius;
};
st_Data_Temp st_temperature;

// structure contenant les infos liées au module SIM800L  
struct st_Data_Sim
{
	char s8_received;	           // caractère reçu
	String str_gsm_data;	       // concaténation des caractères reçus
	String str_numero_tel;	       // numéro de téléphone (figé pour le moment)
	unsigned char u8_mode_pilote;  // u8_mode_pilote du fil pilote (confort, etc)
};
st_Data_Sim st_gsm;


void setup()
{
	pinMode(Pin_MOC_Haut, OUTPUT);	            // MOC haut 
	pinMode(Pin_MOC_Bas, OUTPUT);	            // MOC bas
    set_Arret();                                // valeur initial (sinon démarre sur confort)
	st_gsm.str_numero_tel = "+33xxxxxxxxx";	    // numéro de téléphone 
    #ifdef DEBUG
        Serial.begin(9600);
        Serial.println("Démarrage programme");
    #endif
	Serial_Sim.begin(9600);
    
    delay(5000);                                // laisse le module démarrer
	Serial_Sim.println("AT");	                // répond OK 
	updateSerial();
    delay(1000);
    Serial_Sim.println("AT+CFUN=0");	        // configure mode avion ON
	updateSerial();
    delay(3000);
    Serial_Sim.println("AT+CFUN=1");	        // configure mode avion OFF
	updateSerial();
    delay(3000);
	Serial_Sim.println("AT+CMGF=1");	        // configure mode TEXT
	updateSerial();
    delay(1000);
	Serial_Sim.println("AT+CNMI=1,2,0,0,0");	// paramètrage réception sms
	updateSerial();
    delay(1000);
    
    #ifdef DEBUG
        Serial_Sim.println("AT+COPS?");         // liste les réseaux disponibles 
        updateSerial();
        delay(1000);
        Serial.println("GSM OK");
    #endif
    
	updateSerial();

	if (!Temperature.search(st_temperature.u8_addr))
	{
        #ifdef DEBUG
            Serial.println("Plus d'adresses.");
            Serial.println();
        #endif
		Temperature.reset_search();
		delay(250);
		return;
	}

	if (OneWire::crc8(st_temperature.u8_addr, 7) != st_temperature.u8_addr[7])
	{
        #ifdef DEBUG
            Serial.println("CRC invalide!");
        #endif
		return;
	}

    #ifdef DEBUG
        Serial.println();
    #endif

	// octet 1 : version du composant 
	switch (st_temperature.u8_addr[0])
	{
		case 0x10: // DS18S20 or old DS1820
			st_temperature.u8_type_capteur = 1;
			break;
		case 0x28: // DS18B20
			st_temperature.u8_type_capteur = 0;
			break;
		case 0x22: // DS1822
			st_temperature.u8_type_capteur = 0;
			break;
		default:
            #ifdef DEBUG
                Serial.println("Composant non reconnu : pas un DS18x20.");
            #endif
			return;
	}

	Temperature.reset();
	Temperature.select(st_temperature.u8_addr);
	Temperature.write(0x44, 1);	// début conversion, parasite power on 
	delay(1000);
	st_temperature.u8_present = Temperature.reset();
    #ifdef DEBUG
        Serial.println("Temperature OK"); 
    #endif

	st_gsm.u8_mode_pilote = EEPROM.read(u8_EE_addr);	// recharge le mode du fil pilote depuis l'eeprom
    switch(st_gsm.u8_mode_pilote)
    {
        case CONFORT:
            set_Confort();
            break;
        case ECO:
            set_Eco();
            break;
        case ARRET:
            set_Arret();
            break;
        case HORS_GEL:
        default:
            set_HorsGel();
            break;
    }
    #ifdef DEBUG
        Serial.println("Initialisation terminée");
    #endif
	updateSerial();
}

/*
 * positionne les 2 sorties qui controlent les optocoupleurs
 */
void set_Pilote(char h, char l)
{
	digitalWrite(Pin_MOC_Haut, h);
	digitalWrite(Pin_MOC_Bas, l);
}

/*
 * acquisition et ecriture de la température dans la variable situé dans la structure
 */
void read_Celsius()
{
	unsigned char i = 0;
	Temperature.reset();
	Temperature.select(st_temperature.u8_addr);
	Temperature.write(0x44, 1);	// début conversion, parasite power on 
	delay(1000);

	st_temperature.u8_present = Temperature.reset();
	Temperature.select(st_temperature.u8_addr);
	Temperature.write(0xBE);	// lire Scratchpad

    #ifdef DEBUG
        Serial.print("  u8_data = ");
        Serial.print(st_temperature.u8_present, HEX);
        Serial.print(" ");
    #endif
	for (i = 0; i < 9; i++) // 9 octets
	{
		st_temperature.u8_data[i] = Temperature.read();
        #ifdef DEBUG
            Serial.print(st_temperature.u8_data[i], HEX);
            Serial.print(" ");
        #endif
	}
    #ifdef DEBUG
        Serial.print(" CRC=");
        Serial.print(OneWire::crc8(st_temperature.u8_data, 8), HEX);
        Serial.println();
    #endif

	// Convertir les données en température
	// résultat 16 bits signées
	int16_t raw = (st_temperature.u8_data[1] << 8) | st_temperature.u8_data[0];
	if (st_temperature.u8_type_capteur)
	{
		raw = raw << 3;	// resolution 9 bits par défault
		if (st_temperature.u8_data[7] == 0x10)
		{
			// "count remain" résolution 12 bit 
			raw = (raw & 0xFFF0) + 12 - st_temperature.u8_data[6];
		}
	}
	else
	{
		byte cfg = (st_temperature.u8_data[4] &0x60);
		// en résolution basse les lsd sont non définie donc on les mets à zéro
		if (cfg == 0x00) raw = raw &~7;	// 9 bits, 93.75 ms
		else if (cfg == 0x20) raw = raw &~3;	// 10 bits, 187.5 ms
		else if (cfg == 0x40) raw = raw &~1;	// 11 bits, 375 ms
		// defaut resolution 12 bit, 750 ms 
	}

	st_temperature.f_celsius = (float) raw / 16.0;
    #ifdef DEBUG
        Serial.print("  Temperature = ");
        Serial.print(st_temperature.f_celsius);
        Serial.print(" f_celsius, ");
        Serial.println("");
    #endif
}

/*
 * SIM800L mode réception
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
 * Envoie la chaine situé dans st_gsm.str_gsm_data au numéro st_gsm.str_numero_tel
 */
void Send_Data()
{
    #ifdef DEBUG
        Serial.println("Envoie des données sms ...");
    #endif
	Serial_Sim.print("AT+CMGF=1\r");	// mode SMS
	delay(100);
	Serial_Sim.print("AT+CMGS=\"" + st_gsm.str_numero_tel + "\"\r");
	delay(500);
	Serial_Sim.print(st_gsm.str_gsm_data);	// envoie le contenu de la variable 
	delay(500);
	Serial_Sim.print((char) 26);	// requis pour confirmer l'envoie
	delay(500);
	Serial_Sim.println();
    #ifdef DEBUG
        Serial.println("Données envoyés.");
    #endif
	delay(500);

}

/*
 * Vérifie si le GSM est actif, sinon on reset le µC pour relancer la recherche de connection
 */
void check_GSM()
{
    String str_recep;
    unsigned char u8_CREG_Index = 0;
    #ifdef DEBUG
        Serial.println("Vérification GSM connecté");
    #endif
    Serial_Sim.println("AT+CREG?");
    delay(1000);

    while (Serial_Sim.available())
  	{
        st_gsm.s8_received = Serial_Sim.read();  // 1 caractère
		str_recep.concat(st_gsm.s8_received);	//on concatène le char à la chaine  
        delay(1); // nécessaire car la liaison uart est 9600 (1ms par caractère)
        #ifdef DEBUG
            Serial.print(st_gsm.s8_received);
        #endif
	}
    
    u8_CREG_Index = str_recep.indexOf(",");
    if (u8_CREG_Index != -1)	// le message reçue est +CREG: x,y
	{
        switch(str_recep.charAt(u8_CREG_Index + 1)) // https://docs.eseye.com/Content/ELS61/ATCommands/ELS61CREG.htm
        {
            /* ok on peut recevoir des SMS */
            case '1' : // Registered to home network.
            case '2' : // Not registered, but the device is currently searching for a new operator. 
            case '5' : // Registered, roaming. The device is registered on a foreign (national or international) network.
                
                break;
                
            /* pas ok on reset le µC */    
            case '0' : // Not registered, the device is currently not searching for new operator.
            case '3' : // Registration denied.
            case '4' : // Unknown. For example, out of range.
            default :
                wdt_enable(WDTO_15MS); // on reset 
				while (1) {}
                #ifdef DEBUG
                    Serial.println("Jamais atteint");
                #endif
                break;
        }
	}
}

/*
 * Réception des données, transfère entre GSM et terminal série
 */
void updateSerial()
{
    #ifdef DEBUG
        while (Serial.available())
        {
            Serial_Sim.write(Serial.read());	// Renvoie ce qui est lu sur la liaison série GSM vers la console
        }
  
        while (Serial_Sim.available())
        {
            Serial.write(Serial_Sim.read());	// Renvoie ce qui est lu sur la liaison série PC vers le GSM (non utilisé)
        }
    #else
        while (Serial_Sim.available())
        {
            Serial_Sim.read();                  // Lire sinon boucle de sms envoyé
        }
    #endif
}

void loop()
{
	String str_rx;	// concaténation des caractères lus par la liaison série
    unsigned long u32_tempsCourant = millis(); // actualise temps
    if(u32_tempsCourant - u32_tempsPrecedent >= GSM_CHECK_INTERVAL) // vérification connection
    {
        u32_tempsPrecedent = u32_tempsCourant;
        check_GSM(); 
    }
    
	while (Serial_Sim.available() > 0)
	{
		st_gsm.s8_received = Serial_Sim.read();	// 1 caractère
        #ifdef DEBUG
            Serial.print(st_gsm.s8_received);
        #endif
		str_rx.concat(st_gsm.s8_received);	// on concatène le char au string
		if (str_rx.indexOf("Temp") != -1)	// le message contient Temp -> on renvoie la température
		{
			read_Celsius();
			st_gsm.str_gsm_data = "Temperature : " + String(st_temperature.f_celsius) + " C";
			Send_Data();
			ReceiveMode();
		}
		else
		{
			if (str_rx.indexOf("Confort") != -1)	// on positionne les optocoupleurs et en renvoie ok
			{
				set_Confort();
				st_gsm.u8_mode_pilote = CONFORT;
				EEPROM.write(u8_EE_addr, st_gsm.u8_mode_pilote);
				st_gsm.str_gsm_data = "OK Confort";
				Send_Data();
				ReceiveMode();
			}
			else
			{
				if (str_rx.indexOf("Arret") != -1)	// on positionne les optocoupleurs et en renvoie ok
				{
					set_Arret();
					st_gsm.u8_mode_pilote = ARRET;
					EEPROM.write(u8_EE_addr, st_gsm.u8_mode_pilote);
					st_gsm.str_gsm_data = "OK Arret";
					Send_Data();
					ReceiveMode();
				}
				else
				{
					if (str_rx.indexOf("Eco") != -1)	// on positionne les optocoupleurs et en renvoie ok
					{
						set_Eco();
						st_gsm.u8_mode_pilote = ECO;
						EEPROM.write(u8_EE_addr, st_gsm.u8_mode_pilote);
						st_gsm.str_gsm_data = "OK Eco";
						Send_Data();
						ReceiveMode();
					}
					else
					{
						if (str_rx.indexOf("Hors") != -1)	// on positionne les optocoupleurs et en renvoie ok
						{
							set_HorsGel();
							st_gsm.u8_mode_pilote = HORS_GEL;
							EEPROM.write(u8_EE_addr, st_gsm.u8_mode_pilote);
							st_gsm.str_gsm_data = "OK Hors gel";
							Send_Data();
							ReceiveMode();
						}
						else
						{
							if (str_rx.indexOf("Mode") != -1)	// on répond à la requete et on envoie le mode actuel
							{
								switch (st_gsm.u8_mode_pilote)
								{
									case ARRET:
										st_gsm.str_gsm_data = "Mode arret";
										break;
									case CONFORT:
										st_gsm.str_gsm_data = "Mode confort";
										break;
									case ECO:
										st_gsm.str_gsm_data = "Mode eco";
										break;
									case HORS_GEL:
										st_gsm.str_gsm_data = "Mode hors gel";
										break;
								}
								Send_Data();
								ReceiveMode();
							}
							else
							{
								if (str_rx.indexOf("Reset") != -1)	// on force le reset de l'arduino
								{
									wdt_enable(WDTO_15MS);
									while (1) {}
                                        #ifdef DEBUG
                                            Serial.println("Jamais atteint");
                                        #endif
								}
								else
								{
									// pas reconnu on ne fait rien !!!  (si tel surtaxé envoie sms)
								}
							}
						}
					}
				}
			}
		}
	}
}
