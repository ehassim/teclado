
void tela(int tela) {

  switch (tela) {
    case INICIANDO:
      lcd.clear();
      lcd.setCursor(0, 4);
      lcd.print("Inicializando...");
      break;
    case INICIO:
      telaSelectAnt = 0;
      itemSelected = false;
      lcd.clear();
      lcd.noBlink();
      lcd.setCursor(0, 0);
      lcd.print("CH: ");
      lcd.print(usbChannel + 1);
      if (split) {
        lcd.print(" / ");
        lcd.print("16");
      }
      lcd.setCursor(0, 1);
      lcd.print("Tra: ");
      if (transpose > 0) {
        lcd.print("+");
      }
      lcd.print(transpose);
      if (split) {
        lcd.print(" / ");
        lcd.print("-11");
      }

      lcd.setCursor(0, 2);
      lcd.print("Oit: ");
      if (oitava > 0) {
        lcd.print("+");
      }
      lcd.print(oitava);
      if (split) {
        lcd.print(" / ");
        lcd.print("-3");
      }

      //pedal
      pedalLCD();
      playLCD();

      break;
    case MENU:
      linhaMenu = linhaMenu + giroEncoder;
      tempoMenu = millis();
      if (menuSelect < 4) {
        telaSelect = 1;
      } else if (menuSelect < 8) {
        telaSelect = 2;
      } else if (menuSelect < 12) {
        telaSelect = 3;
      } else if (menuSelect < 16) {
        telaSelect = 4;
      } else if (menuSelect < 20) {
        telaSelect = 5;
      } else if (menuSelect < 24) {
        telaSelect = 6;
      } else if (menuSelect < 28) {
        telaSelect = 7;
      } else if (menuSelect < 32) {
        telaSelect = 8;
      } else if (menuSelect < 36) {
        telaSelect = 9;
      } else if (menuSelect < 40) {
        telaSelect = 10;
      }

      if (telaSelect != telaSelectAnt) {
        lcd.clear();
      }
      switch (telaSelect) {
        case 1: //TELA 1
          linhaMenu = menuSelect;
          if (telaSelect != telaSelectAnt) {
            telaSelectAnt = telaSelect;
            lcd.setCursor(6, 0);
            lcd.print("AJUSTES");
            lcd.setCursor(1, 1);
            lcd.print("Transpose: ");
            if (transpose > 0) {
              lcd.print("+");
            }
            lcd.print(transpose);
            lcd.setCursor(1, 2);
            lcd.print("Oitava: ");
            if (oitava > 0) {
              lcd.print("+");
            }
            lcd.print(oitava);
            lcd.setCursor(1, 3);
            lcd.print("Polaridade Pedal: ");
            lcd.print(pedalInvert ? "-" : "+");
          }

          break;
        case 2: //TELA 2
          linhaMenu = menuSelect - 4;
          if (telaSelect != telaSelectAnt) {
            telaSelectAnt = telaSelect;
            lcd.setCursor(1, 0);
            lcd.print("CH USB: ");
            lcd.print(usbChannel + 1);
            lcd.setCursor(1, 1);
            lcd.print("CH MIDI: ");
            lcd.print(midiChannel + 1);
            lcd.setCursor(1, 2);
            lcd.print("CH USB Split: ");
            lcd.print(usbSplitChannel + 1);
            lcd.setCursor(1, 3);
            lcd.print("CH MIDI Split: ");
            lcd.print(midiSplitChannel + 1);
          }
          break;
        case 3: //TELA 3
          linhaMenu = menuSelect - 8;
          if (telaSelect != telaSelectAnt) {
            telaSelectAnt = telaSelect;
            lcd.setCursor(1, 0);
            lcd.print("Split: OFF");
            //lcd.print(usbChannel+1);
            lcd.setCursor(1, 1);
            lcd.print("Transp Split: 0");
            //lcd.print(midiChannel+1);
            lcd.setCursor(1, 2);
            lcd.print("Oitava Split: 0");
            //lcd.print(usbSplitChannel+1);
            lcd.setCursor(1, 3);
            lcd.print("Sustain Split: ON");
            //lcd.print(midiSplitChannel+1);
          }
          break;
        case 4: //TELA 4
          linhaMenu = menuSelect - 12;
          if (telaSelect != telaSelectAnt) {
            telaSelectAnt = telaSelect;
            lcd.setCursor(1, 0);
            lcd.print("Curva Velocit: ");
            lcd.print(curvaVelocitValor);
            lcd.setCursor(1, 1);
            lcd.print("CC Dial-: ");
            lcd.print(ccDialMenos);
            lcd.setCursor(1, 2);
            lcd.print("CC Dial+: ");
            lcd.print(ccDialMais);
            lcd.setCursor(1, 3);
            lcd.print("CC Pedal: ");
            lcd.print(ccPedal);
          }
          break;
        case 5: //TELA 5
          linhaMenu = menuSelect - 16;
          if (telaSelect != telaSelectAnt) {
            telaSelectAnt = telaSelect;
            lcd.setCursor(1, 0);
            lcd.print("CC Play: ");
            lcd.print(ccPlay);
            lcd.setCursor(1, 1);
            lcd.print("CC Stop: ");
            lcd.print(ccStop);
            lcd.setCursor(1, 2);
            lcd.print("CC Return Play: ");
            lcd.print(retornoCCPlay);
            lcd.setCursor(1, 3);
            lcd.print("CC Return Stop: ");
            lcd.print(retornoCCStop);
          }
          break;
        case 6: //TELA 6
          linhaMenu = menuSelect - 20;
          if (telaSelect != telaSelectAnt) {
            telaSelectAnt = telaSelect;
            lcd.setCursor(1, 0);
            lcd.print("CC Botao 1: ");
            lcd.print("");
            lcd.setCursor(1, 1);
            lcd.print("CC Botao 2: ");
            lcd.print("");
            lcd.setCursor(1, 2);
            lcd.print("CC Botao <<: ");
            lcd.print("");
            lcd.setCursor(1, 3);
            lcd.print("CC Botao >>: ");
            lcd.print("");
          }
          break;
        case 7: //TELA 7
          linhaMenu = menuSelect - 24;
          if (telaSelect != telaSelectAnt) {
            telaSelectAnt = telaSelect;
            lcd.setCursor(1, 0);
            lcd.print("CC Pitch Bend: ");
            if (faderCC[0] == 128) {
              lcd.print("DFLT");
            } else {
              lcd.print(faderCC[0]);
            }
            lcd.setCursor(1, 1);
            lcd.print("CC Modulation: ");
            lcd.print(faderCC[1]);
            lcd.setCursor(1, 2);
            lcd.print("CC Fader 1: ");
            lcd.print(faderCC[2]);
            lcd.setCursor(1, 3);
            lcd.print("CC Fader 2: ");
            lcd.print(faderCC[3]);
          }
          break;
        case 8: //TELA 8
          linhaMenu = menuSelect - 28;
          if (telaSelect != telaSelectAnt) {
            telaSelectAnt = telaSelect;
            lcd.setCursor(1, 0);
            lcd.print("CC Fader 3: ");
            lcd.print(faderCC[4]);
            lcd.setCursor(1, 1);
            lcd.print("CC Fader 4: ");
            lcd.print(faderCC[5]);
            lcd.setCursor(1, 2);
            lcd.print("CC Fader 5: ");
            lcd.print(faderCC[6]);
            lcd.setCursor(1, 3);
            lcd.print("CC Fader 6: ");
            lcd.print(faderCC[7]);
          }
          break;
        case 9: //TELA 9
          linhaMenu = menuSelect - 32;
          if (telaSelect != telaSelectAnt) {
            telaSelectAnt = telaSelect;
            lcd.setCursor(1, 0);
            lcd.print("CC Fader 7: ");
            lcd.print(faderCC[8]);
            lcd.setCursor(1, 1);
            lcd.print("CC Fader 8: ");
            lcd.print(faderCC[9]);
            lcd.setCursor(1, 2);
            lcd.print("CC Fader 9: ");
            lcd.print(faderCC[10]);
            lcd.setCursor(1, 3);
            lcd.print("CC Fader 10: ");
            lcd.print(faderCC[11]);
          }
          break;
        case 10: //TELA 10
          linhaMenu = menuSelect - 36;
          if (telaSelect != telaSelectAnt) {
            telaSelectAnt = telaSelect;
            lcd.setCursor(1, 0);
            lcd.print("CC Fader 11: ");
            lcd.print(faderCC[12]);
            lcd.setCursor(1, 1);
            lcd.print("CC Fader 12: ");
            lcd.print(faderCC[13]);
            lcd.setCursor(1, 2);
            lcd.print("CC Fader 13: ");
            lcd.print(faderCC[14]);
            lcd.setCursor(1, 3);
            lcd.print("CC Fader 14: ");
            lcd.print(faderCC[15]);
          }
          break;

      }

      lcd.noBlink();
      for (int t = 0 ; t <= 3 ; t++) {
        lcd.setCursor(0, t);
        if (linhaMenu == t) {
          if (telaSelect == 1 && t == 0) {
            lcd.print("X");
          } else {
            lcd.print(">");

          }
        } else {
          lcd.print(" ");
        }
      }
      if (linhaMenu == 0 && telaSelect == 1) {
        lcd.setCursor(0, 0);
        lcd.blink();
      }

      break;
  }
}
