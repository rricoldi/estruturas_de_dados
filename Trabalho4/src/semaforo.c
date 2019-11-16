#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semaforo.h"



typedef struct radio{
    char id[20], corP[20], corB[20];
    double x, y, espessura;
}ItemS;

Semaforo criarSemaforo(char id[20], char corB[20], char corP[20], double x, double y, double espessura)
{
    ItemS *s;
    s = (ItemS*) calloc(1, sizeof(ItemS));
    strcpy(s->id, id);
    strcpy(s->corP, corP);
    strcpy(s->corB, corB);
    s->x = x;
    s->y = y;
    s->espessura = espessura;
    
    return s;
}
void* semaforoFinalizar(Semaforo semaf){
    ItemS* s = (ItemS*)semaf;
    free(s);
    s = NULL;
    return s;
}

double retornaSX(Semaforo s)
{
    ItemS* item = (ItemS*) s;
    return item->x;
}

void setSX(Semaforo s, double x)
{
    ItemS* item = (ItemS*) s;
    item->x = x;
}

double retornaSY(Semaforo s)
{
    ItemS* item = (ItemS*) s;
    return item->y;
}

void setSY(Semaforo s, double y)
{
    ItemS* item = (ItemS*) s;
    item->y = y;
}

double retornaSEspessura(Semaforo s)
{
    ItemS* item = (ItemS*) s;
    return item->espessura;
}

char *retornaSID(Semaforo s)
{
    ItemS* item = (ItemS*) s;
    return item->id;
}

char *retornaSCorB(Semaforo s)
{
    ItemS* item = (ItemS*) s;
    return item->corB;
}

char *retornaSCorP(Semaforo s)
{
    ItemS* item = (ItemS*) s;
    return item->corP;
}

double comparaSemaforo(Semaforo s1, Semaforo s2)
{
    ItemS *semaforo1 = (ItemS *)s1;
    ItemS *semaforo2 = (ItemS *)s2;

    if(semaforo1->x != semaforo2->x)
        return semaforo1->x - semaforo2->x;
    return semaforo1->y - semaforo2->y;
}

void imprimirSemaforoDaArvore(Semaforo *sem, FILE *arquivoSVG, int x, int y, char cor, int tam)
{   
    static int ultimoInfo = 0;
    ItemS *semaforo = sem;
    char corDoSvg[20];

    if(cor == 1)
        strcpy(corDoSvg,"black");      
    else if(cor == 0)
        strcpy(corDoSvg,"red");
    
    fprintf(arquivoSVG,"\n\t<circle r='%d' cx='%d' cy='%d' stroke='%s' fill='%s' stroke-width='1.0' fill-opacity='1'/>",15,x,y,corDoSvg,corDoSvg);
    fprintf(arquivoSVG,"\n\t<text x='%d' y='%d' fill=\"white\" text-anchor='middle' fill-opacity='1' font-size='4px'>cep = %s</text>",x,y-5,semaforo->id);
    fprintf(arquivoSVG,"\n\t<text x='%d' y='%d' fill=\"white\" text-anchor='middle' fill-opacity='1' font-size='4px'>x = %f</text>",x,y,semaforo->x);
    fprintf(arquivoSVG,"\n\t<text x='%d' y='%d' fill=\"white\" text-anchor='middle' fill-opacity='1' font-size='4px'>y = %f</text>",x,y+5,semaforo->y);

    if(semaforo->x < ultimoInfo)
        ultimoInfo = semaforo->x;
}