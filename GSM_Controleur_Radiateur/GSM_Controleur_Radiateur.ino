#define Pin_Pilote_High 13 /* D13 */
#define Pin_Pilote_Low  12 /* D12 */
#define Pin_Temperature 4  /* D4  */

#include "OneWire.h"
#include "SoftwareSerial.h"

SoftwareSerial Serial_Sim(6,5); // pin6 =  D6 = RX, pin5 =  D5 = TX
OneWire  Temperature(Pin_Temperature);  
  
byte type_s;
byte data[12];
byte addr[8];
byte present = 0;
float celsius;
char sms_text[128];
int sms_text_index = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(Pin_Pilote_High, OUTPUT);
  pinMode(Pin_Pilote_Low, OUTPUT);
  //delay(7000);
  Serial.begin(9600);
  Serial_Sim.begin(9600);
  delay(1000);
  Serial_Sim.println("AT");
  updateSerial();
  Serial.println("Initialisation terminée");
  updateSerial();

  Serial_Sim.println("AT+CMGF=1"); // configure TEXT mode
  updateSerial();
  Serial_Sim.println("AT+CNMI=1,2,0,0,0");
  updateSerial();

  if ( !Temperature.search(addr)) {
    Serial.println("No more addresses.");
    Serial.println();
    Temperature.reset_search();
    delay(250);
    return;
  }
  Serial.print("ROM =");
  for(int i = 0; i < 8; i++) {
    Serial.write(' ');
    Serial.print(addr[i], HEX);
  }

  if (OneWire::crc8(addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return;
  }
  Serial.println();
 
  // the first ROM byte indicates which chip
  switch (addr[0]) {
    case 0x10:
      Serial.println("  Chip = DS18S20");  // or old DS1820
      type_s = 1;
      break;
    case 0x28:
      Serial.println("  Chip = DS18B20");
      type_s = 0;
      break;
    case 0x22:
      Serial.println("  Chip = DS1822");
      type_s = 0;
      break;
    default:
      Serial.println("Device is not a DS18x20 family device.");
      return;
  } 

  Temperature.reset();
  Temperature.select(addr);
  Temperature.write(0x44, 1);        // start conversion, with parasite power on at the end
  
  delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
  present = Temperature.reset();

}

void read_Celsius(){
  int i;
  Temperature.reset();
  Temperature.select(addr);
  Temperature.write(0x44, 1);        // start conversion, with parasite power on at the end
  
  delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
  
  present = Temperature.reset();
  Temperature.select(addr);    
  Temperature.write(0xBE);         // Read Scratchpad

  Serial.print("  Data = ");
  Serial.print(present, HEX);
  Serial.print(" ");
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = Temperature.read();
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.print(" CRC=");
  Serial.print(OneWire::crc8(data, 8), HEX);
  Serial.println();

  // Convert the data to actual temperature
  // because the result is a 16 bit signed integer, it should
  // be stored to an "int16_t" type, which is always 16 bits
  // even when compiled on a 32 bit processor.
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  celsius = (float)raw / 16.0;
  Serial.print("  Temperature = ");
  Serial.print(celsius);
  Serial.print(" Celsius, ");
  Serial.println("");
}

void updateSerial()
{
  char c;
  delay(1000);
  while (Serial.available()) 
  {
    Serial_Sim.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(Serial_Sim.available()) 
  {
    c = Serial_Sim.read();
    Serial.write(c);//Forward what Software Serial received to Serial Port
    if(c == '+')
    {
      for(int i =0; i < 128; i++)sms_text[i]=0;
    }
    sms_text[sms_text_index] = c;
  }
}

void loop() {
  updateSerial();
}
