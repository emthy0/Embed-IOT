#include <LEDController.h>
#include <Arduino.h>
#include <TaskBase.h>

LEDController::LEDController(int pin) : TaskClass("LED Thread", 1000, 1000)
{
    _pin = pin;
    pinMode(_pin, OUTPUT);
    this->_mode = OFF;
}

void LEDController::execute(char* command[3])
{
    if (command[0] == "activate")
    {
        this->activate();
    }
    else if (command[0] == "deactivate")
    {
        this->deactivate();
    }
    
    // xTaskCreate(LEDController::classTask, "ledThread", 128, (void *)*this, 1, NULL)
}

void LEDController::activate()
{
    this->_mode = ON;
    recreateTask("LED Thread", 1000, 1000);

}

void LEDController::deactivate()
{
    this->_mode = OFF;
    recreateTask("LED Thread", 1000, 1000);
}

void LEDController::classTask()
{

        if (this->_mode == ON)
        {
            digitalWrite(_pin, HIGH);
        }
        else
        {
            digitalWrite(_pin, LOW);
        }
        vTaskDelete(NULL);
    
}
