#include "CurtainController.h"

CurtainController::CurtainController()
{
  this->setMode(MANUAL);
  this->setLevel(0);
}

void CurtainController::execute(char* command[3])
{
  CurtainMode mode = (CurtainMode)atoi(command[0]);
  int level = atoi(command[1]);
  this->setMode(mode);
  this->setLevel(level);
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