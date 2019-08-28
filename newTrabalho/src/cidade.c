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
    Lista listaPredio;
    Lista listaMuro;
} cidade;


Cidade criarCidade(int numeroDeFiguras, int numeroDeQuadras, int numeroDeHidrantes, int numeroDeRadios, int numeroDeSemaforos, int numeroDePredios, int numeroDeMuros)
{
    Cidade cid    = calloc(1, sizeof(cidade));
    cidade *city  = (cidade *)  cid;
    city->listaCirculo   = iniciaLista(numeroDeFiguras);
    city->listaRetangulo = iniciaLista(numeroDeFiguras);
    city->listaQuadra    = iniciaLista(numeroDeQuadras);
    city->listaHidrante  = iniciaLista(numeroDeHidrantes);
    city->listaRadio     = iniciaLista(numeroDeRadios);
    city->listaSemaforo  = iniciaLista(numeroDeSemaforos);
    city->listaPredio    = iniciaLista(numeroDePredios);
    city->listaMuro      = iniciaLista(numeroDeMuros);

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
    finalizaLista(city->listaPredio);
    finalizaLista(city->listaMuro);

    free(city);
}

void imprimeCidade(Cidade cid, char nomeDoArquivoSvg[])
{
    cidade *city = (cidade *)cid;
    
    imprimeCirculos(city->listaCirculo, nomeDoArquivoSvg);
    imprimeRetangulos(city->listaRetangulo, nomeDoArquivoSvg);
    imprimeQuadras(city->listaQuadra, nomeDoArquivoSvg);
    imprimeHidrantes(city->listaHidrante, nomeDoArquivoSvg);
    imprimeSemaforos(city->listaSemaforo, nomeDoArquivoSvg);
    imprimeRadios(city->listaRadio, nomeDoArquivoSvg);
    // imprimePredios(city->listaPredio, nomeDoArquivoSvg);
    // imprimeMuros(city->listaMuro, nomeDoArquivoSvg);
}

Info procuraNaCidade(Cidade cid, char id[], int *tipo, char face[], double num)
{
    cidade *city = (cidade *)cid;
    int posicao;
    posicao = procuraCirculo(city->listaCirculo, id);
    if (posicao != -1)
    {
        *tipo = 1;
        return get(city->listaCirculo, posicao);
    }

    posicao = procuraRetangulo(city->listaRetangulo, id);
    if (posicao != -1)
    {
        *tipo = 2;
        return get(city->listaRetangulo, posicao);
    }

    posicao = procuraQuadra(city->listaQuadra, id);
    if (posicao != -1)
    {
        *tipo = 3;
        return get(city->listaQuadra, posicao);
    }

    posicao = procuraHidrante(city->listaHidrante, id);
    if (posicao != -1)
    {
        *tipo = 4;
        return get(city->listaHidrante, posicao);
    }

    posicao = procuraSemaforo(city->listaSemaforo, id);
    if (posicao != -1)
    {
        *tipo = 5;
        return get(city->listaSemaforo, posicao);
    }

    posicao = procuraRadio(city->listaRadio, id);
    if (posicao != -1)
    {
        *tipo = 6;
        return get(city->listaRadio, posicao);
    }

    posicao = procuraPredio(city->listaPredio, id, face, num);
    if (posicao != -1)
    {
        *tipo = 7;
        return get(city->listaPredio, posicao);
    }

    printf("Nao foi possivel achar o elemento na cidade\n");
    return NULL;
}

int adicionarCirculo(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    return insereLista(city->listaCirculo, info);
}


Circulo getCirculo(Cidade cid, int i)
{
    cidade *city = (cidade *)cid;
    return get(city->listaCirculo, i);
}

int adicionarRetangulo(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    return insereLista(city->listaRetangulo, info);
}

Retangulo getRetangulo(Cidade cid, int i)
{
    cidade *city = (cidade *)cid;
    return get(city->listaRetangulo, i);
}

int adicionarQuadra(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    return insereLista(city->listaQuadra, info);
}

Quadra getQuadra(Cidade cid, int i)
{
    cidade *city = (cidade *)cid;
    return get(city->listaQuadra, i);
}

int adicionarHidrante(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    return insereLista(city->listaHidrante, info);
}

Hidrante getHidrante(Cidade cid, int i)
{
    cidade *city = (cidade *)cid;
    return get(city->listaHidrante, i);
}

int adicionarRadioBase(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    return insereLista(city->listaRadio, info);
}

Radio getRadio(Cidade cid, int i)
{
    cidade *city = (cidade *)cid;
    return get(city->listaRadio, i);
}

int adicionarSemaforo(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    return insereLista(city->listaSemaforo, info);
}

Semaforo getSemaforo(Cidade cid, int i)
{
    cidade *city = (cidade *)cid;
    return get(city->listaSemaforo, i);
}


int adicionarPredio(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    return insereLista(city->listaPredio, info);
}

Predio getPredio(Cidade cid, int i)
{
    cidade *city = (cidade *)cid;
    return get(city->listaPredio, i);
}

int adicionarMuro(Cidade cid, Info info)
{
    cidade *city = (cidade *)cid;
    return insereLista(city->listaMuro, info);
}

Muro getMuro(Cidade cid, int i)
{
    cidade *city = (cidade *)cid;
    return get(city->listaMuro, i);
}