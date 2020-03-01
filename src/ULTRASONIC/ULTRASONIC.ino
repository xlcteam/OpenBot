#include <NewPing.h>
#include<SPI.h>
volatile boolean received = false;
volatile byte Slavereceived, Slavesend;

NewPing ultra_1(5, 5, 400);
NewPing ultra_2(6, 6, 400);
NewPing ultra_3(7, 7, 400);
//23cm
//3 left
//20 cm
//2 back
//23cm
//1right
//0 0 0   1
//0 0 1   2
//0 1 0   3
//0 1 1   4
//1 0 0   5
//1 0 1   6
//1 1 0   7
//1 1 1   8
int tipe = 0;
bool ultra_free[3] = {0, 0, 0};
void setup() {
  Serial.begin(9600);

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
  
  if (received) {
    SPDR = 85;
    received = false;
  }

  if (ultra_1.ping_cm() > 23) {
    ultra_free[0] = 0;
  }
  
  else {
    ultra_free[0] = 1;
  }

  if (ultra_3.ping_cm() > 23) {
    ultra_free[2] = 0;
  }
  else {
    ultra_free[2] = 1;
  }
tipe = ultra_free[0]|(ultra_free[2]<<1);
   // Serial.println(tipe);

}
