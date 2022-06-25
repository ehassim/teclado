void loop() {


  encoderClick();
  fila();

  if (oitava != oitavaAntiga) {
    EEPROM.write(0, oitava + 20);
    oitavaAntiga = oitava;
  }
  if (transpose != transposeAntigo) {
    EEPROM.write(1, transpose + 20);
    transposeAntigo = transpose;
  }

  if (usbChannel != usbChannelAntigo) {
    EEPROM.write(2, usbChannel);
    usbChannelAntigo = usbChannel;
  }
  if (midiChannel != midiChannelAntigo) {
    EEPROM.write(3, midiChannel);
    midiChannelAntigo = midiChannel;
  }
  if (usbSplitChannel != usbSplitChannelAntigo) {
    EEPROM.write(4, usbSplitChannel);
    usbSplitChannelAntigo = usbSplitChannel;
  }
  if (midiSplitChannel != midiSplitChannelAntigo) {
    EEPROM.write(5, midiSplitChannel);
    midiSplitChannelAntigo = midiSplitChannel;
  }
  if (ccPlay != ccPlayAntigo) {
    EEPROM.write(6, ccPlay);
    ccPlayAntigo = ccPlay;
  }
  if (ccStop != ccStopAntigo) {
    EEPROM.write(7, ccStop);
    ccStopAntigo = ccStop;
  }
  if (retornoCCPlay != retornoCCPlayAntigo) {
    EEPROM.write(8, retornoCCPlay);
    retornoCCPlayAntigo = retornoCCPlay;
  }
  if (retornoCCStop != retornoCCStopAntigo) {
    EEPROM.write(9, retornoCCStop);
    retornoCCStopAntigo = retornoCCStop;
  }
  if (curvaVelocitValor != curvaVelocitAntigo) {
    EEPROM.write(10, curvaVelocitValor);
    curvaVelocitAntigo = curvaVelocitValor;
  }
  if (ccDialMenos != ccDialMenosAntigo) {
    EEPROM.write(11, ccDialMenos);
    ccDialMenosAntigo = ccDialMenos;
  }
  if (ccDialMais != ccDialMaisAntigo) {
    EEPROM.write(12, ccDialMais);
    ccDialMaisAntigo = ccDialMais;
  }
  if (ccPedal != ccPedalAntigo) {
    EEPROM.write(13, ccPedal);
    ccPedalAntigo = ccPedal;
  }

  for (int i = 0; i < Pots ; i++) {
    if (faderCC[i] != faderCCAntigo[i]) {
      EEPROM.write(i + 14, faderCC[i]);
      faderCCAntigo[i] = faderCC[i];
    }
  }

  //INCIO LEITURA DOS FADERS/PITCH BEND/ MODULATION

  for (int p = 0 ; p < Pots ; p++) {
    fadersValues = analogRead(pinosPot[p]);
    if (fadersValues > 180) {
      fadersValues = map(fadersValues, 180, 1019, 64, -1);
    } else {
      fadersValues = map(fadersValues, 3, 180, 127, 64);
    }
    fader[leiturasFades - 1][p] = fadersValues;
  }

  for (int p = 2 ; p < Pots ; p++) {
    if (mediaAnterior[p] != media[p] && (media[p] - mediaAnterior[p] > 1 || mediaAnterior[p] - media[p] > 1)) {
      mediaAnterior[p] = media[p];
      media[p] = media[p] > 127 ? 127 : (media[p] < 0 ? 0 : media[p]);
      MIDI_TX(176, faderCC[p], media[p]);
      // PITCH BEND
      //int pitchBend = map(sensor, 0, 1023, 0, 16383);
      // convert 8-bit bytes to 7-bit bytes:
      // int shiftedValue = pitchBend << 1;        // shift so top bit of lsb is in msb
      // byte msb = highByte(shiftedValue);        // get the high bits
      // byte lsb = lowByte(shiftedValue) >> 1;    // get the low 7 bits and shift right
      // MIDI_TX(224, lsb, msb);

    }
  }
  for (int p = 0 ; p < Pots ; p++) {
    media[p] = 0;
    for (int i = 0 ; i < leiturasFades ; i++) {
      media[p] = media[p] + fader[i][p];
    }
    media[p] = media[p] / (leiturasFades);
  }
  //FIM LEITURA DOS FADERS/PITCH BEND/ MODULATION

  //INICIO CONTROLE DE LED
  if (oitava > 0) {
    digitalWrite(ledOitavaMenos, LOW);
    digitalWrite(ledOitavaMais, HIGH);
  } else if (oitava < 0) {
    digitalWrite(ledOitavaMenos, HIGH);
    digitalWrite(ledOitavaMais, LOW);
  } else {
    digitalWrite(ledOitavaMenos, LOW);
    digitalWrite(ledOitavaMais, LOW);
  }

  if (transpose > 0) {
    digitalWrite(ledTransposeMenos, LOW);
    digitalWrite(ledTransposeMais, HIGH);
  } else if (transpose < 0) {
    digitalWrite(ledTransposeMenos, HIGH);
    digitalWrite(ledTransposeMais, LOW);
  } else {
    digitalWrite(ledTransposeMenos, LOW);
    digitalWrite(ledTransposeMais, LOW);
  }
  //FIM CONTROLE DE LEDS

  //INICIO ZERAMENTO DE TRANSPOSE E OITAVA
  if (digitalRead(btnTMenos) == LOW && digitalRead(btnTMais) == LOW && transpose != 0) {
    transpose = 0;
    transposeLCD();
  }
  if (digitalRead(btnOMenos) == LOW && digitalRead(btnOMais) == LOW && oitava != 0) {
    oitava = 0;
    oitavaLCD();
  }
  //FIM ZERAMENTO DE TRANSPOSE E OITAVA

  //INICIO DE LEITURAS DOS BOTOES DO PAINEL
  for (int i = 0 ; i < qbotoes ; i++) {
    botoesValor[i] = digitalRead(pinosBotoes[i]);
    if (statusPinos[i] != botoesValor[i] && tempoDeboucebotoes[i] == 0) {
      if (botoesValor[i] == LOW) {
        switch (pinosBotoes[i]) { //{44,43,30,39,34,37,38,33};
          case btnRwd:
            MIDI_TX(176, ccRwd, 127);
            digitalWrite(ledRwd, HIGH);
            break;
          case btnFfwd:
            MIDI_TX(176, ccFfwd, 127);
            digitalWrite(ledFfwd, HIGH);
            break;
          case btnPlay: //PLAY
            MIDI_TX(176, ccPlay, 127);
            onPlay();
            playing = true;
            playLCD();
            break;
          case btnStop : //STOP
            MIDI_TX(176, ccStop, 127);
            onStop();
            playing = false;
            playLCD();
            break;
          case btnTMenos: //TRANSPOSE -
            if (transpose > -12) {
              transpose--;
              transposeLCD();
            }
            break;
          case btnTMais: //TRANSPOSE +
            if (transpose < 12) {
              transpose++;
              transposeLCD();
            }
            break;
          case btnOMenos: //OITAVA -
            if (oitava > -3) {
              oitava--;
              oitavaLCD();
            }
            break;
          case btnOMais:// OITAVA +
            if (oitava < 3) {
              oitava++;
              oitavaLCD();
            }
            break;
        }
      } else {
        switch (pinosBotoes[i]) {
          case btnRwd:
            MIDI_TX(176, ccRwd, 0);
            digitalWrite(ledRwd, LOW);
            break;
          case btnFfwd:
            MIDI_TX(176, ccFfwd, 0);
            digitalWrite(ledFfwd, LOW);
            break;
        }
      }
      statusPinos[i] = botoesValor[i];
    } else {
      tempoDeboucebotoes[i]++;
      if (tempoDeboucebotoes[i] > maxDebounce) {
        tempoDeboucebotoes[i] = 0;
      }
    }
  }
  //FIM BOTOES DO PAINEL

  //INCIO CONTROLES DE LED TRANSPORT
  //NO STOP ABLETON RETORNA CC 123
  if (ultimoCC == 123 || ultimoCC == ccRwd || ultimoCC == ccFfwd) {
    if (timeCCStop < 500) {
      timeCCStop++;
    } else {
      if (digitalRead(btnRwd) == HIGH && digitalRead(btnFfwd) == HIGH) {
        timeCCStop = 0;
      }
    }
  } else {
    timeCCStop = 0;
  }
  if (Serial.available() > 0 ) {
    serialMidi = Serial.read();
    rxCC = Serial.read();
    rxValue = Serial.read();

    //serialMidi = 100;
    if (serialMidi == 176 ) { // se tiver recebendo controle

      if (rxCC == retornoCCStop || rxCC == ccRwd || rxCC == ccFfwd) {
        ultimoCC = rxCC;
        if (rxCC == retornoCCStop) {
          onStop();
          playing = false;
          playLCD();
        }
      } else {
        ultimoCC = 0;
      }
      if (rxCC == retornoCCPlay && timeCCStop == 0 && digitalRead(btnRwd) == HIGH && digitalRead(btnFfwd) == HIGH) {
        onPlay();
        playing = true;
        playLCD();
      }


    }
  }
  //FIM CONTROLES DE LED TRANSPORT

  //INCIO CONTROLE DO PEDAL DE SUSTAIN
  if (digitalRead(pinoPedal) == LOW && !pedal && (millis() - tempoPedal > 50)) {
    pedal = true;
    pedalP = pedalInvert ? false : true;
    MIDI_TX(176, ccPedal, pedalInvert ? 0 : 127);
    tempoPedal = millis();
    pedalLCD();
  }
  if (digitalRead(pinoPedal) == HIGH && pedal && (millis() - tempoPedal > 50) ) {
    pedal = false;
    pedalP = pedalInvert ? true : false;
    MIDI_TX(176, ccPedal, pedalInvert ? 127 : 0);
    tempoPedal = millis();
    pedalLCD();
  }
  //FIM CONTROLE DO PEDAL DE SUSTAIN


  if (updateEncoder && millis() - tempEncoder > 500 && !menuOpen) {
    lcd.setCursor(19, 3);
    lcd.print(" ");
    lcd.setCursor(19, 0);
    lcd.print(" ");
    updateEncoder = false;
  }

  // INICIO FECHA MENU DEPOIS DE 10 SEGUNDOS
  if (menuOpen) {
    if ((millis() - tempoMenu) / 1000 > tempoMenuOpen) {
      menuOpen = false;
      tela(INICIO);
    }
  }
  //FIM FECHA MENU DEPOIS DE 10 SEGUNDOS
}//loop
