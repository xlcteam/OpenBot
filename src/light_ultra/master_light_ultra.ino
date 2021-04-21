#include<SPI.h>
#include <Wire.h>

#define SS_motor_right 8
#define SS_motor_left 9
#define SS_small 6
#define SS_ultra 10
#define SS_kick 7
byte x;
byte Mastersend = 1, Mastereceive_ultra, Mastereceive_right, Mastereceive_left, Mastereceive_small, Mastereceive_kick;
bool  right_line[8];
bool small_line[8];
bool  line_data[20] {0};
float x_vector, y_vector;
int final_angle;
int detected_count;
//330 , 345 , 15 , 30
//70 , 80 , 90 , 100 , 110
//160 , 170 , 180 , 190 , 200
//250 , 260 ,270 ,280 , 300



//ultra table
/*
  l z p
  0 0 0
  0 0 1
  0 1 0
  0 1 1
  1 0 0
  1 0 1
  1 1 0
  1 1 1
*/
float vector_table[19][2] {
  { -0.50000, 0.86602},
  { -0.25882, 0.96592},
  {0.25882, 0.96593},
  {0.50000, 0.86603},
  {0.93969, 0.34202},
  {0.98481, 0.17365},
  {1.00000, 0.00000},
  {0.98481, -0.17365},
  {0.93969, -0.34202},
  {0.34202, -0.93969},
  {0.17365, -0.98481},
  {0.00000, -1.00000},
  { -0.17365, -0.98481},
  { -0.34202, -0.93969},
  { -0.93969, -0.34202},
  { -0.98481, -0.17365},
  { -1.00000, -0.00000},
  { -0.98481, 0.17364},
  { -0.86603, 0.50000}
};

void setup (void)

{
  Serial.begin(9600);
  Wire.begin(8);
  Wire.onRequest(requestEvent);
  pinMode(SS_ultra, OUTPUT);
  pinMode(SS_motor_left, OUTPUT);
  pinMode(SS_motor_right, OUTPUT);
  pinMode(SS_small, OUTPUT);
  pinMode(SS_kick, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(3, INPUT);
  pinMode(5, INPUT);
  pinMode(4, INPUT);
  pinMode(2, INPUT);
  digitalWrite(SS_ultra, HIGH);
  digitalWrite(SS_motor_right, HIGH);
  digitalWrite(SS_motor_left, HIGH);
  digitalWrite(SS_small, HIGH);
  digitalWrite(SS_kick, HIGH);
  digitalWrite(A0, LOW);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);
}
void requestEvent() {
  if (final_angle > 0) {
    Wire.write(1);
    Wire.write(final_angle);
  }
  else {
    Wire.write(2);
    Wire.write(final_angle * -1);
  }
}
void loop(void)
{
  digitalWrite(SS_ultra, HIGH);
  digitalWrite(SS_motor_right, HIGH);
  digitalWrite(SS_motor_left, HIGH);
  digitalWrite(SS_small, HIGH);
  digitalWrite(SS_kick, HIGH);

  x_vector = 0;
  y_vector = 0;
  detected_count = 0;
  if (digitalRead(3)) {
    digitalWrite(SS_motor_right, LOW);
    Mastereceive_right = SPI.transfer(Mastersend);
    digitalWrite(SS_motor_right, HIGH);
    for (unsigned int i = 0; i != 5; ++i)
    {
      line_data[i + 4] = Mastereceive_right & 1;
      Mastereceive_right /= 2;
      if (line_data[i + 4]) {
        x_vector += vector_table[i + 4][0] ;
        y_vector += vector_table[i + 4][1] ;
        detected_count++;
      }
    }
  }
  if (digitalRead(5)) {
    digitalWrite(SS_small, LOW);
    Mastereceive_small = SPI.transfer(Mastersend);
    digitalWrite(SS_small, HIGH);
    for (unsigned int i = 0; i != 4; ++i)
    {
      line_data[i] = Mastereceive_small & 1;
      Mastereceive_small /= 2;
      if ( line_data[i]) {
        x_vector += vector_table[i][0] ;
        y_vector += vector_table[i][1] ;
        detected_count++;
      }
    }
  }
  if (digitalRead(4)) {
    digitalWrite(SS_motor_left, LOW);
    Mastereceive_left = SPI.transfer(Mastersend);
    digitalWrite(SS_motor_left, HIGH);
    for (unsigned int i = 0; i != 5; ++i)
    {
      line_data[i + 14] = Mastereceive_left & 1;
      Mastereceive_left /= 2;
      if ( line_data[i + 14]) {
        x_vector += vector_table[i + 14][0] ;
        y_vector += vector_table[i + 14][1] ;
        detected_count++;
      }
    }
  }
  if (digitalRead(2)) {
    digitalWrite(SS_kick, LOW);
    Mastereceive_kick = SPI.transfer(Mastersend);
    digitalWrite(SS_kick, HIGH);
    for (unsigned int i = 0; i != 5; ++i)
    {
      line_data[i + 9] = Mastereceive_kick & 1;
      Mastereceive_kick /= 2;
      if ( line_data[i + 9]) {
        x_vector += vector_table[i + 9][0] ;
        y_vector += vector_table[i + 9][1] ;
        detected_count++;
      }
    }
  }
  if (detected_count == 0) {
    digitalWrite(A0, LOW);
  }
  else {
    final_angle = (atan2(x_vector , y_vector) * 180) / 3.14159;

    //Serial.println(final_angle);
/*
    digitalWrite(SS_ultra, LOW);
    Mastereceive_ultra = SPI.transfer(Mastersend);
    delayMicroseconds(20);
    digitalWrite(SS_ultra, HIGH);
   // Serial.println(Mastereceive_ultra);
    //2 right
    //3 left

    if (final_angle > 60 && final_angle < 120) {
      if ( Mastereceive_ultra == 3 ) {
        final_angle = final_angle - 180;
      }
    }
    else if (final_angle < -60 && final_angle > -120) {
      if ( Mastereceive_ultra == 2 ) {
        final_angle = final_angle + 180;
      }
    }*/
    //Serial.println(final_angle);
    digitalWrite(A0, HIGH);
  }

}
