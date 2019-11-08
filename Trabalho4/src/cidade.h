#ifndef __CIDADE_H
#define __CIDADE_H

#include "lista.h"
#include "arvore.h"
#include "hashTable.h"
#include<stdio.h>
/*  
    Aqui implementamos uma cidade onde todas as listas estao, aqui podemos inicia-las, remove-las, e eh ponte para todas as funcoes envolvendo as listas e os seus elementos 
    Tambem eh utilizada para resolver alguns problemas do Qry, e para conseguir os valores de uma determinada forma
*/

typedef void *Cidade;

Cidade criarCidade();
void iniciaComercios(Cidade, char* arquivoEc);
void iniciaPessoas(Cidade, char* arquivoPm);

void removeCidade(Cidade cid);

void imprimeCirculosERetangulos(Cidade cid, char nomeDoArquivoSvg[]);

void imprimeBoundingBox(Cidade cid, char nomeDoArquivoSvg[], char cor[]);

void imprimeCidade(Cidade cid, char nomeDoArquivoSvg[]);

Info procuraNaCidade(Cidade cid, char id[], int *tipo, char face[], double num);

void removeDaCidade(Cidade cid, char id[], char txt[]);

void adicionarCirculo(Cidade cid, Info info);

void adicionarRetangulo(Cidade cid, Info info);

void adicionarQuadra(Cidade cid, Info info);

void adicionarHidrante(Cidade cid, Info info);

void adicionarRadioBase(Cidade cid, Info info);

void adicionarSemaforo(Cidade cid, Info info);

void adicionarPredio(Cidade cid, Info info);

void adicionarPredio(Cidade cid, Info info);

void adicionarMuro(Cidade cid, Info info);

Circulo getCirculo(Cidade cid, int i);

Retangulo getRetangulo(Cidade cid, int i);

Quadra getQuadra(Cidade cid, int i);

Hidrante getHidrante(Cidade cid, int i);

Radio getRadio(Cidade cid, int i);

Semaforo getSemaforo(Cidade cid, int i);

Predio getPredio(Cidade cid, int i);

Muro getMuro(Cidade cid, int i);

void percorreCidade(Cidade cid, double r, double fx, double fy, char tipo[], char svg[], char txt[], char id[], int option, char cor[], double largura, double altura, double dx, double dy);

void resolveIncendios(Cidade cid, double x, double y, double raio, int numeroDeSemaforos, char nomeDoArquivoSvg[], char nomeDoArquivoTxt[]);

void resolveFH(Cidade cid, Info quadra, int numeroDeHidrantes, char nomeDoArquivoSvg[], char nomeDoArquivoTxt[]);

void resolveFS(Cidade cid, Info quadra, int numeroDeHidrantes, char nomeDoArquivoSvg[], char nomeDoArquivoTxt[]);

void qry_m(FILE* arquivoTxt, char* cep, Cidade);
void qry_md(FILE* arquivoTxt, char* cpf, Cidade);
void qry_de(FILE* arquivoTxt, char* cnpj, Cidade);

#endif