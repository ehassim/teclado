void loop() {
  int sensor = 0;
  //ATIVA CI
  for (int CI = 0 ; CI < 3 ; CI++) {
    if (CI == 0) { //Primeiro CI
      digitalWrite(SC1_2, HIGH);
      digitalWrite(SC2_2, HIGH);

      digitalWrite(SC1_3, HIGH);
      digitalWrite(SC2_3, HIGH);

      digitalWrite(SC2_1, LOW);
      digitalWrite(SC3_1, LOW);
    }
    if (CI == 1) { //Segundo CI
      digitalWrite(SC2_1, HIGH);
      digitalWrite(SC3_1, HIGH);

      digitalWrite(SC1_3, HIGH);
      digitalWrite(SC2_3, HIGH);

      digitalWrite(SC1_2, HIGH);
      digitalWrite(SC2_2, LOW);
    }
    if (CI == 2) { //Segundo CI
      digitalWrite(SC2_1, HIGH);
      digitalWrite(SC3_1, HIGH);

      digitalWrite(SC1_2, HIGH);
      digitalWrite(SC2_2, HIGH);

      digitalWrite(SC1_3, HIGH);
      digitalWrite(SC2_3, LOW);
    }

    //percorre pinos CI
    //ATIVA PINO Y
    for (int i = 0 ; i < 8; i++) {
      digitalWrite(A_0[CI], matrizY[i][0]);
      digitalWrite(A_1[CI], matrizY[i][1]);
      digitalWrite(A_2[CI], matrizY[i][2]);

      // percorre os KD
      for (int j = 0 ; j < 8 ; j++) {
        sensor++;
        if (digitalRead(KD[j]) == LOW) {
          if (j < 4) { //primeiro sensor
            if (tempo_tecla[sensor] == 0) {
              tempo_tecla[sensor] = millis();
            }
          }
          if (j >= 4) { //segundo sensor
            if (!estado_tecla[sensor]) {
              int diftemp = millis() - tempo_tecla[sensor - 4];
              //Serial.println(diftemp);
              int velocit = map(diftemp, 5, 70, 127, 0);
              velocit = velocit > 127 ? 127 : (velocit < 0 ? 1 : velocit);
              if (!estado_tecla[sensor]) {
                estado_tecla[sensor] = true;
                sendNota(144, nota(sensor), velocit);
              }
            }
          }

        } else {
          tempo_tecla[sensor] = 0;
          if (estado_tecla[sensor] && digitalRead(KD[j - 4]) != LOW ) {
            sendNota(128, nota(sensor), 0);
            estado_tecla[sensor] = false;
          }
        }
      }
    }
  }
}
