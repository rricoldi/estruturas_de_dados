#ifndef __HIDRANTE_H
#define __HIDRANTE_H

typedef void *Hidrante;

Hidrante criaHidrante(char id[20], char corB[20], char corP[20], double espessura, double x, double y);

double retornaHX(Hidrante h);

void setHX(Hidrante h, double x);

double retornaHY(Hidrante h);

void setHY(Hidrante h, double y);

double retornaHEspessura(Hidrante h);

char *retornaHID(Hidrante h);

char *retornaHCorB(Hidrante h);

char *retornaHCorP(Hidrante h);

#endif