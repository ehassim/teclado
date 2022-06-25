void encoderClick() {
  if (digitalRead(BTN_ENC) == LOW) {
    if (!statusENC) {
      statusENC = true;
      //MIDI_TX(176,18,127);
      if (!menuOpen) {
        menuOpen = true;
        tela(MENU);
      } else {
        if (itemSelected) {
          itemSelected = false;
          lcd.noBlink();
        } else {
          lcd.blink();
          //SET CURSOR BLINK
          lcd.setCursor(cursorBlink[menuSelect], linhaMenu);

          if (menuSelect == 0) {
            menuOpen = false;
            tela(INICIO);
          } else {
            itemSelected = true;
            lcd.blink();
          }
        }
      }
    }
  } else {
    statusENC = false;
  }
}
