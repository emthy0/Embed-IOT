#include <MQController.h>
#include <Arduino.h>

int  MQGetPercentage(float rs_ro_ratio, float *pcurve)
{
  return (pow(10,( ((log(rs_ro_ratio)-pcurve[1])/pcurve[2]) + pcurve[0])));
}

MQController::MQController() 
// : TaskClass("MQ Thread", 1000, 1000)
{
}

void MQController::setPin(int pin)
{
  _pin = pin;
}

void MQController::_setCO(int co)
{
  _co = co;
}

void MQController::_setLPG(int lpg)
{
  _lpg = lpg;
}

void MQController::_setSmoke(int smoke)
{
  _smoke = smoke;
}

int MQController::getCO()
{
  int rs_ro_ratio = this->_MQRead() / _Ro;
  return MQGetPercentage(rs_ro_ratio, _COCurve);
}

int MQController::getLPG(){
  int rs_ro_ratio = this->_MQRead() / _Ro;
    return MQGetPercentage(rs_ro_ratio, _LPGCurve);
}

int MQController::getSmoke()
{
  int rs_ro_ratio = this->_MQRead() / _Ro;
    return MQGetPercentage(rs_ro_ratio, _SmokeCurve);
}

float MQController::_MQResistanceCalculation(int raw_adc)
{
  return ( ((float)_RL_VALUE*(1023-raw_adc)/raw_adc));
}




float MQController::_MQRead()
{
    int i;
    float rs = 0;
    for (i=0;i<_READ_SAMPLE_TIMES;i++) {
        rs += this->_MQResistanceCalculation(analogRead(_pin));
        vTaskDelay(_READ_SAMPLE_TIMES);
    }

    rs = rs/_READ_SAMPLE_TIMES;

    return rs;  
}


void MQController::classTask()
{
    if (_pin != -1)
    {
    int rs_ro_ratio = this->_MQRead() / _Ro;
    this->_setCO(MQGetPercentage(rs_ro_ratio, _COCurve));
    this->_setLPG(MQGetPercentage(rs_ro_ratio, _LPGCurve));
    this->_setSmoke(MQGetPercentage(rs_ro_ratio, _SmokeCurve));
    vTaskDelay(1000);
    }



}