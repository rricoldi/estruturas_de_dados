#ifndef __LISTA_H
#define __LISTA_H
#include "quadra.h"
#include "hidrante.h"
#include "radio.h"
#include "semaforo.h"
#include "circulo.h"
#include "retangulo.h"

typedef void *Lista;
typedef int Posic;
typedef void *Info;

Lista iniciaLista(int capacidade);

void finalizaLista(Lista L);

void printaQuadras(Lista L, char svg[]);

void printaHidrantes(Lista L, char svg[]);

void printaSemaforos(Lista L, char svg[]);

void printaRadios(Lista L, char svg[]);

void printaCirculos(Lista L, char svg[]);

void printaRetangulos(Lista L, char svg[]);

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

void removeLista(Lista L, Posic pos);

Info get(Lista L, Posic pos);

int procuraListaC(Lista L, char id[]);

int procuraListaRe(Lista L, char id[]);

int procuraListaQ(Lista L, char id[]);

int procuraListaH(Lista L, char id[]);

int procuraListaS(Lista L, char id[]);

int procuraListaR(Lista L, char id[]);

void percorreListaQ(Lista L, double r, double fx, double fy, char tipo[], char svg[], char txt[], char id[], int opcao, char cor[], double largura, double altura, double dx, double dy);

void percorreListaH(Lista L, double x, double y, double w, double h, double dx, double dy, char txt[]);

void percorreListaS(Lista L, double x, double y, double w, double h, double dx, double dy, char txt[]);

void percorreListaR(Lista L, double x, double y, double w, double h, double dx, double dy, char txt[]);




#endif      