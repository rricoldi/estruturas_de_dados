#ifndef __SVG_H
#define __SVG_H

/*
    Aqui realizamos a impressao dos codigos svg no arquivo determinado  
*/

//Cria a tag inicial de um svg para o arquivo com o nome recebido
void iniciaSvg(char nomeDoArquivoSvg[]);

//Cria um circulo a partir do ponto x y e do raio, no arquivo svg
void imprimirCirculo(double raio, double x, double y, char corB[], char corP[], char nomeDoArquivoSvg[], double espessura);

//Cria um retangulo a partir do ponto x y e da altura e largura, no arquivo svg
void imprimirRetangulo(double largura, double altura, double x, double y, char corB[], char corP[], char svg[], double espessura);

//Escreve o texto no ponto x y
void escreverNoSvg(float x, float y, char texto[], char svg[]);

void imprimirElipse(char svg[], double cx, double cy, double rx, double ry, char corP[], char corB[], double espessura);

#endif