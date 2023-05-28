#ifndef SLAVECURTAINCONTROLLER_H
#define SLAVECURTAINCONTROLLER_H


#include <CurtainController.h>
#include <ServoController.h>

class SlaveCurtainController : public CurtainController
{
    public:
        SlaveCurtainController(int pin);
        // void setMode(enum CurtainMode mode);
        // void setLevel(int level);
        // int getLevel();
        void execute(char* command[3]);
    private:
        // MotorController& _motorController;
        // ServoController __servoController;
        int _angle;
        void _setAngle(int angle);
        
        int _currentLevel;
        int _currentMode;
        
    
};

#endif