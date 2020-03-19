void rpi_setup() {
  Serial3.begin(115200);
  pinMode(30, OUTPUT);
  pinMode(31, OUTPUT);
  pinMode(39, OUTPUT);
  pinMode(38, OUTPUT);
  digitalWrite(30, LOW);
  digitalWrite(31, LOW);
  digitalWrite(39, LOW);
  digitalWrite(38, LOW);
}
int get_x_ball() {
  int value;
  digitalWrite(30, HIGH);
  while (!Serial3.available())
    value = Serial3.parseInt();
  while (Serial3.available())Serial3.read();
  digitalWrite(30, LOW);
  //Serial.println(value);
  if (value == -1) {
    return -1000;
  }
  else {
    return value > 176 ? -((176 - value) / CAM_COEFICIENT) :   360-((176 - value) / CAM_COEFICIENT);
  }
}
int get_y_ball() {
  int value;
  digitalWrite(31, HIGH);
  while (!Serial3.available())
    value = Serial3.parseInt();
  while (Serial3.available())Serial3.read();
  digitalWrite(31, LOW);
  return (176 - value) / CAM_COEFICIENT ;
}
int get_x_goal() {
  int value;
  digitalWrite(39, HIGH);
  while (!Serial3.available())
    value = Serial3.parseInt();
  while (Serial3.available())Serial3.read();
  digitalWrite(39, LOW);
  if (value == -1) {
    return -1000;
  }
  else {
    return (176 - value) / CAM_COEFICIENT;
  }
}
int get_y_goal() {
  int value;
  digitalWrite(38, HIGH);
  while (!Serial3.available())
    value = Serial3.parseInt();
  while (Serial3.available())Serial3.read();
  digitalWrite(38, LOW);
  return (176 - value) / CAM_COEFICIENT;
}
