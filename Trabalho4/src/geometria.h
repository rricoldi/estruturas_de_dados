#ifndef GEOMETRIA_H
#define GEOMETRIA_H

#include<stdbool.h>

/*  Aqui se encontram funções relacionadas à pontos, retas, interações entre eles e algumas contas
//  NOTA: os parametros que pedem Reta ou Ponto não podem receber NULL, nem um TAD diferente do requisitado
*/

typedef void* Reta;
typedef void* Ponto;

//  Constante usasda como epsilon na função nearlyEqual
#define double_BAIXO 0.000001

//  Retorna o tamanho em bytes da struct reta
int retaSizeof(void);

//  Verifica se a diferença entre dois a e b é negligenciavel em relação à epsilon
bool nearlyEqual(double a, double b, double epsilon);
//  Retorna a distancia entre dois pontos a e b
double distanciaPontos(Ponto a, Ponto b);
//  Retorna o ponto de intersecção entre duas retas, NULL caso não intersectem
Ponto intersecta(Reta r, Reta s);
//  Verifica se um dado ponto está entre outos dois
bool estaEntre(Ponto a, Ponto b, Ponto entre);

//  Retorna o endereço do ponto criado
Ponto criarPonto(double x, double y);
void* pontoFinalizar(Ponto);

//  Altera as coordenadas de um ponto
//  ATENÇÃO: se usado para alterar retas, os coeficientes das mesmas não serão atualizados
void setPonto(Ponto a, double x, double y);
//  As funções a seguir retornam uma das coordenadas de um ponto
double getPontoX(Ponto a);
double getPontoY(Ponto a);

//  Retorna o endereço de uma reta criada a partir de dois pontos
Reta criarReta(double x1, double y1, double x2, double y2);
void* retaFinalizar(Reta);
void retaPrint(Reta);
//  Retorna um ponto (A ou B) de uma reta
Ponto getRetaA(Reta);
Ponto getRetaB(Reta);
//  Altera um ponto (A ou B) de uma reta
void setRetaA(Reta r, double x, double y);
void setRetaB(Reta r, double x, double y);
//Retorna o tamanho da reta
double getRetaTamanho(Reta r);

//Verifica se o ponto (x,y) está contido no dado poligono
bool pontoDentroPoligono(double x, double y, Reta poligono[], int qtsLadosPoligono);

//Verifica se um dado retangulo está inteiramente dentro do polígono
//Retorna true caso esteja, false caso contrário
bool retanguloTotalDentroPoligono(Reta retangulo[], Reta poligono[], int qtdRetasDoPoligono);

//Verifica se alguma dos lados do retangulo intersecta o poligno
bool retanguloIntersectaPoligono(Reta retangulo[], Reta poligono[], int qtdRetasDoPoligono);
#endif
