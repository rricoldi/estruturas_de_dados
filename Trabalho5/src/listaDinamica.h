#ifndef __LISTADINAMICA_H
#define __LISTADINAMICA_H

#include "tipos.h"

List* criaLista();

void criaNoListaDinamica(List* list, char id[], double x, double y);

void excluirLista(List* list);

int getTamanho(List* list);

void insereVertice(Graph grafo, List list);

#endif