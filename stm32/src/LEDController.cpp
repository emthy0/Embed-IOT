#include <LEDController.h>
#include <Arduino.h>
#include <TaskBase.h>

LEDController::LEDController(int pin) : TaskClass("LED Thread", 1000, 1000)
{
    _pin = pin;
    pinMode(_pin, OUTPUT);
    this->_mode = OFF;
}

void LEDController::activate()
{
    this->_mode = ON;

}

void LEDController::deactivate()
{
    this->_mode = OFF;
}

void LEDController::classTask()
{
    while (true)
    {
        if (this->_mode == ON)
        {
            digitalWrite(_pin, HIGH);
        }
        else
        {
            digitalWrite(_pin, LOW);
        }
    }
}
