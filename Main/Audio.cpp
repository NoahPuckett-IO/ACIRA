#include "Audio.h"
//-----------------------------------------------------------------------
// Create the Player object
//-----------------------------------------------------------------------
DFRobotDFPlayerMini player;
const char track1max=4;   
const char track2max=4;   
static char track1=1;   
static char track2=1;  
long timeStart;
//-----------------------------------------------------------------------
//
//-----------------------------------------------------------------------
void setupAudio(){  
  // setup DFPlayer
  Serial.begin(9600);
  FPSerial.begin(9600, SERIAL_8N1, 16, 17);
  if (!player.begin(FPSerial, /*isACK = */true, /*doReset = */true)) {  //Use serial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  pinMode(DFPLAYERBUSYPIN, INPUT); //input for df player busy
  Serial.println(F("DFPlayer Mini online."));
  Serial.println(F("DFplayer Found!"));
  player.volume(25); // set volume
}

//Folder 1    MPU sensor
//Folder 2    Button 
//-----------------------------------------------------------------------
//
//-----------------------------------------------------------------------
void runAUDIO(char playFolder) {
  //play the right file 
  if (playFolder == 1){    
    Serial.print("playFolder ");Serial.print(int(playFolder));Serial.print(" track ");Serial.println(int(track1));
    player.playFolder(1,track1);  
    waitUntilPlayerFinished();
    track1++;  
    if (track1>track1max)
      track1=1; 
  }
  
  else if (playFolder == 2){  
    Serial.print("playFolder ");Serial.print(int(playFolder));Serial.print(" track ");Serial.println(int(track2));
    player.playFolder(2,track2);  
    waitUntilPlayerFinished();
    track2++;  
    if (track2>track2max)
      track2=1; 
  }

  else if (playFolder == 4){  
    Serial.print("playFolder ");Serial.println(int(playFolder));
    player.playFolder(4,1); 
    delay(2000);
  }
}

void waitUntilPlayerFinished(){
  int maxCount = 50; int count=0;
  while ( (!digitalRead(DFPLAYERBUSYPIN)) || (count<maxCount) ){ //the busy pin is true when not busy
    count++;
    delay(200); 
    Serial.println(count);
  }
  delay(100);
}