#ifndef SLAVECURTAINCONTROLLER_H
#define SLAVECURTAINCONTROLLER_H


#include <CurtainController.h>
#include <MotorController.h>

class SlaveCurtainController : public CurtainController , private MotorController
{
    public:
        SlaveCurtainController(int motor_pinIn1 ,int  motor_pinIn2, int motor_pinPWM);
        // void setMode(enum CurtainMode mode);
        // void setLevel(int level);
        // int getLevel();
        void execute(char* command[3]);
    private:
        // MotorController& _motorController;
        int _currentLevel;
        int _currentMode;
        
    
};

#endif