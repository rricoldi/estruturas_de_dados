#ifndef __SEMAFORO_H
#define __SEMAFORO_H

typedef void *Semaforo;

Semaforo criaSemaforo(char id[20], char corB[20], char corP[20], double x, double y, double espessura);

double retornaSX(Semaforo s);

double retornaSY(Semaforo s);

double retornaSEspessura(Semaforo s);

char *retornaSID(Semaforo s);

char *retornaSCorP(Semaforo s);

char *retornaSCorB(Semaforo s);

#endif