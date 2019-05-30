#ifndef __RADIO_H
#define __RADIO_H

typedef void *Radio;

Radio criaRadio(char id[20], char corB[20], char corP[20], double x, double y, double espessura);

double retornaRX(Radio r);

void setRX(Radio r, double x);

double retornaRY(Radio r);

void setRY(Radio r, double y);

double retornaREspessura(Radio r);

char *retornaRID(Radio r);

char *retornaRCorP(Radio r);

char *retornaRCorB(Radio r);

#endif