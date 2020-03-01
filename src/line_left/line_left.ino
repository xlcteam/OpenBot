#include<SPI.h>
volatile boolean received;
volatile byte Slavereceived, Slavesend;
byte buttonvalue;
byte result = 0;
int line_treshold = 650;
float x, y;
bool detected = false;
bool sensorArr[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void setup() {
 //Serial.begin(9600);

  pinMode(MISO, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(A7, INPUT);
  pinMode(A6, INPUT);
  pinMode(A3, INPUT);
  pinMode(A1, INPUT); //down
  pinMode(A2, INPUT);
  pinMode(A0, INPUT);
  digitalWrite(3, LOW);

  SPCR |= _BV(SPE);
  received = false;
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  SPI.attachInterrupt();
}
ISR (SPI_STC_vect)
{
  Slavereceived = SPDR;
  received = true;
}
void loop() {
  detected = false;
  if (analogRead(A7) > line_treshold) {
    detected = true;
    sensorArr[0] = true;
  }
  else {
    sensorArr[0] = false;
  }
  if (analogRead(A6) > line_treshold) {
    detected = true;
    sensorArr[1] = true;
  }
  else {
    sensorArr[1] = false;
  }
  
  if (analogRead(A2) > line_treshold) {
    detected = true;
    sensorArr[2] = true;
  }
  else {
    if (analogRead(A1) > line_treshold) {
      detected = true;
      sensorArr[2] = true;
    }
    else {
      sensorArr[2] = false;
    }
  }
  
  if (analogRead(A3) > line_treshold) {
    detected = true;
    sensorArr[3] = true;
  }
  else {
    sensorArr[3] = false;
  }
  if (analogRead(A0) > line_treshold) {
    detected = true;
    sensorArr[4] = true;
  }
  else {
    sensorArr[4] = false;
  }

  if (detected) {
    result = 0;
    for (int i = 0; i < 5; i++)
    {
      if (sensorArr[i])
      {
        result = result | (1 << i);
      }
    }
    digitalWrite(3, HIGH);
  }
  else {
    digitalWrite(3, LOW);
  }

  if (received) {
    SPDR = result;
    received = false;
  }
  
   /* Serial.print(sensorArr[0]);
    Serial.print('\t');
    Serial.print(sensorArr[1]);
    Serial.print('\t');
    Serial.print(sensorArr[2]);
    Serial.print('\t');
    Serial.print(sensorArr[3]);
    Serial.print('\t');
    Serial.println(sensorArr[4]);*/
}
