#define BLYNK_PRINT Serial

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266_SSL.h>
#include <CurtainController.h>
#define BLYNK_TEMPLATE_ID "TMPL6rXyIyR1E"
#define BLYNK_TEMPLATE_NAME "SMARTCURTAIN"
#define BLYNK_AUTH_TOKEN "drFzungMkQBmEgqMe5r8Q8_wVuwsa_4Q"
#define SSID "IOT8D"
#define PASS "iot888=D"

#define STM_RX D5
#define STM_TX D4

SoftwareSerial chat(STM_RX, STM_TX); // RX, TX

String a;

void setup()
{

  Serial.begin(9600);

  chat.begin(4800);

  Blynk.begin(BLYNK_AUTH_TOKEN, SSID, PASS);

  delay(10);
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