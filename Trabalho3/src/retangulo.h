#ifndef __RETANGULO_H
#define __RETANGULO_H

/*
    Aqui temos a forma do retangulo, definimos um void pointer para podermos acessar os atributos desta forma apenas a partir das funcoes retornaRe...
*/

typedef void *Retangulo;

Retangulo criarRetangulo(char id[20], char corB[20], char corP[20], double largura, double altura, double x, double y, double espessura);

double retornaReX(Retangulo re);

double retornaReY(Retangulo re);

double retornaReW(Retangulo re);

double retornaReH(Retangulo re);

double retornaReEspessura(Retangulo re);

char *retornaReID(Retangulo re);

char *retornaReCorP(Retangulo re);

char *retornaReCorB(Retangulo re);

#endif