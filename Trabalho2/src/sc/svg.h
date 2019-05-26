#ifndef __SVG_H
#define __SVG_H

//Cria a tag inicial de um svg para o arquivo com o nome recebido
void iniciaSvg(char arq[]);

//Cria a tag final de um svg para o arquivo com o nome recebido
void finalizaSvg(char arq[]);

//Cria um circulo a partir do ponto x y e do raio, no arquivo svg
void printaCirculo(double raio, double x, double y, char corB[], char corP[], char svg[], double espessura);

//Cria um retangulo a partir do ponto x y e da altura e largura, no arquivo svg
void printaRetangulo(double largura, double altura, double x, double y, char corB[], char corP[], char svg[], double espessura);

void criaElipse(char svg[], double cx, double cy, double rx, double ry, char corP[], char corB[], double espessura);

//Escreve o texto no ponto x y
void escreveSvg(float x, float y, char texto[], char svg[]);

#endif