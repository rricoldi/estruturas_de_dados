#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "radio.h"


typedef struct radio{
    char id[20], corP[20], corB[20];
    double x, y, espessura;
}ItemR;

Radio criarRadioBase(char id[20], char corB[20], char corP[20], double x, double y, double espessura)
{
    ItemR *r;
    r = (ItemR*) calloc(1, sizeof(ItemR));
    strcpy(r->id, id);
    strcpy(r->corP, corP);
    strcpy(r->corB, corB);
    r->x = x;
    r->y = y;
    r->espessura = espessura;


    return r;
}

double retornaRX(Radio r)
{
    ItemR* item = (ItemR*) r;
    return item->x;
}

void setRX(Radio r, double x)
{
    ItemR* item = (ItemR*) r;
    item->x = x;
}

double retornaRY(Radio r)
{
    ItemR* item = (ItemR*) r;
    return item->y;
}

void setRY(Radio r, double y)
{
    ItemR* item = (ItemR*) r;
    item->y = y;
}

double retornaREspessura(Radio r)
{
    ItemR* item = (ItemR*) r;
    return item->espessura;
}

char *retornaRID(Radio r)
{
    ItemR* item = (ItemR*) r;
    return item->id;
}

char *retornaRCorB(Radio r)
{
    ItemR* item = (ItemR*) r;
    return item->corB;
}

char *retornaRCorP(Radio r)
{
    ItemR* item = (ItemR*) r;
    return item->corP;
}
