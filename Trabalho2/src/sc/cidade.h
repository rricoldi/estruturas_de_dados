#ifndef __CIDADE_H
#define __CIDADE_H

#include "lista.h"

typedef void *Cidade;

Cidade criaCidade(long int nq, long int nh, long int nr, long int ns);

void removeCidade(Cidade cid);

int addQuadra(Cidade cid, Info info);

Quadra getQuadra(Cidade cid, long int i);

int addHidrante(Cidade cid, Info info);

Hidrante getHidrante(Cidade cid, long int i);

int addRadio(Cidade cid, Info info);

Radio getRadio(Cidade cid, long int i);

int addSemaforo(Cidade cid, Info info);

Semaforo getSemaforo(Cidade cid, long int i);

#endif