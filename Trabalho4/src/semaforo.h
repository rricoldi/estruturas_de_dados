#ifndef __SEMAFORO_H
#define __SEMAFORO_H

/*
    Aqui temos o semaforo, definimos um void pointer para podermos acessar os atributos deste equipamento urbano apenas a partir das funcoes retornaS... e setS...
    Eh reresentada por um retangulo comprido    
*/


typedef void *Semaforo;

Semaforo criarSemaforo(char id[20], char corB[20], char corP[20], double x, double y, double espessura);
void semaforoFinalizar(Semaforo);

double retornaSX(Semaforo s);

void setSX(Semaforo s, double x);

double retornaSY(Semaforo s);

void setSY(Semaforo s, double y);

double retornaSEspessura(Semaforo s);

char *retornaSID(Semaforo s);

char *retornaSCorP(Semaforo s);

char *retornaSCorB(Semaforo s);

double comparaSemaforo(Semaforo s1, Semaforo s2);

void navegaSemaforo(Semaforo sem);

void imprimirSemaforoDaArvore(Semaforo *sem, FILE *arquivoSVG, int x, int y, char cor);

#endif