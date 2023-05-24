#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <Arduino.h>
#include <TaskBase.h>

enum MotorMode
{
    STOP = 0,
    FORWARD = 1,
    BACKWARD = -1
};



class MotorController :  TaskClass
{
public:
    MotorController(int in1, int in2, int pwm);
    void setMode(MotorMode mode);
    void setPower(int power);
    void activate(MotorMode mode, int duration);
    int getMode();
    int getPower();
    bool isActive();
private:
    int _duration;
    int _pinIn1;
    int _pinIn2;
    int _pinPWM;
    int _power;
    bool _active;
    void _stop();
    MotorMode _mode;
    // void motorThread(void *pvParameters);
    void classTask() override;
    // void motorTask()
};

#endif