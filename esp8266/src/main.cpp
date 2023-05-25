#define BLYNK_PRINT Serial
#define NO_GLOBAL_BLYNK true
#include <BlynkSimpleEsp8266.h>
#include <BlynkConfig.h>
#include <BlynkAdapter.h>
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

// SoftwareSerial MasterCurtainController::chat (const chat&);
MasterCurtainController curtainCC(chat);

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
    controller = "buzzer";
    break;
  case CURTAIN:
    controller = "curtain";
    break;
  case LED:
    controller = "led";
    break;
  case SENSOR:
    controller = "sensor";
    break;
  default:
    controller = "unknown";
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

  Serial.printf("\n\n\n\nInitializing NodeMCU\n\n");
  const char *blynkCred[5] = {BLYNK_TEMPLATE_ID, BLYNK_TEMPLATE_NAME, BLYNK_AUTH_TOKEN, BLYNK_SSID, BLYNK_PASS};
  // BlynkConnector blynk(blynkCred, curtainCC);
  Serial.printf("\n\n\n\nInitialized NodeMCU\n\n");
}
int mode = 0;
int count = 0;
void loop()
{
  Serial.printf("Looping %d\n", count);
  count++;
  byte dataBytes[sizeof(float) * 8];
  sendChat(SENSOR, "0", "0", "0");
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

  if (brightness < 2) {
    sendChat(LED, "activate", "0", "0");
  } else {
    sendChat(LED, "deactivate", "0", "0");
  }
  delay(1000);
}