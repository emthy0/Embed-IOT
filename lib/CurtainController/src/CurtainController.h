#ifndef CURTAINCONTROLLER_H
#define CURTAINCONTROLLER_H

#include "Arduino.h"

enum Mode
{
  MANUAL,
  AUTO
};

class CurtainController
{
  public:
    CurtainController(int pin);
    void setMode(enum Mode mode);
    void setLevel(int level);
    void dash();
  private:
    int _currentLevel;
    int _currentMode;
    int _controllerMode = CONTROLLER_PLATFORM
};

#endif