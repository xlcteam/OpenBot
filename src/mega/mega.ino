#include <Wire.h>
#include <LiquidCrystal.h>
extern const float pomery_pohybou[360][4];
int spd = 150;
byte a, b;
int angle;
int anti_angle;
LiquidCrystal lcd(26, 27, 28, 29, 40, 41);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pinMode(3, INPUT);
  lcd.begin(16, 2);
  butons_setup();
  NXT_setup();
  NXT_nort_set();

}
void loop() {
//TODO piny
  if (digitalRead(3)) {
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
    Serial.print(a);
    Serial.print('\t');
    Serial.println(b);
    movement(anti_angle, 510,NXT_angle());
  }
  else {
    movement(90, 500,NXT_angle());
  }

  //na_mieste(NXT_angle());
}

void na_mieste(int vstup) {
  int16_t speeds[4] = {0, 0, 0, 0};
  int compensation;
  compensation = PID(speeds, 0, vstup);
  rotate_motor(1, speeds[0] + compensation);
  rotate_motor(2, speeds[1] + compensation);
  rotate_motor(3, speeds[2] + compensation);
  rotate_motor(4, speeds[3] + compensation);
}
void movement(int smer , int rychlost , int feedback) {
  smer = (smer + 90) % 360; //ja viem ze som to mohol prehodit v poli //TODO
  int16_t speeds[4] = {pomery_pohybou[smer][0]*rychlost, pomery_pohybou[smer][1]*rychlost, pomery_pohybou[smer][2]*rychlost, pomery_pohybou[smer][3]*rychlost};
  int compensation;
  compensation = PID(speeds, 0, feedback);

  
  rotate_motor(1, speeds[0] + compensation);
  rotate_motor(2, speeds[1] + compensation);
  rotate_motor(3, speeds[2] + compensation);
  rotate_motor(4, speeds[3] + compensation);
}
void off_motors() {
  rotate_motor(1, 0);
  rotate_motor(2, 0);
  rotate_motor(3, 0);
  rotate_motor(4, 0);
}
void vpred(int vstup) {
  int16_t speeds[4] = { -spd, -spd, spd, spd};
  int compensation;
  compensation = PID(speeds, 0, vstup);
  rotate_motor(1, speeds[0] + compensation);
  rotate_motor(2, speeds[1] + compensation);
  rotate_motor(3, speeds[2] + compensation);
  rotate_motor(4, speeds[3] + compensation);
}
