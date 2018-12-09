#include "config.h" //I don't know what this does, but it makes scary errors go away.
//LED
const int LED_TOTAL = 12;
const double LED_HALF = LED_TOTAL / 2;
const int LED_PIN = 13;
//TODO: Color rotation  (degrees offset)

//FFT
const int analog_pin = A0;

const int BASS_SAMPLING_FREQUENCY = 1900; //Hz, must be less than 10000 due to ADC
const int BASS_SAMPLES = 128; //Must be a power of 2
const double MIN_BASS_FREQ = 30;
const double MAX_BASS_FREQ = 110;

const int VOCAL_SAMPLING_FREQUENCY = 9500; //Hz, must be less than 10000 due to ADC
const int VOCAL_SAMPLES = 64;
const double MIN_VOCAL_FREQ = 200; //These frequencies are just guesses - maybe start with some acapella tracks.
const double MAX_VOCAL_FREQ = 1000;


//Filtering
const double NOISE_BASELINE = 1000; //Definitely want this to be percent based with a minimum bound (or min between average and peak?)
