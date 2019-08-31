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

void bbcLista(Lista L, char arqout[]);

void bbrLista(Lista L, char arqout[], char cor[]);

int lenght(Lista L);

Posic getFirst(Lista L);

Posic getLast(Lista L);

Posic getNext(Lista L, Posic p);

Posic getPrevious(Lista L, Posic p);

int getLivre(Lista L);

Posic insertBefore(Lista L, Info info, Posic posicao);

Posic insertAfter(Lista L, Info info, Posic posicao);

Posic insereLista(Lista L, Info info);

Info get(Lista L, Posic pos);

int procuraCirculo(Lista L, char id[]);

int procuraRetangulo(Lista L, char id[]);

int procuraQuadra(Lista L, char id[]);

int procuraHidrante(Lista L, char id[]);

int procuraSemaforo(Lista L, char id[]);

int procuraRadio(Lista L, char id[]);

int procuraPredio(Lista L, char id[], char face[], double num);

#endif