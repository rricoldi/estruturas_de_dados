#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "retangulo.h"


typedef struct retangulo
{
    char id[20], corP[20], corB[20];
    double x, y, w, h, espessura;
}ItemRe;

Retangulo criarRetangulo(char id[20], char corB[20], char corP[20], double largura, double altura, double x, double y, double espessura)
{
    ItemRe *re;
    re = (ItemRe*) calloc(1, sizeof(ItemRe));
    strcpy(re->id, id);
    strcpy(re->corP, corP);
    strcpy(re->corB, corB);
    re->w = largura;
    re->h = altura;
    re->x = x;
    re->y = y;
    re->espessura = espessura;

    return re;
}

double retornaReX(Retangulo re)
{
    ItemRe* item = (ItemRe*) re;
    return item->x;
}

double retornaReY(Retangulo re)
{
    ItemRe* item = (ItemRe*) re;
    return item->y;
}

double retornaReW(Retangulo re)
{
    ItemRe* item = (ItemRe*) re;
    return item->w;
}

double retornaReH(Retangulo re)
{
    ItemRe* item = (ItemRe*) re;
    return item->h;
}

double retornaReEspessura(Retangulo re)
{
    ItemRe* item = (ItemRe*) re;
    return item->espessura;
}

char *retornaReID(Retangulo re)
{
    ItemRe* item = (ItemRe*) re;
    return item->id;
}

char *retornaReCorB(Retangulo re)
{
    ItemRe* item = (ItemRe*) re;
    return item->corB;
}

char *retornaReCorP(Retangulo re)
{
    ItemRe* item = (ItemRe*) re;
    return item->corP;
}

