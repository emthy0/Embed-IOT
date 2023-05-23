#ifndef BUZZERCONTROLLER_H

#define BUZZERCONTROLLER_H

#include "Arduino.h"

class BuzzerController
{
  public:
    BuzzerController(int pin);
    void setMode(enum Mode mode);
    void setLevel(int level);
    void dash();
  private:
    int _currentLevel;
    int _currentMode;
    int _controllerMode = CONTROLLER_PLATFORM;
};

#endif
