#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include<TaskBase.h>
#include <Arduino.h>

enum LEDMode
{
    OFF = 0,
    ON = 1,
    // BLINK = 2
};

void ledThread(void *pvParameters);

class LEDController : protected TaskClass
{
public:
    LEDController(int pin);
    void activate();
    void deactivate();
    bool isActive();
private:
    LEDMode _mode;
    int _pin;
    void classTask();
};

#endif