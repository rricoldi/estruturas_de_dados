#ifndef __RADIO_H
#define __RADIO_H

/*
    Aqui temos a radio base, definimos um void pointer para podermos acessar os atributos deste equipamento urbano apenas a partir das funcoes retornaR... e setR...
    Eh reresentada por uma elipse comprida    
*/

typedef void *Radio;

Radio criarRadioBase(char id[20], char corB[20], char corP[20], double x, double y, double espessura);
void radioBaseFinalizar(Radio);

double retornaRX(Radio r);

void setRX(Radio r, double x);

double retornaRY(Radio r);

void setRY(Radio r, double y);

double retornaREspessura(Radio r);

char *retornaRID(Radio r);

char *retornaRCorP(Radio r);

char *retornaRCorB(Radio r);

double comparaRadio(Radio r1, Radio r2);

void navegaRadio(Radio rad);

void imprimirRadioDaArvore(Radio *rad, FILE *arquivoSVG, int x, int y, char cor);

#endif