void onPlay() {
  digitalWrite(ledStop, LOW);
  digitalWrite(ledPlay, HIGH);
}
void onStop() {
  digitalWrite(ledStop, HIGH);
  digitalWrite(ledPlay, LOW);
}
