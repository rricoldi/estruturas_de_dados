#ifndef __QUADRA_H
#define __QUADRA_H

typedef void *Quadra;

Quadra criaQuadra(char cep[20], char corB[20], char corP[20], double largura, double altura, double x, double y, double espessura);

double retornaQX(Quadra q);

double retornaQY(Quadra q);

double retornaQW(Quadra q);

double retornaQH(Quadra q);

double retornaQEspessura(Quadra q);

char *retornaQCEP(Quadra q);

char *retornaQCorP(Quadra q);

char *retornaQCorB(Quadra q);

#endif