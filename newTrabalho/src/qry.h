#ifndef __QRY_H
#define __QRY_H

/*
    Aqui temos quase todas as funcoes usadas para resolver os procedimentos informados pelo .qry
*/

#include <stdbool.h>

double max(double n1, double n2);

double min(double n1, double n2);

bool retornaDistanciaL2(double r, double fx, double fy, double x, double y, double w, double h);

bool retornaDistanciaL1(double r, double fx, double fy, double x, double y, double w, double h);

void colisaoEntreCirculosERetangulos(float cx, float cy, float r, float rx, float ry, float w, float h, char j[], char k[], char txt[], char svg[]);

void colisaoEntreCirculos(int x1, int y1, float r1, int x2, int y2, float r2, char j[], char k[], char txt[], char svg[]);

double distancia (double x1, double y1, double x2, double y2);

void colisaoEntreRetangulos(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2, char j[], char k[], char txt[], char svg[]);

bool verificaColisao(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);

bool pontoInternoCirculo(float px, float py, float cx, float cy, float r);

bool pontoInternoRetangulo(float px, float py, float rx, float ry, float h, float w);

double distanciaDaFigura(double x1, double y1, double x2, double y2, char svg[]);

#endif