#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h> //https://github.com/adafruit/Adafruit_NeoPixel

//-------- Customise the above values --------

#define LED_TOTAL 12 // Your Led strip pixel
#define LED_HALF LED_TOTAL/2
#define VISUALS 6
#define analog_pin A0
#define LED_PIN 13
#define online_pin 4

Adafruit_NeoPixel strand = Adafruit_NeoPixel(LED_TOTAL, LED_PIN, NEO_GRB + NEO_KHZ800);

int reading;

uint16_t gradient = 0;
uint16_t thresholds[] = {1529, 1019, 764, 764, 764, 1274};
uint8_t palette = 0;
uint8_t visual = 0;
uint8_t volume = 0;
uint8_t last = 0;

float maxVol = 15;
float avgBump = 0;
float avgVol = 0;

int8_t pos[LED_TOTAL] = { -2};
uint8_t rgb[LED_TOTAL][3] = {0};

bool shuffle = true;
bool bump = true;

bool left = false;
int8_t dotPos = 0;
float timeBump = 0;
float avgTime = 0;


//Initialization
void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(online_pin, OUTPUT);
  Serial.begin(115200);
  Serial.println();
  strand.begin();
}

void loop() {
  reading = digitalRead(online_pin);
  getDance();
}

//Primary
void getDance() {
  volume = analogRead(analog_pin);


  if (volume < avgVol / 2.0 || volume < 15) {
    volume = 0;
  } else {
    avgVol = (avgVol + volume) / 2.0;
  }

  if (volume > maxVol) maxVol = volume;
  if (gradient > thresholds[palette]) {
    gradient %= thresholds[palette] + 1;
    maxVol = (maxVol + volume) / 2.0;
  }

  if (volume - last > 10) avgBump = (avgBump + (volume - last)) / 2.0;
  bump = (volume - last > avgBump * .9);

  if (bump) {
    avgTime = (((millis() / 1000.0) - timeBump) + avgTime) / 2.0;
    timeBump = millis() / 1000.0;
  }

  Visualize();
  gradient++;
  last = volume;
  delay(30);
}

///////////////////////////////////////////////////////////////////////


void Visualize() {
  return Pulse();
}

//////////////////////////////////////////////////


uint32_t ColorPalette(float num) {
  return (num < 0) ? Rainbow(gradient) : Rainbow(num);
}

///////////////////////////////////////////////////////////


void Pulse() {
  fade(0.9);
  if (bump) gradient += thresholds[palette] / 24;
  if (volume > 0) {
    uint32_t col = ColorPalette(-1);
    int start = LED_HALF - (LED_HALF * (volume / maxVol));
    int finish = LED_HALF + (LED_HALF * (volume / maxVol)) + strand.numPixels() % 2;

    for (int i = start; i < finish; i++) {
      float damp = sin((i - start) * PI / float(finish - start));
      damp = pow(damp, 2.0);
      uint32_t col2 = strand.getPixelColor(i);
      uint8_t colors[3];
      float avgCol = 0;
      float avgCol2 = 0;
      for (int k = 0; k < 3; k++) {
        colors[k] = split(col, k) * damp * pow(volume / maxVol, 2);
        avgCol += colors[k];
        avgCol2 += split(col2, k);
      }
      avgCol /= 3.0, avgCol2 /= 3.0;
      if (avgCol > avgCol2) strand.setPixelColor(i, strand.Color(colors[0], colors[1], colors[2]));
    }
  }
  strand.show();
}

//////////////////////////////////////////////////////////////


void fade(float damper) {
  for (int i = 0; i < strand.numPixels(); i++) {
    uint32_t col = strand.getPixelColor(i);
    if (col == 0) continue;
    float colors[3];
    for (int j = 0; j < 3; j++) colors[j] = split(col, j) * damper;
    strand.setPixelColor(i, strand.Color(colors[0] , colors[1], colors[2]));
  }
}

/////////////////////////////////////////////////////////////////////////////////


uint8_t split(uint32_t color, uint8_t i ) {
  if (i == 0) return color >> 16;
  if (i == 1) return color >> 8;
  if (i == 2) return color >> 0;
  return -1;
}

//////////////////////////////////////////////////
//COLOR PALETTES
//////////////////////////////////////////////////


uint32_t Rainbow(unsigned int i) {
  if (i > 1529) return Rainbow(i % 1530);
  if (i > 1274) return strand.Color(255, 0, 255 - (i % 255));
  if (i > 1019) return strand.Color((i % 255), 0, 255);
  if (i > 764) return strand.Color(0, 255 - (i % 255), 255);
  if (i > 509) return strand.Color(0, 255, (i % 255));
  if (i > 255) return strand.Color(255 - (i % 255), 255, 0);
  return strand.Color(255, i, 0);
}
