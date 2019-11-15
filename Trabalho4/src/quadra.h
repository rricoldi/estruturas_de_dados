#ifndef __QUADRA_H
#define __QUADRA_H

/*
    Aqui temos a quadra, definimos um void pointer para podermos acessar os atributos desta apenas a partir das funcoes retornaQ... e setQ...
    Eh reresentada por um retangulo com as dimensoes passadas    
*/
#include<stdarg.h>

typedef void *Quadra;

Quadra criarQuadra(char cep[20], char corB[20], char corP[20], double largura, double altura, double x, double y, double espessura);
void* quadraFinalizar(Quadra);

double retornaQX(Quadra q);

void setQX(Quadra q, double x);

double retornaQY(Quadra q);

void setQY(Quadra q, double y);

double retornaQW(Quadra q);

double retornaQH(Quadra q);

double retornaQEspessura(Quadra q);

void setQEspessura(Quadra, double);

char *retornaQCEP(Quadra q);

char *retornaQCorB(Quadra q);

void setQCorB(Quadra q, char cor[]);

char *retornaQCorP(Quadra q);
void setQcorP(Quadra, char* novaCor);

double comparaQuadra(Quadra q1, Quadra q2);

void imprimirQuadra(Quadra quad, va_list args);

#endif