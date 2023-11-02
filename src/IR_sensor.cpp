#include <Romi32U4.h>
#include "IR_sensor.h"

void IRsensor::Init(void)
{
    pinMode(pin_IR, INPUT);
}

float IRsensor::PrintData(void)
{
    Serial.println(ReadData());
}

float IRsensor::ReadData(void)
{
  //assignment 1.1
  //read out and calibrate your IR sensor, to convert readouts to distance in [cm]

  int adc = analogRead(pin_IR);
  
  float v_ref = 5.0; // V
  int bits = pow(2, 10) - 1;

  // Calibration equation format: y = a*x + b
  // Calibration equation: adc = 2941.5(1/distance) + 132.35
  float a = 2941.5;
  float b = 132.35;
  float cm = 1 / ((adc - b) / a);
  // Serial.print(adc);
  // Serial.print("\t");
  // Calibration equation: voltage = 18.772(1/distance) + 0.3523
  // float voltage = adc * v_ref / bits;
  // a = 18.772;
  // b = 0.3523;
  // cm = 1 / ((voltage - b) / a);

  return cm;
  
}