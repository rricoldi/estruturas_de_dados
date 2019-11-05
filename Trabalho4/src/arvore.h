#ifndef __ARVORE_H
#define __ARVORE_H

typedef void *Info;
typedef void *Node;
typedef void *Tree;


Tree criaArvore(double (*comparaInfo) (Info, Info));

void insereNaArvore(Tree** arvore, Info info);

// void imprimeArvore(Tree* arvore);

void deletaDaArvore(Tree tree, Node* node);

// Info* buscaNaArvore(Tree* arvore, int numero);


#endif