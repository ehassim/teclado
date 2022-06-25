void sendNota(byte cc, byte n, byte v) {
 // Serial.println(n);
  Wire.beginTransmission(8);
  Wire.write(cc);
  Wire.write(n);
  Wire.write(v);
  Wire.endTransmission();
  
}
