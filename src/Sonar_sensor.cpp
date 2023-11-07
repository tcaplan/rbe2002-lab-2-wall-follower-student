#include <Romi32U4.h>
#include "Sonar_sensor.h"

unsigned long volatile startTime = 0; 
unsigned long volatile endTime = 0; 

static void isrHigh(void)
{
    startTime = micros(); 
}

static void isrLow(void)
{
    endTime = micros(); 
}

void SonarSensor::Init(void)
{
    pinMode(pin_TRIG,OUTPUT);
    pinMode(pin_ECHO, INPUT);  
    attachInterrupt(pin_ECHO, isrHigh, RISING); 
    attachInterrupt(pin_ECHO, isrLow, FALLING);   
}

float SonarSensor::PrintData(void)
{
    Serial.println(ReadData());
}

unsigned long SonarSensor::ReadData(void)
{
    //assignment 1.2
    //read out and calibrate your sonar sensor, to convert readouts to distance in [cm]
    digitalWrite(pin_TRIG, HIGH); 
    delayMicroseconds(10);
    digitalWrite(pin_TRIG, LOW);  
    return pulseIn(pin_ECHO, HIGH); 
}