#include <LEDController.h>
#include <Arduino.h>

LEDController::LEDController(int pin) : TaskBase("LED Thread", 1000, 1000)
{
    _pin = pin;
    pinMode(_pin, OUTPUT);
    setMode(OFF); // set default mode to OFF (0
    this->active = false;
}

void LEDController::activate()
{
    this->_mode = ON;

}

void LEDController::deactivate()
{
    this->_mode = OFF;
}

void LEDController::ledTask()
{
    while (true)
    {
        if (this->_ == ON)
        {
            digitalWrite(_pin, HIGH);
        }
        else
        {
            digitalWrite(_pin, LOW);
        }
    }
}
