#ifndef CURTAINCONTROLLER_H
#define CURTAINCONTROLLER_H

#include "Arduino.h"

enum CurtainMode
{
  MANUAL,
  AUTO
};

// enum CurtainState
// {
//   STOPPED,
//   OPENING,
//   CLOSING
// };

enum ControllerMode
{
  MASTER,
  SLAVE
};

class CurtainController
{
  public:
    CurtainController();
    // CurtainController(SoftwareSerial chat);
    // __weak CurtainController(int RX, int TX, int baudrate);
    void setMode(enum CurtainMode mode);
    void setLevel(int level);
    int getLevel();
    void execute(char* command[3]);
  private:
    int _pin;
    int _currentLevel;
    CurtainMode _currentMode;
    // CurtainState _currentState;
    int _controllerMode = CONTROLLER_PLATFORM;
};

// class CurtainController
// {
//   public:
//     CurtainController();
    
//     #if CONTROLLER_PLATFORM == 0
//     CurtainController(int RX, int TX, int baudrate);
//     #else
//     CurtainController(int pin);
//     #endif
//     void setMode(enum CurtainMode mode);
//     void setLevel(int level);
//     int getLevel();
//   private:
//     #if CONTROLLER_PLATFORM == 0
//     SoftwareSerial _chat;
//     #else
//     int _pin;
//     #endif
//     int _currentLevel;
//     int _currentMode;
//     int _controllerMode = CONTROLLER_PLATFORM;
// };

#endif