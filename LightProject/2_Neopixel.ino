
#include "config.h"
#include <Adafruit_NeoPixel.h> //https://github.com/adafruit/Adafruit_NeoPixel
Adafruit_NeoPixel strand = Adafruit_NeoPixel(LED_TOTAL, LED_PIN, NEO_GRB + NEO_KHZ800);

void setupNeopixel() {
  pinMode(LED_PIN, OUTPUT);
  strand.begin();
}
