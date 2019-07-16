#ifndef __SEMAFORO_H
#define __SEMAFORO_H

/*
    Aqui temos o semaforo, definimos um void pointer para podermos acessar os atributos deste equipamento urbano apenas a partir das funcoes retornaS... e setS...
    Eh reresentada por um retangulo comprido    
*/


typedef void *Semaforo;

Semaforo criaSemaforo(char id[20], char corB[20], char corP[20], double x, double y, double espessura);

double retornaSX(Semaforo s);

void setSX(Semaforo s, double x);

double retornaSY(Semaforo s);

void setSY(Semaforo s, double y);

double retornaSEspessura(Semaforo s);

char *retornaSID(Semaforo s);

char *retornaSCorP(Semaforo s);

char *retornaSCorB(Semaforo s);

#endif