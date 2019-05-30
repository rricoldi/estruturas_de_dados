#ifndef __QRY_H
#define __QRY_H

#include "struct.h"

//Retorna o maior de dois numeros
float max(float n1, float n2);

//Retorna o menor de dois numeros
float min(float n1, float n2);

//Resolve se um ponto e interno a uma figura
int interno(float px, float py, float rx, float ry, float h, float w);

//Retorna a Distancia entre dois pontos
float distancia (float x1, float y1, float x2, float y2);

//Retorna a Distancia entre duas figuras
void distanciaFig(float x1, float y1, float x2, float y2, char txt[], char svg[], int j, int k);

//Verifica se ha colisao entre dois retangulos
void colisaoRR(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2, char j[], char k[], char txt[], char svg[]);

//Verifica se ha colisao entre um circulo e um retangulo
void colisaoCR(float cx, float cy, float r, float rx, float ry, float w, float h, int j, int k, char txt[], char svg[]);

//Verifica se ha colisao entre dois circulos
void colisaoCC(int x1, int y1, float r1, int x2, int y2, float r2, int j, int k, char txt[], char svg[]);

//Arruma o svg baseado na existencia ou nao de colisao entre figuras
void boundingBox(char cor[], char arquivo[], char sufixo[], No *inicio);

//Arruma o svg baseado se o ponto e interno ao circulo
void pontoInternoCirculo(float px, float py, float cx, float cy, float r, char arquivo[], int j, char svg[]);

//Arruma o svg baseado se o ponto e interno ao retangulo
void pontoInternoQuadrado(float px, float py, float rx, float ry, float h, float w, char arquivo[], int j, char svg[]);

#endif