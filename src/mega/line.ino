void line_event() {
  Wire.requestFrom(8, 2);
  a = Wire.read();
  b = Wire.read();
  while (Wire.available()) {
    Wire.read();
  }
  if (a == 1) {
    angle = b;
  }
  else {
    angle = b * -1;
  }

  anti_angle =  180 + angle;
  movement(anti_angle, 510, NXT_angle());
}
