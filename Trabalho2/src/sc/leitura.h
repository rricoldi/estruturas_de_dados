#ifndef __LEITURA_H
#define __LEITURA_H

#include "cidade.h"
#include "svg.h"

Cidade leiaGeo(char arq[], char svg[]);

void leiaQry(char prefixoArq[], char arq[], Cidade cidade);

#endif