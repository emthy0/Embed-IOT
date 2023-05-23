#ifndef CURTAINCONTROLLER_H
#define CURTAINCONTROLLER_H

#include "Arduino.h"

enum CurtainMode
{
  MANUAL,
  AUTO
};

enum ControllerMode
{
  MASTER,
  SLAVE
};

class CurtainController
{
  public:
    CurtainController(int pin);
    void setMode(enum CurtainMode mode);
    void setLevel(int level);
    int getLevel();
  private:
    int _pin;
    int _currentLevel;
    int _currentMode;
    int _controllerMode = CONTROLLER_PLATFORM;
};

#endif