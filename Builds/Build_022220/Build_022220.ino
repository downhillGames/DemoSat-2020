    #include <SparkFun_VEML6075_Arduino_Library.h>
    #include <Wire.h>
    #include "SparkFunMPL3115A2.h"

    #define TCAADDR1 0x70  //Multiplexer 1
//Create an instance of the object
MPL3115A2 myPressure;


    VEML6075 uv_1; // Create VEML6075 object 1
    VEML6075 uv_2; // Create VEML6075 object 2
    VEML6075 uv_3; // Create VEML6075 object 3
    VEML6075 uv_4; // Create VEML6075 object 4

    void tcaselect(uint8_t i) {
      if (i > 7) return;
      Wire.beginTransmission(TCAADDR1);
      Wire.write(1 << i);
      Wire.endTransmission();
    }


    void setup(void)
    {
      Serial.begin(9600);

      Wire.begin();
     
       myPressure.begin(); // Get sensor online

      //Configure the sensor
      myPressure.setModeAltimeter(); // Measure altitude above sea level in meters
      //myPressure.setModeBarometer(); // Measure pressure in Pascals from 20 to 110 kPa

      myPressure.setOversampleRate(7); // Set Oversample to the recommended 128
      myPressure.enableEventFlags(); // Enable all three pressure and temp event flags 

      tcaselect(0);
      if(uv_1.begin() != VEML6075_SUCCESS){
        // There was a problem detecting the VEML6075 ... check your connections
       Serial.println("Failed to communicate with VEML6075 sensor 1, check wiring?");
       }
       else if 

      tcaselect(1);
      if(uv_2.begin() != VEML6075_SUCCESS)
      {
        // There was a problem detecting the VEML6075 ... check your connections
       Serial.println("Failed to communicate with VEML6075 sensor 2, check wiring?");
       }

      tcaselect(2);
      if(uv_3.begin() != VEML6075_SUCCESS)
      {
        // There was a problem detecting the VEML6075 ... check your connections
       Serial.println("Failed to communicate with VEML6075 sensor 3, check wiring?");
       }

      tcaselect(3);
      if(uv_4.begin() != VEML6075_SUCCESS)
      {
        // There was a problem detecting the VEML6075 ... check your connections
       Serial.println("Failed to communicate with VEML6075 sensor 4, check wiring?");
       }

     
    }

    void loop(void)
    {
      /*
      tcaselect(0);
      Serial.println(String(uv_1.a()) + ", " + String(uv_1.b()) + ", " +
                String(uv_1.uvComp1()) + ", " + String(uv_1.uvComp2()) + ", " + 
                String(uv_1.index()));
     tcaselect(1);
     Serial.println(String(uv_2.a()) + ", " + String(uv_2.b()) + ", " +
                String(uv_2.uvComp1()) + ", " + String(uv_2.uvComp2()) + ", " + 
                String(uv_2.index()));
     tcaselect(2);
     Serial.println(String(uv_3.a()) + ", " + String(uv_3.b()) + ", " +
                String(uv_3.uvComp1()) + ", " + String(uv_1.uvComp2()) + ", " + 
                String(uv_3.index()));
     tcaselect(3);
     Serial.println(String(uv_4.a()) + ", " + String(uv_4.b()) + ", " +
                String(uv_4.uvComp1()) + ", " + String(uv_4.uvComp2()) + ", " + 
                String(uv_4.index()));
         delay(250);*/

          //float altitude = myPressure.readAltitude();
  //Serial.print("Altitude(m):");
  //Serial.print(altitude, 2);

  float altitude = myPressure.readAltitudeFt();
  Serial.print(" Altitude(ft):");
  Serial.print(altitude, 2);

  //float pressure = myPressure.readPressure();
  //Serial.print("Pressure(Pa):");
  //Serial.print(pressure, 2);

  //float temperature = myPressure.readTemp();
  //Serial.print(" Temp(c):");
  //Serial.print(temperature, 2);

  float temperature = myPressure.readTempF();
  Serial.print(" Temp(f):");
  Serial.print(temperature, 2);

  Serial.println();
    }
