#define BLYNK_PRINT Serial
#define NO_GLOBAL_BLYNK true
#include <BlynkSimpleEsp8266.h>
#include <BlynkConfig.h>
// #include <BlynkAdapter.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <BlynkConnector.h>
#include <MasterCurtainController.h>

void setup()
{
  Wire.begin();
  Serial.begin(9600);
}

void loop()
{
  Wire.requestFrom(8, 1);
  byte a = Wire.read();
  if (a == 1)
  {
    Serial.println("Master LED ON");
  }
  else
  {
    Serial.println("Master LED OFF");
  }
  Wire.beginTransmission(8);
  Wire.write("Hola");
  Wire.endTransmission();
  delay(1000);
}
