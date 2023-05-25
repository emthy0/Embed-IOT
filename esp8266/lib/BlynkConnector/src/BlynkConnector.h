#ifndef BLYNKCONTROLLER_H
#define BLYNKCONTROLLER_H

#include "Arduino.h"
// #include <BlynkAdapter.h>
// #include <BlynkCredential.h>
#include <CurtainController.h>

/**
 * @brief 
 * 
 */
class BlynkConnector
{
  public:

    BlynkConnector(CurtainController& curtainController);
    void SendHumidity(double Humidity);
    void SendTemperature(double Temp);
    void SendCO2(double CO2);
    void SendTVOC(double TVOC);
    void SendBrightness(int Brightness);
    void SetupBlynk(const char* blynkCred[5]);
    // int GetCurtainLevel();
    // int GetCurtaionMode();
  private:
    int _controllerMode = CONTROLLER_PLATFORM;
    CurtainController _curtainController;
    void _setCurtainLevel(int level);
};


#endif