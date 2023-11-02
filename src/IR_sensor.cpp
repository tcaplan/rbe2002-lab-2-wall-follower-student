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

  // Calibration equation: adc = -24.049(1/distance) + 365.16
  float cm = 1 / ((adc - 365.16) / -24.049);
  // Calibration equation: voltage = -0.1174(1/distance) + 1.783
  float voltage = adc * v_ref / bits;
  cm = 1 / ((voltage - 1.783) / -0.1174);


  return cm;
  
}