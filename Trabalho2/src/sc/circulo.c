#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circulo.h"


typedef struct circulo
{
    char id[20], corP[20], corB[20];
    double x, y, r, espessura;
}ItemC;

Circulo criaCirculo(char id[20], char corB[20], char corP[20], double raio, double x, double y, double espessura)
{
    ItemC *c;
    c = (ItemC*) calloc(1, sizeof(ItemC));
    strcpy(c->id, id);
    strcpy(c->corP, corP);
    strcpy(c->corB, corB);
    c->x = x;
    c->y = y;
    c->r = raio;
    c->espessura = espessura;

    return c;
}

double retornaCX(Circulo c)
{
    ItemC* item = (ItemC*) c;
    return item->x;
}

double retornaCY(Circulo c)
{
    ItemC* item = (ItemC*) c;
    return item->y;
}

double retornaCR(Circulo c)
{
    ItemC* item = (ItemC*) c;
    return item->r;
}

double retornaCEspessura(Circulo c)
{
    ItemC* item = (ItemC*) c;
    return item->espessura;
}

char *retornaCID(Circulo c)
{
    ItemC* item = (ItemC*) c;
    return item->id;
}

char *retornaCCorB(Circulo c)
{
    ItemC* item = (ItemC*) c;
    return item->corB;
}

char *retornaCCorP(Circulo c)
{
    ItemC* item = (ItemC*) c;
    return item->corP;
}

