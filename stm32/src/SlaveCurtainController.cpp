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
  CurtainMode mode = (CurtainMode)atoi(command[0]);
  int level = atoi(command[1]);
  CurtainController::setMode(mode);
  int prevLevel = CurtainController::getLevel();
  MotorController::setPower(50);
  int duration = 10*(level - prevLevel);
  MotorController::activate(FORWARD, duration);
  CurtainController::setLevel(level);
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