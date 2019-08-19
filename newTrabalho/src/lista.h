#ifndef __LISTA_H
#define __LISTA_H
#include "quadra.h"
#include "hidrante.h"
#include "radio.h"
#include "semaforo.h"
#include "circulo.h"
#include "retangulo.h"
#include "predio.h"
#include "muro.h"


/*
    Aqui implementamos o TAD da lista estatica duplamente encadeada, tendo as funcoes pedidas no TAD, alem de funcoes que realizam a impressao, busca e remocao dos elementos
    contidos nela 
*/

typedef void *Lista;
typedef int Posic;
typedef void *Info;


Lista iniciaLista(int capacidade);

void finalizaLista(Lista L);

void imprimeCirculos(Lista L, char nomeDoArquivoSvg[]);

void imprimeRetangulos(Lista L, char nomeDoArquivoSvg[]);

void imprimeQuadras(Lista L, char nomeDoArquivoSvg[]);

void imprimeHidrantes(Lista L, char nomeDoArquivoSvg[]);

void imprimeSemaforos(Lista L, char nomeDoArquivoSvg[]);

void imprimeRadios(Lista L, char nomeDoArquivoSvg[]);

#endif