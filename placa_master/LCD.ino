
void transposeLCD() {
  if (!menuOpen) {
    lcd.setCursor(5, 1);
    if (transpose > 0) {
      lcd.print("+");
    }
    lcd.print(transpose);
    lcd.print("  ");
  } else if (itemSelected <= 3) {
    lcd.setCursor(12, 1);
    if (transpose > 0) {
      lcd.print("+");
    }
    lcd.print(transpose);
    lcd.print("  ");
    lcd.setCursor(12, 1);
  }
}
void oitavaLCD() {
  if (!menuOpen) {
    lcd.setCursor(5, 2);
    if (oitava > 0) {
      lcd.print("+");
    }
    lcd.print(oitava);
    lcd.print("  ");
  } else if (itemSelected <= 3) {
    lcd.setCursor(9, 2);
    if (oitava > 0) {
      lcd.print("+");
    }
    lcd.print(oitava);
    lcd.print("  ");
    lcd.setCursor(9, 2);
  }
}
void playLCD() {
  if (!menuOpen) {
    lcd.setCursor(17, 0);
    if (playing) {
      lcd.write(4);
    } else {
      lcd.write(5);
    }
  }
}
void pedalLCD() {
  if (!menuOpen) {
    lcd.setCursor(15, 0);
    if (pedalP) {
      lcd.write(2);
    } else {
      lcd.write(3);
    }
  }
}
void ccLCD(int cc, int value) {
  if (!menuOpen) {
    lcd.setCursor(0, 3);
    lcd.print("CC: ");
    lcd.print(cc);
    lcd.print(" V: ");
    lcd.print(value);
    lcd.print("     ");
  }
}
