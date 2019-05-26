#ifndef __RADIO_H
#define __RADIO_H

typedef void *Radio;

Radio criaRadio(char id[20], char corB[20], char corP[20], double x, double y, double espessura);

double retornaRX(Radio r);

double retornaRY(Radio r);

double retornaREspessura(Radio r);

char *retornaRID(Radio r);

char *retornaRCorP(Radio r);

char *retornaRCorB(Radio r);

#endif