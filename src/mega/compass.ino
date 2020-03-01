int NXT_adress = 0x01;
int _ofeset = 0;
uint16_t ReadCompassSensor() {
  Wire.beginTransmission(NXT_adress);
  Wire.write(0x44);
  Wire.endTransmission();
  Wire.requestFrom(NXT_adress, 2);
  while (Wire.available() < 2);
  byte lowbyte = Wire.read();
  byte highbyte = Wire.read();
  return highbyte * 256 + lowbyte;
}
void NXT_setup() {
  Wire.begin();
  Wire.beginTransmission(NXT_adress);
  Wire.write(0x00);
  Wire.endTransmission();
  while (Wire.available() > 0)
    Wire.read();
}
void NXT_nort_set() {
  _ofeset = ReadCompassSensor();
}

int16_t NXT_angle()
{
  uint16_t relative_angle = (ReadCompassSensor() -  _ofeset + 360) % 360;

  if (relative_angle > 180 ) {
    relative_angle -= 360;

  }
  return relative_angle;
}
