
#include "Arduino.h"
#include "BuzzerController.h"
#include <STM32FreeRTOS.h>

bool BUZZER_STATE = false;

// tasks
void buzzerThread(void *pvParameters)
{
  int buzzer_pin = *((int *)pvParameters);
  pinMode(buzzer_pin, OUTPUT);

  while (true)
  {
    if (BUZZER_STATE)
    {
      digitalWrite(buzzer_pin, HIGH);
      vTaskDelay(10);
      digitalWrite(buzzer_pin, LOW);
      vTaskDelay(10);
    }
    else
    {
      digitalWrite(buzzer_pin, LOW);
    }
    //vTaskDelete(NULL);
  }
}

BuzzerController::BuzzerController(int pin)
{
  _pin = pin;
  pinMode(_pin, OUTPUT);
  BUZZER_STATE = _pin;
  xTaskCreate(buzzerThread, "buzzerThread", 128, (void *)&_pin, 1, NULL);
}

void BuzzerController::execute(char* command[3])
{
  char* rawAction = command[0];
    String parsedCommand = String(rawAction[0]) + String(rawAction[1]) + String(rawAction[2]) + String(rawAction[3]);
    //Serial.println(parsedCommand);
    if (parsedCommand == "acti")
    {
        this->activate();
    }
    else if (parsedCommand == "deac")
    {
        this->deactivate();
    }
        if (BUZZER_STATE)
    {
      digitalWrite(_pin, HIGH);
      vTaskDelay(10);
      digitalWrite(_pin, LOW);
      delay(10);
    }
    else
    {
      digitalWrite(_pin, LOW);
    }
    
  
}

void BuzzerController::activate()
{
  Serial.println("Buzzer ON");
  _currentState = true;
  BUZZER_STATE = true;
  //xTaskCreate(buzzerThread, "buzzerThread", 128, (void *)&PC0, 1, NULL);
}

void BuzzerController::deactivate()
{
  Serial.println("Buzzer OFF");
  _currentState = false;
  BUZZER_STATE = false;
  // xTaskCreate(buzzerThread, "buzzerThread", 128, (void *)&_pin, 1, NULL);
  //xTaskCreate(buzzerThread, "buzzerThread", 128, (void *)&PC0, 1, NULL);
}

bool BuzzerController::getState()
{
  return _currentState;
}

int BuzzerController::getControllerMode()
{
  return _controllerMode;
}