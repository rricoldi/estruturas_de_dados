#ifndef __ARVORE_H
#define __ARVORE_H

#include "quadra.h"
#include "hidrante.h"
#include "radio.h"
#include "semaforo.h"
#include "circulo.h"
#include "retangulo.h"
#include "predio.h"
#include "muro.h"
#include "qry.h"


typedef void *Info;
typedef void *Node;
typedef void *Tree;


Tree criaArvore(double (*comparaInfo) (Info, Info));

void insereNaArvore(Tree** arvore, Info info);

// void imprimeArvore(Tree* arvore);

void deletaDaArvore(Tree tree, Node* node);

// Info* buscaNaArvore(Tree* arvore, int numero);


#endif