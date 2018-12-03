#include <Arduino.h>
#include "start.cpp"

#define PI 3.1415926535897932384626433832795

struct Color {
  int R;
  int G;
  int B;
};

class ColorGenerator {
  public:
    static Color getColor(struct FreqData data[], unsigned int len) {
      double slice = PI / (len - 1);
      filterNoise(data, len);
      double lowest = getLowestAmp(data, len);
      double highest = getHighestAmp(data, len);

      struct Color avgCol = Color {
        absRelu(255.0 * (data[0].amplitude - lowest) / (highest - lowest)*cos(0), false),
                255.0 * (data[0].amplitude - lowest) / (highest - lowest)*sin(0),
                absRelu(255.0 * (data[0].amplitude - lowest) / (highest - lowest)*cos(0), true)
      };
      for (int i = 1; i < len; i++) {
        if (data[i].amplitude == 0) {
          break;
        }

        Color color = Color {
          absRelu(255.0 * (data[i].amplitude - lowest) / (highest - lowest)*cos(slice * i), false),
          255.0 * (data[i].amplitude - lowest) / (highest - lowest)*sin(slice * i),
          absRelu(255.0 * (data[i].amplitude - lowest) / (highest - lowest)*cos(slice * i), true)
        };

        avgCol = averageColor(avgCol, color);
      }

      return avgCol;
    }

  private:
    static double absRelu(double val, bool neg) {
      if (neg) {
        return val < 0 ? abs(val) : 0;
      } else {
        return val > 0 ? val : 0;
      }
    }

    static void filterNoise(struct FreqData data[], unsigned int len) {
      unsigned int skip = 0;

      for (int i = 0; i < len - skip; i++) {
        if (data[i].amplitude < NOISE_BASELINE) {
          skip++;
        }
        data[i] = data[i + skip];
      }

      for (int i = len - skip; i < len; i++) {
        data[i] = FreqData{0, 0};
      }
    }

    static Color averageColor(struct Color c1, struct Color c2) {
      return Color{sqrt(c1.R ^ 2 + c2.R ^ 2), sqrt(c1.G ^ 2 + c2.G ^ 2), sqrt(c1.B ^ 2 + c2.B ^ 2)};
    }

    static double getLowestAmp(struct FreqData data[], unsigned int len) {
      double lowest = data[0].amplitude;
      for (int i = 0; i < len; i++) {
        if (data[i].amplitude == 0) {
          break;
        }

        if (lowest > data[i].amplitude) {
          lowest = data[i].amplitude;
        }
      }

      return lowest;
    }

    static double getHighestAmp(struct FreqData data[], unsigned int len) {
      double highest = data[0].amplitude;
      for (int i = 0; i < len; i++) {
        if (data[i].amplitude == 0) {
          break;
        }

        if (highest < data[i].amplitude) {
          highest = data[i].amplitude;
        }
      }

      return highest;
    }
};
