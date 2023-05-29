#include <MQController.h>
#include <Arduino.h>

#define         MQ_PIN                       (PA1)  
#define         MQ_PIN                       (PA1)     
#define         RL_VALUE                     (PA1)     
#define         RO_CLEAN_AIR_FACTOR          (9.83)                                                  
#define         CALIBARAION_SAMPLE_TIMES     (50)   
#define         CALIBRATION_SAMPLE_INTERVAL  (500)                                                      
#define         READ_SAMPLE_INTERVAL         (50)    
#define         READ_SAMPLE_TIMES            (5)     
#define         GAS_LPG                      (0)
#define         GAS_CO                       (1)
#define         GAS_SMOKE                    (2)

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
  int rs_ro_ratio = this->_MQRead(MQ_PIN) / _Ro;
  return MQGetPercentage(rs_ro_ratio, _COCurve);
}

int MQController::getLPG(){
  int rs_ro_ratio = this->_MQRead(MQ_PIN) / _Ro;
    return MQGetPercentage(rs_ro_ratio, _LPGCurve);
}

int MQController::getSmoke()
{
  int rs_ro_ratio = this->_MQRead(MQ_PIN) / _Ro;
    return MQGetPercentage(rs_ro_ratio, _SmokeCurve);
}

float MQController::_MQResistanceCalculation(int raw_adc)
{
  return ( ((float)_RL_VALUE*(1023-raw_adc)/raw_adc));
}




float MQController::_MQRead(int mq_pin)
{
    int i;
    float rs = 0;
    for (i=0;i<_READ_SAMPLE_TIMES;i++) {
        rs += this->_MQResistanceCalculation(analogRead(_pin));
        //vTaskDelay(_READ_SAMPLE_TIMES);
    }

    rs = rs/_READ_SAMPLE_TIMES;

    return rs;  
}


void MQController::classTask()
{
    if (_pin != -1)
    {
    int rs_ro_ratio = this->_MQRead(MQ_PIN) / _Ro;
    this->_setCO(MQGetPercentage(rs_ro_ratio, _COCurve));
    this->_setLPG(MQGetPercentage(rs_ro_ratio, _LPGCurve));
    this->_setSmoke(MQGetPercentage(rs_ro_ratio, _SmokeCurve));
    vTaskDelay(1000);
    }



}

int MQController::_MQGetGasPercentage(float rs_ro_ratio, int gas_id)
{
  if ( gas_id == GAS_LPG ) {
     return MQGetPercentage(rs_ro_ratio,_LPGCurve);
  } else if ( gas_id == GAS_CO ) {
     return MQGetPercentage(rs_ro_ratio,_COCurve);
  } else if ( gas_id == GAS_SMOKE ) {
     return MQGetPercentage(rs_ro_ratio,_SmokeCurve);
  }    

  return 0;
}

float MQController::_MQCalibration(int mq_pin)
{
  int i;
  float val=0;

  for (i=0;i<CALIBARAION_SAMPLE_TIMES;i++) {            //take multiple samples
    val += _MQResistanceCalculation(analogRead(mq_pin));
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }
  val = val/CALIBARAION_SAMPLE_TIMES;                   //calculate the average value

  val = val/RO_CLEAN_AIR_FACTOR;                        //divided by RO_CLEAN_AIR_FACTOR yields the Ro 
                                                        //according to the chart in the datasheet 

  return val; 
}

