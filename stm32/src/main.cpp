#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <Wire.h>  
#include "DHT.h"
#include "SparkFun_SGP30_Arduino_Library.h" // Click here to get the library: http://librarymanager/All#SparkFun_SGP30
#include <Wire.h>
#include <SoftwareSerial.h>
#include <BuzzerController.h>
#include <CurtainController.h>
#include <SensorController.h>
#include <MotorController.h>
#include <LEDController.h>
#include <PinConfig.h>
#include <GlobalVar.h>
#include <SlaveChatController.h>
#include <SlaveCurtainController.h>
#include <DHTController.h>
#include <MQController.h>
#include <SGPController.h>
#include <LDRController.h>

String data = "";

void requestEvent()                         
  {
  Wire.write(1);                           
}
 

void receiveEvent(int howMany)
{
  Serial.println("receiveEvent");
  data = "";
  while( Wire.available()){
    data += (char)Wire.read();
    Serial.println(data);
  }
}


void setup()
{
  Serial.begin(9600); 
  Wire.begin(8);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
  
}


void loop()
{
  // 
  // requestEvent()
  // delay(1000);
}
