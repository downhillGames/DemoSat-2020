

#include <Wire.h>
#include "SparkFunMPL3115A2.h"

//Create an instance of the object
MPL3115A2 altimeter;

void setup()
{
  Wire.begin();        // Join i2c bus
  Serial.begin(9600);  // Start serial for output

  altimeter.begin(); // Get sensor online



  //Configure the sensor
  altimeter.setModeAltimeter(); // Measure altitude above sea level in meters
  //myPressure.setModeBarometer(); // Measure pressure in Pascals from 20 to 110 kPa

  altimeter.setOversampleRate(7); // Set Oversample to the recommended 128
  altimeter.enableEventFlags(); // Enable all three pressure and temp event flags 

  if (altimeter.readAltitude() < 0 ){
    Serial.println("Failed to communicated with altimeter");
  }
}

void loop()
{
  float altitude = altimeter.readAltitude();
  Serial.print("Altitude(m):");
  Serial.print(altitude, 2);


  Serial.println();
}
