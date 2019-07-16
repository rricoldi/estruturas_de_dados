#include <stdlib.h>
#include <stdio.h>
#include "cidade.h"

typedef struct city
{
    Lista listaCirculo;
    Lista listaRetangulo;
    Lista listaQuadra;
    Lista listaHidrante;
    Lista listaRadio;
    Lista listaSemaforo;
} cidade;

Cidade criaCidade(int numeroDeFiguras, int numeroDeQuadras, int numeroDeHidrantes, int numeroDeRadios, int numeroDeSemaforos)
{
    Cidade cid    = calloc(1, sizeof(cidade));
    cidade *city  = (cidade *)  cid;
    city->listaCirculo   = iniciaLista(numeroDeFiguras);
    city->listaRetangulo = iniciaLista(numeroDeFiguras);
    city->listaQuadra    = iniciaLista(numeroDeQuadras);
    city->listaHidrante  = iniciaLista(numeroDeHidrantes);
    city->listaRadio     = iniciaLista(numeroDeRadios);
    city->listaSemaforo  = iniciaLista(numeroDeSemaforos);

    return city;
}

void removeCidade(Cidade cid)
{
    cidade *city = (cidade *)cid;

    finalizaLista(city->listaCirculo);
    finalizaLista(city->listaRetangulo);
    finalizaLista(city->listaQuadra);
    finalizaLista(city->listaHidrante);
    finalizaLista(city->listaRadio);
    finalizaLista(city->listaSemaforo);

    free(city);
}

void printaCirculoseRetangulos(Cidade cid, char svg[])
{
    cidade *city = (cidade *)cid;

    printaCirculos(city->listaCirculo, svg);
    printaRetangulos(city->listaRetangulo, svg);
}

void printaCidade(Cidade cid, char svg[])
{
    cidade *city = (cidade *)cid;
    
    printaQuadras(city->listaQuadra, svg);
    printaHidrantes(city->listaHidrante, svg);
    printaSemaforos(city->listaSemaforo, svg);
    printaRadios(city->listaRadio, svg);
}

void boudingBoxCirculos(Cidade cid, char arquivo[])
{
    cidade *city = (cidade *)cid;

    bbcLista(city->listaCirculo, arquivo);
}

void boundingBoxRetangulos(Cidade cid, char arquivo[], char cor[])
{
    cidade *city = (cidade *)cid;

    bbrLista(city->listaRetangulo, arquivo, cor);
}

Info procuraCidade(Cidade cid, char id[], int *tipo)
{
    cidade *city = (cidade *)cid;
    int posicao;

    posicao = procuraListaC(city->listaCirculo, id);
    if (posicao != -1)
    {
        *tipo = 1;
        return get(city->listaCirculo, posicao);
    }

    posicao = procuraListaRe(city->listaRetangulo, id);
    if (posicao != -1)
    {
        *tipo = 2;
        return get(city->listaRetangulo, posicao);
    }

    posicao = procuraListaQ(city->listaQuadra, id);
    if (posicao != -1)
    {
        *tipo = 3;
        return get(city->listaQuadra, posicao);
    }

    posicao = procuraListaH(city->listaHidrante, id);
    if (posicao != -1)
    {
        *tipo = 4;
        return get(city->listaHidrante, posicao);
    }

    posicao = procuraListaS(city->listaSemaforo, id);
    if (posicao != -1)
    {
        *tipo = 5;
        return get(city->listaSemaforo, posicao);
    }

    posicao = procuraListaR(city->listaRadio, id);
    if (posicao != -1)
    {
        *tipo = 6;
        return get(city->listaRadio, posicao);
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

    posicao = procuraListaQ(city->listaQuadra, id);
    if (posicao != -1)
    {
        fprintf(arqTxt, "del %s\nquadra -> x: %lf y: %lf w: %lf h: %lf\n", id, retornaQX(getQuadra(city, posicao)), retornaQY(getQuadra(city, posicao)), retornaQW(getQuadra(city, posicao)), retornaQH(getQuadra(city, posicao)));
        removeLista(city->listaQuadra, posicao);
        fclose(arqTxt);
        return;
    }

    posicao = procuraListaH(city->listaHidrante, id);
    if (posicao != -1)
    {
        fprintf(arqTxt, "del %s\nhidrante -> x: %lf y: %lf\n", id, retornaHX(getHidrante(city, posicao)), retornaHY(getHidrante(city, posicao)));
        removeLista(city->listaHidrante, posicao);
        fclose(arqTxt);
        return;
    }

    posicao = procuraListaS(city->listaSemaforo, id);
    if (posicao != -1)
    {
        fprintf(arqTxt, "del %s\nsemaforo -> x: %lf y: %lf\n", id, retornaSX(getSemaforo(city, posicao)), retornaSY(getSemaforo(city, posicao)));
        removeLista(city->listaHidrante, posicao);
        fclose(arqTxt);
        return;
    }

    posicao = procuraListaR(city->listaRadio, id);
    if (posicao != -1)
    {
        fprintf(arqTxt, "del %s\nradio base -> x: %lf y: %lf\n", id, retornaRX(getRadio(city, posicao)), retornaRY(getRadio(city, posicao)));
        removeLista(city->listaHidrante, posicao);
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
        percorreListaQ(city->listaQuadra, r, fx, fy, tipo, svg, txt, id, option, cor, largura, altura, dx, dy);
    else
    {
        percorreListaQ(city->listaQuadra, r, fx, fy, tipo, svg, txt, id, option, cor, largura, altura, dx, dy);
        percorreListaH(city->listaHidrante, fx, fy, largura, altura, dx, dy, txt);
        percorreListaS(city->listaSemaforo, fx, fy, largura, altura, dx, dy, txt);
        percorreListaR(city->listaRadio, fx, fy, largura, altura, dx, dy, txt);
    }
}

int addCirculo(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    return insereLista(city->listaCirculo, info);
}

Circulo getCirculo(Cidade cid, int i)
{
    cidade *city = (cidade *)cid;
    return get(city->listaCirculo, i);
}

int addRetangulo(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    return insereLista(city->listaRetangulo, info);
}

Retangulo getRetangulo(Cidade cid, int i)
{
    cidade *city = (cidade *)cid;
    return get(city->listaRetangulo, i);
}

int addQuadra(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    return insereLista(city->listaQuadra, info);
}

Quadra getQuadra(Cidade cid, int i)
{
    cidade *city = (cidade *)cid;
    return get(city->listaQuadra, i);
}

int addHidrante(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    return insereLista(city->listaHidrante, info);
}

Hidrante getHidrante(Cidade cid, int i)
{
    cidade *city = (cidade *)cid;
    return get(city->listaHidrante, i);
}

int addRadio(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    return insereLista(city->listaRadio, info);
}

Radio getRadio(Cidade cid, int i)
{
    cidade *city = (cidade *)cid;
    return get(city->listaRadio, i);
}

int addSemaforo(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    return insereLista(city->listaSemaforo, info);
}

Semaforo getSemaforo(Cidade cid, int i)
{
    cidade *city = (cidade *)cid;
    return get(city->listaSemaforo, i);
}
