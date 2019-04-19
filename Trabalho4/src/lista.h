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
#include "qry.h"


/*
    Aqui implementamos o TAD da lista estatica duplamente encadeada, tendo as funcoes pedidas no TAD, alem de funcoes que realizam a impressao, busca e remocao dos elementos
    contidos nela 
*/

typedef void *Lista;
typedef int Posic;
typedef void *Info;


Lista iniciaLista(int capacidade);

void finalizaLista(Lista L);

int lenght(Lista L);

int getLivre(Lista L);

Posic insereLista(Lista L, Info info);

void removerDaLista(Lista L, Posic pos);

int transformaListaEmVetor(Lista L, Info vetor[]);

#endif