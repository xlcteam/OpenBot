void motor_setup() {
  //pwm
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  //direction
  pinMode(A14, OUTPUT);
  pinMode(A15, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(42, OUTPUT);
  pinMode(43, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(45, OUTPUT);

  //zero
}
void motor(int a, int b, int pwm, int motor_speed) {
  if (motor_speed > 0) {
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    analogWrite(pwm, motor_speed);
  }
  else if (motor_speed < 0) {
    digitalWrite(a, LOW);
    digitalWrite(b, HIGH);
    analogWrite(pwm, motor_speed * -1);
  }
  else {
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
  }

}
void rotate_motor(byte motor_number, int motor_speed ) {
  switch (motor_number) {
    case 1:
      motor(23, 22, 7, motor_speed);
      break;
    case 2:
      motor(44, 45, 6, motor_speed);
      break;
    case 3:
      motor(43, 42, 5, motor_speed);
      break;
    case 4:
      motor(A14, A15, 4, motor_speed);
      break;
    case 5:
      motor(24, 25, 8, motor_speed);
      break;
  }
}
