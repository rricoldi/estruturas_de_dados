#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quadra.h"


typedef struct quadra
{
    char cep[20], corP[20], corB[20];
    double x, y, w, h, espessura;
}ItemQ;

Quadra criaQuadra(char cep[20], char corB[20], char corP[20], double largura, double altura, double x, double y, double espessura)
{
    ItemQ *q;
    q = (ItemQ*) calloc(1, sizeof(ItemQ));
    strcpy(q->cep, cep);
    strcpy(q->corP, corP);
    strcpy(q->corB, corB);
    q->x = x;
    q->y = y;
    q->w = largura;
    q->h = altura;
    q->espessura = espessura;

    return q;
}

double retornaQX(Quadra q)
{
    ItemQ* item = (ItemQ*) q;
    return item->x;
}

double retornaQY(Quadra q)
{
    ItemQ* item = (ItemQ*) q;
    return item->y;
}

double retornaQW(Quadra q)
{
    ItemQ* item = (ItemQ*) q;
    return item->w;
}

double retornaQH(Quadra q)
{
    ItemQ* item = (ItemQ*) q;
    return item->h;
}

double retornaQEspessura(Quadra q)
{
    ItemQ* item = (ItemQ*) q;
    return item->espessura;
}

char *retornaQCEP(Quadra q)
{
    ItemQ* item = (ItemQ*) q;
    return item->cep;
}

char *retornaQCorB(Quadra q)
{
    ItemQ* item = (ItemQ*) q;
    return item->corB;
}

char *retornaQCorP(Quadra q)
{
    ItemQ* item = (ItemQ*) q;
    return item->corP;
}

