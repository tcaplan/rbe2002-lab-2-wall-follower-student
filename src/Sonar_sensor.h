#ifndef SONAR_SENSOR
#define SONAR_SENSOR

#include <Romi32U4.h>

class SonarSensor{
    private:
        const int pin_TRIG = 0;
        const int pin_ECHO = 1;
    public:
        void Init(void); 
        unsigned long ReadData(void); 
        float PrintData(void);
        //static void isrHigh(void); 
        //static void isrLow(void);   
};

#endif