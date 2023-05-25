#define BLYNK_PRINT Serial
#define NO_GLOBAL_BLYNK true
#include <BlynkSimpleEsp8266.h>
#include <BlynkConfig.h>
// #include <BlynkAdapter.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <BlynkConnector.h>
#include <MasterCurtainController.h>

#define STM_RX D5
#define STM_TX D4

#define CURTAIN_RX D6
#define CURTAIN_TX D7

SoftwareSerial chat(D5, D4); // RX, TX
String a;
int curtainLevel, curtainMode;
const char *blynkCred[5] = {BLYNK_TEMPLATE_ID, BLYNK_TEMPLATE_NAME, BLYNK_AUTH_TOKEN, BLYNK_SSID, BLYNK_PASS};

// SoftwareSerial MasterCurtainController::chat (const chat&);
MasterCurtainController curtainCC(chat);
BlynkConnector blynk(curtainCC);

enum Controllers
{
  UNKNOWN = -1,
  BUZZER,
  CURTAIN,
  LED,
  SENSOR
};

void sendChat(Controllers intcontroller, String command, String arg1 = "0", String arg2 = "0")
{
  String controller;
  switch (intcontroller)
  {
  case BUZZER:
    controller = "buzz";
    break;
  case CURTAIN:
    controller = "curt";
    break;
  case LED:
    controller = "ledd";
    break;
  case SENSOR:
    controller = "sens";
    break;
  default:
    controller = "unkn";
    break;
  }
  chat.printf("%s %s %s %s\n", controller.c_str(), command.c_str(), arg1.c_str(), arg2.c_str());
}

float co2, tvoc, temp, humid, co, lpg, smoke, fbrightness;
int brightness;
void setup()
{
  chat.begin(9600);
  Serial.begin(38400);
  blynk.SetupBlynk(blynkCred);
  Serial.printf("\n\n\n\nInitializing NodeMCU\n\n");

  Serial.printf("\n\n\n\nInitialized NodeMCU\n\n");
}
int mode = 0;
int count = 0;
void loop()
{
  Serial.printf("Looping %d\n", count);
  count++;
  byte dataBytes[sizeof(float) * 8];
  sendChat(SENSOR, "0000", "0000", "0000");

  chat.readBytes(dataBytes, sizeof(float) * 8);
  memcpy(&co2, dataBytes, sizeof(float));
  memcpy(&tvoc, dataBytes + sizeof(float), sizeof(float));
  memcpy(&temp, dataBytes + sizeof(float) * 2, sizeof(float));
  memcpy(&humid, dataBytes + sizeof(float) * 3, sizeof(float));
  memcpy(&co, dataBytes + sizeof(float) * 4, sizeof(float));
  memcpy(&lpg, dataBytes + sizeof(float) * 5, sizeof(float));
  memcpy(&smoke, dataBytes + sizeof(float) * 6, sizeof(float));
  memcpy(&fbrightness, dataBytes + sizeof(float) * 7, sizeof(float));
  brightness = (int)fbrightness;
  Serial.printf("CO2: %f | TVOC: %f | Temperature: %f| Humidity: %f | CO: %f | LPG: %f | Smoke: %f | Brightness: %d \n", co2, tvoc, temp, humid, co, lpg, smoke, brightness);
  // if (curtainMode == 1) {
  //   // AUTO CURTAIN LEVEL CALCULATION HERE
  // } else {
  //   curtainCC.setLevel(50);
  // }
  // curtainCC.setLevel(50);
  blynk.SendCO2(co2);
  blynk.SendTVOC(tvoc);
  blynk.SendTemperature(temp);
  blynk.SendHumidity(humid);
  blynk.SendBrightness(brightness);
  if (brightness < 3)
  {
    sendChat(LED, "acti", "0000", "0000");
  }
  else
  {
    sendChat(LED, "deat", "0000", "0000");
  }
  Serial.printf("Level: %d",curtainLevel );

  if (brightness < 3)
  {
    sendChat(BUZZER, "acti", "0000", "0000");
  }
  else
  {
    sendChat(BUZZER, "deat", "0000", "0000");
  }

  delay(1000);
}

BLYNK_WRITE(V0) {
  int curtainMode = param.asInt();
  if (curtainMode == 1) {
    curtainCC.setMode(AUTO);
  } else {
    curtainCC.setMode(MANUAL);
  }
}

BLYNK_WRITE(V1) {
  curtainLevel = param.asInt();
  curtainCC.setLevel(curtainLevel);
}
