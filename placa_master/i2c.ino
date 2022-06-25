void receiveEvent(int howMany) {
  while (Wire.available() > 0) {
    getCC = Wire.read();
    getNota = Wire.read();
    getVelocit = Wire.read();
  }

  byte doCenter = 60;
  if (digitalRead(btnTMenos) == HIGH && digitalRead(btnTMais) == HIGH) {
    notaProcess = nota(getNota);
    if (getCC == 144) {
      if (notaProcess >= 0 && notaProcess <= 127) {
        MIDI_TX(getCC, notaProcess, curvaVelocit(getVelocit));
        notasON[getNota - 20] = notaProcess;
      }else{
        notasON[getNota - 20] = -1;
      }
    } else if (getCC == 128 && notasON[getNota - 20]>=0) {
      MIDI_TX(getCC, notasON[getNota - 20], 0);
    }

  } else if (getNota >= doCenter - 12 && getNota <= doCenter + 12) {
    if (getNota == doCenter) {
      transpose = 0;
    } else  {
      transpose = getNota - doCenter;
    }
    transposeLCD();
  }

}
