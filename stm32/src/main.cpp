#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include "DHT.h"
#include "SparkFun_SGP30_Arduino_Library.h" // Click here to get the library: http://librarymanager/All#SparkFun_SGP30
#include <Wire.h>
#include <SoftwareSerial.h>
#include <BuzzerController.h>
#include <CurtainController.h>
#include <SensorController.h>
#include <MotorController.h>
#include <LEDController.h>
#include <PinConfig.h>
#include <SlaveChatController.h>
#include <SlaveCurtainController.h>
#include <DHTController.h>
#include <MQController.h>
#include <SGPController.h>
#include <LDRController.h>

// #define configASSERT( x ) if( x == 0 ) { taskDISABLE_INTERRUPTS(); for(;;); }

SoftwareSerial chat(PA8, PA7_ALT1); // RX, TX to NodeMCU

BuzzerController buzzer(BUZZER_PIN);
// SensorController sensor(888);
DHTController dht;
MQController mqc;
// SGPController sgpc;
LDRController ldrc;
LEDController led(LED_PIN);
SlaveCurtainController curtain(MOTOR_PIN_IN1, MOTOR_PIN_IN2, MOTOR_PWM);

// MotorController motor(MOTOR_PIN_IN1, MOTOR_PIN_IN2, MOTOR_PWM);
// SlaveChatController::chat = SoftwareSerial(ESP_RX, ESP_TX)
// SlaveChatController slaveChatController(ESP_RX, ESP_TX, ESP_BAUDRATE);
void loopThread(void *pvParameters);
void printThread(void *pvParameters);

enum Controllers
{
  UNKNOWN = -1,
  BUZZER,
  CURTAIN,
  LED,
  SENSOR
};

void setup()
{

  //
  // xTaskCreate(printThread, "printThread", 100, NULL, 1, NULL);
  Serial.begin(115200);
  Serial.println("Hello World");

  chat.begin(9600);
  dht.setPin(DHT_PIN);
  mqc.setPin(MQ_PIN);
  ldrc.setPin(LDR_PIN);
  char* command[3] = {"0","25","0"};
  curtain.execute(command);
  // sensor.setDHTpin(DHT_PIN);
  // sensor.setMQpin(MQ_PIN);
  // sensor.setLDRpin(LDR_PIN);
  Serial.println("Hello World in setup");
  xTaskCreate(loopThread, "loopThread", 1010, NULL, 1, NULL);
  Serial.println("Hello World in setup2");
  vTaskStartScheduler();
  Serial.println("Hello World in setup3");
}

int counter = 0;
int i;

Controllers getController(char controller[4])
{
  if (controller == "buzz")
  {
    return BUZZER;
  }
  else if (controller == "curt")
  {
    return CURTAIN;
  }
  else if (controller == "ledd")
  {
    return LED;
  }
  else if (controller == "sens")
  {
    return SENSOR;
  }
  else
  {
    return UNKNOWN;
  }
}

void loopThread(void *pvParameters)
{
  Serial.println("Hello World eiesssi");
  (void)pvParameters;

  while (true)
  {
    Serial.println("Starting loop");
    char buffer[20];
    char *fullCommand;
    char rawController[4];
    char action[4];
    char args1[4];
    char args2[4];
    
    // chat.readBytesUntil('\n',buffer,20);
    chat.readBytes(buffer, 20);
    // fullCommand = strtok(buffer, "\n");
    String(buffer).toCharArray(rawController,4,0);
    String(buffer).toCharArray(action,4,5);
    String(buffer).toCharArray(args1,4,10);
    String(buffer).toCharArray(args2,4,15);
    Serial.printf("Controller: %s | Command: %s | args %s %s\n", rawController, action, args1, args2);
    Controllers controller = getController(rawController);
    if (controller != UNKNOWN)
    {
      char* command[3] = {action, args1, args2};
      if (controller == BUZZER)
      {
        buzzer.execute(command);
      }
      else if (controller == CURTAIN)
      {
        curtain.execute(command);
      }
      else if (controller == LED)
      {
        led.execute(command);
      }
      else if (controller == SENSOR)
      {
        float co2, tvoc, temp, humid, co, lpg, smoke, brightness;
        byte dataByts[sizeof(float) * 8];
        // co2 = sensor.getCO2();
        // tvoc = sensor.getTVOC();
        temp = dht.getTemperature();
        humid = dht.getHumidity();
        co = mqc.getCO();
        lpg = mqc.getLPG();
        smoke = mqc.getSmoke();
        brightness = ldrc.getBrightness();
        // Serial.printf("CO2: %d | TVOC: %d | Temperature: %d | Humidity: %d | CO: %d | LPG: %d | Smoke: %d | Brightness: %d \n", co2, tvoc, temp, humid, co, lpg, smoke, brightness);
        Serial.printf("CO2: %f | TVOC: %f | Temperature: %f| Humidity: %f | CO: %f | LPG: %f | Smoke: %f | Brightness: %f \n", co2, tvoc, temp, humid, co, lpg, smoke, brightness);
        float data[8] = {co2, tvoc, temp, humid, co, lpg, smoke, brightness};
        for (int i = 0; i < 8; i++)
        {
          memcpy(&dataByts[i * sizeof(float)], &data[i], sizeof(float));
        }
        chat.write(dataByts, sizeof(dataByts));
      }
      vTaskDelay(1000);
    }
  }
  Serial.println("Hello Hell in loopThread");
}

void loop()
{
  Serial.begin(9600);
  Serial.println("Should not be here");
}
