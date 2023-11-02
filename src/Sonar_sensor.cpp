#include <Romi32U4.h>
#include "Sonar_sensor.h"

unsigned long readingStartTime = 0;
unsigned long duration = 0;

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

    if(millis() - readingStartTime >= 6) {
        readingStartTime = millis();
        // clear trig
        digitalWrite(pin_TRIG, LOW);
        delayMicroseconds(2);
        // send pulse
        digitalWrite(pin_TRIG, HIGH);
        delayMicroseconds(10);
        digitalWrite(pin_TRIG, LOW);

        // get duration between trig pulse and echo received
        unsigned long temp_duration = pulseIn(pin_ECHO, HIGH);
        if(temp_duration > 0) {
            duration = temp_duration;
        }
    }

    // return the time difference
    return duration;
}



