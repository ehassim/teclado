int nota(int sensor) {
  for (int n = 4 ; n <= sensor ; n = n + 4) {
    if (sensor > n) {
      sensor = sensor - 4;
    }
  }
  return sensor + 20;
}
