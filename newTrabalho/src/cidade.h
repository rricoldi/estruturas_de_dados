#ifndef __CIDADE_H
#define __CIDADE_H

#include "lista.h"

/*  
    Aqui implementamos uma cidade onde todas as listas estao, aqui podemos inicia-las, remove-las, e eh ponte para todas as funcoes envolvendo as listas e os seus elementos 
    Tambem eh utilizada para resolver alguns problemas do Qry, e para conseguir os valores de uma determinada forma
*/

typedef void *Cidade;

Cidade criaCidade(int numeroDeFiguras, int numeroDeQuadras, int numeroDeHidrantes, int numeroDeRadios, int numeroDeSemaforos, int numeroDePredios, int numeroDeMuros);

void removeCidade(Cidade cid);

void imprimeCidade(Cidade cid, char nomeDoArquivoSvg[]);

#endif