#define BLYNK_PRINT Serial
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include "BlynkAdapter.h"
#include "BlynkConnector.h"
#include "CurtainController.h"
// #include "CurtainController.*"

BlynkConnector::BlynkConnector(CurtainController& acurtainController)
{
  _curtainController = acurtainController;
  // Serial.println("BlynkConnector::BlynkConnector");
  // Serial.println(blynkCred[2]);
  // Serial.println(blynkCred[3]);
  // Serial.println(blynkCred[4]);
  // Blynk.begin(blynkCred[2], blynkCred[3], blynkCred[4]);
  // Serial.println("after BlynkConnector::BlynkConnector");
  // Serial.println(Blynk.connected());
}

void BlynkConnector::SetupBlynk(const char* blynkCred[5])
{
  Serial.println("BlynkConnector::SetupBlynk");
  Serial.println(blynkCred[2]);
  Serial.println(blynkCred[3]);
  Serial.println(blynkCred[4]);
  Blynk.begin(blynkCred[2], blynkCred[3], blynkCred[4]);
  Serial.println("after BlynkConnector::SetupBlynk");
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

void BlynkConnector::SendCO2(double CO2)
{
  Blynk.virtualWrite(V13, CO2);
}

void BlynkConnector::SendTVOC(double TVOC)
{
  Blynk.virtualWrite(V14, TVOC);
}

void BlynkConnector::SendBrightness(int Brightness)
{
  Blynk.virtualWrite(V15, Brightness);
}

void BlynkConnector::SendWindowOpen(bool WindowOpen)
{
  Blynk.virtualWrite(V0, WindowOpen);
}

void BlynkConnector::SendWindowMode(bool WindowMode)
{
  Blynk.virtualWrite(V1, WindowMode);
}

// int BlynkConnector::GetCurtainLevel()
// {
//   return _curtainController.getLevel();
// }

// int BlynkConnector::GetCurtaionMode()
// {
//   return _curtainController.getMode();
// }