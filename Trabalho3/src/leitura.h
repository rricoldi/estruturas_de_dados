#ifndef __LEITURA_H
#define __LEITURA_H


/*
    Aqui eh onde resolvemos a parte de leitura dos arquivos .geo e .qry, decidindo quais funcoes chamar e quais procedimentos realizar
*/

#include "svg.h"
#include "qry.h"
#include "cidade.h"

Cidade leiaGeo(char nomeDoArquivoGeo[], char nomeDoArquivoSvg[]);

void leiaQry(char prefixoArq[], char arq[], Cidade cidade);


#endif