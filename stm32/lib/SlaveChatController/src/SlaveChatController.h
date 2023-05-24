#ifndef SLAVECHATCONTROLLER_H
#define SLAVECHATCONTROLLER_H

#include "Arduino.h"
#include <SoftwareSerial.h>

class SlaveChatController
{
  public:
    SlaveChatController();
    SlaveChatController(int RX, int TX, int baudrate);
    // SendCommand(hex command);
    void RecvCommand();
    static SoftwareSerial chat;
  private:
    static int _RX;
    static int _TX;
    static int _baudrate;
};

#endif