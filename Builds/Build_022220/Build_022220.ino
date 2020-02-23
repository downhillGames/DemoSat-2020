#include <SparkFun_VEML6075_Arduino_Library.h>
#include <Wire.h>
#include "SparkFunMPL3115A2.h"
#include "MQ131.h"

#define TCAADDR1 0x70  //Multiplexer 1

// bit 0 - sd card (if we can get that)
// bit 1 - uv sensor 1
// bit 2 - uv sensor 2
// bit 3 - uv sensor 3
// bit 4 - uv sensor 4
// bit 5 - altimeter
// bit 6 - ozone sensor
// bit 7 - temp sensor
char connectionBit = 0;
int count = 1;
//Create an instance altimeter
MPL3115A2 altimeter;

VEML6075 uv_1; // Create VEML6075 object 1 (uv sensor 1)
VEML6075 uv_2; // Create VEML6075 object 2 (uv sensor 2)
VEML6075 uv_3; // Create VEML6075 object 3 (uv sensor 3)
VEML6075 uv_4; // Create VEML6075 object 4 (uv sensor 4)

/*Selects the channel on the multiplexor (starts at 0)*/
void tcaselect(uint8_t i) {
    if (i > 7) return;
    Wire.beginTransmission(TCAADDR1);
    Wire.write(1 << i);
    Wire.endTransmission();
}

void connectAltimeter(){
    altimeter.begin(); // Get sensor online
        
    //Configure the sensor
    altimeter.setModeAltimeter(); // Measure altitude above sea level in meters
    //myPressure.setModeBarometer(); // Measure pressure in Pascals from 20 to 110 kPa
        
    altimeter.setOversampleRate(7); // Set Oversample to the recommended 128
    altimeter.enableEventFlags(); // Enable all three pressure and temp event flags 
        
    float altitude = altimeter.readAltitudeFt();
        
    if (altitude > 0){
        bitSet(connectionBit, 5);
    }
}    
    

void connectOzoneSensor(){

    MQ131.begin(2,A0, LOW_CONCENTRATION, 10000);  
  
    Serial.println("Calibration in progress...");
    
    MQ131.calibrate();
  
    if (MQ131.getR0() < 1){
        Serial.println("Failed to communacate with ozone sensor");
    }
    else{
      bitSet(connectionBit, 6);
    }
}

    
void connectUVSensors(){
    
    tcaselect(0);
    if(uv_1.begin() != VEML6075_SUCCESS){
        // There was a problem detecting the VEML6075 ... check your connections
        Serial.println("Failed to communicate with VEML6075 sensor 1, check wiring?");
    }
    else if (uv_1.begin() == VEML6075_SUCCESS){
        // we connected to VEML6075 sensor 1
        bitSet(connectionBit, 1);
    }
    
    tcaselect(1);
    if(uv_2.begin() != VEML6075_SUCCESS){
        // There was a problem detecting the VEML6075 ... check your connections
        Serial.println("Failed to communicate with VEML6075 sensor 2, check wiring?");
    }
    else if (uv_2.begin() == VEML6075_SUCCESS){
        // we connected to VEML6075 sensor 2
        bitSet(connectionBit, 2);
    }
        
        
    tcaselect(2);
    if(uv_3.begin() != VEML6075_SUCCESS){
        // There was a problem detecting the VEML6075 ... check your connections
        Serial.println("Failed to communicate with VEML6075 sensor 3, check wiring?");
    }
    else if (uv_3.begin() == VEML6075_SUCCESS){
        // we connected to VEML6075 sensor 3
        bitSet(connectionBit, 3);
    }
        
    tcaselect(3);
    if(uv_4.begin() != VEML6075_SUCCESS){
        // There was a problem detecting the VEML6075 ... check your connections
        Serial.println("Failed to communicate with VEML6075 sensor 4, check wiring?");
    }
    else if (uv_4.begin() == VEML6075_SUCCESS){
        // we connected to VEML6075 sensor 4
        bitSet(connectionBit, 4);
    }
    
    
}

