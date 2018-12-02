#define PI 3.1415926535897932384626433832795

struct Color {
  int R;
  int G;
  int B;
};

class ColorGenerator {
  public:
  Color getColor(int offset, int range) {
    double section = PI / range * offset;
    if(section < PI / 2) {
      return Color { absRelu(255*cos(section), false), 255*sin(section), absRelu(255*cos(section), true) };
    }
  }

  private:
  int absRelu(int val, bool neg) {
    if(neg) {
      return val < 0 ? abs(val) : 0;
    } else {
      return val > 0 ? val : 0;
    }
  }
};
