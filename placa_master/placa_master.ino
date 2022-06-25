/*
   note on MIDI 144
   note off MIDI 128
   progama MIDI 192
   cc MIDI 176
   224 Pitch Bend

  (decimal) (Hex)     Command             Data bytes
  128-143   80-8F     Note off            2 (note, velocity)
  144-159   90-9F     Note on             2 (note, velocity)
  160-175   A0-AF     Key Pressure        2 (note, key pressure)
  176-191   B0-BF     Control Change      2 (controller no., value)
  192-207   C0-CF     Program Change      1 (program no.)
  208-223   D0-DF     Channel Pressure    1 (pressure)
  224-239   E0-EF     Pitch Bend          2 (least significant byte, most significant byte)
*/

#include <Wire.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <ErriezRotaryFullStep.h>

boolean INICIADO = false;
boolean split = false;
unsigned long tempoMenu;
int menuSelect = 0;
int totalMenu = 39;
int telaSelect = 0;
int telaSelectAnt = 0;
int linhaMenu = 0;
unsigned long tempoMenuOpen = 10; //segundos;
boolean itemSelected = false;

#define Pots 16
#define leiturasFades  10
int fader[leiturasFades][Pots];
int pinosPot[Pots] = {A15, A14, A12, A13, A11, A9, A10, A8, A7, A6, A5, A4, A3, A2, A1, A0};
int faderCC[Pots] = {128, 1, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27};
int faderCCAntigo[Pots] = {128, 1, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27};
int media[Pots];
int mediaAnterior[Pots];
int fadersValues = 0;

int timeCCStop = 0;
int ultimoCC = 0;

boolean playing = false;

#define LCD_PINS_RS        25
#define LCD_PINS_ENABLE    24
#define LCD_PINS_D4        29
#define LCD_PINS_D5        28
#define LCD_PINS_D6        26
#define LCD_PINS_D7        23
#define LCD_HEIGHT         4
#define LCD_WIDTH          20

LiquidCrystal lcd(LCD_PINS_RS, LCD_PINS_ENABLE, LCD_PINS_D4, LCD_PINS_D5, LCD_PINS_D6, LCD_PINS_D7);

byte setaCima[] = {B00000, B00000, B00100, B01110, B11111, B00000, B00000, B00000};
byte setaBaixo[] = {B00000, B00000, B00000, B11111, B01110, B00100, B00000, B00000};
byte pedalON[] = {B01110, B01110, B01110, B11111, B11111, B11111, B11111, B01110};
byte pedalOFF[] = {B01010, B01010, B01010, B10001, B10001, B10001, B10001, B01110};
byte play[] = {B00000, B10000, B11000, B11100, B11110, B11100, B11000, B10000};
byte stoped[] = {B00000, B11111, B11111, B11111, B11111, B11111, B11111, B00000};
byte sair[] = {B00000, B11111, B01110, B10101, B11011, B10101, B01110, B11111};

#define ledPlay             33 //BNT 31
#define ledStop             37 //BNT 35
#define ledRwd              45 //BNT 43
#define ledFfwd             41 //BNT 39

#define ledSplit1           32 //BNT 30
#define ledSplit2           52 //BNT 50
#define ledTransposeMenos   36 //BNT 34
#define ledTransposeMais    48 //BNT 46
#define ledOitavaMenos      40 //BNT 38
#define ledOitavaMais       44 //BNT 42

#define btnSplit1  30
#define btnSplit2  50
#define btnTMenos  34
#define btnTMais  46
#define btnOMenos  38
#define btnOMais  42

#define btnRwd 43
#define btnFfwd 39
#define btnPlay  31
#define btnStop  35

const int qbotoes = 10;
int pinosBotoes[qbotoes] = {btnRwd, btnFfwd, btnPlay, btnStop, btnSplit1, btnSplit2, btnTMenos, btnTMais, btnOMenos, btnOMais};
int botoesValor[qbotoes];
int statusPinos[qbotoes];
int tempoDeboucebotoes[qbotoes];
int maxDebounce = 5;

#define INICIANDO   0
#define INICIO  1
#define MENU  2
boolean menuOpen = false;
boolean updateEncoder = false;
unsigned long tempEncoder = 0;

// Encoder rotation values
#define BTN_ENC            27
boolean statusENC = false;
#define ROTARY_PIN1   18
#define ROTARY_PIN2   19

int curva = 0;

RotaryFullStep rotary(ROTARY_PIN1, ROTARY_PIN2, true, 10);
void rotaryInterrupt();
int giroEncoder;


int pinoPedal = 22;
boolean pedal = false;
boolean pedalInvert = false;
boolean pedalP = false;
unsigned long tempoPedal = 0;

int oitava = 0; // 0 EPROM
int oitavaAntiga = 0;
int transpose = 0; // 1 EPROM
int transposeAntigo = 0;

int usbChannel = 0; // 2 EPROM
int midiChannel = 0; // 3 EPROM
int usbSplitChannel = 0; // 4 EPROM
int midiSplitChannel = 0;  // 5 EPROM
int usbChannelAntigo = 0;
int midiChannelAntigo = 0;
int usbSplitChannelAntigo = 0;
int midiSplitChannelAntigo = 0;

int cursorBlink[40] = {0, 12, 9, 19, 9, 10, 15, 16, 8, 15, 15, 16, 16, 11, 11, 11, 10, 10, 17, 17, 13, 13, 14, 14, 16, 16, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14};

int ccPlay = 100; //EPROM 6
int ccPlayAntigo = ccPlay;
int ccStop = 101; //EPROM 7
int ccStopAntigo = ccStop;
int retornoCCPlay = 119; //EPROM 8
int retornoCCPlayAntigo = retornoCCPlay;
int retornoCCStop = 123; //EPROM 9
int retornoCCStopAntigo = retornoCCStop;

int curvaVelocitValor = 0; //EPROM 10
int curvaVelocitAntigo = curvaVelocitValor;
int ccDialMenos = 29; //EPROM 11
int ccDialMenosAntigo = ccDialMenos;
int ccDialMais = 30; //EPROM 12
int ccDialMaisAntigo = ccDialMais;
int ccPedal = 64; //EPROM 13
int ccPedalAntigo = ccPedal;

int ccRwd = 20;
int ccFfwd = 21;


byte getCC;
byte getNota;
byte getVelocit;

unsigned char status;
byte serialMidi;
byte rxCC;
byte rxValue;

int notaProcess;
int notasON[89]; 
