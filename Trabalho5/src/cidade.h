#ifndef __CIDADE_H
#define __CIDADE_H

#include "lista.h"
#include "arvore.h"
#include "hashTable.h"
#include "svg.h"

#include<stdio.h>

/*  
    Aqui implementamos uma cidade onde todas as listas estao, aqui podemos inicia-las, remove-las, e eh ponte para todas as funcoes envolvendo as listas e os seus elementos 
    Tambem eh utilizada para resolver alguns problemas do Qry, e para conseguir os valores de uma determinada forma
*/

typedef void *Cidade;

//Cria as estruturas de dados de uma cidade;
//Pós condição: retorna uma Cidade.
Cidade criarCidade();

void iniciaComercios(Cidade, char* arquivoEc);

void iniciaPessoas(Cidade, char* arquivoPm);

//remove as estruturas de dados de uma cidade;
//Pré-requisito: Cidade criada;
//Pós condição: desaloca todos os elementos da cidade.
void removeCidade(Cidade cid);

//Imprime todos os circulos e retangulos de uma cidade;
//Pré-requisito: cidade com circulos e retangulos;
//Pós condição: imprime os circulos e retangulos da cidade no svg.
void imprimeCirculosERetangulos(Cidade cid, char nomeDoArquivoSvg[]);

//Imprime os elementos necessários do comando bb;
//Pré-requisito: Cidade não vazia;
//Pós condição: elipses e retangulos impressos no svg.
void imprimeBoundingBox(Cidade cid, char nomeDoArquivoSvg[], char cor[]);

//Imprime todos os elementos urbanos de uma cidade;
//Pré-requisito: cidade com elementos urbanos;
//Pós condição: imprime os elementos urbanos da cidade no svg.
void imprimeCidade(Cidade cid, char nomeDoArquivoSvg[]);

//Procura um elemento na cidade;
//Pré-requisito: cidade com elementos urbanos, ponteiro para um int, e id do elemento desejado;
//Pós condição: retorna o elemento e informa qual o tipo retornado.
Info procuraNaCidade(Cidade cid, char id[], int *tipo, char face[], double num);

//Remove um elemento da cidade;
//Pré-requisito: id;
//Pós condição: remove da árvore, da hashtable e desaloca o nó.
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

Circulo getCirculo(Cidade cid, char id[]);

Retangulo getRetangulo(Cidade cid, char id[]);

Quadra getQuadra(Cidade cid, char id[]);

Hidrante getHidrante(Cidade cid, char id[]);

Radio getRadio(Cidade cid, char id[]);

Semaforo getSemaforo(Cidade cid, char id[]);

Predio getPredio(Cidade cid, char id[]);

Muro getMuro(Cidade cid, int i);

//Executa os comandos do .qry de mesmo nome;
//Pré-requisito: todos os parâmetros devem existir (caminho do arquivo é opcional);
//Pós condição: comandos executados;

void percorreCidade(Cidade cid, double r, double fx, double fy, char tipo[], char svg[], char txt[], char id[], int option, char cor[], double largura, double altura, double dx, double dy);

void qry_fi(Cidade cid, double x, double y, double raio, int numeroDeSemaforos, char nomeDoArquivoSvg[], char nomeDoArquivoTxt[]);

void resolveFH(Cidade cid, Info quadra, int numeroDeHidrantes, char nomeDoArquivoSvg[], char nomeDoArquivoTxt[]);

void resolveFS(Cidade cid, Info quadra, int numeroDeHidrantes, char nomeDoArquivoSvg[], char nomeDoArquivoTxt[]);

void qry_dq(Cidade cid, Info info, double r, double fx, double fy, char svg[], char txt[], char id[], char metrica[], int tipo);

void qry_cbq(Cidade cid, double raio, double x, double y, char cor[], char nomeDoArquivoTxt[]);

void qry_trns(Cidade cid, double largura, double altura, double x, double y, double dx, double dy, char nomeDoArquivoTxt[]);

void qry_crd(Cidade cid, char id[], char txt[]);
void qry_bombaRadiacaoLum(Cidade, double x, double y, char* nomeArqSvg);
void qry_bombaRadiacaoNuc(Cidade, double x, double y, char* nomeArqSvg, char* nomeArqTxt, char* nomeArqPol, char* caminhoDoArquivo);
void qry_m(FILE* arquivoTxt, char* cep, Cidade);

void qry_dm(FILE* arquivoTxt, char* cpf, Cidade);

void qry_de(FILE* arquivoTxt, char* cnpj, Cidade);

void qry_mud(FILE* arquivoTxt, char* cpf, char* cep, char face, int num, char* complemento, Cidade);

void qry_dmprbt(Cidade cid, char* nomeDoArquivoSvg, char comando);

void qry_mplg(char caminhoDoArquivo[], Reta poligono[], int tamanhoDoPoligono, FILE* arquivoTxt, char* nomeArquivoSvg, Cidade cidade);

void qry_eplg(char* caminhoDoArquivo, Reta poligono[], int tamPolig, FILE* arquivoTxt, char* nomeArqSvg, char* tipo, Cidade cidade);

void qry_nav(Cidade cid, char arvore);

void qry_catac(FILE* arquivoTxt, char* nomeArquivoSvg, Reta poligono[], int tamPolig, Cidade);
//Comandos @'algumacoisa'?
void qry_ATmQM(char* cpf, Ponto* R, int index, Cidade);
void qry_ATeQM(char* cep, char face, int num, Ponto* R, int index, Cidade);
void qry_ATgQM(char* id, Ponto* R, int index, Cidade);

#endif
