#ifndef __SVG_H
#define __SVG_H

//Cria a tag inicial de um svg para o arquivo com o nome recebido
void iniciaSvg(char arq[]);

//Cria a tag final de um svg para o arquivo com o nome recebido
void finalizaSvg(char arq[]);

//Cria uma linha entre dois pontos com a cor selecionada no arquivo svg
void criaLinha(float x1, float y1, float x2, float y2, char cor[], char svg[]);

//Cria um circulo a partir do ponto x y e do raio, no arquivo svg
void criaCirculo(float raio, float x, float y, char cor1[], char cor2[], char svg[]);

//Cria um retangulo a partir do ponto x y e da altura e largura, no arquivo svg
void criaRetangulo(float largura, float altura, float x, float y, char cor1[], char cor2[], char svg[]);

//Escreve a distancia entre dois pontos na metade da distancia entre eles
void escreveDistancia(float x1, float y1, float x2, float y2, float distancia, char svg[]);

//Escreve o texto no ponto x y
void escreveSvg(float x, float y, char texto[], char svg[]);

#endif