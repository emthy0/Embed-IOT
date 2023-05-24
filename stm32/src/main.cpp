#include <Arduino.h>
#include <STM32FreeRTOS.h>
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
#include <SlaveChatController.h>

SoftwareSerial SlaveChatController::chat(ESP_RX,ESP_TX); // RX, TX to NodeMCU
BuzzerController buzzer(BUZZER_PIN);
SensorController sensorController;
LEDController led(LED_PIN);
MotorController motor(MOTOR_PIN_IN1, MOTOR_PIN_IN2, MOTOR_PWM);
// SlaveChatController::chat = SoftwareSerial(ESP_RX, ESP_TX)
SlaveChatController slaveChatController(ESP_RX, ESP_TX, ESP_BAUDRATE);


void setup()
{
  // SlaveChatController::chat.begin(4800);
  Serial.begin(9600);
  
  sensorController.setDHTpin(DHT_PIN);
  sensorController.setMQpin(MQ_PIN);
  sensorController.setLDRpin(LDR_PIN);
  vTaskStartScheduler();
  
}

int counter = 0;
void loop()
{
  // put your main code here, to run repeatedly:
  // Serial.println("Hello World");
  // Serial.printf
}