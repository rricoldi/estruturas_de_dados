#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "muro.h"
#include "quadra.h"
#include "geometria.h"

typedef struct muro{
    Reta r;
}ItemM;

Muro criarMuro(double x1, double x2, double y1, double y2)
{
    /* arrumar a questão pra impressão do geo*/
    ItemM *m = calloc(1, sizeof(ItemM));
    m->r = criarReta(x1, y1, x2, y2);

    return m;
}
void* muroFinalizar(Muro muro){
    ItemM *m = (ItemM*)muro;
    retaFinalizar(m->r);
    free(m);
    m = NULL;
    return m;
}

double retornaMX1(Muro m)
{
    ItemM* item = (ItemM*) m;
    return getPontoX(getRetaA(item->r));
}

double retornaMX2(Muro m)
{
    ItemM* item = (ItemM*) m;
    return getPontoX(getRetaB(item->r));
}

double retornaMY1(Muro m)
{
    ItemM* item = (ItemM*) m;
    return getPontoY(getRetaA(item->r));
}

double retornaMY2(Muro m)
{
    ItemM* item = (ItemM*) m;
    return getPontoY(getRetaB(item->r));
}

double comparaMuro(Muro m1, Muro m2)
{
    ItemM* muro1 = (ItemM*) m1;
    ItemM* muro2 = (ItemM*) m2;

    if(getPontoX(getRetaA(muro1->r)) != getPontoX(getRetaA(muro2->r)))
        return getPontoX(getRetaA(muro1->r)) - getPontoX(getRetaA(muro2->r));
    return getPontoY(getRetaA(muro1->r)) != getPontoY(getRetaA(muro2->r));
}
