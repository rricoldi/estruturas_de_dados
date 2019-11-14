#ifndef __LEITURA_H
#define __LEITURA_H


/*
    Aqui eh onde resolvemos a parte de leitura dos arquivos .geo e .qry, decidindo quais funcoes chamar e quais procedimentos realizar
*/

#include "svg.h"
#include "qry.h"
#include "cidade.h"
#include"hashTable.h"
#include"geometria.h"

Cidade leiaGeo(char nomeDoArquivoGeo[], char nomeDoArquivoSvg[]);

void leiaQry(char prefixoArq[], char arq[], char caminhoDoArquivo[], Cidade cidade);

void leiaEc(char* arquivoEc, HashTable comercios, HashTable tiposComercio);
void leiaPm(char* arquivoPm, HashTable pessoas, HashTable moradias, HashTable moradiaPessoa);

//Retorna um vetor de retas que representam o polígono, array_size é o tamanho do vetor
//Nota: finalizar cada reta, e dar free no vetor
Reta* leiaPol(char* caminhoDoArquivo, char* nomeDoArquivoPoligono, int *array_size);
#endif