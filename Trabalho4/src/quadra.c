#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quadra.h"
#include "svg.h"


typedef struct quadra
{
    char cep[20], corP[20], corB[20];
    double x, y, w, h, espessura;
}ItemQ;

Quadra criarQuadra(char cep[20], char corB[20], char corP[20], double largura, double altura, double x, double y, double espessura)
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
void quadraFinalizar(Quadra quadra){
    ItemQ *q = (ItemQ*)quadra;
    free(q);
    q = NULL;
}

double retornaQX(Quadra q)
{
    ItemQ* item = (ItemQ*) q;
    return item->x;
}

void setQX(Quadra q, double x)
{
    ItemQ* q2 = (ItemQ*) q;
    q2->x = x;
}

double retornaQY(Quadra q)
{
    ItemQ* item = (ItemQ*) q;
    return item->y;
}

void setQY(Quadra q, double y)
{
    ItemQ* q2 = (ItemQ*) q;
    q2->y = y;
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
void setQEspessura(Quadra q, double espessura){
    ItemQ *quad = q;
    quad->espessura = espessura;
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


void setQCorB(Quadra q, char cor[])
{
    ItemQ* q2 = (ItemQ*) q;
    sprintf(q2->corB, cor);
}


char *retornaQCorP(Quadra q)
{
    ItemQ* item = (ItemQ*) q;
    return item->corP;
}
void setQCorP(Quadra quad, char cor[]){
    ItemQ *q = quad;
    strcpy(q->corP, cor);
}

double comparaQuadra(Quadra q1, Quadra q2)
{
    ItemQ *quadra1 = (ItemQ *)q1;
    ItemQ *quadra2 = (ItemQ *)q2;

    if(quadra1->x != quadra2->x)
        return quadra1->x - quadra2->x;
    return quadra1->y - quadra2->y;
}

void imprimirQuadra(Quadra quad, va_list args)
{
    va_list variaveis;
    va_copy(variaveis, args);
    char *nomeDoArquivoSvg = va_arg(variaveis, char*);
    ItemQ* quadra = (ItemQ*) quad;
    imprimirRetangulo(quadra->w, quadra->h, quadra->x, quadra->y, quadra->corB, quadra->corP, nomeDoArquivoSvg, quadra->espessura);
}


void navegaQuadra(Quadra quad)
{
    ItemQ* quadra = (ItemQ*) quad;
    printf("\ncep = %s cor da borda = %s cor do preenchimento = %s x = %lf y = %lf largura = %lf altura = %lf espessura = %lf", quadra->cep, quadra->corB, quadra->corP, quadra->x, quadra->y, quadra->w, quadra->h, quadra->espessura);
}

void imprimirQuadraDaArvore(Quadra *quarter, FILE *arquivoSVG, int x, int y, char cor)
{   
    static int ultimoInfo = 0;
    ItemQ *quadra1 = quarter;
    char corDoSvg[20];

    if(cor == 1)
        strcpy(corDoSvg,"black");      
    else if(cor == 0)
        strcpy(corDoSvg,"red");
    
    fprintf(arquivoSVG,"\n\t<circle r='%d' cx='%d' cy='%d' stroke='%s' fill='%s' stroke-width='1.0' fill-opacity='1'/>",15,x,y,corDoSvg,corDoSvg);
    fprintf(arquivoSVG,"\n\t<text x='%d' y='%d' fill=\"white\" text-anchor='middle' fill-opacity='1' font-size='4px'>cep = %s</text>",x,y-5,quadra1->cep);
    fprintf(arquivoSVG,"\n\t<text x='%d' y='%d' fill=\"white\" text-anchor='middle' fill-opacity='1' font-size='4px'>x = %f</text>",x,y,quadra1->x);
    fprintf(arquivoSVG,"\n\t<text x='%d' y='%d' fill=\"white\" text-anchor='middle' fill-opacity='1' font-size='4px'>y = %f</text>",x,y+5,quadra1->y);

    if(quadra1->x < ultimoInfo)
        ultimoInfo = quadra1->x;
}