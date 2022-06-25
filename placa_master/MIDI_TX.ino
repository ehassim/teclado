void MIDI_TX(unsigned char CC, unsigned char PITCH, unsigned char VELOCITY) {
  status = CC + usbChannel;
  Serial.write(status);
  Serial.write(PITCH);
  Serial.write(VELOCITY);
  if(CC==176){
    ccLCD(PITCH,VELOCITY);
 }
}
