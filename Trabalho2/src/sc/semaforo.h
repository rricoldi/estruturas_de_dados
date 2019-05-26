#ifndef __SEMAFORO_H
#define __SEMAFORO_H

typedef void *Semaforo;

Semaforo criaSemaforo(char id[20], char corB[20], char corP[20], double x, double y, double espessura);

double retornaSX(Semaforo r);

double retornaSY(Semaforo r);

double retornaSEspessura(Semaforo r);

char *retornaSID(Semaforo r);

char *retornaSCorP(Semaforo r);

char *retornaSCorB(Semaforo r);

#endif