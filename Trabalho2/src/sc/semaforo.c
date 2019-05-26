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

double retornaRX(Semaforo s)
{
    ItemS* item = (ItemS*) s;
    return item->x;
}

double retornaRY(Semaforo s)
{
    ItemS* item = (ItemS*) s;
    return item->y;
}

double retornaREspessura(Semaforo s)
{
    ItemS* item = (ItemS*) s;
    return item->espessura;
}

char *retornaRCEP(Semaforo s)
{
    ItemS* item = (ItemS*) s;
    return item->id;
}

char *retornaRCorB(Semaforo s)
{
    ItemS* item = (ItemS*) s;
    return item->corB;
}

char *retornaRCorP(Semaforo s)
{
    ItemS* item = (ItemS*) s;
    return item->corP;
}
