#include "DHT.h"
#include "SparkFun_SGP30_Arduino_Library.h" // Click here to get the library: http://librarymanager/All#SparkFun_SGP30
#include <Wire.h>
#include <SoftwareSerial.h>

#define ESP_RX  PA8
#define ESP_TX PA7_ALT1
#define DHT_PIN PA0_ALT1
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
SGP30 mySensor; //create an object of the SGP30 class
SoftwareSerial chat(ESP_RX,ESP_TX); // RX, TX to NodeMCU
DHT dht;

int a = 13;
int b = 25;
int i;
float           LPGCurve[3]  =  {2.3,0.21,-0.47};   
float           COCurve[3]  =  {2.3,0.72,-0.34};    
float           SmokeCurve[3] ={2.3,0.53,-0.44};                                               
float           Ro           =  10;

int analogPin = PA2;
int val = 0;

void setup()
{
  chat.begin(4800);
  Serial.begin(9600);
  //Serial.println();
  //Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)");
  dht.setup(DHT_PIN); // data pin 2

  Wire.begin();
  //Initialize sensor
  if (mySensor.begin() == false) 
  {
    Serial.println("No SGP30 Detected. Check connections.");
    while (1);
  }
  //Initializes sensor for air quality readings
  //measureAirQuality should be called in one second increments after a call to initAirQuality
  mySensor.initAirQuality();
  
  Serial.print("Calibrating...\n");                
  Ro = MQCalibration(MQ_PIN);                       //Calibrating the sensor. Please make sure the sensor is in clean air 
                                                    //when you perform the calibration                    
  Serial.print("Calibration is done...\n"); 
  Serial.print("Ro=");
  Serial.print(Ro);
  Serial.print("kohm");
  Serial.print("\n");

  
}

void loop()
{
  val = analogRead(analogPin);
  mySensor.measureAirQuality();
  Serial.print("CO2: ");
  Serial.print(mySensor.CO2);
  Serial.print(" ppm\tTVOC: ");
  Serial.print(mySensor.TVOC);
  Serial.println(" ppb");

  if (chat.readString() != ""){
     if(chat.readString() == "1"){ //Send all val to esp8266 in term hummidity  tem(C)  LPG(ppm) CO(ppm) SMOKE(ppm) CO2(ppb) TVOC(ppb) LDR
        delay(dht.getMinimumSamplingPeriod());
        float humidity = dht.getHumidity(); // ดึงค่าความชื้น
        float temperature = dht.getTemperature(); // ดึงค่าอุณหภูมิ

        chat.print(humidity);
        chat.print("\t");
        chat.print((dht.toFahrenheit(temperature)/100000-32)*5/8);
        chat.print("\t");
        chat.print(MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_LPG));
        chat.print("\t");
        chat.print(MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_CO));
        chat.print("\t");
        chat.print(MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_SMOKE));
        chat.print("\t");
        chat.print(mySensor.CO2);
        chat.print("\t");
        chat.print(mySensor.TVOC);
        chat.print("\t");
        chat.print(val);
        chat.print("\t");
        
        Serial.print(humidity);
        Serial.print("\t");
        Serial.print((dht.toFahrenheit(temperature)/100000-32)*5/8, 1);
        Serial.print("\t");
        Serial.print(MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_LPG));
        Serial.print("\t");
        Serial.print(MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_CO));
        Serial.print("\t");
        Serial.print(MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_SMOKE));
        Serial.print("\t");
        Serial.print(mySensor.CO2);
        Serial.print("\t");
        Serial.print(mySensor.TVOC);
        Serial.print("\t");
        Serial.print(val);
        Serial.print("\t");
     }
     else if(chat.readString() == "00"){ //Setled ON/OFF/Auto
      chat.print(b);
     }
     else if(chat.readString() == "01"){
       chat.print("*01*");
     }
     
     
  Serial.print("Send = ");
  Serial.println(i);

  }

  i++;
  delay(1000);
}

float MQResistanceCalculation(int raw_adc)
{
  return ( ((float)RL_VALUE*(1023-raw_adc)/raw_adc));
}

float MQCalibration(int mq_pin)
{
  int i;
  float val=0;

  for (i=0;i<CALIBARAION_SAMPLE_TIMES;i++) {            //take multiple samples
    val += MQResistanceCalculation(analogRead(mq_pin));
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }
  val = val/CALIBARAION_SAMPLE_TIMES;                   //calculate the average value

  val = val/RO_CLEAN_AIR_FACTOR;                        //divided by RO_CLEAN_AIR_FACTOR yields the Ro 
                                                        //according to the chart in the datasheet 

  return val; 
}

float MQRead(int mq_pin)
{
  int i;
  float rs=0;

  for (i=0;i<READ_SAMPLE_TIMES;i++) {
    rs += MQResistanceCalculation(analogRead(mq_pin));
    delay(READ_SAMPLE_INTERVAL);
  }

  rs = rs/READ_SAMPLE_TIMES;

  return rs;  
}

int MQGetGasPercentage(float rs_ro_ratio, int gas_id)
{
  if ( gas_id == GAS_LPG ) {
     return MQGetPercentage(rs_ro_ratio,LPGCurve);
  } else if ( gas_id == GAS_CO ) {
     return MQGetPercentage(rs_ro_ratio,COCurve);
  } else if ( gas_id == GAS_SMOKE ) {
     return MQGetPercentage(rs_ro_ratio,SmokeCurve);
  }    

  return 0;
}

int  MQGetPercentage(float rs_ro_ratio, float *pcurve)
{
  return (pow(10,( ((log(rs_ro_ratio)-pcurve[1])/pcurve[2]) + pcurve[0])));
}


