
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
  if (command[0] == "activate")
  {
    this->activate();
  }
  else if (command[0] == "deactivate")
  {
    this->deactivate();
  }
  else
  {
    // do nothing
  }
}

void BuzzerController::activate()
{
  _currentState = true;
  BUZZER_STATE = true;
}

void BuzzerController::deactivate()
{
  _currentState = false;
  BUZZER_STATE = false;
}

bool BuzzerController::getState()
{
  return _currentState;
}

int BuzzerController::getControllerMode()
{
  return _controllerMode;
}