void setup(void)
{
    Serial.begin(9600);
    
    Wire.begin();
        
    connectUVSensors();
    connectAltimeter();
    connectOzoneSensor();

    //Serial.print("UV_1_A, UV_1_B, UV_1_COMP_1, UV_1_COMP_2, UV_1_INDEX, ");
    //Serial.print("UV_2_A, UV_2_B, UV_2_COMP_1, UV_2_COMP_2, UV_2_INDEX, " );
    //Serial.print("UV_2_A, UV_2_B, UV_2_COMP_1, UV_2_COMP_2, UV_2_INDEX, " );
    //Serial.print("UV_3_A, UV_3_B, UV_3_COMP_1, UV_3_COMP_2, UV_3_INDEX, " );
    //Serial.print("UV_4_A, UV_4_B, UV_4_COMP_4, UV_4_COMP_4, UV_4_INDEX, " );
    //Serial.print("ALTITUDE, OZONE, TEMP, TIMESTAMP " );  
}




void printUV(int sensor){

  if (sensor == 1){
     Serial.print("uv_1_a "+ String(uv_1.a()) + ", " + "uv_1_b " + String(uv_1.b()) + ", " + "uv_1_comp1 " + String(uv_1.uvComp1()) + ", " + "uv_1_comp2 " + String(uv_1.uvComp2()) + ", " + "uv_1_index" + String(uv_1.index()) + ", ");
  }
  else if (sensor == 2){
     Serial.print("uv_2_a "+ String(uv_2.a()) + ", " + "uv_2_b " + String(uv_2.b()) + ", " + "uv_2_comp1 " + String(uv_2.uvComp1()) + ", " + "uv_2_comp2 " + String(uv_2.uvComp2()) + ", " + "uv_2_index" + String(uv_2.index()) + ", ");
  }
  else if (sensor == 3){
     Serial.print("uv_3_a "+ String(uv_3.a()) + ", " + "uv_3_b " + String(uv_3.b()) + ", " + "uv_3_comp1 " + String(uv_3.uvComp1()) + ", " + "uv_3_comp2 " + String(uv_3.uvComp2()) + ", " + "uv_3_index" + String(uv_3.index()) + ", ");
  }
  else if (sensor == 4){
    Serial.print("uv_4_a "+ String(uv_4.a()) + ", " + "uv_4_b " + String(uv_4.b()) + ", " + "uv_4_comp1 " + String(uv_4.uvComp1()) + ", " + "uv_4_comp2 " + String(uv_4.uvComp2()) + ", " + "uv_4_index" + String(uv_4.index()) + ", ");
  }
}


void loop(void){

    //trigger everything every 10 m in altitude - comment out the if statement and the final ending curly brace if you just want to record every half second (or be time based)
    if (int (altimeter.readAltitude()) %  10 == 0)
    {

        Serial.print("COUNT ");
        Serial.print(++count);
        //count++;
        Serial.println(", ");
        
         //if uv sensor 1 is detected
        if (bitRead(connectionBit, 1) == 1){
            tcaselect(0);
            printUV(1);
        }
    
       //if uv sensor 2 is detected
        if (bitRead(connectionBit, 2) == 1){
            tcaselect(1);
            printUV(2);
        }
    
        //if uv sensor 3 is detected
        if (bitRead(connectionBit, 3) == 1){
            tcaselect(2);
            printUV(3);
        }
    
        
        //if uv sensor 4 is detected
        if (bitRead(connectionBit, 4) == 1){
            tcaselect(3);
            printUV(4);
        }
    
        //if altimeter is detected
        if (bitRead(connectionBit, 5) == 1){
            float altitude = altimeter.readAltitude();
            Serial.print("Alt ");
            Serial.print(altitude, 2);
            Serial.print(", ");
        }
    
        //if ozone sensor is detected
        if (bitRead(connectionBit, 6) == 1){
            MQ131.sample();
            Serial.print("CO3 ");
            Serial.print(MQ131.getO3(PPM));
            Serial.print(", ");
        }

        //TODO
        //if temp sensor is detected 
        if (bitRead(connectionBit, 7) == 1){
            Serial.print("TEMP ");
            Serial.print(", ");
        
        }

        Serial.print("TIME ");
        Serial.print(millis() / 1000);
        Serial.println(", ");
   
    
    
    } // this is this '} ' that you want to comment out - just put // in front of it
   
             
    delay(500); //delay 500 milliseconds
    


}
