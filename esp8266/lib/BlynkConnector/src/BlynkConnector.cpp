#define BLYNK_PRINT Serial
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include "BlynkAdapter.h"
#include "BlynkConnector.h"
#include "CurtainController.h"
// #include "CurtainController.*"

BlynkConnector::BlynkConnector(const char* blynkCred[5], CurtainController& acurtainController)
{
  _curtainController = acurtainController;
  Blynk.begin(blynkCred[2], blynkCred[3], blynkCred[4]);
  Serial.println(Blynk.connected());
}

void BlynkConnector::SendHumidity(double Humidity)
{
  Blynk.virtualWrite(V11, Humidity);
}

void BlynkConnector::SendTemperature(double Temperature)
{
  Blynk.virtualWrite(V12, Temperature);
}
