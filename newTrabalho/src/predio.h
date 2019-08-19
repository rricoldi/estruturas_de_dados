#ifndef __PREDIO_H
#define __PREDIO_H


typedef void *Predio;

Predio criarPredio(char cep[20], char face[10], char numero[20], double frente, double profundidade, double calcada);

double retornaPX(Predio r);

void setPX(Predio r, double x);

double retornaPY(Predio r);

void setPY(Predio r, double y);

double retornaPEspessura(Predio r);

char *retornaPID(Predio r);

char *retornaPCorP(Predio r);

char *retornaPCorB(Predio r);

#endif