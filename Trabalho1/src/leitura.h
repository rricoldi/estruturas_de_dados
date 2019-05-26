#ifndef __LEITURA_H
#define __LEITURA_H

#include "struct.h"

//Le o arquivo Geo
No *leiaGeo(char arq[], No *inicio, char svg[]);

//Le o arquivo Qry
void leiaQry(char prefixoArq[], char arq[], No *inicio);

#endif