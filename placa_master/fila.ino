void fila() {
  for (int p = 0 ; p < Pots ; p++) {
    for (int i = 1 ; i < leiturasFades ; i++) {
      fader[i - 1][p] = fader[i][p];
    }
  }
}
