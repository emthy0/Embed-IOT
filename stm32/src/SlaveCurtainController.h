#ifndef SLAVECURTAINCONTROLLER_H
#define SLAVECURTAINCONTROLLER_H


#include <CurtainController.h>
#include <ServoController.h>

class SlaveCurtainController : public CurtainController , public ServoController
{
    public:
        SlaveCurtainController();
        void setPin(int pin);
        // void setMode(enum CurtainMode mode);
        // void setLevel(int level);
        // int getLevel();
        void execute(char* command[3]);
    private:
        // MotorController& _motorController;
        // ServoController __servoController;
        int _currentLevel;
        int _currentMode;
        
    
};

#endif