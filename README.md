# TECLADO CONTROLADOR

Códigos do teclado controlador

# placa_teclas
 Essa pasta contém os códigos gravados no arduino NANO que faz a leitura das teclas e envia uma mensagem (I2C) informando qual tecla foi precionada, velocity, e quando a tecla foi solta para o arduino mega (placa_master).
 
# placa_master
  Essa pasta contém os códigos gravado no arduino MEGA onde estão conectados todos os botões, leds, faders, tela LCD, pedal de sustain.
  O arduino MEGA recebe uma mensagem I2C do arduino NANO, com infomações de tecla pressionada, velocity e tecla solta.
  O arduino MEGA envia uma mensagem na porta serial (USB) com as mensagem MIDI para o computador.

# MIDI Class Compilant
 Essa pasta contém os arquivos para converter o arduino MEGA em um dispositivo MIDI nativo.
