#ifndef __STRUCT_H
#define __STRUCT_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct parametros{
    int id;
    float raio;
    float x;
    float y;
    float altura;
    float largura;
	char cor1[20];
    char cor2[20];
    char type;
}par;

typedef struct figura{
    struct parametros *par;
    struct figura *prox;
}No;

#endif