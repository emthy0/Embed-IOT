#include "Arduino.h"
#include <SoftwareSerial.h>
#include "MasterCurtainController.h"


CurtainController::CurtainController()
{
  // _chat = chat;
}


// CurtainController::CurtainController(int RX_pin, int TX_pin, int baudrate)
// {
//   SoftwareSerial _chat(RX_pin, TX_pin);
//   _chat.begin(baudrate);
// }

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