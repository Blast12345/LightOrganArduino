#include "config.h" //I don't know what this does, but it makes scary errors go away.
//LED
const int LED_TOTAL = 12;
const double LED_HALF = LED_TOTAL / 2;
const int LED_PIN = 13;
//TODO: Color rotation  (degrees offset)

//FFT
const int analog_pin = A0;
const int SAMPLING_FREQUENCY = 10000; //Hz, must be less than 10000 due to ADC
const int BASS_SAMPLES = 1024; //Must be a power of 2 - higher is slower, but allows for lower frequency
const int VOCAL_SAMPLES = 256;
const double MIN_BASS_FREQ = 20;
const double MAX_BASS_FREQ = 150;


//Filtering
const double NOISE_BASELINE = 70000;
