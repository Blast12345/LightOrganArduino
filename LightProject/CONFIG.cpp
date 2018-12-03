#include <Arduino.h>

//LED
extern const int LED_TOTAL = 12;
extern const double LED_HALF = LED_TOTAL / 2;
extern const int LED_PIN = 13;

//FFT
extern const int analog_pin = A0;
extern const int SAMPLING_FREQUENCY = 10000; //Hz, must be less than 10000 due to ADC
extern const int BASS_SAMPLES = 1024; //Must be a power of 2 - higher is slower, but allows for lower frequency
extern const int VOCAL_SAMPLES = 256;

//Filtering
extern const double NOISE_BASELINE = 0.1;
