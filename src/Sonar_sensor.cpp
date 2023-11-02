#include <Romi32U4.h>
#include "Sonar_sensor.h"
#include <math.h>

unsigned long volatile triggerStartTime = 0;
unsigned long startTime = -1;
unsigned long volatile endTime = -1;

unsigned long volatile readingStartTime = 0;

const unsigned int speed_of_sound = 340; // m/s
const unsigned int micros_to_sec = pow(10, 9);

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

        // set the time for the start of the measurement window
        startTime = millis();

        // send the pulse
        analogWrite(pin_TRIG, LOW);
        delayMicroseconds(2);
        analogWrite(pin_TRIG, HIGH);
        delayMicroseconds(10);
        analogWrite(pin_TRIG, LOW);
    }

    // return the time difference
    unsigned long time_diff = endTime - startTime;
    float range = time_diff / speed_of_sound / micros_to_sec / 2.0;
    float cm = range / 58.0;

    // Calibration equation: read_cm = -0.0008(distance) + 730.14
    float distance = (cm - 730.14) / -0.008;

    return distance;

}

/**
 * @brief ISR that sets the time the echo signal is received
 * 
 */
static void echoHighISR() {
    endTime = micros();
}



