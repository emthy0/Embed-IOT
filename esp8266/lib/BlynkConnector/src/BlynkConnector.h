#ifndef BLYNKCONTROLLER_H
#define BLYNKCONTROLLER_H

#include "Arduino.h"
// #include <BlynkAdapter.h>

#include <CurtainController.h>

class BlynkConnector
{
  public:
    BlynkConnector(CurtainController curtainController);
    void SendHumidity(double Humidity);
    void SendTemperature(double Temp);
  private:
    int _controllerMode = CONTROLLER_PLATFORM;
    CurtainController _curtainController;
    void _setCurtainLevel(int level);
};


#endif