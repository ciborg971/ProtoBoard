#define version 0.1
#include "pin.hpp"
#include "config.h"

AnalogPin* ap_arr[32];
bool ap_val_arr[32];
#include <ESP32Servo.h>
#include <Adafruit_NeoPixel.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("Starting HW-Test ");
  Serial.println(version);
  Adafruit_NeoPixel pixels(1, 23, NEO_GRB + NEO_KHZ800);
  pixels.begin();
  // Battery pin
  for(int i = 0; i < 32; i++)
  {
    ap_val_arr[i] = false;
  }
  ap_val_arr[22] = true;
  //---------Multiplexer Test---------
  pixels.setPixelColor(0, pixels.Color(0, 150, 0));
  pixels.show();
  Serial.println("---------Multiplexer Test---------");
  pinMode(MUX_SEL_0, OUTPUT);
  pinMode(MUX_SEL_1, OUTPUT);
  pinMode(MUX_SEL_2, OUTPUT);
  pinMode(MUX_SEL_3, OUTPUT);
  initAllMultiplexed();
  Serial.println("Put every multiplexed pin to 3.3V one by one");
  while(!checkAllMultiplexed())
  {
    ;;  
  }
  Serial.println("Multiplexer Test done");
  
  
  //---------Battery voltage---------
  pixels.setPixelColor(0, pixels.Color(0, 150, 150));
  pixels.show();
  Serial.println("----------Battery voltage Test---------");
  Serial.print("Battery : ");
  Serial.print((ap_arr[22]->read() * 0.166) / 4096);
  Serial.print(" Volt : ");
  Serial.println(((ap_arr[22]->read() * 0.166) / 4096) >= 7.0 ? "OK" : "KO");

  //ERM
  pixels.setPixelColor(0, pixels.Color(150, 0, 150));
  pixels.show();
  Serial.println("----------ERM---------");
  activateAllERM();

  //Servo
  pixels.setPixelColor(0, pixels.Color(150, 150, 0));
  pixels.show();
  Serial.println("----------Servo---------");
  activateAllServo();
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}


void activateAllServo()
{
  int minUs = 1000;
  int maxUs = 2000;
  int pos = 0;
  ESP32PWM pwm;
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  Servo* servos[] = {new Servo(), new Servo(), new Servo(), new Servo(), new Servo()};
  servos[0]->setPeriodHertz(50);
  servos[1]->setPeriodHertz(50);
  servos[2]->setPeriodHertz(50);
  servos[3]->setPeriodHertz(50);
  servos[4]->setPeriodHertz(50);

  pwm.attachPin(27, 10000);//10khz
   
  servos[0]->attach(PIN_THUMB_FFB, minUs, maxUs);
  servos[1]->attach(PIN_INDEX_FFB, minUs, maxUs);
  servos[2]->attach(PIN_MIDDLE_FFB, minUs, maxUs);
  servos[3]->attach(PIN_RING_FFB, minUs, maxUs);
  servos[4]->attach(PIN_PINKY_FFB, minUs, maxUs);


  for (pos = 0; pos <= 180; pos += 1) 
  { // sweep from 0 degrees to 180 degrees
    // in steps of 1 degree
    for(int i = 0; i < sizeof(servos); i++)
    {
      servos[i]->write(pos);
    }
    delay(1);             // waits 20ms for the servo to reach the position
  }
  
  for (pos = 180; pos >= 0; pos -= 1) 
  { // sweep from 180 degrees to 0 degrees
    for(int i = 0; i < sizeof(servos); i++)
    {
      servos[i]->write(pos);
    }
    delay(1);
  }

  for(int i = 0; i < sizeof(servos); i++)
  {
    servos[i]->detach();
  }

  pwm.detachPin(27);
}


void activateAllERM()
{
  const int freq = 5000;
  const int resolution = 8;
  
  int ERM_Pin[] = {18, 5, 19, 17, 16};
  for(int i = 0; i < sizeof(ERM_Pin); i++)
  {
    Serial.print("Testing ERM ");
    Serial.println(i);
    ledcAttachPin(ERM_Pin[i], i);
    for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){
      ledcWrite(i, dutyCycle);
      delay(15);
    }
    ledcDetachPin(i);
    Serial.println();
  }
}

bool checkAllMultiplexed()
{
  bool result = true;
  
  for(int i = 0; i < 32; i++)
  {
    bool pin_res = ap_arr[i]->read() > 2048;
    if(pin_res)
    {
      ap_val_arr[i] = true;
      Serial.print("Pin M");
      Serial.print(i);
      Serial.print(" val : ");
      Serial.print(ap_arr[i]->read());
      Serial.println(" : OK"); 
    }
    else
    {
      result = result && ap_val_arr[i];
    }
  }
  return result;
}

void initAllMultiplexed()
{
  ap_arr[0] = new MultiplexedPin<M0>();
  ap_arr[1] = new MultiplexedPin<M1>();
  ap_arr[2] = new MultiplexedPin<M2>();
  ap_arr[3] = new MultiplexedPin<M3>();
  ap_arr[4] = new MultiplexedPin<M4>();
  ap_arr[5] = new MultiplexedPin<M5>();
  ap_arr[6] = new MultiplexedPin<M6>();
  ap_arr[7] = new MultiplexedPin<M7>();
  ap_arr[8] = new MultiplexedPin<M8>();
  ap_arr[9] = new MultiplexedPin<M9>();
  ap_arr[10] = new MultiplexedPin<M10>();
  ap_arr[11] = new MultiplexedPin<M11>();
  ap_arr[12] = new MultiplexedPin<M12>();
  ap_arr[13] = new MultiplexedPin<M13>();
  ap_arr[14] = new MultiplexedPin<M14>();
  ap_arr[15] = new MultiplexedPin<M15>();
  ap_arr[16] = new MultiplexedPin<M16>();
  ap_arr[17] = new MultiplexedPin<M17>();
  ap_arr[18] = new MultiplexedPin<M18>();
  ap_arr[19] = new MultiplexedPin<M19>();
  ap_arr[20] = new MultiplexedPin<M20>();
  ap_arr[21] = new MultiplexedPin<M21>();
  ap_arr[22] = new MultiplexedPin<M22>();
  ap_arr[23] = new MultiplexedPin<M23>();
  ap_arr[24] = new MultiplexedPin<M24>();
  ap_arr[25] = new MultiplexedPin<M25>();
  ap_arr[26] = new MultiplexedPin<M26>();
  ap_arr[27] = new MultiplexedPin<M27>();
  ap_arr[28] = new MultiplexedPin<M28>();
  ap_arr[29] = new MultiplexedPin<M29>();
  ap_arr[30] = new MultiplexedPin<M30>();
  ap_arr[31] = new MultiplexedPin<M31>();
}

void loop() {
  // put your main code here, to run repeatedly:

}
