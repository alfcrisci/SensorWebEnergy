#include "EmonLib.h"                   // Include Emon Library
EnergyMonitor emon1;                   // Create an instance

void init_sensors(){
  //CT SENSOR
  emon1.current(CT_PIN, 111.1);
  
  
}


//DHT
#include <dht.h>
dht DHT; //dichiaro una variabile globale per la classe del sensore


void readDHT(){

  if(DHT.read22(DHT22_PIN)==0){  //valore di ritorno : 0 -> Lettura andata a buon fine
    _temp = DHT.temperature;
    _hum = DHT.humidity;
  }
  else{    
    check_sensor_error = true;    
  }
}




#define ERROR_VALUE 404

float readTempWater(byte type){
 OneWire ds(type);

 //returns the temperature from one DS18S20 in DEG Celsius
 byte data[12];
 byte addr[8];

 if ( !ds.search(addr)) {
   //no more sensors on chain, reset search
   ds.reset_search();
   //check_sensor_error = true; 
   return ERROR_VALUE;
 }

 if ( OneWire::crc8( addr, 7) != addr[7]) {
   showString(PSTR("CRC is not valid!\n"));
   //check_sensor_error = true; 
   return ERROR_VALUE;
 }

 if ( addr[0] != 0x10 && addr[0] != 0x28) {
   showString(PSTR("Device is not recognized\n"));
   //check_sensor_error = true; 
   return ERROR_VALUE;
 }

 ds.reset();
 ds.select(addr);
 ds.write(0x44,1); // start conversion, with parasite power on at the end

 byte present = ds.reset();
 ds.select(addr);  
 ds.write(0xBE); // Read Scratchpad

 
 for (int i = 0; i < 9; i++) { // we need 9 bytes
  data[i] = ds.read();
 }
 
 ds.reset_search();
 
 byte MSB = data[1];
 byte LSB = data[0];

 float tempRead = ((MSB << 8) | LSB); //using two's compliment
 
 float TemperatureSum = tempRead / 16;

 return TemperatureSum;  
}






float readFlusso(){
   //check_sensor_error = true; 
   return ERROR_VALUE;
}






SoftwareSerial sonar(RS232_SONAR, 10, true);

float readSonar_data(){  
  sonar.begin(9600);
  delay(250);
  delay(150);

  char *buffer;
  char x;
  char array[3];  
  float inch, cm;
  
  while(sonar.available())
  {
     x = sonar.read();//Bytes(buffer,1);
     if(x=='R'){ 
       x= sonar.read();//Bytes(buffer,1);       
       array[0]=x; 
       x= sonar.read();//Bytes(buffer,1);       
       array[1]=x;//*buffer; 
       x= sonar.read();//Bytes(buffer,1);       
       array[2]=x;//*buffer;
     }     
  }  
  
  inch = (array[0]-48)*100 + (array[1]-48)*10 +(array[2]-48) ;
  cm = inch*2.54;
  
  return cm*(0.42); 
}





void readSonar(){
  byte camp = 10;
  for(int i=0; i<camp; i++)
    _sonar += readSonar_data();
  _sonar /= camp;

  if(_sonar<0) 
    check_sensor_error = true; 
  //Serial.println(_sonar);
}







void readEnergy(){
  double Irms = emon1.calcIrms(1480);  // Calculate Irms only
  
  _power = Irms*sqrt(2);
}






bool vanoCeneriAperto(){
  if(digitalRead(CENERI)==HIGH)
    return true;
  else
    return false;
}




bool vanoCaldaiaAperto(){
  if(digitalRead(CALDAIA)==HIGH)
    return true;
  else
    return false;
}


