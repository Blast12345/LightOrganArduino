struct FreqData {
  double frequency;
  double amplitude;
};

void setup() {
  Serial.begin(115200);

  setupAudioService();
  setupNeopixel();
}

void loop() {
  startListening();
}
