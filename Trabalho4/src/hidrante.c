#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hidrante.h"

typedef struct hidrante
{
    char id[20], corP[20], corB[20];
    double x, y, espessura;
} ItemH;

Hidrante criarHidrante(char id[20], char corB[20], char corP[20], double espessura, double x, double y)
{
    ItemH *h;

    h = (ItemH *)calloc(1, sizeof(ItemH));

    strcpy(h->id, id);
    strcpy(h->corB, corB);
    strcpy(h->corP, corP);

    h->x = x;
    h->y = y;
    h->espessura = espessura;

    return h;
}

double retornaHX(Hidrante h)
{
    ItemH *h2 = (ItemH *)h;
    return h2->x;
}

void setHX(Hidrante h, double x)
{
    ItemH *h2 = (ItemH *)h;
    h2->x = x;
}

double retornaHY(Hidrante h)
{
    ItemH *h2 = (ItemH *)h;
    return h2->y;
}

void setHY(Hidrante h, double y)
{
    ItemH *h2 = (ItemH *)h;
    h2->y = y;
}

double retornaHEspessura(Hidrante h)
{
    ItemH *item = (ItemH *)h;
    return item->espessura;
}

char *retornaHID(Hidrante h)
{
    ItemH *h2 = (ItemH *)h;
    return h2->id;
}

char *retornaHCorB(Hidrante h)

{
    ItemH *item = (ItemH *)h;
    return item->corB;
}

char *retornaHCorP(Hidrante h)

{
    ItemH *item = (ItemH *)h;
    return item->corP;
}

double comparaHidrante(Hidrante h1, Hidrante h2)
{
    ItemH *hidrante1 = (ItemH *)h1;
    ItemH *hidrante2 = (ItemH *)h2;

    if(hidrante1->x != hidrante2->x)
        return hidrante1->x - hidrante2->x;
    return hidrante1->y - hidrante2->y;
}
