#include "Arduino.h"
#include <SoftwareSerial.h>
#include "MasterCurtainController.h"


MasterCurtainController::MasterCurtainController(SoftwareSerial& serial):  _chat(serial)
{
  // _chat = &serial;
  _currentLevel = 0;
  _currentMode = MANUAL;
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

CurtainMode MasterCurtainController::getMode()
{
  return _currentMode;
}

void MasterCurtainController::_execute()
{
  // char* command[3];
  // char* controller = "curtain";
  // command[0] = (char*)controller;
  // command[1] = (char*)_currentMode;
  // command[2] = (char*)_currentLevel;
    char mode[4];
  char level[4];
  String paddedLevel = String("0000") + String(_currentLevel);
  paddedLevel = paddedLevel.substring(paddedLevel.length() - 4);
  paddedLevel.toCharArray(level, sizeof(level));


  String paddedMode = String("0000") + String(_currentMode);
  paddedMode = paddedMode.substring(paddedMode.length() - 4);
  paddedMode.toCharArray(mode, sizeof(mode));
  _chat.printf("%s %s %s 0000\n", "curt", mode, level);
}