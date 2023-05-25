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
#include <SlaveCurtainController.h>

SoftwareSerial chat(ESP_RX, ESP_TX); // RX, TX to NodeMCU
BuzzerController buzzer(BUZZER_PIN);
SensorController sensor;
LEDController led(LED_PIN);
SlaveCurtainController curtain(MOTOR_PIN_IN1, MOTOR_PIN_IN2, MOTOR_PWM);
// MotorController motor(MOTOR_PIN_IN1, MOTOR_PIN_IN2, MOTOR_PWM);
// SlaveChatController::chat = SoftwareSerial(ESP_RX, ESP_TX)
// SlaveChatController slaveChatController(ESP_RX, ESP_TX, ESP_BAUDRATE);
void loopThread(void *pvParameters);
enum Controllers
{
  UNKNOWN = -1,
  BUZZER,
  CURTAIN,
  LED,
  SENSOR
};

void setup()
{
  chat.begin(ESP_BAUDRATE);
  Serial.begin(9600);
  Serial.println("Hello World");
  sensor.setDHTpin(DHT_PIN);
  sensor.setMQpin(MQ_PIN);
  sensor.setLDRpin(LDR_PIN);
  xTaskCreate(loopThread, "loopThread", 10000, NULL, 1, NULL);
  vTaskStartScheduler();
}

int counter = 0;
int i;

Controllers getController(char *controller)
{
  if (controller == "buzzer")
  {
    return BUZZER;
  }
  else if (controller == "curtain")
  {
    return CURTAIN;
  }
  else if (controller == "led")
  {
    return LED;
  }
  else if (controller == "sensor")
  {
    return SENSOR;
  }
  else
  {
    return UNKNOWN;
  }
}


void loopThread(void *pvParameters)
{
  
  (void) pvParameters;

  while(true)
  {
  // put your main code here, to run repeatedly:
  // Serial.println("Hello World");
  // Serial.printf
  Serial.println("Hello World eiei");
  String rawFullcommand;
  char *rawController;
  const char *delimiter = " ";
  char *substring;
  char *command[3];

  rawFullcommand = chat.readStringUntil('\n');
  Serial.println(rawFullcommand);
  i = 0;
  char fullCommand[rawFullcommand.length() + 1];
  strcpy(fullCommand, rawFullcommand.c_str());
  substring = strtok(fullCommand, delimiter);
  while (substring != NULL && i < 4)
  {
    if (i == 0)
    {
      rawController = substring;
    }
    else
    {
      command[i-1] = substring;
    }

    substring = strtok(NULL, delimiter);
    i++;
  }

  Controllers controller = getController(rawController);
  // char *command[3];
  // command = substrings [1:];
  Serial.printf("AtController: %s | Executing %s \n",rawController, command[0]);
  switch (controller)
  {
  case BUZZER:
    buzzer.execute(command);
    break;
  case CURTAIN:
    curtain.execute(command);
    break;
  case LED:
    led.execute(command);
    break;
  case SENSOR:
    {
      float co2, tvoc, temp, humid, co, lpg, smoke, brightness;
      byte dataByts[sizeof(float) * 8];
      co2 = sensor.getCO2();
      tvoc = sensor.getTVOC();
      temp = sensor.getTemperature();
      humid = sensor.getHumidity();
      co = sensor.getCO();
      lpg = sensor.getLPG();
      smoke = sensor.getSmoke();
      brightness = sensor.getBrightness();
      // Serial.printf("CO2: %d | TVOC: %d | Temperature: %d | Humidity: %d | CO: %d | LPG: %d | Smoke: %d | Brightness: %d \n", co2, tvoc, temp, humid, co, lpg, smoke, brightness);
      Serial.printf("CO2: %f | TVOC: %f | Temperature: %f| Humidity: %f | CO: %f | LPG: %f | Smoke: %f | Brightness: %f \n", co2, tvoc, temp, humid, co, lpg, smoke, brightness);
      float data[8] = {co2, tvoc, temp, humid, co, lpg, smoke, brightness};
      for (int i = 0; i < 8; i++)
      {
        memcpy(&dataByts[i * sizeof(float)], &data[i], sizeof(float));
      }
      chat.write(dataByts, sizeof(dataByts));
      break;
    }
  default:
    break;
  }
  }
}

