#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "predio.h"
#include "quadra.h"
#include "lista.h"


typedef struct predio{
    char cep[20], face[10];
    double numero;
    double x, y, frente, profundidade, calcada;
    double xCalcada, yCalcada, xCalcadaMax, yCalcadaMax;
	double xNum, yNum;
}ItemP;

Predio criarPredio(char cep[20], char face[10], double numero, double frente, double profundidade, double calcada, double x, double y, double xCalcada, double xCalcadaMax, double yCalcada, double yCalcadaMax, double xNum, double yNum)
{
    /* arrumar a questão pra impressão do geo*/
    ItemP *p;
    p = (ItemP*) calloc(1, sizeof(ItemP));
    strcpy(p->cep, cep);
    strcpy(p->face, face);
    p->numero       = numero;
    p->frente       = frente;
    p->profundidade = profundidade;
    p->calcada      = calcada;
    p->x            = x;
    p->y            = y;
    p->xCalcada     = xCalcada;
    p->xCalcadaMax  = xCalcadaMax;
    p->yCalcada     = yCalcada;
    p->yCalcadaMax  = yCalcadaMax;
    p->xNum         = xNum;
    p->yNum         = yNum;
    

    return p;
}

double retornaPX(Predio p)
{
    ItemP* item = (ItemP*) p;
    return item->x;
}

double retornaPY(Predio p)
{
    ItemP* item = (ItemP*) p;
    return item->y;
}

char *retornaPCep(Predio p)
{
    ItemP* item = (ItemP*) p;
    return item->cep;
}

char *retornaPFace(Predio p)
{
    ItemP* item = (ItemP*) p;
    return item->face;
}

double retornaPNumero(Predio p)
{
    ItemP* item = (ItemP*) p;
    return item->numero;
}

double retornaPFrente(Predio p)
{
    ItemP* item = (ItemP*) p;
    return item->frente;
}

double retornaPProfundidade(Predio p)
{
    ItemP* item = (ItemP*) p;
    return item->profundidade;
}

double retornaPCalcada(Predio p)
{
    ItemP* item = (ItemP*) p;
    return item->calcada;
}

double retornaPXCalcada(Predio p)
{
    ItemP* item = (ItemP*) p;
    return item->xCalcada;
}

double retornaPYCalcada(Predio p)
{
    ItemP* item = (ItemP*) p;
    return item->yCalcada;
}

double retornaPXCalcadaMax(Predio p)
{
    ItemP* item = (ItemP*) p;
    return item->xCalcadaMax;
}

double retornaPYCalcadaMax(Predio p)
{
    ItemP* item = (ItemP*) p;
    return item->yCalcadaMax;
}

double retornaPXNum(Predio p)
{
    ItemP* item = (ItemP*) p;
    return item->xNum;
}

double retornaPYNum(Predio p)
{
    ItemP* item = (ItemP*) p;
    return item->yNum;
}