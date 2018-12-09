#define PI 3.1415926535897932384626433832795

struct Color {
  int R;
  int G;
  int B;

  struct Color operator-(struct Color color) const {
    double deltaR = R - color.R;
    double deltaG = G - color.G;
    double deltaB = B - color.B;
    return Color {deltaR, deltaG, deltaB};
  }

  struct Color operator+(struct Color color) const {
    double deltaR = R + color.R;
    double deltaG = G + color.G;
    double deltaB = B + color.B;
    return Color {deltaR, deltaG, deltaB};
  }  

  struct Color operator*(double scale) const {
    double deltaR = R * scale;
    double deltaG = G * scale;
    double deltaB = B * scale;
    return Color {deltaR, deltaG, deltaB};
  }
};

struct Color getColor(struct FreqData data[], unsigned int len) {
  //TODO: Maybe reimplement the noise filter later. Definitely add some scaling logic.

  filterNoise(data, len);

  Serial.println();
  Serial.print("MIN:");
  Serial.print(data[0].frequency);
  Serial.println();
  Serial.print("MAX:");
  Serial.print(data[len - 1].frequency);
  Serial.println();

  //Find Total Amplitude(s)
  double weightedAmp = 0;
  double totalAmp = 0;

  for (int i = 0; i < len; i++) {
    weightedAmp += data[i].frequency * data[i].amplitude;
    totalAmp += data[i].amplitude;
  }

  //Find Average Frequency
  double average = weightedAmp / totalAmp; //Handle case of 0 as total amp.

  //Calculate RGB Values
  //TODO: CALCULATE COLORS
  double minFrequency = data[0].frequency;
  double maxFrequency = data[len - 1].frequency;
  double range = maxFrequency - minFrequency;
  double scaleFreq = average - minFrequency;
  //  double middleFrequency = (maxFrequency + minFrequency) / 2;

  //  double RB_Range = middleFrequency - minFrequency; //Upper - lower
  //  double GB_Range = maxFrequency - middleFrequency;

  int R = colorWave(0, average, minFrequency, maxFrequency);
  int G = colorWave(-(2 * 256), average, minFrequency, maxFrequency);
  int B = colorWave(-(4 * 256), average, minFrequency, maxFrequency);

  Serial.println(average);
  //  Serial.print(R);
  //  Serial.print(" ");
  //  Serial.print(G);
  //  Serial.print(" ");
  //  Serial.println(B);

  if (totalAmp > 0) {
    return Color {R, G, B};
  } else {
    return Color {0, 0, 0};
  }
}

int colorWave(int offset, double frequency, double minFrequency, double maxFrequency) {
  double ratio = (6.0 * 256.0) / (maxFrequency - minFrequency);
  int scalePos = (int((frequency - minFrequency) * ratio) + offset) % (6 * 256);
  int colPos = scalePos % 256;

  if (scalePos < 0) {
    scalePos = 6 * 256 + scalePos;
  }

  if (colPos < 0) {
    colPos = 256 + colPos;
  }

  //  Serial.print("Ratio:  ");
  //  Serial.println(ratio);

  if (0 <= scalePos && scalePos < 256) {
    return 255;
  } else if (256 <= scalePos && scalePos < 2 * 256) {
    return 255 - colPos;
  } else if (256 * 4 <= scalePos && scalePos < 256 * 5) {
    return colPos;
  } else if (256 * 5 <= scalePos && scalePos < 256 * 6) {
    return 255;
  } else {
    return 0;
  }
}

//double absRelu(double val, bool neg) {
//  if (neg) {
//    return val < 0 ? abs(val) : 0;
//  } else {
//    return val > 0 ? val : 0;
//  }
//}

void filterNoise(struct FreqData data[], unsigned int len) {
  for (int i = 0; i < len; i++) {
    if (data[i].amplitude < NOISE_BASELINE) {
      data[i].amplitude = 0;
    }
  }
}



//struct Color averageColor(struct Color c1, struct Color c2) {
//  struct Color col = Color {
//    sqrt(c1.R * c1.R + c2.R * c2.R), sqrt(c1.G * c1.G + c2.G * c2.G), sqrt(c1.B * c1.B + c2.B * c2.B)
//  };
//
//  return Color{sqrt(c1.R * c1.R + c2.R * c2.R), sqrt(c1.G * c1.G + c2.G * c2.G), sqrt(c1.B * c1.B + c2.B * c2.B)};
//}

//double getLowestAmp(struct FreqData data[], unsigned int len) {
//  double lowest = data[0].amplitude;
//  for (int i = 0; i < len; i++) {
//    if (data[i].amplitude != -1 && lowest > data[i].amplitude) {
//      lowest = data[i].amplitude;
//    }
//  }
//
//  return lowest > 0 ? lowest : 0;
//}
//
//double getHighestAmp(struct FreqData data[], unsigned int len) {
//  double highest = data[0].amplitude;
//  for (int i = 0; i < len; i++) {
//    if (highest < data[i].amplitude) {
//      highest = data[i].amplitude;
//    }
//  }
//
//  return highest;
//}
