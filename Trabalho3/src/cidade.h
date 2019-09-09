#ifndef __CIDADE_H
#define __CIDADE_H

#include "lista.h"

/*  
    Aqui implementamos uma cidade onde todas as listas estao, aqui podemos inicia-las, remove-las, e eh ponte para todas as funcoes envolvendo as listas e os seus elementos 
    Tambem eh utilizada para resolver alguns problemas do Qry, e para conseguir os valores de uma determinada forma
*/

typedef void *Cidade;

Cidade criarCidade(int numeroDeFiguras, int numeroDeQuadras, int numeroDeHidrantes, int numeroDeRadios, int numeroDeSemaforos, int numeroDePredios, int numeroDeMuros);

void removeCidade(Cidade cid);

void boudingBoxCirculos(Cidade cid, char arquivo[]);

void boundingBoxRetangulos(Cidade cid, char arquivo[], char cor[]);

void imprimeCirculosERetangulos(Cidade cid, char nomeDoArquivoSvg[]);

void imprimeCidade(Cidade cid, char nomeDoArquivoSvg[]);

Info procuraNaCidade(Cidade cid, char id[], int *tipo, char face[], double num);

void removeDaCidade(Cidade cid, char id[], char txt[]);

int adicionarCirculo(Cidade cid, Info info);

int adicionarRetangulo(Cidade cid, Info info);

int adicionarQuadra(Cidade cid, Info info);

int adicionarHidrante(Cidade cid, Info info);

int adicionarRadioBase(Cidade cid, Info info);

int adicionarSemaforo(Cidade cid, Info info);

int adicionarPredio(Cidade cid, Info info);

Circulo getCirculo(Cidade cid, int i);

Retangulo getRetangulo(Cidade cid, int i);

Quadra getQuadra(Cidade cid, int i);

Hidrante getHidrante(Cidade cid, int i);

Radio getRadio(Cidade cid, int i);

Semaforo getSemaforo(Cidade cid, int i);

Predio getPredio(Cidade cid, int i);

int adicionarPredio(Cidade cid, Info info);

Muro getMuro(Cidade cid, int i);

int adicionarMuro(Cidade cid, Info info);

void percorreCidade(Cidade cid, double r, double fx, double fy, char tipo[], char svg[], char txt[], char id[], int option, char cor[], double largura, double altura, double dx, double dy);

void resolveIncendios(Cidade cid, double x, double y, double raio, int numeroDeSemaforos, char nomeDoArquivoSvg[], char nomeDoArquivoTxt[]);

void resolveFH(Cidade cid, Info quadra, int numeroDeHidrantes, char nomeDoArquivoSvg[], char nomeDoArquivoTxt[]);

void resolveFS(Cidade cid, Info quadra, int numeroDeHidrantes, char nomeDoArquivoSvg[], char nomeDoArquivoTxt[]);

#endif