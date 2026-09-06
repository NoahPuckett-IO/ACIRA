#ifndef _MY_ACCEL    
#define _MY_ACCEL 
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

//define this struct to handle acc and gyro
struct myAccel_t {float x;float y;float z;};
//
void setupAccel();
bool getCommentFromAccGyro();
void getAccelGyroReading();
void printAccelGyro();
//
#endif