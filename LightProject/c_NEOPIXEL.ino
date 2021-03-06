
#include <Adafruit_NeoPixel.h> //https://github.com/adafruit/Adafruit_NeoPixel
Adafruit_NeoPixel strand = Adafruit_NeoPixel(LED_TOTAL, LED_PIN, NEO_GRB + NEO_KHZ800);

void setupNeopixel() {
  pinMode(LED_PIN, OUTPUT);
  strand.begin();
}

struct Color deltaC = Color {
  0, 0, 0
};
struct Color startC = Color {
  0, 0, 0
}; //Easier than retrieving the current color from the neopixel byte array (getPixelColor func)
bool hasMetColor = false;

void setBass(struct Color color) {
  setColor(color);
//  deltaC = color - startC;
//  hasMetColor = false;
}

void tickColor(double transitionPercent) {
  if (hasMetColor == true) {
    return;
  }

  struct Color currentColor = (deltaC * transitionPercent) + startC;
  setColor(currentColor);

  if (transitionPercent == 1) {
    startC = currentColor;
    hasMetColor = true;
  }
}

void setColor(struct Color color) {
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
    strand.setPixelColor(led, strand.Color(color.R, color.G, color.B));
  }

}
