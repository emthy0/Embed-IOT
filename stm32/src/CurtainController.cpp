#include "Arduino.h"
#include "CurtainController.h"

CurtainController::CurtainController(int pin)
{
  _pin = pin;
  pinMode(_pin, OUTPUT);
}

void CurtainController::setMode(enum CurtainMode mode)
{
  _currentMode = mode;
}

void CurtainController::setLevel(int level)
{
  _currentLevel = level;
}

int CurtainController::getLevel()
{
  return _currentLevel;
}