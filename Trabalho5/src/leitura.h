#ifndef __LEITURA_H
#define __LEITURA_H


/*
    Aqui eh onde resolvemos a parte de leitura dos arquivos .geo e .qry, decidindo quais funcoes chamar e quais procedimentos realizar
*/

#include "svg.h"
#include "qry.h"
#include "cidade.h"
#include "hashTable.h"
#include "geometria.h"
#include "grafo.h"
#include "listaDinamica.h"

//Lê o arquivo geo e retorna a cidade;
//Pré-requisito: arquivo geo deve existir;
//Pós condição: cidade criada e impressa no arquivo svg.
Cidade leiaGeo(char nomeDoArquivoGeo[], char nomeDoArquivoSvg[]);

//Lê o arquivo qry e executa os comandos;
//Pré-requisito: nome do arquivo, prefixo, cidade e arquivo de saída existem;
//Pós condição: comandos do .qry executados.
void leiaQry(char caminhoDoArquivoEntrada[], char prefixoDoArquivoQry[], char nomeDoArquivoQry[], Cidade cidade, char caminhoDoArquivoDeSaida[]);

//Lê o arquivo ec;
//Pré-requisito: arquivo e tabelas existem;
//Pós condição: tabelas populadas com os tipos e estabelecimentos do arquivo;
void leiaEc(char* arquivoEc, HashTable comercios, HashTable tiposComercio, HashTable comercios_cpf);
//Lê o arquivo pm;
//Pré-requisito: arquivo e tabelas existem;
//Pós condição: tabelas populadas com as pessoas e moradias do arquivo
void leiaPm(char* arquivoPm, HashTable pessoas, HashTable moradias, HashTable moradiaPessoa);

//Lê o arquivo e retorna um vetor de retas que representam o polígono;
//Pré-requisito: nomeDoArquivoPoligono deve existir, quantidade de pontos deve ser maior que 2;
//Pós condição: arquivo lido;
//Nota: Todas as retas, tal como o vetor, são alocadas na memória, portanto deve ser dado um free() para cada reta e para o vetor.
Reta* leiaPol(char* caminhoDoArquivo, char* nomeDoArquivoPoligono, int *array_size);

Graph leiaVia(char* nomeDoArquivoVia);
#endif