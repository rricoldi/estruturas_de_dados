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

void imprimeQuadras(Lista L, char nomeDoArquivoSvg[]);

void imprimeHidrantes(Lista L, char nomeDoArquivoSvg[]);

void imprimeSemaforos(Lista L, char nomeDoArquivoSvg[]);

void imprimeRadios(Lista L, char nomeDoArquivoSvg[]);

void imprimePredios(Lista L, char nomeDoArquivoSvg[]);

void imprimeMuros(Lista L, char nomeDoArquivoSvg[]);

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

void removerDaLista(Lista L, Posic pos);

Info get(Lista L, Posic pos);

int procuraCirculo(Lista L, char id[]);

int procuraRetangulo(Lista L, char id[]);

int procuraQuadra(Lista L, char id[]);

int procuraHidrante(Lista L, char id[]);

int procuraSemaforo(Lista L, char id[]);

int procuraRadio(Lista L, char id[]);

int procuraPredio(Lista L, char id[], char face[], double num);

void percorreListaQ(Lista L, double r, double fx, double fy, char tipo[], char svg[], char txt[], char id[], int opcao, char cor[], double largura, double altura, double dx, double dy);

void percorreListaH(Lista L, double x, double y, double w, double h, double dx, double dy, char txt[]);

void percorreListaS(Lista L, double x, double y, double w, double h, double dx, double dy, char txt[]);

void percorreListaR(Lista L, double x, double y, double w, double h, double dx, double dy, char txt[]);

int transformaListaEmVetor(Lista L, Info vetor[]);

void resolveSemaforos(Lista L, double xIncendio, double yIncendio, int numeroDeSemaforos, char nomeDoArquivoSvg[], char nomeDoArquivoTxt[], char comando[]);

void quickSortSemaforo(Info vetor[], int inicio, int fim, double xIncendio, double yIncendio);

void resolveHidrantes(Lista L, double xIncendio, double yIncendio, double raio, char nomeDoArquivoSvg[], char nomeDoArquivoTxt[]);

void resolveFHidrantes(Lista L, double x, double y, int numeroDeHidrantes, int sinal, char nomeDoArquivoSvg[], char nomeDoArquivoTxt[]);

void quickSortHidrante(Info vetor[], int inicio, int fim, double x, double y);

#endif