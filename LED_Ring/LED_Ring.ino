#include <Adafruit_NeoPixel.h>
#include "hsv.h"

// data pin
#define PIN 6
// led count
#define CNT 16
// max Hue
#define MAXHUE 256*6

int position = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(CNT, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
}

void loop() {
  // hue - red
  // saturation - max
  // value - 0-255
  for (int i = 0; i < CNT; i++)
    strip.setPixelColor((i + position) % CNT, getPixelColorHsv(i, 0, 250, strip.gamma8(i * (70 / CNT))));
  strip.show();
  position++;
  position %= CNT;
  delay(50);
}
