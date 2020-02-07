char connectionBit = 0;

void setup() {
 

  Serial.begin(9600);

  //flip bits 0,3,5,7
  bitSet(connectionBit, 0);
  bitSet(connectionBit, 3);
  bitSet(connectionBit, 5);
  bitSet(connectionBit, 7);

 /*Print out what the bit looks like =]*/
 Serial.println(bitRead(connectionBit, 0));
 Serial.println(bitRead(connectionBit, 1));
 Serial.println(bitRead(connectionBit, 2));
 Serial.println(bitRead(connectionBit, 3));
 Serial.println(bitRead(connectionBit, 4));
 Serial.println(bitRead(connectionBit, 5));
 Serial.println(bitRead(connectionBit, 6));
 Serial.println(bitRead(connectionBit, 7));
 Serial.println(bitRead(connectionBit, 8));
}

void loop() {
  {}// pass
}
