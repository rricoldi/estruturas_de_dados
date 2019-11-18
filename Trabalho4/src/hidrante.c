#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hidrante.h"
#include "svg.h"


typedef struct hidrante
{
    char id[20], corP[20], corB[20];
    double x, y, espessura;
} ItemH;

Hidrante criarHidrante(char id[20], char corB[20], char corP[20], double espessura, double x, double y)
{
    ItemH *h;

    h = (ItemH *)calloc(1, sizeof(ItemH));

    strcpy(h->id, id);
    strcpy(h->corB, corB);
    strcpy(h->corP, corP);

    h->x = x;
    h->y = y;
    h->espessura = espessura;

    return h;
}

void hidranteFinalizar(Hidrante hidrante){
    ItemH *hid = (ItemH*) hidrante;
    free(hid);
    hid = NULL;
}

double retornaHX(Hidrante h)
{
    ItemH *h2 = (ItemH *)h;
    return h2->x;
}

void setHX(Hidrante h, double x)
{
    ItemH *h2 = (ItemH *)h;
    h2->x = x;
}

double retornaHY(Hidrante h)
{
    ItemH *h2 = (ItemH *)h;
    return h2->y;
}

void setHY(Hidrante h, double y)
{
    ItemH *h2 = (ItemH *)h;
    h2->y = y;
}

double retornaHEspessura(Hidrante h)
{
    ItemH *item = (ItemH *)h;
    return item->espessura;
}

char *retornaHID(Hidrante h)
{
    ItemH *h2 = (ItemH *)h;
    return h2->id;
}

char *retornaHCorB(Hidrante h)

{
    ItemH *item = (ItemH *)h;
    return item->corB;
}

char *retornaHCorP(Hidrante h)

{
    ItemH *item = (ItemH *)h;
    return item->corP;
}

double comparaHidrante(Hidrante h1, Hidrante h2)
{
    ItemH *hidrante1 = (ItemH *)h1;
    ItemH *hidrante2 = (ItemH *)h2;

    if(hidrante1->x != hidrante2->x)
        return hidrante1->x - hidrante2->x;
    return hidrante1->y - hidrante2->y;
}

void imprimirHidrante(Hidrante hid, va_list args)
{
    va_list variaveis;
    va_copy(variaveis, args);
    char *nomeDoArquivoSvg = va_arg(variaveis, char*);
    ItemH* hidrante = (ItemH*) hid;
    imprimirCirculo(2, hidrante->x, hidrante->y, hidrante->corB, hidrante->corP, nomeDoArquivoSvg, hidrante->espessura);

}


void navegaHidrante(Hidrante hid)
{
    ItemH* hidrante = (ItemH*) hid;
    printf("\nid = %s cor da borda = %s cor do preenchimento = %s x = %lf y = %lf espessura = %lf", hidrante->id, hidrante->corB, hidrante->corP, hidrante->x, hidrante->y, hidrante->espessura);
}

void imprimirHidranteDaArvore(Hidrante *hid, FILE *arquivoSVG, int x, int y, char cor)
{   
    static int ultimoInfo = 0;
    ItemH *hidrante = hid;
    char corDoSvg[20];

    if(cor == 1)
        strcpy(corDoSvg,"black");      
    else if(cor == 0)
        strcpy(corDoSvg,"red");
    
    fprintf(arquivoSVG,"\n\t<circle r='%d' cx='%d' cy='%d' stroke='%s' fill='%s' stroke-width='1.0' fill-opacity='1'/>",15,x,y,corDoSvg,corDoSvg);
    fprintf(arquivoSVG,"\n\t<text x='%d' y='%d' fill=\"white\" text-anchor='middle' fill-opacity='1' font-size='4px'>cep = %s</text>",x,y-5,hidrante->id);
    fprintf(arquivoSVG,"\n\t<text x='%d' y='%d' fill=\"white\" text-anchor='middle' fill-opacity='1' font-size='4px'>x = %f</text>",x,y,hidrante->x);
    fprintf(arquivoSVG,"\n\t<text x='%d' y='%d' fill=\"white\" text-anchor='middle' fill-opacity='1' font-size='4px'>y = %f</text>",x,y+5,hidrante->y);

    if(hidrante->x < ultimoInfo)
        ultimoInfo = hidrante->x;
}