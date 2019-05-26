#ifndef __LISTA_H
#define __LISTA_H
#include "quadra.h"
#include "hidrante.h"
#include "radio.h"
#include "semaforo.h"

typedef void *Lista;
typedef long int Posic;
typedef void *Info;

Lista iniciaLista(long int capacidade);

void finalizaLista(Lista L);

long int getLivre(Lista L);

Info get(Lista L, Posic pos);

Posic insereLista(Lista L, Info info);

//Info procuraLista(Lista L, char cep[]);




#endif      