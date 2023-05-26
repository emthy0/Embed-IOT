#ifndef MASTERCURTAINCONTROLLER_H
#define MASTERCURTAINCONTROLLER_H

#include <CurtainController.h>
#include <SoftwareSerial.h>
class MasterCurtainController : public CurtainController
{
    public:
        MasterCurtainController(SoftwareSerial& chat);
        void setMode(enum CurtainMode mode);
        void setLevel(int level);
        int getLevel();
        CurtainMode getMode();
    private:
        SoftwareSerial& _chat;
        int _currentLevel;
        CurtainMode _currentMode;
        void _execute();
    
};

#endif