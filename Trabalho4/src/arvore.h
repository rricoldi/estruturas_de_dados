#ifndef __ARVORE_H
#define __ARVORE_H

#include<stdarg.h>
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

void desalocaArvore(Tree tree);

// Info* buscaNaArvore(Tree* arvore, int numero);

#endif