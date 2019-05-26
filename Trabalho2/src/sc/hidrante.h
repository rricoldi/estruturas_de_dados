#ifndef __HIDRANTE_H
#define __HIDRANTE_H

typedef void *Hidrante;

Hidrante criaHidrante(char id[20], char corB[20], char corP[20], double espessura, double x, double y);

double retornaHX(Hidrante h);

double retornaHY(Hidrante h);

char *retornaHID(Hidrante h);

#endif