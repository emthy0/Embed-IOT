#include "Arduino.h"
#include "CurtainController.h"
#include "SlaveCurtainController.h"
// #include <ServoController.h>
#include <servo.h>

Servo __servoController;

SlaveCurtainController::SlaveCurtainController(int pin): CurtainController()
{
  // _motorController = motorController;
  // _
  __servoController.attach(pin);
  _angle = 0;
}

void SlaveCurtainController::_setAngle(int angle)
{
    // if (angle == _angle)
    // {
    //     return;
    // }
    angle = max(0, min(180, angle));
    if (angle < _angle)
    {
        for (int i = _angle; i > angle; i--)
        {
            Serial.println(i);
            __servoController.write(i);
            // delay(150);
            // vTaskDelay(150);
        }
    } else {
        for (int i = _angle; i < angle; i++)
        {
            Serial.println(i);
            __servoController.write(i);
            // delay(150);
            // vTaskDelay(150);
        }
    }
    _angle = angle;

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
    this->_setAngle(90);
  }
  else if (mode == "clos")
  {
    this->_setAngle(0);
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