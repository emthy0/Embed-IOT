#include "Arduino.h"
#include "CurtainController.h"
#include <ServoController.h>
#include <SlaveCurtainController.h>
SlaveCurtainController::SlaveCurtainController(): CurtainController(), ServoController("CurtainServo")
{
  // _motorController = motorController;
  // _
}

void SlaveCurtainController::setPin(int pin)
{
  ServoController::setPin(pin);
  ServoController::setAngle(0);
}

void SlaveCurtainController::execute(char* command[3])
{
  Serial.println("SlaveCurtainController::execute");
  //CurtainMode mode = (CurtainMode)atoi(command[0]);
  String rawAction = command[0];
  String mode = String(rawAction[0]) + String(rawAction[1]) + String(rawAction[2]) + String(rawAction[3]);
  Serial.println("Setting Curtain: " + mode);
  if (mode == "open")
  {
    ServoController::setAngle(90);
  }
  else if (mode == "clos")
  {
    ServoController::setAngle(0);
  }
  return;
  // CurtainController::setLevel(prevLevel+level);
}

// void SlaveCurtainController::setMode(enum CurtainMode mode)
// {
//   _currentMode = mode;
// }

// void SlaveCurtainController::setLevel(int level)
// {
//   _currentLevel = level;
// }

// int SlaveCurtainController::getLevel()
// {
//   return _currentLevel;
// }