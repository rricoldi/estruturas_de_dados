#ifndef __LEITURA_H
#define __LEITURA_H


/*
    Aqui eh onde resolvemos a parte de leitura dos arquivos .geo e .qry, decidindo quais funcoes chamar e quais procedimentos realizar
*/

#include "cidade.h"
#include "svg.h"

Cidade leiaGeo(char arq[], char svg[]);

void leiaQry(char prefixoArq[], char arq[], Cidade cidade);

#endif