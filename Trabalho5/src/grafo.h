#ifndef __GRAFO_H
#define __GRAFO_H

#include "leitura.h"
#include "listaDinamica.h"
#include "tipos.h"

//Inicia o grafo com um vetor de vértices, cujo tamanho é passado como parâmetro
Graph *criaGrafo(int numeroDeVertices);

//Define os valores do vértice dado
void defineInfoVertice(Graph* graph, int no, char id[], double x, double y);

//Retorna o índice do vértice dado
int getIndiceVertice(Graph* graph, char id[]);

//Define os valores da aresta dada
void defineInfoAresta(Graph* graph, int noInicial, int noFinal, char nomeDaRua[], char ladoDireito[], char ladoEsquerdo[], double comprimento, double velocidade);

//Retorna as informações da aresta dada
Info getInfoAresta(Graph* graph, int noInicial, int noFinal);

//Remove a aresta que vai de nóInicial para nóFinal
void removeAresta(Graph* graph, int noInicial, int noFinal);

//Insere uma aresta no grafo
bool insereAresta(Graph* graph, int noInicial, int noFinal, char ladoDireito[], char ladoEsquerdo[], double comprimento, double velocidade, char nomeDaRua[]);

//Retorna o X do vértice
double getX(Info info);

//Retorna o Y do vértice
double getY(Info info);

//Retorna o ID do vértice
char* getID(Info info);

//Getters e Setters para alguns parâmetros da aresta
double arestaGetX1(Info);
double arestaGetY1(Info);
double arestaGetX2(Info);
double arestaGetY2(Info);
void setArestaComprimento(Info info, double comprimento);
void setArestaVelocidade(Info info, double velocidade);

//Aplica uma dada função à todas as arestas do grafo
void percorreArestas(Graph, void (*func) (Reta*, Info, int), Reta* polig, int tamPolig);

//Verifica se o dado vértice está ou não ativo
bool getAtivo(Info info);

//Define a lista
void setLista(Graph* graph, List* lista);

//Retorna a lista
List* getLista(Graph* graph);

//
void auxilioDirecao(Graph graph, int *caminho, int modo, int noFinal);

//Aplica o algoritmo de dijkstra para um grafo dado, com vértices inicial e final indicado
int* dijkstra(Graph* graph, int noInicial, int noFinal, char nomeDoArquivoSvg[], char nomeDoArquivoTxt[], char cor1[], char cor2[], int modo);

#endif