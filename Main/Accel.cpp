#include "Accel.h"
Adafruit_MPU6050 mpu;
// store acceleration(x,y,z) and gyro
myAccel_t acc,accLast,gyro;   
const float accThresh  = 2;
const float gyroThresh = 0.8;
const int Nmeasurements = 3;   
//-----------------------------------------------------------------------
//
//-----------------------------------------------------------------------
void setupAccel(){
  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
  //setting mpu range
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  //get initial reading
  getAccelGyroReading();
  accLast = acc;
}

//-----------------------------------------------------------------------
//
//-----------------------------------------------------------------------
bool getCommentFromAccGyro(){
  bool output = 0;           //don't play anything is default
  getAccelGyroReading();
  float accValue = sqrt( sq(acc.x-accLast.x)+sq(acc.y-accLast.y)+sq(acc.z-accLast.z));
  float gyroValue= sqrt( sq(gyro.x)+sq(gyro.y)+sq(gyro.z));
  //-------------------------------------------
  //debuging
  Serial.print("accValue : ");Serial.print(accValue);Serial.print(" gyroValue : ");Serial.println(gyroValue);
  //-------------------------------------------
  if (( gyroValue > gyroThresh) && ( accValue > accThresh)){
      output = 1;           //play folder 1
      Serial.println("Playing 1");
  }

  // only update acc last if there was an event
  if (output!=0)
    accLast=acc;
  //-------------------------------------------
  return output;
}

//-----------------------------------------------------------------------
//
//-----------------------------------------------------------------------
void getAccelGyroReading(){
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  acc.x = a.acceleration.x;    //acc.x = acc.x + newMeas.x
  acc.y = a.acceleration.y;
  acc.z = a.acceleration.z;
  gyro.x = g.gyro.x;
  gyro.y = g.gyro.y;
  gyro.z = g.gyro.z; 
  //
  printAccelGyro();
}

//-----------------------------------------------------------------------
//
//-----------------------------------------------------------------------
void printAccelGyro(){
  /* Print out the values */
  Serial.print("Acceleration X: ");
  Serial.print(acc.x);
  Serial.print(", Y: ");
  Serial.print(acc.y);
  Serial.print(", Z: ");
  Serial.print(acc.z);
  Serial.println(" m/s^2");  
  Serial.print("Rotation X: ");
  Serial.print(gyro.x);
  Serial.print(", Y: ");
  Serial.print(gyro.y);
  Serial.print(", Z: ");
  Serial.print(gyro.z);
  Serial.println(" rad/s");
}
