#include <Wire.h>
#include "Audio.h"
#include "MyServo.h"
#include "OLED.h"
#include "Accel.h"
const int OPENBUTTONPIN = 15;
bool openButton=false;
bool openButtonLast=false;
bool isDaysToOpenZero=false;
float degreesHome=0;
float degreesOpen=120;
//-----------------------------------------------------------------------
//
//-----------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  setupServo(degreesHome);   //
  setupAudio();   // Booting up all sensors
  setupOLED();    // 
  setupAccel();   // 
  pinMode(OPENBUTTONPIN, INPUT_PULLUP); //input for open button
  openButton=!(digitalRead(OPENBUTTONPIN));
  openButtonLast=openButton;
  closeBox();  //make sure box is closed
}
//-----------------------------------------------------------------------
// main loop
//-----------------------------------------------------------------------
void loop() {
  openButton=!(digitalRead(OPENBUTTONPIN));
  isDaysToOpenZero = runOLED();      //read knob, set OLED display
  //-------------------------------------------------
  if (isDaysToOpenZero){
    if (openButton!=openButtonLast){  //openButton was changed
      if (openButton)
        openBox();
      else
        closeBox();
      openButtonLast=openButton;
    }//end if openButton was changed
  }
  else{
    if ( getCommentFromAccGyro() ) //chcek accel if it was picked up
      runAUDIO(1);  //play accel comment
    else{             //no acceleration
      if (openButton) //check if openButton is true
        runAUDIO(2); //play button comment
    }
  }//end
  delay(50);
}
//-----------------------------------------------------------------------
//
//-----------------------------------------------------------------------
void openBox(){
  Serial.println("Box is opening"); 
  oledCelebration();
  runAUDIO(4);
  moveServoSlow(degreesOpen, 100); 
}

void closeBox(){
  Serial.println("Box is closing"); 
  moveServoSlow(degreesHome, 100); 
}