
#include <Adafruit_NeoPixel.h> //https://github.com/adafruit/Adafruit_NeoPixel
Adafruit_NeoPixel strand = Adafruit_NeoPixel(LED_TOTAL, LED_PIN, NEO_GRB + NEO_KHZ800);

void setupNeopixel() {
  pinMode(LED_PIN, OUTPUT);
  strand.begin();
}

void setBass(struct Color color) {
  for (int led = 0; led < LED_TOTAL; led++)
  {
    strand.setPixelColor(led, strand.Color(int(color.R), int(color.G), int(color.B)));
  }

  strand.show();
}

//For intensity - determine some scale and pass in either 0-1 or 0-100.
//Test min and max intensity to determine if the distance loops are correct.
void setVocal(struct Color color, double intensity) {
  int distance = LED_HALF * intensity;

  //First Half
  for (int led = LED_HALF; led > 0; led--) {
    strand.setPixelColor(led, strand.Color(int(color.R), int(color.G), int(color.B)));
  }

  //Second Half
  for (int led = LED_HALF; led < LED_TOTAL; led++) {
    strand.setPixelColor(led, strand.Color(int(color.R), int(color.G), int(color.B)));
  }

}
