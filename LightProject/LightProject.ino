#include "arduinoFFT.h" // Standard Arduino FFT library



#define BASS_SAMPLES 1024             //Must be a power of 2 - higher is slower, but allows for lower frequency
#define BASS_SAMPLING_FREQUENCY 10000 //Hz, must be less than 10000 due to ADC
arduinoFFT BassFFT = arduinoFFT();
unsigned int bass_sampling_period_us;



#define VOCAL_SAMPLES 256             //Must be a power of 2 - higher is slower, but allows for lower frequency
#define VOCAL_SAMPLING_FREQUENCY 10000 //Hz, must be less than 10000 due to ADC
arduinoFFT VocalFFT = arduinoFFT();
unsigned int vocal_sampling_period_us;



unsigned long microseconds, oldTime;

double vReal[BASS_SAMPLES];
double vImag[BASS_SAMPLES];

void setup() {
  Serial.begin(115200);
  bass_sampling_period_us = round(1000000 * (1.0 / BASS_SAMPLING_FREQUENCY));
  vocal_sampling_period_us = round(1000000 * (1.0 / VOCAL_SAMPLING_FREQUENCY));
}

void loop() {

  for (int i = 0; i < BASS_SAMPLES; i++)
  {
    microseconds = micros() - oldTime;
    oldTime = microseconds;

    vReal[i] = analogRead(0);
    vImag[i] = 0;

    //

//    delay(bass_sampling_period_us);
    while (micros() < (microseconds + bass_sampling_period_us)) {
      /* do nothing until we enter the next sampling period - think of this as a delay */
    }
  }

  bassLoop();

  /*SAMPLING*/
  //  for (int i = 0; i < SAMPLES; i++)
  //  {
  //    microseconds = micros() - oldTime;
  //    oldTime = microseconds;
  //
  //    vReal[i] = analogRead(0);
  //    vImag[i] = 0;
  //
  //    while (micros() < (microseconds + sampling_period_us)) {
  //      /* do nothing until we enter the next sampling period - think of this as a delay */
  //    }
  //  }

  //if we have enough samples for bass, call the bassLoop();

  //if we have enough samples for vocals, call the vocalLoop();
}

void bassLoop() {
  BassFFT.Windowing(vReal, BASS_SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  BassFFT.Compute(vReal, vImag, BASS_SAMPLES, FFT_FORWARD);
  BassFFT.ComplexToMagnitude(vReal, vImag, BASS_SAMPLES);
  double peak = BassFFT.MajorPeak(vReal, BASS_SAMPLES, BASS_SAMPLING_FREQUENCY);

  /*PRINT RESULTS*/
  Serial.println(peak);     //Print out what frequency is the most dominant.


  //  for (int i = 0; i < (SAMPLES / 2); i++)
  //  {
  //    /*View all these three lines in serial terminal to see which frequencies has which amplitudes*/
  //
  //    Serial.print((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES, 1);
  //    Serial.print(" ");
  //    Serial.println(vReal[i], 1);    //View only this line in serial plotter to visualize the bins
  //  }
}

void vocalLoop() {
  VocalFFT.Windowing(vReal, VOCAL_SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  VocalFFT.Compute(vReal, vImag, VOCAL_SAMPLES, FFT_FORWARD);
  VocalFFT.ComplexToMagnitude(vReal, vImag, VOCAL_SAMPLES);
  double peak = VocalFFT.MajorPeak(vReal, VOCAL_SAMPLES, VOCAL_SAMPLING_FREQUENCY);

  //TODO: Filter output to 400-3200hz. Determine amplitude of this range. Determine a minimum/baseline value in which there is NO LED change.

  /*PRINT RESULTS*/
  Serial.println(peak);     //Print out what frequency is the most dominant.


  //  for (int i = 0; i < (SAMPLES / 2); i++)
  //  {
  //    /*View all these three lines in serial terminal to see which frequencies has which amplitudes*/
  //
  //    Serial.print((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES, 1);
  //    Serial.print(" ");
  //    Serial.println(vReal[i], 1);    //View only this line in serial plotter to visualize the bins
  //  }
}
