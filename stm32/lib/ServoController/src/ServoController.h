#ifndef SERVOCONTROLLER_H
#define SERVOCONTROLLER_H
#include <Arduino.h>
#include <TaskBase.h>


class ServoController : TaskClass
{
    public:
    ServoController(char* name);
    void setPin(int pin);
    void setAngle(int angle);
    int getAngle();
private:
    int _pin = -1;
    int _angle = 0;
    void classTask();
}