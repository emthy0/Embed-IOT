#ifndef CHATCONTROLLER_H
#define CHATCONTROLLER_H

#include "Arduino.h"
#include <SoftwareSerial.h>

class ChatController
{
  public:
    ChatController(int RX, int TX, int baudrate);
    void setMode(enum CurtainMode mode);
    void setLevel(int level);
    int getLevel();
  private:
    SoftwareSerial _chat;
    int _currentLevel;
    int _currentMode;
    int _controllerMode = CONTROLLER_PLATFORM;
};