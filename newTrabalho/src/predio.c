#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "predio.h"
#include "quadra.h"
#include "lista.h"


typedef struct predio{
    char cep[20], face[10], numero[20];
    double x, y, frente, profundidade, calcada;
}ItemP;

Predio criarPredio(char cep[20], char face[10], char numero[20], double frente, double profundidade, double calcada)
{
    /* arrumar a questão pra impressão do geo*/
    ItemP *p;
    p = (ItemP*) calloc(1, sizeof(ItemP));
    strcpy(p->cep, cep);
    strcpy(p->face, face);
    strcpy(p->numero, numero);
    p->frente = frente;
    p->profundidade = profundidade;
    p->calcada = calcada;

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

char *retornaPNumero(Predio p)
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