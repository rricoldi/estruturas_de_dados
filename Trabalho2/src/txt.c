#include "txt.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void iniciaTxt(char txt[])
{
    FILE *arqout;
    
    arqout = fopen(txt, "w");
    if (arqout == NULL)
    { 
        printf("Nao foi possivel iniciar o arquivo txt");
        exit(1);
    }

    fclose(arqout);
}

