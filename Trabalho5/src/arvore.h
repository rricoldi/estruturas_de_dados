#ifndef __ARVORE_H
#define __ARVORE_H

#include<stdarg.h>
#include <stdio.h>

#include "quadra.h"
#include "hidrante.h"
#include "radio.h"
#include "semaforo.h"
#include "circulo.h"
#include "retangulo.h"
#include "predio.h"
#include "muro.h"
#include "hashTable.h"
#include "qry.h"
#include "tipos.h"

//Cria uma arvore vazia, e define sua folha (nil);
//Pré-requisito: uma função que recebe dois Infos e retorna a subtracao de um pelo outro;
//Pós condição: retorna um ponteiro para a arvore criada.
Tree criaArvore(double (*comparaInfo) (Info, Info));

//Cria um no na arvore com o Info passado;
//Pré-requisito: Arvore existente.
void insereNaArvore(Tree** arvore, Info info);

//Permite a navegação por uma árvore;
//Pré-requisito: Arvore com pelo menos um elemento.
void imprimeArvore(Tree tree, void (*print) (Info));

//Imprime todos os elementos de uma arvore no svg;
//Pré-requisito: arvore com elementos, funcao que imprime o elemento no svg.
void imprimeNoSvg(Tree tree, void (*funcao) (Info, char[], char[]), char nomeDoArquivoSvg[], char cor[]);

//Deleta um nó da árvore;
//Pré-requisito: nó existente na árvore.
void deletaDaArvore(Tree tree, Node* node);

//percorre a árvore aplicando uma função, que recebe Info, em todos os nós;
//Pré-requisito: funcao para aplicacao e arvore não vazia.
void percorreArvore(Tree tree, void (*funcao) (Info, va_list), ...);


//Percorre a árvore imprimindo os nós da árvore no svg, segundo o comando ;
//Pré-requisito: funcao para aplicacao e arvore não vazia;
//Pós condição: árvore impressa no svg;
void percorreArvoreParaImpressaoNoSvg(Tree *tree, void (*imprimeSvg)(void*, FILE*, int, int, char, int), FILE *arquivoSVG);

//percorre a árvore aplicando uma função, que recebe Info e Node, em todos os nós;
//Pré-requisito: funcao para aplicacao e arvore não vazia.
void percorreArvore2(Tree tree, void (*funcao) (Node, Info, va_list), ...);


//percorre a árvore desalocando os nós e por fim a árvore;
//Pré-requisito: árvore não vazia.
void desalocaArvore(Tree tree);

//Busca um elemento na árvore;
//Pré-requisito: uma função que retorne o Id ou Cep de um Info;
//Pós condição: retorna o nó que contem a informação passada.
Node buscaNaArvore(Tree tree, Info info, char* (*retornaId) (Info));

//Cria uma arvore vazia, e define sua folha (nil);
//Pré-requisito: uma função que recebe dois Infos e retorna a subtracao de um pelo outro;
//Pós condição: retorna um ponteiro para a arvore criada.
int getTamanhoDaArvore(Tree);

//Retorna a informação de um nó;
//Pré-requisito: um nó;
//Pós condição: retorna um Info contendo a informação daquele nó.
Info getInfo(Node node);

//Ordena um vetor de Infos usando heapsort;
//Pré-requisito: vetor de Info não vazio, funções que retorne as coordenadas de cada Info.
void heapsort(Info vetor[], int tamanho, double x, double y, double (*retorna)(Info), double (*retorna2)(Info));

//Resolve o comando fi do qry;
//Pré-requisito: vetor ordenado de Infos (semaforos ou hidrantes) e a coordenada do incêndio;
//Pós condição: comando resolvido;
void resolveSemaforos(Info vetor[], double xIncendio, double yIncendio, int numeroDeSemaforos, char nomeDoArquivoSvg[], char nomeDoArquivoTxt[], char comando[]);

//Resolve o comando fh do qry;
//Pré-requisito: vetor ordenado de Infos (semaforos ou hidrantes) e a coordenada do endereço;
//Pós condição: comando resolvido
void resolveFHidrantes(Info vetor[], double x, double y, int numeroDeHidrantes, int fim, int sinal, char nomeDoArquivoSvg[], char nomeDoArquivoTxt[]);

#endif