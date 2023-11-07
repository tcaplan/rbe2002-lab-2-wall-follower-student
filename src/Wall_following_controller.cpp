#include <Romi32U4.h>
#include "Encoders.h"
#include "Wall_following_controller.h"
#include "IR_sensor.h"
#include "Sonar_sensor.h"

#define SIZE 19
#define ANGLE 60

IRsensor SharpIR;
SonarSensor HCSR04;
float speeds[SIZE];
int index = 0;
bool filled = false;

void sort(float* arr, int i);

void WallFollowingController::Init(void)
{
    SharpIR.Init();
    HCSR04.Init();
    filled = false;
}

float WallFollowingController::Process(float target_distance)
{
  //assignment 2: write a PD controller that outputs speed as a function of distance error
  float angle = 0.7;// rad //cos(ANGLE * M_1_PI / 180.0);
  float reading = (SharpIR.ReadData() * angle) - 4;
  E_distance = target_distance - reading;
  float de = E_distance - prev_e_distance;
  float speed = Kp * E_distance + Kd * de;
  // Serial.print("\tD ");
  // Serial.print(reading);
  // Serial.print("\t");
  // Serial.print(E_distance);
  // Serial.print("\t");
  // Serial.print(de); 
  prev_e_distance = E_distance;
  if(!filled) {
    index = 0;
    for(int i = 0; i < SIZE; i++) {
      speeds[i] = speed;
    }
  } else {
    index++;
    if(index >= SIZE) index = 0;
  }

  speeds[index] = speed;
  
  sort(speeds, index);

  index++;
  if(index >= SIZE) index = 0;
  


  Serial.print(" [");
  for(int i = 0; i < SIZE; i++) {
    Serial.print(speeds[i]);
    if(i != SIZE - 1) {
      Serial.print(", ");
    }
  }
  Serial.print(" ]\t");
  Serial.print(speeds[SIZE/2]);
  return speeds[SIZE/2];
}


void sort(float* arr, int i) {

  bool shiftedDown = false;
  int j = i;
  while(j > 0 && arr[j-1] > arr[j]) {
    float temp = arr[j-1];
    arr[j-1] = arr[j];
    arr[j] = temp;
    j--;
    shiftedDown = true;
  }
  if(!shiftedDown) {
    j = i;
    while(j < 5 && arr[j+1] < arr[j]) {
      float temp = arr[j+1];
      arr[j+1] = arr[j];
      arr[j] = temp;
    }
  }
}