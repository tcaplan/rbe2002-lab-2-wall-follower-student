#include <Romi32U4.h>
#include "Encoders.h"
#include "Wall_following_controller.h"
#include "IR_sensor.h"
#include "Sonar_sensor.h"

IRsensor SharpIR;
SonarSensor HCSR04;
float speeds[5];
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
  E_distance = target_distance - (SharpIR.ReadData() * cos(50));
  float de = E_distance - prev_e_distance;
  float speed = Kp * E_distance + Kd * de;
  Serial.print(E_distance);
  Serial.print("\t");
  Serial.println(de);
  prev_e_distance = E_distance;
  if(!filled) {
    index = 0;
    for(int i = 0; i < 5; i++) {
      speeds[i] = speed;
    }
  } else {
    index++;
    if(index >= 5) index = 0;
  }

  speeds[index] = speed;
  
  sort(speeds, index);

  index++;
  if(index >= 5) index = 0;
  

  return speeds[2];
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