#ifndef __MURO_H
#define __MURO_H


typedef void *Muro;

Muro criarMuro(double x1, double x2, double y1, double y2);

double retornaMX1(Muro r);

double retornaMX2(Muro r);

double retornaMY1(Muro r);

double retornaMY2(Muro r);

#endif