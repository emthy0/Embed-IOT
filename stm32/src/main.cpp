#include <string.h>
#include <Arduino.h>

#include <STM32FreeRTOS.h>
#include "DHT.h"
// #include "SparkFun_SGP30_Arduino_Library.h" // Click here to get the library: http://librarymanager/All#SparkFun_SGP30
#include <Wire.h>
#include <SoftwareSerial.h>
#include <BuzzerController.h>
// #include <CurtainController.h>
// #include <SensorController.h>
// #include <MotorController.h>
// #include <LEDController.h>
#include <PinConfig.h>
// #include <SlaveChatController.h>
// #include <SlaveCurtainController.h>
#include <DHTController.h>
#include <MQController.h>
// #include <SGPController.h>
#include <LDRController.h>
#include <servo.h>

#define MQ_PIN (PA1)
#define RL_VALUE (PA1)
#define RO_CLEAN_AIR_FACTOR (9.83)
#define CALIBARAION_SAMPLE_TIMES (50)
#define CALIBRATION_SAMPLE_INTERVAL (500)
#define READ_SAMPLE_INTERVAL (50)
#define READ_SAMPLE_TIMES (5)
#define GAS_LPG (0)
#define GAS_CO (1)
#define GAS_SMOKE (2)
float _Ro = 10;
float _RL_VALUE = 5;

// #define configASSERT( x ) if( x == 0 ) { taskDISABLE_INTERRUPTS(); for(;;); }

HardwareSerial Serial6(PA_12, PA_11); // RX, TX to NodeMCU
#define chat Serial6
// BuzzerController buzzer(BUZZER_PIN);
DHTController dht;
MQController mqc;
LDRController ldrc;
// LEDController led(LED_PIN);
// SlaveCurtainController curtain(PC7);
Servo myServo;
// MotorController motor(MOTOR_PIN_IN1, MOTOR_PIN_IN2, MOTOR_PWM);
// SlaveChatController::chat = SoftwareSerial(ESP_RX, ESP_TX)
// SlaveChatController slaveChatController(ESP_RX, ESP_TX, ESP_BAUDRATE);
void loopThread(void *pvParameters);
void printThread(void *pvParameters);
// int curtainPos = 0 // 0 = lowest, 100 = highest

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
  myServo.attach(PB3, 0);

  Serial.println("Hello World in setup1");

  Serial.println("Hello World");

  chat.begin(9600);
  dht.setPin(DHT_PIN);
  mqc.setPin(MQ_PIN);
  ldrc.setPin(LDR_PIN);
  pinMode(PC0, OUTPUT);

  // char* command[3] = {"0","-20","0"}; // pulls the curtain down
  //  curtain.setPin(PC7);
  //  char* command[3] = {"open","0000","0000"}; // pulls the curtain up
  //  curtain.execute(command);
  //  delay(1000);
  //  char* command2[3] = {"clos","0000","0000"}; // pulls the curtain up
  //  curtain.execute(command2);
  //  curtain::setAngle(0);
  //  sensor.setDHTpin(DHT_PIN);
  //  sensor.setMQpin(MQ_PIN);
  //  sensor.setLDRpin(LDR_PIN);
  Serial.println("Hello World in setup");
  // xTaskCreate(loopThread, "loopThread", 20000, NULL, 1, NULL);
  Serial.println("Hello World in setup2");

  Serial.print("Calibrating...\n");
  float Ro = mqc._MQCalibration(MQ_PIN); // Calibrating the sensor. Please make sure the sensor is in clean air
  // when you perform the calibration
  Serial.print("Calibration is done...\n");

  Serial.print("Ro=");
  Serial.print(Ro);
  Serial.print("kohm");
  Serial.print("\n");

  // vTaskStartScheduler();
  Serial.println("Hello World in setup3");
}

int counter = 0;
int i;

