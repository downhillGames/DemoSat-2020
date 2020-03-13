#include <SparkFun_VEML6075_Arduino_Library.h>
#include <Wire.h>
#include "SparkFunMPL3115A2.h"



//#define TCAADDR1 0x70  //Multiplexer 1

// bit 0 - sd card (if we can get that)
// bit 1 - uv sensor 1
// bit 2 - uv sensor 2
// bit 3 - uv sensor 3
// bit 4 - uv sensor 4
// bit 5 - altimeter
// bit 6 - ozone sensor
// bit 7 - temp sensor

// Chip Select pin is tied to pin 8 on the SparkFun SD Card Shield
//const int chipSelect = 8;  

char connectionBit = 0;
    
//Create an instance altimeter
MPL3115A2 altimeter;

VEML6075 uv_1; // Create VEML6075 object 1 (uv sensor 1)
VEML6075 uv_2; // Create VEML6075 object 2 (uv sensor 2)
VEML6075 uv_3; // Create VEML6075 object 3 (uv sensor 3)
VEML6075 uv_4; // Create VEML6075 object 4 (uv sensor 4)

/*Selects the channel on the multiplexor (starts at 0)*/
void tcaselect(uint8_t i) {
    if (i > 7) return;
    Wire.beginTransmission(0x70);
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
}

void loop(void){

    //if uv sensor 1 is detected
    if (bitRead(connectionBit, 1) == 1 ){
        tcaselect(0);
        Serial.print("UV_1_A " + String(uv_1.a()) + ",UV_1_B " + String(uv_1.b()) + ",UV_1_COMP1 " + String(uv_1.uvComp1()) + ",UV_1_COMP2, " + String(uv_1.uvComp2()) + ",UV_1_INDEX " + String(uv_1.index()) + ",");

    }

   //if uv sensor 2 is detected
    if (bitRead(connectionBit, 2) == 1 ){
        tcaselect(1);
        Serial.print("UV_2_A " + String(uv_2.a()) + ",UV_2_B " + String(uv_2.b()) + ",UV_2_COMP1 " + String(uv_2.uvComp1()) + ",UV_2_COMP2, " + String(uv_2.uvComp2()) + ",UV_2_INDEX " + String(uv_2.index()) + ",");

    }

    //if uv sensor 3 is detected
    if (bitRead(connectionBit, 3) == 1 ){
        tcaselect(2);
        Serial.print("UV_3_A " + String(uv_3.a()) + ",UV_3_B " + String(uv_3.b()) + ",UV_3_COMP1 " + String(uv_3.uvComp1()) + ",UV_3_COMP2, " + String(uv_3.uvComp2()) + ",UV_3_INDEX " + String(uv_3.index()) + ",");

    }

    
    //if uv sensor 4 is detected
    if (bitRead(connectionBit, 4) == 1 ){
        tcaselect(3);
        Serial.print("UV_4_A " + String(uv_4.a()) + ",UV_4_B " + String(uv_4.b()) + ",UV_4_COMP1 " + String(uv_4.uvComp1()) + ",UV_4_COMP2, " + String(uv_4.uvComp2()) + ",UV_4_INDEX " + String(uv_4.index()) + ",");
        
    }

    //if altimeter is detected
    if (bitRead(connectionBit, 5) == 1 ){
        float altitude = altimeter.readAltitude();
        Serial.print("Altitude");
        Serial.print(altitude, 2);
        Serial.print(", ");
    }

     //if altimeter is detected
    if (bitRead(connectionBit, 5) == 1 ){
        float temperature = altimeter.readTempF();
        Serial.print("Temp");
        Serial.print(temperature, 2);
        Serial.print(", ");
    }

    Serial.print(millis() / 1000);
    Serial.print("\r");
    delay(500); //delay 500
    


}
