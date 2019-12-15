#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "predio.h"
#include "quadra.h"
#include "lista.h"
#include "geometria.h"

typedef struct predio{
    char cep[20], face[10];
    double numero;
    double frente, profundidade, calcada;
    Reta superior, esquerda, direita, inferior;
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
    p->xCalcada     = xCalcada;
    p->xCalcadaMax  = xCalcadaMax;
    p->yCalcada     = yCalcada;
    p->yCalcadaMax  = yCalcadaMax;
    p->xNum         = xNum;
    p->yNum         = yNum;
    
    // double w, h;
    // if(p->face[0] == 'N' || p->face == 'S'){
    //     h = p->profundidade;
    //     w = p->frente;
    // }else{
    //     h = p->frente;
    //     w = p->profundidade;
    // }
    p->superior = criarReta(x, y, x+p->frente, y);
    p->esquerda = criarReta(x, y, x, y+p->profundidade);
    p->direita = criarReta(x+p->frente, y, x+p->frente, y+p->profundidade);
    p->inferior = criarReta(x, y+p->profundidade, x+p->frente, y+p->profundidade);

    return p;
}
void predioFinalizar(Predio predio){
    ItemP *p = (ItemP*)predio;
    retaFinalizar(p->superior);
    retaFinalizar(p->inferior);
    retaFinalizar(p->esquerda);
    retaFinalizar(p->direita);
    free(p);
    p = NULL;
}

double retornaPX(Predio p)
{
    ItemP* item = (ItemP*) p;
    return getPontoX(getRetaA(item->superior));
}

double retornaPY(Predio p)
{
    ItemP* item = (ItemP*) p;
    return getPontoY(getRetaA(item->superior));
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

double retornaPWidth(Predio p){
    ItemP* essa = (ItemP*)p;
    if(essa->face[0] == 'N' || essa->face[0] == 'S')
        return essa->frente;
    else
        return essa->profundidade;
}
double retornaPHeight(Predio p){
    ItemP* essa = (ItemP*)p;
    if(essa->face[0] == 'N' || essa->face[0] == 'S')
        return essa->profundidade;
    else
        return essa->frente;
}
Reta* retornaPredioLados(Predio predio){
    ItemP *p = predio;
    Reta *lados = malloc(4*sizeof(Reta));
    lados[0] = p->superior;
    lados[1] = p->direita;
    lados[2] = p->inferior;
    lados[3] = p->esquerda;
    return lados;
}
double comparaPredio(Predio p1, Predio p2)
{
    ItemP *predio1 = (ItemP *)p1;
    ItemP *predio2 = (ItemP *)p2;

    if(getPontoX(getRetaA(predio1->superior)) != getPontoX(getRetaA(predio2->superior)))
        return getPontoX(getRetaA(predio1->superior)) - getPontoX(getRetaA(predio2->superior));
    return getPontoY(getRetaA(predio1->superior)) != getPontoY(getRetaA(predio2->superior));
}

//imprimirPredio(nomeDoArquivoSvg, x, y, tamanhoDaFrente, tamanhoDoLado, xCalcada, yCalcada, xCalcadaMax, yCalcadaMax, numeroDoPredio, xNum, yNum);
void imprimirPredio2(Predio pred, va_list args)
{
    va_list variaveis;
    va_copy(variaveis, args);
    char *nomeDoArquivoSvg = va_arg(variaveis, char*);
    ItemP* predio = (ItemP*) pred;
    imprimirPredio(nomeDoArquivoSvg, getPontoX(getRetaA(predio->superior)), getPontoY(getRetaA(predio->superior)), predio->frente, predio->profundidade, predio->xCalcada, predio->yCalcada, predio->xCalcadaMax, predio->yCalcadaMax, predio->numero, predio->xNum,  predio->yNum);
    // FILE* svg = fopen(nomeDoArquivoSvg, "a+");//
    // retaPrintSvg(predio->superior, svg);
    // retaPrintSvg(predio->esquerda, svg);
    // retaPrintSvg(predio->direita, svg);
    // retaPrintSvg(predio->inferior, svg);
    // fclose(svg);//
    va_end(variaveis);
}


void navegaPredio(Predio pred)
{
    ItemP* predio = (ItemP*) pred;
    printf("\ncep = %s face = %s numero = %lf frente = %lf profundidade = %lf calcada = %lf", predio->cep, predio->face, predio->numero, predio->frente, predio->profundidade, predio->calcada);
}

void imprimirPredioDaArvore(Predio *pred, FILE *arquivoSVG, int x, int y, char cor)
{   
    static int ultimoInfo = 0;
    ItemP *predio = pred;
    char corDoSvg[20];

    if(cor == 1)
        strcpy(corDoSvg,"black");      
    else if(cor == 0)
        strcpy(corDoSvg,"red");
    
    fprintf(arquivoSVG,"\n\t<circle r='%d' cx='%d' cy='%d' stroke='%s' fill='%s' stroke-width='1.0' fill-opacity='1'/>",15,x,y,corDoSvg,corDoSvg);
    fprintf(arquivoSVG,"\n\t<text x='%d' y='%d' fill=\"white\" text-anchor='middle' fill-opacity='1' font-size='4px'>cep = %s</text>",x,y-5,predio->cep);
    fprintf(arquivoSVG,"\n\t<text x='%d' y='%d' fill=\"white\" text-anchor='middle' fill-opacity='1' font-size='4px'>x = %f</text>",x,y,getPontoX(getRetaA(predio->superior)));
    fprintf(arquivoSVG,"\n\t<text x='%d' y='%d' fill=\"white\" text-anchor='middle' fill-opacity='1' font-size='4px'>y = %f</text>",x,y+5,getPontoY(getRetaA(predio->superior)));

    if(getPontoX(getRetaA(predio->superior)) < ultimoInfo)
        ultimoInfo = getPontoX(getRetaA(predio->superior));
}