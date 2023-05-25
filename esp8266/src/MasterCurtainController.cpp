#include "Arduino.h"
#include <SoftwareSerial.h>
#include "MasterCurtainController.h"


MasterCurtainController::MasterCurtainController(SoftwareSerial& serial):  _chat(serial)
{
  // _chat = &serial;
  _currentLevel = 0;
  _currentMode = 0;
}

void MasterCurtainController::setMode(enum CurtainMode mode)
{
  // _chat.ex
  _currentMode = mode;
  _execute();
}

void MasterCurtainController::setLevel(int level)
{
  _currentLevel = level;
  _execute();
}

int MasterCurtainController::getLevel()
{
  return _currentLevel;
}

void MasterCurtainController::_execute()
{
  // char* command[3];
  // char* controller = "curtain";
  // command[0] = (char*)controller;
  // command[1] = (char*)_currentMode;
  // command[2] = (char*)_currentLevel;
  _chat.printf("%s %d %d\n", "curtain", _currentMode, _currentLevel);
}