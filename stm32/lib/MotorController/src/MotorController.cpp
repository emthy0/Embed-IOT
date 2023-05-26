#include <MotorController.h>
#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <TaskBase.h>
MotorController::MotorController(int in1, int in2, int pwm) : TaskClass("motor Thread", 1000, 1000)
{
    _pinIn1 = in1;
    _pinIn2 = in2;
    _pinPWM = pwm;
    pinMode(_pinIn1, OUTPUT);
    pinMode(_pinIn2, OUTPUT);
    pinMode(_pinPWM, OUTPUT);
    setMode(STOP); // set default mode to STOP (0
    setPower(0);   // set default power to 0
    this->_active = false;
}

void MotorController::setMode(MotorMode mode)
{
    this->_mode = mode;
}

void MotorController::setPower(int power)
{
    this->_power = power;
}

void MotorController::activate(MotorMode mode, int duration)
{

    this->_duration = duration;
    this->_mode = mode;
        this->_active = true;
    if (_mode == STOP)
    {
        this->_stop();
    }
    else
    {
        if (_mode == 1)
        {
            digitalWrite(_pinIn1, HIGH);
            digitalWrite(_pinIn2, LOW);
        }
        else
        {
            digitalWrite(_pinIn1, LOW);
            digitalWrite(_pinIn2, HIGH);
        }
        analogWrite(_pinPWM, (_power * 255 / 100));
        delay(_duration);
        this->_stop();
        
    }
}

int MotorController::getMode()
{
    return this->_mode;
}

int MotorController::getPower()
{
    return this->_power;
}

bool MotorController::isActive()
{
    return this->_active;
}

void MotorController::_stop()
{
    this->_mode = STOP;
    this->_power = 0;
    this->_active = false;
    digitalWrite(_pinIn1, LOW);
    digitalWrite(_pinIn2, LOW);
    analogWrite(_pinPWM, 0);
}

void MotorController::classTask()
{
    this->_active = true;
    if (_mode == STOP)
    {
        this->_stop();
    }
    else
    {
        if (_mode == 1)
        {
            digitalWrite(_pinIn1, HIGH);
            digitalWrite(_pinIn2, LOW);
        }
        else
        {
            digitalWrite(_pinIn1, LOW);
            digitalWrite(_pinIn2, HIGH);
        }
        analogWrite(_pinPWM, (_power * 255 / 100));
        vTaskDelay(_duration);
        this->_stop();
        
    }
    vTaskDelete(NULL);
}