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
    m->r = criarReta(criarPonto(x1, y1), criarPonto(x2, y2));

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
