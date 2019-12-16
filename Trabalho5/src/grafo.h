#ifndef __GRAFO_H
#define __GRAFO_H

#include "cidade.h"

typedef void* Graph;

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

int getIndiceVertice(Graph* graph, char id[]);

bool getAtivo(Info info);

void imprimeGrafo(Graph* graph);

double dijkstra(Graph* graph, int noInicial, int noFinal, int modo);

#endif