#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "cidade.h"


int main()
{
    long int i;

    Cidade cidade = criaCidade(10, 10);

    Info inf = criaQuadra("012345", 198210.123, 1000, 2000, 2000);
    i = addQuadra(cidade, inf);

    Info res = getQuadra(cidade, 0);
    Quadra* info = (Quadra*) res;

    printf("quadra cep: %s\nx: %lf\ny: %lf\nw: %lf\nh: %lf", retornaQCEP(info), retornaQX(info), retornaQY(info), retornaQW(info), retornaQH(info));


    removeCidade(cidade);
    return 0;
}
