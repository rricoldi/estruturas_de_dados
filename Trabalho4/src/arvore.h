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



typedef void *Info;
typedef void *Node;
typedef void *Tree;


Tree criaArvore(double (*comparaInfo) (Info, Info));

void insereNaArvore(Tree** arvore, Info info);

void imprimeArvore(Tree tree, void (*print) (Info));

void imprimeNoSvg(Tree tree, void (*funcao) (Info, char[], char[]), char nomeDoArquivoSvg[], char cor[]);

void deletaDaArvore(Tree tree, Node* node);

void percorreArvore(Tree tree, void (*funcao) (Info, va_list), ...);

void percorreArvoreParaImpressaoNoSvg(Tree *tree, void (*imprimeSvg)(void*, FILE*, int, int, char, int), FILE *arquivoSVG);

void percorreArvore2(Tree tree, void (*funcao) (Node, Info, va_list), ...);

void desalocaArvore(Tree tree);

Node buscaNaArvore(Tree tree, Info info, char* (*retornaId) (Info));

#endif