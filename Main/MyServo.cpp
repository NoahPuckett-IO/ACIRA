#include "MyServo.h"
const int servoNum=0;       //using servo number 0 on PCA8855
const int SERVOMIN=600;
const int SERVOMAX=2400;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
float lastServoPosition=0;
//-----------------------------------------------------------------------
//pin 13 ENABLE is servo 
//-----------------------------------------------------------------------
void setupServo(float degrees) {
  Serial.begin(9600);
  Serial.println("PWM test!");
  pwm.begin();
  pwm.setPWMFreq(50); // This is the maximum PWM frequency
  moveServo(degrees);       //make sure in home position
}
//-----------------------------------------------------------------------
//
//-----------------------------------------------------------------------
void moveServo(float degrees){
  int pulselength = map(degrees, 0, 180, SERVOMIN, SERVOMAX);
  pwm.writeMicroseconds(servoNum, pulselength);
}
//-----------------------------------------------------------------------
//
//-----------------------------------------------------------------------
void moveServoSlow(float degrees, int Nsteps){ //position, subdivisions
  Serial.print("moving Servo to ");Serial.println(degrees);
  float position = lastServoPosition;
  float dDegrees = (degrees-position)/Nsteps;
  for (int i=0; i<Nsteps; i++){
    position += dDegrees;
    moveServo(position);
    delay(10);
  }
  lastServoPosition=degrees;
}