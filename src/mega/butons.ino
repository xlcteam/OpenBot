const int butons_pins[8] {47, 52, 51, 50, 53, 49, 48, 46};
bool buton_read(int buton_index) {
  return digitalRead(butons_pins[buton_index]);
}
void butons_setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(INPUT, butons_pins[i]);
  }
}
