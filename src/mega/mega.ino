#include <Wire.h>
#include <LiquidCrystal.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#define LINE_PIN 3
#define KICK_PIN 9
#define KICK_TIME 10
#define MAX_BALL_SPD 340
#define CAM_COEFICIENT 1.8
extern const float pomery_pohybou[360][4];
int spd = 150;
byte a, b;
int angle;
int anti_angle;
int x_b, y_b, x_g, y_g;

int dribler = 0;
LiquidCrystal lcd(26, 27, 28, 29, 40, 41);
Adafruit_BNO055 bno = Adafruit_BNO055(55);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pinMode(LINE_PIN, INPUT);
  pinMode(KICK_PIN, OUTPUT);
  butons_setup();
  NXT_setup();
  NXT_nort_set();
  rpi_setup();
  LCD_setup();
  bno.begin();
  bno.setExtCrystalUse(true);
  menu();
}
void loop() {

  x_b = get_x_ball();
  x_g = get_x_goal();
  if (digitalRead(2)) {
    dribler = 0;
  }
  else {
    dribler++;
  }
  digitalWrite(KICK_PIN, 0);
  if ((x_b > 320 && x_b < 360) || (x_b > 0 && x_b < 40)) {
    rotate_motor(5, 255);
  }
  else {
    rotate_motor(5, 0 );
  }
  if (digitalRead(LINE_PIN)) {
    line_event();
  }
  else {
    if (x_g != -1000) {
      if (x_b != -1000) {
        if (dribler < 1000 || x_g > 10 || x_g < -10) {
          if (dribler > 200 && (x_g > 15 || x_g < -15)) {
            na_mieste(x_g);
          }
          else {
            movement(x_b, 510, x_g);
          }
        }
        else {
          kick();
          dribler = 0;
        }
      }
      else {
        movement(180, 510, x_g);
      }
    } else {
      if (x_b != -1000) {
        movement(x_b, 510, NXT_angle());
      }
      else {
        movement(180, 510, NXT_angle());
      }
    }

  }

}
void kick() {
  rotate_motor(5, 0);
  off_motors();
  delay(10);
  digitalWrite(KICK_PIN, HIGH);
  delay(KICK_TIME);
  digitalWrite(KICK_PIN, LOW);
}
void na_mieste(int vstup) {
  static int rev;
  rev = vstup > 0 ? rev = -1 : rev = 1;
  rotate_motor(1, MAX_BALL_SPD * rev);
  rotate_motor(2, MAX_BALL_SPD * rev);
  rotate_motor(3, MAX_BALL_SPD * rev);
  rotate_motor(4, MAX_BALL_SPD * rev);
}
void movement(int smer , int rychlost , int feedback) {
  smer = (smer + 90) % 360; //prehodit v poli //TODO
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
void na_mieste_pid(int vstup) {
  int16_t speeds[4] = { 0, 0,0,0};
  int compensation;
  compensation = PID(speeds, 0, vstup);
  rotate_motor(1, speeds[0] + compensation);
  rotate_motor(2, speeds[1] + compensation);
  rotate_motor(3, speeds[2] + compensation);
  rotate_motor(4, speeds[3] + compensation);
}
