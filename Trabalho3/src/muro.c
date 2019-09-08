#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "muro.h"
#include "quadra.h"


typedef struct muro{
    double x1, x2, y1, y2;
}ItemM;

Muro criarMuro(double x1, double x2, double y1, double y2)
{
    /* arrumar a questão pra impressão do geo*/
    ItemM *m;
    m = (ItemM*) calloc(1, sizeof(ItemM));
    m->x1 = x1;
    m->x2 = x2;
    m->y1 = y1;
    m->y2 = y2;

    return m;
}

double retornaMX1(Muro m)
{
    ItemM* item = (ItemM*) m;
    return item->x1;
}

double retornaMX2(Muro m)
{
    ItemM* item = (ItemM*) m;
    return item->x2;
}

double retornaMY1(Muro m)
{
    ItemM* item = (ItemM*) m;
    return item->y1;
}

double retornaMY2(Muro m)
{
    ItemM* item = (ItemM*) m;
    return item->y2;
}
