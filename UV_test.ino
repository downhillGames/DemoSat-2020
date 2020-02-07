#include <SPI.h>
#include <SdFat.h>
#include <SparkFun_VEML6075_Arduino_Library.h>


VEML6075 uv_1; // Create VEML6075 object 1
VEML6075 uv_2; // Create VEML6075 object 2
VEML6075 uv_3; // Create VEML6075 object 3
VEML6075 uv_4; // Create VEML6075 object 4



/*TO GET THIS CODE TO COMPILE:*/

/*In order for this code to compile correctly on your computer, you must have the SparkFun VEML6075 library installed into the IDE (this software)
Intalling is really easy download the zip file located here: https://www.sparkfun.com/products/15089, then go to the top of ths software, click 'Sketch',
then click 'include library' then click 'Add .zip library', it will pop up a navigation menu, navigate to the file you just downloaded and click okay. 
That should be it. Of course, just text me if you have any questions about this code!!!*/


/*This function configures the UV sensors to the various Wires that we have available*/
void configureUV(){
  
  /*The if statements below is where you will have to edit the code. I will paste below sparkfuns comments about multiple wires, the only thing I could not figure out is what all the 
  wires names were, if you can't figure it out, we'll just have to do more research on the extension board that we bought and what the Wire variables names are. Anyway, sorry for the rant, 
  just change the variable 'Wire' to our various wires and upload to arduino, youll need the library installed onto your computer to compile this code. */


  // The begin function can take a TwoWire port as a parameter -- in case your platform has more than the one standard "Wire" port.
  if (uv_1.begin(Wire) != VEML6075_SUCCESS) {
    Serial.println("Unable to communicate with VEML6075 1");
  }
  if (uv_2.begin(Wire) != VEML6075_SUCCESS) {
    Serial.println("Unable to communicate with VEML6075 2");
  }
  if (uv_3.begin(Wire) != VEML6075_SUCCESS) {
    Serial.println("Unable to communicate with VEML6075 3");
  }
  if (uv_4.begin(Wire) != VEML6075_SUCCESS) {
    Serial.println("Unable to communicate with VEML6075 4");
  }
  
}

/*No need to mess with, refer to configureUV above, all we do here is configure the Serial monitor and then trigger the configureUV function*/
void setup() {
     Serial.begin(9600);
     configureUV();
 
}


/*the delay line at the end is basically how often this function is called, as it is set currently we call this function and print out the UVI of each sensor we have connected 
you should not have to mess with this at all*/
void loop() { 
  Serial.print("UV Sensor 1 UVI ");
  Serial.println(returnUVI(uv_1));
  Serial.print("UV Sensor 2 UVI ");
  Serial.println(returnUVI(uv_2));
  Serial.print("UV Sensor 3 UVI ");
  Serial.println(returnUVI(uv_3));
  Serial.print("UV Sensor 4 UVI ");
  Serial.println(returnUVI(uv_4));

  delay(1000); //1 second delay 
}


/*This function takes in a VEML6075 object and returns a double value with calculated UVI*/
double returnUVI(VEML6075 uv_obj){
  return uv_obj.index();
}
