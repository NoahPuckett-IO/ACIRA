#ifndef _MY_AUDIO      
#define _MY_AUDIO
#include <DFRobotDFPlayerMini.h>
#define FPSerial Serial1
const int DFPLAYERBUSYPIN = 35; //df player busy pin
//
void loopAudio();
void setupAudio();
void runAUDIO(char playFolder);
void waitUntilPlayerFinished();
//
#endif