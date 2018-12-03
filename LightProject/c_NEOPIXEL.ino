#include <Adafruit_NeoPixel.h> //https://github.com/adafruit/Adafruit_NeoPixel
Adafruit_NeoPixel strand = Adafruit_NeoPixel(LED_TOTAL, LED_PIN, NEO_GRB + NEO_KHZ800);

void setupNeopixel() {
  pinMode(LED_PIN, OUTPUT);
  strand.begin();
}

void setBass(struct Color color) {
  for (int led = 0; led < LED_TOTAL; led++)
  {
    strand.setPixelColor(led, strand.Color(color.R, color.G, color.B));
  }

  strand.show();
}
