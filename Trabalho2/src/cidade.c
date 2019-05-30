#include <stdlib.h>
#include <stdio.h>
#include "cidade.h"

typedef struct city
{
    Lista listaC;
    Lista listaRe;
    Lista listaQ;
    Lista listaH;
    Lista listaR;
    Lista listaS;
} cidade;

Cidade criaCidade(int nx, int nq, int nh, int nr, int ns)
{
    Cidade c = calloc(1, sizeof(cidade));
    cidade *city = (cidade *)c;
    city->listaC = iniciaLista(nx);
    city->listaRe = iniciaLista(nx);
    city->listaQ = iniciaLista(nq);
    city->listaH = iniciaLista(nh);
    city->listaR = iniciaLista(nr);
    city->listaS = iniciaLista(ns);

    return city;
}

void removeCidade(Cidade cid)
{
    cidade *city = (cidade *)cid;

    finalizaLista(city->listaC);
    finalizaLista(city->listaRe);
    finalizaLista(city->listaQ);
    finalizaLista(city->listaH);
    finalizaLista(city->listaR);
    finalizaLista(city->listaS);

    free(city);
}

void printaCeR(Cidade cid, char svg[])
{
    cidade *city = (cidade *)cid;
    printaCirculos(city->listaC, svg);
    printaRetangulos(city->listaRe, svg);
}

void printaCidade(Cidade cid, char svg[])
{
    cidade *city = (cidade *)cid;
    
    printaQuadras(city->listaQ, svg);
    printaHidrantes(city->listaH, svg);
    printaSemaforos(city->listaS, svg);
    printaRadios(city->listaR, svg);
}

void boudingBoxCirculos(Cidade cid, char arquivo[])
{
    cidade *city = (cidade *)cid;
    bbcLista(city->listaC, arquivo);
}

void boundingBoxRetangulos(Cidade cid, char arquivo[], char cor[])
{
    cidade *city = (cidade *)cid;
    bbrLista(city->listaRe, arquivo, cor);
}

Info procuraCidade(Cidade cid, char id[], int *tipo)
{
    cidade *city = (cidade *)cid;
    int posicao;

    posicao = procuraListaC(city->listaC, id);
    if (posicao != -1)
    {
        *tipo = 1;
        return get(city->listaC, posicao);
    }

    posicao = procuraListaRe(city->listaRe, id);
    if (posicao != -1)
    {
        *tipo = 2;
        return get(city->listaRe, posicao);
    }

    posicao = procuraListaQ(city->listaQ, id);
    if (posicao != -1)
    {
        *tipo = 3;
        return get(city->listaQ, posicao);
    }

    posicao = procuraListaH(city->listaH, id);
    if (posicao != -1)
    {
        *tipo = 4;
        return get(city->listaH, posicao);
    }

    posicao = procuraListaS(city->listaS, id);
    if (posicao != -1)
    {
        *tipo = 5;
        return get(city->listaS, posicao);
    }

    posicao = procuraListaR(city->listaR, id);
    if (posicao != -1)
    {
        *tipo = 6;
        return get(city->listaR, posicao);
    }

    printf("Nao foi possivel achar o elemento na cidade\n");
    return NULL;
}

void removeDaCidade(Cidade cid, char id[], char txt[])
{
    FILE *arqTxt;
    arqTxt = fopen(txt, "a");

    cidade *city = (cidade *)cid;
    int posicao;

    posicao = procuraListaQ(city->listaQ, id);
    if (posicao != -1)
    {
        fprintf(arqTxt, "del %s\nquadra -> x: %lf y: %lf w: %lf h: %lf\n", id, retornaQX(getQuadra(city, posicao)), retornaQY(getQuadra(city, posicao)), retornaQW(getQuadra(city, posicao)), retornaQH(getQuadra(city, posicao)));
        removeLista(city->listaQ, posicao);
        fclose(arqTxt);
        return;
    }

    posicao = procuraListaH(city->listaH, id);
    if (posicao != -1)
    {
        fprintf(arqTxt, "del %s\nhidrante -> x: %lf y: %lf\n", id, retornaHX(getHidrante(city, posicao)), retornaHY(getHidrante(city, posicao)));
        removeLista(city->listaH, posicao);
        fclose(arqTxt);
        return;
    }

    posicao = procuraListaS(city->listaS, id);
    if (posicao != -1)
    {
        fprintf(arqTxt, "del %s\nsemaforo -> x: %lf y: %lf\n", id, retornaSX(getSemaforo(city, posicao)), retornaSY(getSemaforo(city, posicao)));
        removeLista(city->listaH, posicao);
        fclose(arqTxt);
        return;
    }

    posicao = procuraListaR(city->listaR, id);
    if (posicao != -1)
    {
        fprintf(arqTxt, "del %s\nradio base -> x: %lf y: %lf\n", id, retornaRX(getRadio(city, posicao)), retornaRY(getRadio(city, posicao)));
        removeLista(city->listaH, posicao);
        fclose(arqTxt);
        return;
    }

    printf("Nao foi possivel achar o elemento na cidade\n");
    fclose(arqTxt);
    return;
}

void percorreCidadeLQ(Cidade cid, double r, double fx, double fy, char tipo[], char svg[], char txt[], char id[], int option, char cor[], double largura, double altura, double dx, double dy)
{
    cidade *city = (cidade *)cid;
    if (option == 1 || option == 2)
        percorreListaQ(city->listaQ, r, fx, fy, tipo, svg, txt, id, option, cor, largura, altura, dx, dy);
    else
    {
        percorreListaQ(city->listaQ, r, fx, fy, tipo, svg, txt, id, option, cor, largura, altura, dx, dy);
        percorreListaH(city->listaH, fx, fy, largura, altura, dx, dy, txt);
        percorreListaS(city->listaS, fx, fy, largura, altura, dx, dy, txt);
        percorreListaR(city->listaR, fx, fy, largura, altura, dx, dy, txt);
    }
}

int addCirculo(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    return insereLista(city->listaC, info);
}

Circulo getCirculo(Cidade cid, int i)
{
    cidade *city = (cidade *)cid;
    return get(city->listaC, i);
}

int addRetangulo(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    return insereLista(city->listaRe, info);
}

Retangulo getRetangulo(Cidade cid, int i)
{
    cidade *city = (cidade *)cid;
    return get(city->listaRe, i);
}

int addQuadra(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    return insereLista(city->listaQ, info);
}

Quadra getQuadra(Cidade cid, int i)
{
    cidade *city = (cidade *)cid;
    return get(city->listaQ, i);
}

int addHidrante(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    return insereLista(city->listaH, info);
}

Hidrante getHidrante(Cidade cid, int i)
{
    cidade *city = (cidade *)cid;
    return get(city->listaH, i);
}

int addRadio(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    return insereLista(city->listaR, info);
}

Radio getRadio(Cidade cid, int i)
{
    cidade *city = (cidade *)cid;
    return get(city->listaR, i);
}

int addSemaforo(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    return insereLista(city->listaS, info);
}

Semaforo getSemaforo(Cidade cid, int i)
{
    cidade *city = (cidade *)cid;
    return get(city->listaS, i);
}
