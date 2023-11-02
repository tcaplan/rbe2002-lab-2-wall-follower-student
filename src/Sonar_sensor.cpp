#include <Romi32U4.h>
#include "Sonar_sensor.h"

unsigned long volatile triggerStartTime = 0;
unsigned long startTime = -1;
unsigned long volatile endTime = -1;

unsigned long volatile readingStartTime = 0;

static void echoHighISR(void);

void SonarSensor::Init(void)
{
    pinMode(pin_TRIG,OUTPUT);
    pinMode(pin_ECHO, INPUT);   

    // set the ISR to trigger when the echo pin has a rising edge
    attachInterrupt(pin_ECHO, echoHighISR, RISING);
}

float SonarSensor::PrintData(void)
{
    Serial.println(ReadData());
}

float SonarSensor::ReadData(void)
{
    //assignment 1.2
    //read out and calibrate your sonar sensor, to convert readouts to distance in [cm]

    // Send the TRIG pulse for 10 microseconds
    if(millis() - readingStartTime > 60) {

        noInterrupts();
        // set the time for the start of the measurement window
        readingStartTime = millis();

        // send the pulse
        analogWrite(pin_TRIG, LOW);
        delayMicroseconds(2);
        analogWrite(pin_TRIG, HIGH);
        delayMicroseconds(10);
        analogWrite(pin_TRIG, LOW);
        startTime = micros();
        interrupts();
    }

    // return the time difference
    return endTime - startTime;
}

/**
 * @brief ISR that sets the time the echo signal is received
 * 
 */
static void echoHighISR() {
    endTime = micros();
}



