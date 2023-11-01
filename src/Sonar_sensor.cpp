#include <Romi32U4.h>
#include "Sonar_sensor.h"

bool waitingEcho = false;
unsigned long time = 0;
unsigned long prev = -1;

void SonarSensor::Init(void)
{
    pinMode(pin_TRIG,OUTPUT);
    pinMode(pin_ECHO, INPUT);   
}

float SonarSensor::PrintData(void)
{
    
    Serial.println(ReadData());
}

float SonarSensor::ReadData(void)
{
    //assignment 1.2
    //read out and calibrate your sonar sensor, to convert readouts to distance in [cm]


    // UNTESTED DO NOT TRUST
    if(!waitingEcho) {
        analogWrite(pin_TRIG, HIGH);
        time = micros();
    }
    if(digitalRead(pin_TRIG) == HIGH && micros() - time >= 10) {
        analogWrite(pin_TRIG, 0);
        waitingEcho = true;
        time = micros();
    }
    if(waitingEcho && digitalRead(pin_ECHO) == HIGH) {
        prev = micros() - time;
    }
    return prev;
}