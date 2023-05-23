
#include "Arduino.h"
#include <BlynkCredential.h>
#include <ESP8266WiFi.h>
#include "BlynkAdapter.h"
#include "BlynkConnector.h"
#include "CurtainController.h"
// #include "CurtainController.*"

BlynkConnector::BlynkConnector(CurtainController acurtainController)
{
  _curtainController = acurtainController;
  Blynk.begin(BLYNK_AUTH_TOKEN, BLYNK_SSID, BLYNK_PASS);
}

void BlynkConnector::SendHumidity(double Humidity)
{
  Blynk.virtualWrite(V11, Humidity);
}

void BlynkConnector::SendTemperature(double Temperature)
{
  Blynk.virtualWrite(V12, Temperature);
}
