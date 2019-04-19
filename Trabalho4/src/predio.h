#ifndef __PREDIO_H
#define __PREDIO_H


typedef void *Predio;

Predio criarPredio(char cep[20], char face[10], double numero, double frente, double profundidade, double calcada, double x, double y, double xCalcada, double xCalcadaMax, double yCalcada, double yCalcadaMax, double xNum, double yNum);

double retornaPX(Predio p);

double retornaPY(Predio p);

char *retornaPCep(Predio p);

char *retornaPFace(Predio p);

double retornaPNumero(Predio p);

double retornaPFrente(Predio p);

double retornaPProfundidade(Predio p);

double retornaPCalcada(Predio p);

double retornaPXCalcada(Predio p);

double retornaPYCalcada(Predio p);

double retornaPXCalcadaMax(Predio p);

double retornaPYCalcadaMax(Predio p);

double retornaPXNum(Predio p);

double retornaPYNum(Predio p);

double retornaPWidth(Predio);
double retornaPHeight(Predio);
double comparaPredio(Predio p1, Predio p2);

#endif