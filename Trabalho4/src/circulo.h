#ifndef __CIRCULO_H
#define __CIRCULO_H

/*
    Aqui temos a forma do circulo, definimos um void pointer para podermos acessar os atributos desta forma apenas a partir das funcoes retornaC...
*/

typedef void *Circulo;

Circulo criarCirculo(char id[20], char corBorda[20], char corPreenchimento[20], double raio, double x, double y, double espessura);

double retornaCX(Circulo c);

double retornaCY(Circulo c);

double retornaCR(Circulo c);

double retornaCEspessura(Circulo c);

char *retornaCID(Circulo c);

char *retornaCCorP(Circulo c);

char *retornaCCorB(Circulo c);

double comparaCirculo(Circulo c1, Circulo c2);

void imprime(Circulo c);

void imprimeCirculos(Circulo circulo, char nomeDoArquivoSvg[], char cor[]);
#endif