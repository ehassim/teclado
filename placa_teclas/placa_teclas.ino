#include <Wire.h>

//FLAT
int SA1 = 2;
int SA2 = 3;
int SA3 = 4;
int SA4 = 5;
int SA5 = 6;
int KD[8] = {7,8,9,10,11,12,15,14};

//74HC138AN
int A_0[3] = {SA1,SA1,SA1};
int A_1[3] = {SA2,SA2,SA2};
int A_2[3] = {SA3,SA3,SA3}; 

int SC2_1 =  SA4;
int SC3_1 =  SA5;
int SC1_2 =  SA4;
int SC2_2 =  SA5;
int SC1_3 =  SA5;
int SC2_3 =  SA4;
int matrizY[8][3] = {{0,0,0},{1,0,0},{0,1,0},{1,1,0},{0,0,1},{1,0,1},{0,1,1},{1,1,1}};

#define NUMBER_ARRAY 200
boolean estado_tecla[NUMBER_ARRAY];   
unsigned long tempo_tecla[NUMBER_ARRAY];
unsigned long tempo_teclaON[NUMBER_ARRAY];
