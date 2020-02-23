#include "MQ131.h"

//Library found here:
//not actually sure if this will work, we havea MIKROE-2767 
// but on https://www.mikroe.com/ozone-2-click they state that the ozone sensor in the MIKROE-2767 is the MQ131
//so im hoping that library works, so if it doesn't we cry, and and then basically have to figure out what address the Arduino is seeing the 
//ozone sensor at and figure out how to read it in from there:

  //before disnmissing this code as not working for us, try replacing LOW_CONCENTRATION with HIGH_CONCENTRATION int the setup function

//Wiring guide and library located here:
// https://github.com/ostaquet/Arduino-MQ131-driver 


void setup() {
  Serial.begin(9600);

  // Init the sensor
  // - Heater control on pin 2
  // - Sensor analog read on pin A0
  // - Model LOW_CONCENTRATION
  // - Load resistance RL of 10KOhms (10000 Ohms)


  //before disnmissing this code as not working for us, try replacing LOW_CONCENTRATION with HIGH_CONCENTRATION
  MQ131.begin(2,A0, LOW_CONCENTRATION, 10000);  

  Serial.println("Calibration in progress...");
  
  MQ131.calibrate();

  if (MQ131.getR0() < 1){
    Serial.println("Failed to communacate with ozone sensor");
  }
  
  Serial.println("Calibration done!");
  Serial.print("R0 = ");
  Serial.print(MQ131.getR0());
  Serial.println(" Ohms");
  Serial.print("Time to heat = ");
  Serial.print(MQ131.getTimeToRead());
  Serial.println(" s");



  
}

void loop() {
  Serial.println("Sampling...");
  MQ131.sample();
  Serial.print("Concentration O3 : ");
  Serial.print(MQ131.getO3(PPM));
  Serial.println(" ppm");
  Serial.print("Concentration O3 : ");
  Serial.print(MQ131.getO3(PPB));
  Serial.println(" ppb");
  Serial.print("Concentration O3 : ");
  Serial.print(MQ131.getO3(MG_M3));
  Serial.println(" mg/m3");
  Serial.print("Concentration O3 : ");
  Serial.print(MQ131.getO3(UG_M3));
  Serial.println(" ug/m3");

  delay(60000);
}
