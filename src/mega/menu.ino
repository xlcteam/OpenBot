/*
  1 STR KIC PEN MOT
  2 LIN NXT BNO CAM
  3 DRI NAB NAR ???

*/
int screen = 1;
int arr_pos = 0;
bool menu_runing = 1;
void select() {
  if (buton_read(5)) {
    while (buton_read(5)) {}
    lcd.setCursor(arr_pos, 1);
    lcd.print(" ");
    arr_pos == 12 ? arr_pos = 0 : arr_pos += 4;
    lcd.setCursor(arr_pos, 1);
    lcd.print(byte(0));
  }
  if (buton_read(2)) {
    while (buton_read(2)) {}
    lcd.setCursor(arr_pos, 1);
    lcd.print(" ");
    arr_pos == 0 ? arr_pos = 12 : arr_pos -= 4;
    lcd.setCursor(arr_pos, 1);
    lcd.write(byte(0));
  }
}
void BNO() {
  while (!buton_read(7)) {
    lcd.setCursor(0, 0);
    lcd.print("BNO angle:");
    lcd.setCursor(0, 1);
    lcd.print(BNO_angle(), DEC);
    delay(30);
    lcd.print("                ");
  }
}
void NXT() {
  while (!buton_read(7)) {
    lcd.setCursor(0, 0);
    lcd.print("NXT angle:");
    lcd.setCursor(0, 1);
    lcd.print(NXT_angle(), DEC);
    delay(30);
    lcd.print("                ");
  }
}
void CAM() {
  while (!buton_read(7)) {
    lcd.setCursor(0, 0);
    lcd.print("b_x ");
    lcd.print(get_x_ball());
    lcd.setCursor(0, 1);
    lcd.print("g_x ");
    lcd.print(get_x_goal());
    delay(30);
    lcd.clear();
  }
}
void LIN() {
  while (!buton_read(7)) {
    lcd.setCursor(0, 0);
    lcd.print("Line angle:");
    lcd.setCursor(0, 1);
    if (digitalRead(LINE_PIN)) {
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
      lcd.print(angle, DEC);
    }
    else {
      lcd.print("None");
    }
    delay(30);
    lcd.print("                ");
  }
}
void MOT() {
  while (!buton_read(7)) {
    lcd.setCursor(0, 0);
    lcd.print("A B C D");
    lcd.setCursor(0, 1);
    lcd.print("press buton");
    if (buton_read(1)) {
      rotate_motor(1, 255);
    }
    else {
      rotate_motor(1, 0);
    }
    if (buton_read(2)) {
      rotate_motor(2, 255);
    }
    else {
      rotate_motor(2, 0);
    }
    if (buton_read(5)) {
      rotate_motor(3, 255);
    }
    else {
      rotate_motor(3, 0);
    }
    if (buton_read(6)) {
      rotate_motor(4, 255);
    }
    else {
      rotate_motor(4, 0);
    }
  }
  lcd.clear();
}
void KIC() {
  while (!buton_read(7)) {
    lcd.setCursor(0, 0);
    lcd.print("kick test");
    lcd.setCursor(0, 1);
    lcd.print("press buton");
    if (buton_read(3)) {
      kick();
      delay(1500);
    }
  }
  lcd.clear();
}
void DRI() {
  int dribler_speed = 100;
  while (!buton_read(7)) {

    lcd.setCursor(0, 0);
    lcd.print("speed:    ");
    lcd.setCursor(7, 0);
    lcd.print(dribler_speed);
    lcd.setCursor(0, 1);
    lcd.print("press buton");
    if (buton_read(1)) {
      rotate_motor(5, dribler_speed );
    }
    else {
      if (buton_read(6)) {
        rotate_motor(5, -dribler_speed );
      }
      else {
        rotate_motor(5, 0);
      }
    }
    if (buton_read(2)) {
      dribler_speed++;
      if (dribler_speed > 255)dribler_speed = 255;
      delay(10);
    }
    if (buton_read(5)) {

      dribler_speed--;
      if (dribler_speed < 0)dribler_speed = 0;
      delay(10);
    }
  }
  lcd.clear();
}
void NAB() { 
  while (!buton_read(7)) {   
    lcd.setCursor(0, 0);
    lcd.print("goal:    ");
    lcd.setCursor(7, 0);
    lcd.print(get_x_goal());
    lcd.setCursor(0, 1);
    lcd.print("runing...");
    na_mieste_pid(get_x_goal());
  }
  lcd.clear();
}
void screen_1() {
  while (screen == 1) {
    select();
    screen_select();
    if (buton_read(4)) {
      lcd.clear();
      while (buton_read(4))
        if (arr_pos == 0) {
          menu_runing = 0;
          return;
        }
        else if (arr_pos == 4) {
          KIC();
        }
        else if (arr_pos == 8) {

        }
        else if (arr_pos == 12) {
          MOT();
        }
      lcd.clear();
    }
    else {
      lcd.setCursor(0, 0);
      lcd.print("STR KIC PEN MOT");
      lcd.setCursor(13, 1);
      lcd.print("1/3");
      lcd.setCursor(arr_pos, 1);
      lcd.write(byte(0));
    }
  }
}
void screen_2() {
  while (screen == 2) {
    select();
    screen_select();
    if (buton_read(4)) {
      lcd.clear();
      while (buton_read(4))
        if (arr_pos == 0) {
          LIN();
        }
        else if (arr_pos == 4) {
          NXT();
        }
        else if (arr_pos == 8) {
          BNO();
        }
        else if (arr_pos == 12) {
          CAM();
        }
      lcd.clear();
    }
    else {
      lcd.setCursor(0, 0);
      lcd.print("LIN NXT BNO CAM");
      lcd.setCursor(13, 1);
      lcd.print("2/3");
      lcd.setCursor(arr_pos, 1);
      lcd.write(byte(0));
      screen_select();
    }
  }
}
void screen_3() {
  while (screen == 3) {
    select();
    screen_select();
    if (buton_read(4)) {
      lcd.clear();
      while (buton_read(4))
        if (arr_pos == 0) {
          DRI();
        }
        else if (arr_pos == 4) {
          NAB();
        }
        else if (arr_pos == 8) {

        }
        else if (arr_pos == 12) {

        }
      lcd.clear();
    }
    else {
      lcd.setCursor(0, 0);
      lcd.print("DRI NAB NAR ???");
      lcd.setCursor(13, 1);
      lcd.print("3/3");
      lcd.setCursor(arr_pos, 1);
      lcd.write(byte(0));
      screen_select();
    }
  }
}
void LCD_setup() {
  lcd.begin(16, 2);
  lcd.clear();

  byte arow[] = {
    B00100,
    B01110,
    B10101,
    B00100,
    B00100,
    B00100,
    B00100,
    B00100
  };
  lcd.createChar(0, arow);
  lcd.setCursor(4, 0);
  lcd.print("XLC TEAM");
  lcd.setCursor(1, 1);
  lcd.print("Jakub Gal 2020");
  delay(1500);
  lcd.clear();
}
void screen_select() {
  if (buton_read(1) && screen < 3) {
    while (buton_read(1)) {}
    screen++;
  }
  if (buton_read(6) && screen > 1) {
    while (buton_read(6)) {}
    screen--;
  }
}

void menu() {
  while (menu_runing) {
    Serial.println(screen);
    switch (screen) {
      case 1:
        screen_1();
        break;
      case 2:
        screen_2();
        break;
      case 3:
        screen_3();
        break;
      default:
        lcd.clear();
        screen_select();
        break;
    }
  }
}
