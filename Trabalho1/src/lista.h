#ifndef __LISTA_H
#define __LISTA_H

#include "struct.h"

//Inicia a lista
No *iniciar();

//Insere um elemento na lista
No *inserir(No *inicio, int id, float raio, float x, float y, float altura, float largura, char cor1[], char cor2[], char type);

//Busca um elemento na lista
No *buscar(No *inicio, int num);

//Desaloca a lista
void desalocar(No *inicio);

#endif