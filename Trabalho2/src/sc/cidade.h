#ifndef __CIDADE_H
#define __CIDADE_H

#include "lista.h"


typedef void *Cidade;

Cidade criaCidade(int nx, int nq, int nh, int nr, int ns);

void removeCidade(Cidade cid);

void printaCeR(Cidade cid, char svg[]);

void printaCidade(Cidade cid, char svg[]);

void boudingBoxCirculos(Cidade cid, char arquivo[]);

void boundingBoxRetangulos(Cidade cid, char arquivo[], char cor[]);

Info procuraCidade(Cidade cid, char id[], int *tipo);

void removeDaCidade(Cidade cid, char id[], char txt[]);

void percorreCidadeLQ(Cidade cid, double r, double fx, double fy, char tipo[], char svg[], char txt[], char id[], int option, char cor[], double largura, double altura, double dx, double dy);

int addCirculo(Cidade cid, Info info);

Circulo getCirculo(Cidade cid, int i);

int addRetangulo(Cidade cid, Info info);

Retangulo getRetangulo(Cidade cid, int i);

int addQuadra(Cidade cid, Info info);

Quadra getQuadra(Cidade cid, int i);

int addHidrante(Cidade cid, Info info);

Hidrante getHidrante(Cidade cid, int i);

int addRadio(Cidade cid, Info info);

Radio getRadio(Cidade cid, int i);

int addSemaforo(Cidade cid, Info info);

Semaforo getSemaforo(Cidade cid, int i);

#endif