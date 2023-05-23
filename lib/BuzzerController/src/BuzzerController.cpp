
#include "Arduino.h"
#include "BuzzerController.h"

BuzzerController::BuzzerController(int pin)
{
  _pin = pin;
  pinMode(_pin, OUTPUT);
}

void BuzzerController::activate()
{
  _currentState = true;
  digitalWrite(_pin, HIGH);
}

void BuzzerController::deactivate()
{
  _currentState = false;
  digitalWrite(_pin, LOW);
}

bool BuzzerController::getState()
{
  return _currentState;
}

int BuzzerController::getControllerMode()
{
  return _controllerMode;
}