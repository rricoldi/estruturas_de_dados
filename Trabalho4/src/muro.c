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
void muroFinalizar(Muro muro){
    ItemM *m = (ItemM*)muro;
    retaFinalizar(m->r);
    free(m);
    m = NULL;
}

Reta muroGetReta(Muro mur){
    ItemM *m = (ItemM*)mur;
    return m->r;
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

void imprimirMuro(Muro mur, va_list args)
{
    va_list variaveis;
    va_copy(variaveis, args);
    char *nomeDoArquivoSvg = va_arg(variaveis, char*);
    ItemM* muro = (ItemM*) mur;
    imprimirLinha(retornaMX1(muro), retornaMY1(muro), retornaMX2(muro), retornaMY2(muro), nomeDoArquivoSvg);
}


void navegaMuro(Muro mur)
{
    printf("\nx1 = %lf x2 = %lf y1 = %lf y2 = %lf", retornaMX1(mur), retornaMX2(mur), retornaMY1(mur), retornaMY2(mur));
}


void imprimirMuroDaArvore(Muro *mur, FILE *arquivoSVG, int x, int y, char cor)
{   
    static int ultimoInfo = 0;
    ItemM *muro = mur;
    char corDoSvg[20];

    if(cor == 1)
        strcpy(corDoSvg,"black");      
    else if(cor == 0)
        strcpy(corDoSvg,"red");
    
    fprintf(arquivoSVG,"\n\t<circle r='%d' cx='%d' cy='%d' stroke='%s' fill='%s' stroke-width='1.0' fill-opacity='1'/>",15,x,y,corDoSvg,corDoSvg);
    fprintf(arquivoSVG,"\n\t<text x='%d' y='%d' fill=\"white\" text-anchor='middle' fill-opacity='1' font-size='4px'>x = %f</text>",x,y,getPontoX(getRetaA(muro->r)));
    fprintf(arquivoSVG,"\n\t<text x='%d' y='%d' fill=\"white\" text-anchor='middle' fill-opacity='1' font-size='4px'>y = %f</text>",x,y+5,getPontoY(getRetaA(muro->r)));

    if(getPontoX(getRetaA(muro->r)) < ultimoInfo)
        ultimoInfo = getPontoX(getRetaA(muro->r));
}
