//INICIO LEITURA ENCODER
#if defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32)
ICACHE_RAM_ATTR
#endif
void rotaryInterrupt() {
  int rotaryState;
  rotaryState = rotary.read();
  if ((rotaryState > 0) || (rotaryState < 0) && INICIADO) {
    tempoMenu = millis();
    updateEncoder = true;
    tempEncoder = millis();
    if (rotaryState > 0) { //rodou para direita
      giroEncoder = 1;
      if (!menuOpen) {
        lcd.setCursor(19, 0);
        lcd.print(" ");
        lcd.setCursor(19, 3);
        lcd.write(byte(1));
        for (int m = 0 ; m < rotaryState ; m++) {
          MIDI_TX(176, ccDialMais, 127);
        }
      }
    } else { //rodou para esquerda
      giroEncoder = -1;
      if (!menuOpen) {
        lcd.setCursor(19, 3);
        lcd.print(" ");
        lcd.setCursor(19, 0);
        lcd.write(byte(0));
        for (int m = rotaryState ; m < 0 ; m++) {
          MIDI_TX(176, ccDialMenos, 127);
        }
      }
    }

    //rodou encoder
    if (menuOpen) {
      if (menuSelect >= 0 && menuSelect <= totalMenu && !itemSelected) {
        if (menuSelect + giroEncoder >= 0 && menuSelect + giroEncoder <= totalMenu) {
          menuSelect = menuSelect + giroEncoder;
          tela(MENU);
        }
      }
      if (itemSelected) {
        switch (menuSelect) {
          case 1: //Transpose
            if (transpose + giroEncoder >= -12 && transpose + giroEncoder <= 12) {
              transpose = transpose + giroEncoder;
              if (transpose > 0) {
                lcd.print("+");
              }
              lcd.print(transpose);
              lcd.print("  ");
            }
            break;
          case 2: //Oitava
            if (oitava + giroEncoder >= -3 && oitava + giroEncoder <= 3) {
              oitava = oitava + giroEncoder;
              if (oitava > 0) {
                lcd.print("+");
              }
              lcd.print(oitava);
              lcd.print("  ");
            }
            break;
          case 3: //Polaridade Pedal
            pedalInvert = pedalInvert ? false : true;
            lcd.print(pedalInvert ? "-" : "+");
            break;
          case 4: //CH USB
            if (usbChannel + giroEncoder >= 0 && usbChannel + giroEncoder <= 15) {
              usbChannel = usbChannel + giroEncoder;
              lcd.print(usbChannel + 1);
              lcd.print("  ");
            }
            break;
          case 5: //CH MIDI
            if (midiChannel + giroEncoder >= 0 && midiChannel + giroEncoder <= 15) {
              midiChannel = midiChannel + giroEncoder;
              lcd.print(midiChannel + 1);
              lcd.print("  ");
            }
            break;
          case 6: //CH USB Split
            if (usbSplitChannel + giroEncoder >= 0 && usbSplitChannel + giroEncoder <= 15) {
              usbSplitChannel = usbSplitChannel + giroEncoder;
              lcd.print(usbSplitChannel + 1);
              lcd.print(" ");
            }
            break;
          case 7: //CH MIDI Split
            if (midiSplitChannel + giroEncoder >= 0 && midiSplitChannel + giroEncoder <= 15) {
              midiSplitChannel = midiSplitChannel + giroEncoder;
              lcd.print(midiSplitChannel + 1);
              lcd.print(" ");
            }
            break;
          case 8:
            break;
          case 9:
            break;
          case 10:
            break;
          case 11:
            break;
          case 12: //Curva Velocit
            if (curvaVelocitValor + giroEncoder >= 0 && curvaVelocitValor + giroEncoder <= 2) {
              curvaVelocitValor = curvaVelocitValor + giroEncoder;
              lcd.print(curvaVelocitValor);
              lcd.print(" ");
            }
            break;
          case 13: //CC Dial-
            if (ccDialMenos + rotaryState >= 0 && ccDialMenos + rotaryState <= 127) {
              ccDialMenos = ccDialMenos + rotaryState;
              lcd.print(ccDialMenos);
              lcd.print(" ");
            }
            break;
          case 14: //CC Dial+
            if (ccDialMais + rotaryState >= 0 && ccDialMais + rotaryState <= 127) {
              ccDialMais = ccDialMais + rotaryState;
              lcd.print(ccDialMais);
              lcd.print(" ");
            }
            break;
          case 15: //CC Pedal
            if (ccPedal + rotaryState >= 0 && ccPedal + rotaryState <= 127) {
              ccPedal = ccPedal + rotaryState;
              lcd.print(ccPedal);
              lcd.print(" ");
            }
            break;
          case 16: //CC Play
            if (ccPlay + rotaryState >= 0 && ccPlay + rotaryState <= 127) {
              ccPlay = ccPlay + rotaryState;
              lcd.print(ccPlay);
              lcd.print(" ");
            }
            break;
          case 17: //CC Stop
            if (ccStop + rotaryState >= 0 && ccStop + rotaryState <= 127) {
              ccStop = ccStop + rotaryState;
              lcd.print(ccStop);
              lcd.print(" ");
            }
            break;
          case 18: //Retorno CC Play
            if (retornoCCPlay + rotaryState >= 0 && retornoCCPlay + rotaryState <= 127) {
              retornoCCPlay = retornoCCPlay + rotaryState;
              lcd.print(retornoCCPlay);
              lcd.print(" ");
            }
            break;
          case 19: //Retorno CC Stop
            if (retornoCCStop + rotaryState >= 0 && retornoCCStop + rotaryState <= 127) {
              retornoCCStop = retornoCCStop + rotaryState;
              lcd.print(retornoCCStop);
              lcd.print(" ");
            }
            break;
          case 20:
            break;
          case 21:
            break;
          case 22:
            break;
          case 23:
            break;
          case 24: //CC Pitch Bend
            if (faderCC[0] + rotaryState >= 0 && faderCC[0] + rotaryState <= 127) {
              faderCC[0] = faderCC[0] + rotaryState;
            } else {
              if (faderCC[0] == 0 && rotaryState < 0) {
                faderCC[0] = 128;
              }
              if (faderCC[0] == 127 && rotaryState > 0) {
                faderCC[0] = 128;
              } else if (faderCC[0] == 128 && rotaryState > 0) {
                faderCC[0] = 0;
              }
            }
            if (faderCC[0] == 128) {
              lcd.print("DFLT");
            } else {
              lcd.print(faderCC[0]);
              lcd.print(faderCC[0] < 10 ? "   " : "  ");
            }
            break;
        }
        // case  25 a 39
        if (menuSelect >= 25 && menuSelect <= 39) {
          if (faderCC[menuSelect - 24] + rotaryState >= 0 && faderCC[menuSelect - 24] + rotaryState <= 127) {
            faderCC[menuSelect - 24] = faderCC[menuSelect - 24] + rotaryState;
            lcd.print(faderCC[menuSelect - 24]);
            lcd.print(" ");
          }
        }
        lcd.setCursor(cursorBlink[menuSelect], linhaMenu);
      }
    }
  }
}
//FIM LEITURA ENCODER
