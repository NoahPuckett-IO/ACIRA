#include "OLED.h"

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT);
int dateKnobPin = 13;
int date = 0;
int dateLast=0;
const int ddate = 1;

void setupOLED() {
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("BOOTING UP...");
  display.display();
  pinMode(36,INPUT); 
  delay(100);
}

bool runOLED() { //returns isDaysToOpenZero
  readDateKnob();
  displayOLED(date);
  return ( date<1 ); //true if date is zero, false otherwise
}

void displayOLED(int date) {
  display.clearDisplay();
  char buffer[5];
  dtostrf(date,3,0,buffer);
  display.setTextColor(WHITE);
  display.setCursor(1, 1);
  display.setTextSize(1);
  display.println("days until opened:");
  display.setTextColor(WHITE);
  display.setTextSize(3);
  display.setCursor(10, 18);
  display.println(buffer);
  if (date<1){
    display.setTextSize(2);
    display.setCursor(2, 40);
    display.println("open now!");
  }
  display.display();
}


bool readDateKnob() {
  bool isDateUpdate=false;
  int aValue = analogRead(dateKnobPin); // read voltage of 27 pin, 0,4095, this is the number for esp32
  float aDate = aValue * (31.0/4095); //fix 
  date = static_cast<int>( aDate);
  Serial.print("DATE:  analog read : ");Serial.print(aValue);Serial.print(" date : ");Serial.println(date);
  if (date != dateLast){     
    isDateUpdate = true;
   } 
  dateLast = date;
  return isDateUpdate;
}

void oledCelebration() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0, 8);
  display.println("Congratulations!");
  display.display();
}
