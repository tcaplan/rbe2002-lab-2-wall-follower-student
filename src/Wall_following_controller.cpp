#include <Romi32U4.h>
#include "Encoders.h"
#include "Wall_following_controller.h"
#include "IR_sensor.h"
#include "Sonar_sensor.h"

IRsensor SharpIR;
SonarSensor HCSR04;
void WallFollowingController::Init(void)
{
    SharpIR.Init();
    HCSR04.Init();
}


float WallFollowingController::Process(float target_distance)
{
  //assignment 2: write a PD controller that outputs speed as a function of distance error
  E_distance = target_distance - (2.8876 / ((SharpIR.ReadData() / 4095.0 * 5.0) - 0.2128)); 
  float de = E_distance - prev_e_distance; 
  float speed = Kp*E_distance + Kd*de;
  Serial.println(E_distance);
  prev_e_distance = E_distance; 
  return speed;
}