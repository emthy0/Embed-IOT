#include <MotorController.h>
#include <Arduino.h>

MotorController::MotorController(int in1, int in2, int pwm)
{
    _pinIn1 = in1;
    _pinIn2 = in2;
    _pinPWM = pwm;
    pinMode(_pinIn1, OUTPUT);
    pinMode(_pinIn2, OUTPUT);
    pinMode(_pinPWM, OUTPUT);
    setMode(STOP); // set default mode to STOP (0
    setPower(0);   // set default power to 0
    this->active = false;
}

void MotorController::setMode(MotorMode mode)
{
    this->mode = mode;
}

void MotorController::setPower(int power)
{
    this->power = power;
}

void MotorController::activate(int duration)
{
    // xTaskCreate(buzzerThread, "motor Thread", 128, (void *)&duration, 1, NULL);
    this->_duration = duration;
    TaskClass("motor Thread", 1000, 1000);
}

int MotorController::getMode()
{
    return this->mode;
}

int MotorController::getPower()
{
    return this->power;
}

bool MotorController::isActive()
{
    return this->active;
}

void MotorController::_stop()
{
    this->mode = STOP;
    this->power = 0;
    this->active = false;
            digitalWrite(_pinIn1, LOW);
        digitalWrite(_pinIn2, LOW);
        analogWrite(_pinPWM, 0);
}

void MotorController::motorTask()
{
    this->_active = true;
    if (_duration == 0 || _mode == STOP)
    {
        this->_stop();
        continue;
    }
    else if (_mode == 1)
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
    vTaskDelete(NULL);
}