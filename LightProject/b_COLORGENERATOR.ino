#define PI 3.1415926535897932384626433832795

struct Color {
  double R;
  double G;
  double B;
};

struct Color getColor(struct FreqData data[], unsigned int len) {
  double slice = PI / (len - 1);
  filterNoise(data, len);
  double lowest = getLowestAmp(data, len);
  double highest = getHighestAmp(data, len);

  struct Color avgCol = Color {
    absRelu(255.0 * (data[0].amplitude - lowest) / (highest - lowest)*cos(0), false),
            255.0 * (data[0].amplitude - lowest) / (highest - lowest)*sin(0),
            absRelu(255.0 * (data[0].amplitude - lowest) / (highest - lowest)*cos(0), true)
  };

  avgCol.R = 0;
  avgCol.G = 0;
  avgCol.B = 0;
  //
  //  Serial.print("Lowest ");
  //  Serial.println(lowest);
  //  Serial.print("Other one ");
  //  Serial.println(highest);
  //
  //  Serial.print("Avrg ");
  //  Serial.print(avgCol.R);
  //  Serial.print(" ");
  //  Serial.print(avgCol.G);
  //  Serial.print(" ");
  //  Serial.println(avgCol.B);

  for (int i = 1; i < len; i++) {
    if (data[i].amplitude != -1) {
      Color color = Color {
        absRelu(255.0 * (data[i].amplitude - lowest) / (highest - lowest)*cos(slice * i), false),
        255.0 * (data[i].amplitude - lowest) / (highest - lowest)*sin(slice * i),
        absRelu(255.0 * (data[i].amplitude - lowest) / (highest - lowest)*cos(slice * i), true)
      };

      Serial.print("Yes ");
      Serial.print(color.R);
      Serial.print(" ");
      Serial.print(color.G);
      Serial.print(" ");
      Serial.println(color.B);

      avgCol = averageColor(avgCol, color);
      //      Serial.print("Avg ");
      //      Serial.print(avgCol.R);
      //      Serial.print(" ");
      //      Serial.print(avgCol.G);
      //      Serial.print(" ");
      //      Serial.println(avgCol.B);
    }
  }

  //0 0 16
  double colorTotal = avgCol.R + avgCol.G + avgCol.B;
  double dimRatio = colorTotal / 255.0;

  //  Serial.print("Dim Ratio: ");
  //  Serial.println(dimRatio);

  if (dimRatio > 0) {
    avgCol.R = avgCol.R / dimRatio;
    avgCol.G = avgCol.G / dimRatio;
    avgCol.B = avgCol.B / dimRatio;

  }

  //  Serial.print("Avg ");
  //  Serial.print(avgCol.R);
  //  Serial.print(" ");
  //  Serial.print(avgCol.G);
  //  Serial.print(" ");
  //  Serial.println(avgCol.B);


  return avgCol;
}

double absRelu(double val, bool neg) {
  if (neg) {
    return val < 0 ? abs(val) : 0;
  } else {
    return val > 0 ? val : 0;
  }
}

void filterNoise(struct FreqData data[], unsigned int len) {
  for (int i = 0; i < len; i++) {
    if (data[i].amplitude < NOISE_BASELINE) {
      data[i] = FreqData{0, -1};
    }
  }
}

struct Color averageColor(struct Color c1, struct Color c2) {
  struct Color col = Color {
    sqrt(c1.R * c1.R + c2.R * c2.R), sqrt(c1.G * c1.G + c2.G * c2.G), sqrt(c1.B * c1.B + c2.B * c2.B)
  };
  //  Serial.print("Avg ");
  //  Serial.print(sqrt(c1.R * c1.R + c2.R * c2.R));
  //  Serial.print(" ");
  //  Serial.print(col.G);
  //  Serial.print(" ");
  //  Serial.println(col.B);

  return Color{sqrt(c1.R * c1.R + c2.R * c2.R), sqrt(c1.G * c1.G + c2.G * c2.G), sqrt(c1.B * c1.B + c2.B * c2.B)};
}

double getLowestAmp(struct FreqData data[], unsigned int len) {
  double lowest = data[0].amplitude;
  for (int i = 0; i < len; i++) {
    if (data[i].amplitude != -1 && lowest > data[i].amplitude) {
      lowest = data[i].amplitude;
    }
  }

  return lowest > 0 ? lowest : 0;
}

double getHighestAmp(struct FreqData data[], unsigned int len) {
  double highest = data[0].amplitude;
  for (int i = 0; i < len; i++) {
    if (highest < data[i].amplitude) {
      highest = data[i].amplitude;
    }
  }

  return highest;
}
