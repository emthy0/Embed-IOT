#ifndef BUZZERCONTROLLER_H

#define BUZZERCONTROLLER_H

#include "Arduino.h"

void buzzerThread(void *pvParameters); 

class BuzzerController
{
  public:
    BuzzerController(int pin);
    void activate();
    void deactivate();
    bool getState();
    int getControllerMode();
    void execute( char* command[3]);
  private:
    int _pin;
    bool _currentState;
    int _controllerMode = CONTROLLER_PLATFORM;
};

#endif
