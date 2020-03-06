#include <Wire.h>
#include <LiquidCrystal.h>
extern const float pomery_pohybou[360][4];
int spd = 150;
byte a, b;
int angle;
int anti_angle;
int x_b, y_b, x_g, y_g;
LiquidCrystal lcd(26, 27, 28, 29, 40, 41);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pinMode(3, INPUT);
  lcd.begin(16, 2);
  butons_setup();
  NXT_setup();
  NXT_nort_set();
  rpi_setup();
}
void loop() {
  //TODO piny
  x_b = get_x_ball();
  x_g = get_x_goal();
  x_b *= -1;
  if (x_b < 0) {
    x_b = 360 - get_x_ball();
  }

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
    movement(anti_angle, 510, NXT_angle());
  }
  else {
    // movement(90, 500, NXT_angle());
        Serial.print("Mo");
        Serial.print('\t');
        Serial.print(x_b);
        Serial.print('\t');
        Serial.println(x_g);
        
    if (x_g != 62) {
      //na_mieste(x_g);
      if (x_b != 298) {
        //Serial.println( x_b);
        movement(x_b, 510, x_g);
      }
      else {
        na_mieste(x_g);
      }
    } else {
      //na_mieste(NXT_angle());
      if (x_b != 298) {
        //Serial.println( x_b);
        movement(x_b, 510, NXT_angle());
      }
      else {
        na_mieste(NXT_angle());
      }
    }

  }

  // na_mieste(x_g);
  //Serial.println( x_b);
  /*
    if (x_g != 70) {
    if (x_b != 70) {
      movement(x_b, 420, x_g);
    }
    else {
      off_motors();
    }
    }
    else {
    off_motors();
    }*/
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
