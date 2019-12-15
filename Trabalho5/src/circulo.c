#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circulo.h"
#include "svg.h"
typedef struct circulo
{
    char id[20], corPreenchimento[20], corBorda[20];
    double x, y, r, espessura;
} ItemCirculo;

void circuloFinalizar(Circulo circulo){
    ItemCirculo *cir = (ItemCirculo*)circulo;
    free(cir);
    cir = NULL;
}

Circulo criarCirculo(char id[20], char corBorda[20], char corPreenchimento[20], double raio, double x, double y, double espessura)
{
    ItemCirculo *c;
    c = (ItemCirculo *)calloc(1, sizeof(ItemCirculo));

    strcpy(c->id, id);
    strcpy(c->corPreenchimento, corPreenchimento);
    strcpy(c->corBorda, corBorda);
    
    c->x         = x;
    c->y         = y;
    c->r         = raio;
    c->espessura = espessura;

    return c;
}


double retornaCX(Circulo c)
{
    ItemCirculo *item = (ItemCirculo *)c;
    return item->x;
}

double retornaCY(Circulo c)
{
    ItemCirculo *item = (ItemCirculo *)c;
    return item->y;
}

double retornaCR(Circulo c)
{
    ItemCirculo *item = (ItemCirculo *)c;
    return item->r;
}

double retornaCEspessura(Circulo c)
{
    ItemCirculo *item = (ItemCirculo *)c;
    return item->espessura;
}

char *retornaCID(Circulo c)
{
    ItemCirculo *item = (ItemCirculo *)c;
    return item->id;
}

char *retornaCCorB(Circulo c)
{
    ItemCirculo *item = (ItemCirculo *)c;
    return item->corBorda;
}

char *retornaCCorP(Circulo c)
{
    ItemCirculo *item = (ItemCirculo *)c;
    return item->corPreenchimento;
}

double comparaCirculo(Circulo c1, Circulo c2)
{
    ItemCirculo *circulo1 = (ItemCirculo *)c1;
    ItemCirculo *circulo2 = (ItemCirculo *)c2;

    if(circulo1->x != circulo2->x)
        return circulo1->x - circulo2->x;
    return circulo1->y - circulo2->y;
}

void imprime(Circulo c)
{
    ItemCirculo *item = (ItemCirculo *)c;
    printf("\nx = %lf y = %lf r = %lf", item->x, item->y, item->r);
}

void imprimeCirculos(Circulo circulo, char nomeDoArquivoSvg[], char cor[])
{
    ItemCirculo *item = (ItemCirculo *)circulo;
    imprimirCirculo(item->r, item->x, item->y, item->corBorda, item->corPreenchimento, nomeDoArquivoSvg, item->espessura);
}