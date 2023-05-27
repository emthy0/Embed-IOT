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
#include <Servo.h>

String data = "";

// global variables
// 0 <= pos <= 180
int desirePos = 0;     // the position that the servo should move to
int currentPos = 0;    // the current position of the servo
bool buzzerOn = false; // whether the buzzer should be on or off
bool ledOn = false;    // whether the led should be on or off

// define tasks
void servoThread(void *p);
void buzzerThread(void *p);
void ledThread(void *p);

// define pins
#define SERVO_PIN PA4
#define BUZZER_PIN PC0
#define LED_PIN PC1 // still need to change this

void requestEvent()
{
  Wire.write(1);
}

void receiveEvent(int howMany)
{
  Serial.println("receiveEvent");
  data = "";
  while (Wire.available())
  {
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

void servoThread(void *p)
{
  // setup
  Servo myServo;
  (void)p;
  myServo.attach(SERVO_PIN);

  // loop
  while (true)
  {
    // doesn't do anything if it's already at the desire position
    if (currentPos == desirePos)
    {
      vTaskDelay(15);
      continue;
    }
    // move the servo to the desire position
    else if (currentPos < desirePos)
    {
      currentPos++;
      myServo.write(currentPos);
      vTaskDelay(15);
    }
    // same as above but in the opposite direction
    else
    {
      currentPos--;
      myServo.write(currentPos);
      vTaskDelay(15);
    }
  }
}

void buzzerThread(void *p)
{
  (void)p;
  pinMode(BUZZER_PIN, OUTPUT);

  while (true)
  {
    if (buzzerOn)
    {
      digitalWrite(BUZZER_PIN, HIGH);
      vTaskDelay(15);
      digitalWrite(BUZZER_PIN, LOW);
      vTaskDelay(15);
    }
    else
    {
      digitalWrite(BUZZER_PIN, LOW);
    }
  }
}

void ledThread(void *p)
{
  (void)pdFREERTOS_BIG_ENDIAN;
  pinMode(LED_PIN, OUTPUT);

  while (true)
  {
    if (ledOn)
    {
      digitalWrite(LED_PIN, HIGH);
    }
    else
    {
      digitalWrite(LED_PIN, LOW);
    }
    vTaskDelay(15);
  }
}