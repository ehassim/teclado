void ccLCD(char cc, char

value){
  if(!menuOpen){
    lcd.setCursor(0, 3);
    lcd.print("CC: ");
    lcd.print(cc);
    lcd.print(" V: ");
    lcd.print(value);
    lcd.print("     ");
   }
}
