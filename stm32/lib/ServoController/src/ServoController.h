#ifndef SERVOCONTROLLER_H
#define SERVOCONTROLLER_H
#include <Arduino.h>
#include <TaskBase.h>
#include <servo.h>

class ServoController
{
    public:
    ServoController(char* name);
    void setServoPin(int pin);
    void setAngle(int angle);
    int getAngle();
private:
    Servo _servo;
    int _pin = -1;
    int _angle = 0;
    void classTask();
};

#endif