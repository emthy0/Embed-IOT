#include "Arduino.h"
#include "CurtainController.h"


CurtainController::CurtainController()
{
  _pin = 9999;  
}


CurtainController::CurtainController(int pin)
{
  _pin = pin;  
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