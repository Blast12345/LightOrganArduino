#include "arduinoFFT.h" // Standard Arduino FFT library


unsigned int sampling_period_us;
unsigned long microseconds, oldTime;

arduinoFFT BassFFT = arduinoFFT();
double vRealBass[BASS_SAMPLES];
double vImagBass[BASS_SAMPLES];

arduinoFFT VocalFFT = arduinoFFT();
double vRealVocal[VOCAL_SAMPLES];
double vImagVocal[VOCAL_SAMPLES];



void setupAudioService() {
  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));
}


void startListening() {
  for (int i = 0; i < BASS_SAMPLES; i++)
  {
    microseconds = micros() - oldTime;
    oldTime = microseconds;

    double newAnalogRead = analogRead(analog_pin);

    vRealBass[i] = newAnalogRead;
    vImagBass[i] = 0;

    vRealVocal[i % VOCAL_SAMPLES] = newAnalogRead;
    vImagVocal[i % VOCAL_SAMPLES] = 0;

    while (micros() < (microseconds + sampling_period_us)) {
      /* do nothing until we enter the next sampling period - think of this as a delay */
    }
  }

  computeBass();
}


int getIndexAboveFrequency(unsigned int vRealLength, double targetFrequency, unsigned int sampleCount) {

  for (int i = 0; i < vRealLength; i++) {
    double currentFrequency = (i * 1.0 * SAMPLING_FREQUENCY) / sampleCount;

    if (currentFrequency > targetFrequency) {
      return i;
    }
  }

  return 0;
}

void computeBass() {
  BassFFT.Windowing(vRealBass, BASS_SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  BassFFT.Compute(vRealBass, vImagBass, BASS_SAMPLES, FFT_FORWARD);
  BassFFT.ComplexToMagnitude(vRealBass, vImagBass, BASS_SAMPLES);

  unsigned int vRealBassLength = sizeof(vRealBass) / sizeof(vRealBass[0]); //must pass this in because arrays as params are treated as pointers; sizeof would be the size of the pointer, not the array
  unsigned int startIndex = getIndexAboveFrequency(vRealBassLength, 20, BASS_SAMPLES) - 1;
  unsigned int endIndex = getIndexAboveFrequency(vRealBassLength, 150, BASS_SAMPLES);
  unsigned int windowLength = endIndex - startIndex;

  FreqData data[windowLength];

  for (int i = startIndex; i <= endIndex; i++)
  {
    unsigned int f = i - startIndex;

    double frequency = (i * 1.0 * SAMPLING_FREQUENCY) / BASS_SAMPLES;
    double amplitude = vRealBass[i];

    FreqData entry = {.frequency = frequency, .amplitude = amplitude};
    data[f] = entry;

    Serial.println(data[f].frequency);
    //    Serial.print((i * 1.0 * SAMPLING_FREQUENCY) / BASS_SAMPLES, 1);
    //    Serial.print(" ");
    //    Serial.println(vRealBass[i], 1);    //View only this line in serial plotter to visualize the bins
  }

  unsigned int dataLength = sizeof(data) / sizeof(data[0]);


  //Testing
  FreqData test[15];
  test[0] = {19.5, 0};
  test[1] = {29.3, 100000};
  test[2] = {39.1, 0};
  test[3] = {48.8, 0};
  test[4] = {58.6, 0};
  test[5] = {68.4, 0};
  test[6] = {78.1, 0};
  test[7] = {87.9, 0};
  test[8] = {97.7, 0};
  test[9] = {107.4, 0};
  test[10] = {117.2, 0};
  test[11] = {127, 0};
  test[12] = {136.7, 0};
  test[13] = {146.5, 0};
  test[14] = {156.3, 0};
  Color newColor = getColor(test, 15);
  setBass(newColor);
}

void computeVocal() {

}
