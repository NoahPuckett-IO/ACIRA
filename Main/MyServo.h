#ifndef _MY_SERVO   
#define _MY_SERVO  
#include <Wire.h>
#include <arduino.h>
#include <Adafruit_PWMServoDriver.h>
//
void setupServo(float degrees);
void moveServo(float degrees);
void moveServoSlow(float degrees, int Nsteps);
//
#endif