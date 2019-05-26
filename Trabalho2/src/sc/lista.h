#ifndef __LISTA_H
#define __LISTA_H
#include "quadra.h"
#include "hidrante.h"
#include "radio.h"
#include "semaforo.h"
#include "circulo.h"
#include "retangulo.h"

typedef void *Lista;
typedef int Posic;
typedef void *Info;

Lista iniciaLista(int capacidade);

void finalizaLista(Lista L);

int getLivre(Lista L);

Info get(Lista L, Posic pos);

Posic insereLista(Lista L, Info info);

Info procuraLista(Lista L, char cep[]);




#endif      