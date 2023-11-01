#include <Romi32U4.h>
#include "Sonar_sensor.h"

unsigned long volatile triggerStartTime = 0;
unsigned long volatile startTime = -1;
unsigned long volatile endTime = -1;

unsigned long volatile readingStartTime = 0;

static void startReading(void);
static void echoLowISR(void);

void SonarSensor::Init(void)
{
    pinMode(pin_TRIG,OUTPUT);
    pinMode(pin_ECHO, INPUT);   

    attachInterrupt(pin_TRIG, startReading, RISING);
    attachInterrupt(pin_ECHO, echoLowISR, RISING);
}

float SonarSensor::PrintData(void)
{
    // Serial.println(ReadData());
    Serial.print(ReadData());
}

float SonarSensor::ReadData(void)
{
    //assignment 1.2
    //read out and calibrate your sonar sensor, to convert readouts to distance in [cm]

    // UNTESTED DO NOT TRUST

    // Send the TRIG pulse for 10 microseconds
    if(millis() - readingStartTime > 60) {
        analogWrite(pin_TRIG, LOW);
        delayMicroseconds(2);
        analogWrite(pin_TRIG, HIGH);
        delayMicroseconds(10);
        analogWrite(pin_TRIG, LOW);
        startTime = micros();
    }

    return endTime - startTime;
}

static void startReading() {
    readingStartTime = millis();
}

static void echoLowISR() {
    Serial.print(" IN ECHO LOW ISR ");
    endTime = micros();
}



