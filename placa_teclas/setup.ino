void setup() {

  //Serial.begin(9600);

  Wire.begin();
  for (int i = 0 ; i < 8 ; i++) {
    pinMode(KD[i], INPUT_PULLUP);
  }

  for (int i = 0 ; i < 3 ; i++) {
    pinMode(A_0[i], OUTPUT);
    pinMode(A_1[i], OUTPUT);
    pinMode(A_2[i], OUTPUT);
  }

  pinMode(SC2_1, OUTPUT);
  pinMode(SC3_1, OUTPUT);
  pinMode(SC1_2, OUTPUT);
  pinMode(SC2_2, OUTPUT);
  pinMode(SC1_3, OUTPUT);
  pinMode(SC2_3, OUTPUT);

}
