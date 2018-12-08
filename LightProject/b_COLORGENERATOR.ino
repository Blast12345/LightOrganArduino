#define PI 3.1415926535897932384626433832795

struct Color {
  double R;
  double G;
  double B;
};

struct Color getColor(struct FreqData data[], unsigned int len) {
  //TODO: Maybe reimplement the noise filter later. Definitely add some scaling logic.

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
  double middleFrequency = (minFrequency + maxFrequency) / 2;

  double RB_Range = middleFrequency - minFrequency; //Upper - lower
  double GB_Range = maxFrequency - middleFrequency;

  double R = 0;
  double G = 0;
  double B = 0;

  return Color {R, G, B};
}

//double absRelu(double val, bool neg) {
//  if (neg) {
//    return val < 0 ? abs(val) : 0;
//  } else {
//    return val > 0 ? val : 0;
//  }
//}

//void filterNoise(struct FreqData data[], unsigned int len) {
//  for (int i = 0; i < len; i++) {
//    if (data[i].amplitude < NOISE_BASELINE) {
//      data[i] = FreqData{0, 0};
//    }
//  }
//}

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
