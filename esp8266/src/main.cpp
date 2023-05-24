#define BLYNK_PRINT Serial
#define NO_GLOBAL_BLYNK true
#include <BlynkSimpleEsp8266.h>
#include <BlynkConfig.h>
#include <BlynkAdapter.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <BlynkConnector.h>
#include <CurtainController.h>


#define STM_RX D5
#define STM_TX D4

#define CURTAIN_RX D6
#define CURTAIN_TX D7


SoftwareSerial chat(STM_RX, STM_TX); // RX, TX
String a;
CurtainController curtainCC;


void setup()
{

  Serial.begin(38400);

  Serial.printf("\n\n\n\nInitializing NodeMCU\n\n");
  const char* blynkCred[5] = {BLYNK_TEMPLATE_ID, BLYNK_TEMPLATE_NAME, BLYNK_AUTH_TOKEN, BLYNK_SSID, BLYNK_PASS};
  BlynkConnector blynk(blynkCred, curtainCC);
}
int mode = 0;
void loop()
{

  Serial.println("Please wait Serial..");
  if (mode == 0)
  {
    while (a == "")
    {

      chat.println("Q1"); // ส่งหัวข้อคำถาม ว่า Question1 ไปยัง Arduino

      a = chat.readString(); // อ่าน Serial และนำไปเก็บในตัวแปร A

      Serial.println(a);

      delay(100);

      Serial.println(".Q1.");
    }
    a = "";
    mode = 1;
  }
  else
  {
    while (a == "")
    {

      chat.print("Q2"); // ส่งหัวข้อคำถาม ว่า Question1 ไปยัง Arduino

      a = chat.readString(); // อ่าน Serial และนำไปเก็บในตัวแปร A

      Serial.print(a);

      delay(100);

      Serial.print(".Q2.");
    }
    a = "";
    mode = 0;
  }
}