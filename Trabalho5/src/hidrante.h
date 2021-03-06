#ifndef __HIDRANTE_H
#define __HIDRANTE_H

/*
    Aqui temos o hidrante, definimos um void pointer para podermos acessar os atributos deste equipamento urbano apenas a partir das funcoes retornaH... e setH...
*/

//Todas as funções de objetos são analogas às funções em circulo.h

#include <stdarg.h>
typedef void *Hidrante;

Hidrante criarHidrante(char id[20], char corB[20], char corP[20], double espessura, double x, double y);
void hidranteFinalizar(Hidrante);

double retornaHX(Hidrante h);

void setHX(Hidrante h, double x);

double retornaHY(Hidrante h);

void setHY(Hidrante h, double y);

double retornaHEspessura(Hidrante h);

char *retornaHID(Hidrante h);

char *retornaHCorB(Hidrante h);

char *retornaHCorP(Hidrante h);

double comparaHidrante(Hidrante h1, Hidrante h2);

void imprimirHidrante(Hidrante hid, va_list args);

void navegaHidrante(Hidrante hid);

void imprimirHidranteDaArvore(Hidrante *hid, FILE *arquivoSVG, int x, int y, char cor);

#endif