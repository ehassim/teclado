void setup() {
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Serial.begin(31250); //Velocidade MIDI Nativa 31250

  lcd.createChar(0, setaCima);
  lcd.createChar(1, setaBaixo);
  lcd.createChar(2, pedalON);
  lcd.createChar(3, pedalOFF);
  lcd.createChar(4, play);
  lcd.createChar(5, stoped);
  lcd.createChar(6, sair);

  pinMode(ledRwd, OUTPUT);
  pinMode(ledFfwd, OUTPUT);
  pinMode(ledPlay, OUTPUT);
  pinMode(ledStop, OUTPUT);
  pinMode(ledSplit1, OUTPUT);
  pinMode(ledSplit2, OUTPUT);
  pinMode(ledTransposeMenos, OUTPUT);
  pinMode(ledTransposeMais, OUTPUT);
  pinMode(ledOitavaMenos, OUTPUT);
  pinMode(ledOitavaMais, OUTPUT);

  for (int i = 0 ; i < qbotoes ; i++) {
    pinMode(pinosBotoes[i], INPUT_PULLUP);
    statusPinos[i] = 1;
    tempoDeboucebotoes[i] = 1;
  }

  for (int p = 0 ; p < Pots ; p++) {
    for (int i = 0 ; i < leiturasFades ; i++) {
      fader[i][p] = map(analogRead(pinosPot[p]), 5, 1023, 1, 127);
    }
  }

  attachInterrupt(digitalPinToInterrupt(ROTARY_PIN1), rotaryInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ROTARY_PIN2), rotaryInterrupt, CHANGE);

  lcd.begin(LCD_WIDTH, LCD_HEIGHT);
  lcd.display();
  lcd.noCursor();
  lcd.clear();

  tela(INICIANDO);

  pinMode(BTN_ENC, INPUT_PULLUP);
  pinMode(pinoPedal, INPUT_PULLUP);

  if (digitalRead(pinoPedal) == LOW) {
    pedalInvert = true;
  }

  if (digitalRead(btnPlay) == LOW && digitalRead(btnStop) == LOW) {
    lcd.setCursor(0, 0);
    lcd.print("Resetando de Fabrica");
    for (int i = 0 ; i < EEPROM.length() ; i++) {
      EEPROM.write(i, 255);
    }
  }

  int auxEPROM;
  auxEPROM = EEPROM.read(0) - 20;
  if (auxEPROM >= -3 && auxEPROM <= 3) {
    oitava = auxEPROM;
  }

  auxEPROM = EEPROM.read(1) - 20;
  if (auxEPROM >= -12 && auxEPROM <= 12) {
    transpose = auxEPROM;
  }

  auxEPROM = EEPROM.read(2);
  if (auxEPROM >= 0 && auxEPROM <= 15) {
    usbChannel = auxEPROM;
  }

  auxEPROM = EEPROM.read(3);
  if (auxEPROM >= 0 && auxEPROM <= 15) {
    midiChannel = auxEPROM;
  }

  auxEPROM = EEPROM.read(4);
  if (auxEPROM >= 0 && auxEPROM <= 15) {
    usbSplitChannel = auxEPROM;
  }
  auxEPROM = EEPROM.read(5);
  if (auxEPROM >= 0 && auxEPROM <= 15) {
    midiSplitChannel = auxEPROM;
  }
  auxEPROM = EEPROM.read(6);
  if (auxEPROM >= 0 && auxEPROM <= 127) {
    ccPlay = auxEPROM;
  }
  auxEPROM = EEPROM.read(7);
  if (auxEPROM >= 0 && auxEPROM <= 127) {
    ccStop = auxEPROM;
  }
  auxEPROM = EEPROM.read(8);
  if (auxEPROM >= 0 && auxEPROM <= 127) {
    retornoCCPlay = auxEPROM;
  }
  auxEPROM = EEPROM.read(9);
  if (auxEPROM >= 0 && auxEPROM <= 127) {
    retornoCCStop = auxEPROM;
  }
  auxEPROM = EEPROM.read(10);
  if (auxEPROM >= 0 && auxEPROM <= 2) {
    curvaVelocitValor = auxEPROM;
  }
  auxEPROM = EEPROM.read(11);
  if (auxEPROM >= 0 && auxEPROM <= 127) {
    ccDialMenos = auxEPROM;
  }
  auxEPROM = EEPROM.read(12);
  if (auxEPROM >= 0 && auxEPROM <= 127) {
    ccDialMais = auxEPROM;
  }
  auxEPROM = EEPROM.read(13);
  if (auxEPROM >= 0 && auxEPROM <= 127) {
    ccPedal = auxEPROM;
  }

  for (int i = 0; i < Pots ; i++) {
    auxEPROM = EEPROM.read(i + 14);
    if (auxEPROM >= 0 && auxEPROM <= 128) {
      faderCC[i] = auxEPROM;
    }
  }

  delay(2000);
  tela(INICIO);

  INICIADO = true;
  MIDI_TX(176, ccPedal, 0); // pedal OFF

  digitalWrite(ledSplit1, LOW);
  digitalWrite(ledSplit2, LOW);
  onStop();
}
