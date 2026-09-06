#ifndef _MY_OLED
#define _MY_OLED  
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <string.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_ADDR 0x3C
#define DATEPIN A0


//
void setupOLED();
bool runOLED();
bool readDateKnob();
void displayOLED(int date);
void oledCelebration() ;
//
#endif