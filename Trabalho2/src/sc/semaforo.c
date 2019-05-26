#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semaforo.h"



typedef struct radio{
    char id[20], corP[20], corB[20];
    double x, y, espessura;
}ItemS;

Semaforo criaSemaforo(char id[20], char corB[20], char corP[20], double x, double y, double espessura)
{
    ItemS *s;
    s = (ItemS*) calloc(1, sizeof(ItemS));
    strcpy(s->id, id);
    strcpy(s->corP, corP);
    strcpy(s->corB, corB);
    s->x = x;
    s->y = y;
    s->espessura = espessura;
    
    return s;
}

double retornaSX(Semaforo s)
{
    ItemS* item = (ItemS*) s;
    return item->x;
}

double retornaSY(Semaforo s)
{
    ItemS* item = (ItemS*) s;
    return item->y;
}

double retornaSEspessura(Semaforo s)
{
    ItemS* item = (ItemS*) s;
    return item->espessura;
}

char *retornaSID(Semaforo s)
{
    ItemS* item = (ItemS*) s;
    return item->id;
}

char *retornaSCorB(Semaforo s)
{
    ItemS* item = (ItemS*) s;
    return item->corB;
}

char *retornaSCorP(Semaforo s)
{
    ItemS* item = (ItemS*) s;
    return item->corP;
}