Controllers getController(char rcontroller[4])
{
  String controller = String(rcontroller[0]) + String(rcontroller[1]) + String(rcontroller[2]) + String(rcontroller[3]);

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

bool isWindowOpen = false;

void loop()

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
  Serial.println(buffer);
  for (int i = 0; i < 4; i++)
  {
    rawController[i] = buffer[i];
    action[i] = buffer[i + 5];
    args1[i] = buffer[i + 10];
    args2[i] = buffer[i + 15];
  }
  // String(buffer).toCharArray(rawController,5,0);
  // String(buffer).toCharArray(action,5,5);
  // String(buffer).toCharArray(args1,5,10);
  // String(buffer).toCharArray(args2,5,15);
  // Serial.println(myServo.attached());
  // for (int i = 0; i < 180; i++)
  // {
  //   Serial.println(myServo.read());
  //   myServo.write(i);
  //   delay(15);
  // }

  // Serial.println("Hello World in setup1");
  // Serial.println(myServo.attached());
  // for (int i = 180; i > 0; i--)
  // {
  //   Serial.println(myServo.read());
  //   myServo.write(i);
  //   delay(15);
  // }
  // Controllers controller = getController(rawController);
  // Serial.println(controller);
  // String cc = "pppp";
  // String cc = String(rawController[0]) + String(rawController[1]) + String(rawController[2]) + String(rawController[3]);
  // Serial.println(cc);
  char cc[4] = {rawController[0], rawController[1], rawController[2], rawController[3]};

  // Serial.printf("Controller: %s | Command: %s | args %s %s\n", rawController, action, args1, args2);
  if (cc != " ")
  // if (false)
  {

    char *command[3] = {action, args1, args2};
    if (rawController[0] == 'c' && rawController[1] == 'u' && rawController[2] == 'r' && rawController[3] == 't')
    {
      // curtain.execute(command);
      Serial.println("SlaveCurtainController::execute");
      // CurtainMode mode = (CurtainMode)atoi(command[0]);
      char *rawAction = command[0];
      if (!isWindowOpen && rawAction[0] == 'o' && rawAction[1] == 'p' && rawAction[2] == 'e' && rawAction[3] == 'n')
      {
        for (int i = 0; i < 90; i++)
        {
          Serial.println(i);
          myServo.write(i);
          delay(15);
        }
        isWindowOpen = true;
      }
      else if (isWindowOpen && rawAction[0] == 'c' && rawAction[1] == 'l')
      {
        for (int i = 90; i > 0; i--)
        {
          Serial.println(i);
          myServo.write(i);
          delay(15);
        }
        isWindowOpen = false;
      }
    }

    else if (rawController[0] == 'b' && rawController[1] == 'u' && rawController[2] == 'z' && rawController[3] == 'z')
    
    {
      char *rawAction = command[0];
      if (rawAction[0] == 'a' && rawAction[1] == 'c' && rawAction[2] == 't' && rawAction[3] == 'i')
    {
      for(int i=0 ; i<100 ; i++)
      {
        Serial.println("Bri~~");
        digitalWrite(PC0, HIGH);
        delay(10);
        digitalWrite(PC0, LOW);
        delay(10);
      }
    }}

    else if (rawController[0] == 's' && rawController[1] == 'e' && rawController[2] == 'n')

    {
      float co2, tvoc, temp, humid;
      int brightness, co, lpg, smoke;
      byte dataByts[sizeof(float) * 8];
      // co2 = mqc.getCO2();
      // tvoc = sensor.getTVOC();
      co = mqc._MQGetGasPercentage(mqc._MQRead(MQ_PIN) / _Ro, GAS_LPG) / 1000;
      lpg = mqc._MQGetGasPercentage(mqc._MQRead(MQ_PIN) / _Ro, GAS_CO) / 100000;
      smoke = mqc._MQGetGasPercentage(mqc._MQRead(MQ_PIN) / _Ro, GAS_SMOKE) / 1000;
      temp = dht.getTemperature();
      humid = dht.getHumidity();

      brightness = static_cast<int>(ldrc.getBrightness());
      // Serial.println("Sending data");
      // Serial.println("Temperature: " + String(dht.getTemperature()) + "C");
      // Serial.println("Humidity: " + String(dht.getHumidity()) + "%");
      // Serial.println("CO: " + String(co));
      // Serial.println("LPG: " + String(lpg));
      // Serial.println("Smoke: " + String(smoke));
      // Serial.printf("CO2: %d | TVOC: %d | Temperature: %d | Humidity: %d | CO: %d | LPG: %d | Smoke: %d | Brightness: %d \n", co2, tvoc, temp, humid, co, lpg, smoke, brightness);
      float data[8] = {co2, tvoc, temp, humid, (float)co, (float)lpg, (float)smoke, (float)brightness};
      for (int i = 0; i < 8; i++)
      {
        memcpy(&dataByts[i * sizeof(float)], &data[i], sizeof(float));
      }
      chat.write(dataByts, sizeof(dataByts));
      // chat.printf("CO2: %.2f | TVOC: %.2f | Temperature: %.2f| Humidity: %.2f | CO: %.2f| LPG: %.2f | Smoke: %.2f | Brightness: %d \n", co2, tvoc, temp, humid, co, lpg, smoke, brightness);
    }
    // vTaskDelay(1000);
  }
}
