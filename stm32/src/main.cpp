#include <Arduino.h>
#include <Wire.h>  

#define SLAVE_ADDRESS 0x08

// TwoWire Wire1(PB_9, PB_8); // I2C1 SDA, SCL D14, D15
TwoWire Wire2(PB3, PB10);
// TwoWire Wire2(PB_3, PB_10); // I2C2 SDA, SCL D6, D3
String data = "";

void requestEvent()                         
  {
  Serial.println("requestEvent");
  Wire2.write(1);                           
}
 

void receiveEvent(int howMany)
{
  Serial.println("receiveEvent");
  data = "";
  while( Wire2.available()){
    data += (char)Wire2.read();
    Serial.println(data);
  }
}


void setup()
{
  Serial.begin(9600); 
  Wire2.begin(SLAVE_ADDRESS);
  Wire2.onRequest(requestEvent);
  Wire2.onReceive(receiveEvent);
  
}


void loop()
{
  // 
  // requestEvent()
  // delay(1000);
  Serial.println("loop");
  delay(1000);
}
