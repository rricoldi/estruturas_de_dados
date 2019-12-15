#ifndef __CIRCULO_H
#define __CIRCULO_H

/*
    Aqui temos a forma do circulo, definimos um void pointer para podermos acessar os atributos desta forma apenas a partir das funcoes retornaC...
*/

typedef void *Circulo;

//Cria um circulo com as caracteristicas passadas;
//Pré-requisito: as características existem;
//Pós condição: círculo criado;
Circulo criarCirculo(char id[20], char corBorda[20], char corPreenchimento[20], double raio, double x, double y, double espessura);
void circuloFinalizar(Circulo);

//Getters dos atributos do círculo;
//Pré-requisito: círculos existem;
//Pós condição: -.
double retornaCX(Circulo c);
double retornaCY(Circulo c);
double retornaCR(Circulo c);
double retornaCEspessura(Circulo c);
char *retornaCID(Circulo c);
char *retornaCCorP(Circulo c);
char *retornaCCorB(Circulo c);

//Verifica se dois círculos representam o mesmo objeto;
//Pré-requisito: círculos existem;
//Pós condição: -.
double comparaCirculo(Circulo c1, Circulo c2);
//Imprime as características do círuclo no cmd;
//Pré-requisto: Círculo existe;
//Pós condição: círculo impresso;
void imprime(Circulo c);

//Imprime o círculo no svg;
//Pré-requisto: Círculo existe;
//Pós condição: círculo impresso;
void imprimeCirculos(Circulo circulo, char nomeDoArquivoSvg[], char cor[]);
#endif