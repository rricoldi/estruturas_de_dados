#ifndef __LEITURA_H
#define __LEITURA_H


/*
    Aqui eh onde resolvemos a parte de leitura dos arquivos .geo e .qry, decidindo quais funcoes chamar e quais procedimentos realizar
*/

#include "svg.h"
#include "qry.h"
#include "cidade.h"
#include"hashTable.h"

Cidade leiaGeo(char nomeDoArquivoGeo[], char nomeDoArquivoSvg[]);

void leiaQry(char prefixoArq[], char arq[], Cidade cidade);

void leiaEc(char* arquivoEc, HashTable comercios, HashTable tiposComercio);
void leiaPm(char* arquivoPm, HashTable pessoas, HashTable moradias, HashTable moradiaPessoa);
#endif