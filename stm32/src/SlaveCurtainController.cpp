#include "Arduino.h"
#include "CurtainController.h"
#include <MotorController.h>
#include <SlaveCurtainController.h>
SlaveCurtainController::SlaveCurtainController(int MOTOR_PIN_IN1,int  MOTOR_PIN_IN2, int MOTOR_PWM): CurtainController(), MotorController(MOTOR_PIN_IN1, MOTOR_PIN_IN2, MOTOR_PWM)
{
  // _motorController = motorController;
}

void SlaveCurtainController::execute(char* command[3])
{
  Serial.println("SlaveCurtainController::execute");
  //CurtainMode mode = (CurtainMode)atoi(command[0]);
  String rawAction = command[0];
  String mode = String(rawAction[0]) + String(rawAction[1]) + String(rawAction[2]) + String(rawAction[3]);
  Serial.println("Nigga ::: "+mode);
  int level = atoi(command[1]);
  //CurtainController::setMode(mode);
  int prevLevel = CurtainController::getLevel();
  MotorController::setPower(45);
  int duration = 10*(level);
  Serial.println(prevLevel);
  if (mode == "posi")
  {
    MotorController::activate(FORWARD, duration);
  }
  else if (mode == "nega")
  {
    MotorController::activate(BACKWARD, duration);
  }
  else
  {
    MotorController::activate(FORWARD, 0);
  }
  CurtainController::setLevel(prevLevel+level);
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