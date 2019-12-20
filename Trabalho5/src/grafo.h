#ifndef __GRAFO_H
#define __GRAFO_H

#include "leitura.h"
#include "listaDinamica.h"
#include "tipos.h"

Graph *criaGrafo(int numeroDeVertices);

void defineInfoVertice(Graph* graph, int no, char id[], double x, double y);

int getIndiceVertice(Graph* graph, char id[]) ;

void defineInfoAresta(Graph* graph, int noInicial, int noFinal, char nomeDaRua[], char ladoDireito[], char ladoEsquerdo[], double comprimento, double velocidade);

Info getInfoAresta(Graph* graph, int noInicial, int noFinal);

void removeAresta(Graph* graph, int noInicial, int noFinal);

bool insereAresta(Graph* graph, int noInicial, int noFinal, char ladoDireito[], char ladoEsquerdo[], double comprimento, double velocidade, char nomeDaRua[]);

double getX(Info info);

double getY(Info info);

char* getID(Info info);

double arestaGetX1(Info);
double arestaGetY1(Info);
double arestaGetX2(Info);
double arestaGetY2(Info);
void setArestaComprimento(Info info, double comprimento);
void setArestaVelocidade(Info info, double velocidade);

void percorreArestas(Graph, void (*func) (Reta*, Info, int), Reta* polig, int tamPolig);

int getIndiceVertice(Graph* graph, char id[]);

bool getAtivo(Info info);

void setLista(Graph* graph, List* lista);

List* getLista(Graph* graph);

void imprimeGrafo(Graph* graph);

void auxilioDirecao(Graph graph, int *caminho, int modo, int noFinal);

int* dijkstra(Graph* graph, int noInicial, int noFinal, char nomeDoArquivoSvg[], char nomeDoArquivoTxt[], char cor1[], char cor2[], int modo);

#endif