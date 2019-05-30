#ifndef __QRY_H
#define __QRY_H

/*
    Aqui temos quase todas as funcoes usadas para resolver os procedimentos informados pelo .qry
*/

#include <stdbool.h>

double max(double n1, double n2);

double min(double n1, double n2);

int interno(double px, double py, double rx, double ry, double h, double w);

double distancia (double x1, double y1, double x2, double y2);

double distanciaFig(double x1, double y1, double x2, double y2, char svg[]);

bool pontoInternoCirculo(float px, float py, float cx, float cy, float r);

bool pontoInternoRetangulo(float px, float py, float rx, float ry, float h, float w);

void colisaoRR(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2, char j[], char k[], char txt[], char svg[]);

bool inRR(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);

void colisaoCR(float cx, float cy, float r, float rx, float ry, float w, float h, char j[], char k[], char txt[], char svg[]);

void colisaoCC(int x1, int y1, float r1, int x2, int y2, float r2, char j[], char k[], char txt[], char svg[]);

bool retornaDistanciaL1(double r, double fx, double fy, double x, double y, double w, double h);

bool retornaDistanciaL2(double r, double fx, double fy, double x, double y, double w, double h);

#endif