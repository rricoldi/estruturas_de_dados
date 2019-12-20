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
extern double svgXMax;
extern double svgYMax;
#define M_PI 3.14159265358979323846

//  Retorna o tamanho em bytes da struct reta
int retaSizeof(void);
int pontoSizeof(void);

//  Verifica se a diferença entre dois a e b é negligenciavel em relação à epsilon
bool nearlyEqual(double a, double b, double epsilon);
//  Retorna a distancia entre dois pontos a e b
double distanciaPontos(Ponto a, Ponto b);
double distanciaPontosD(double x1, double y1, double x2, double y2);

//  Verifica como os 3 pontos estão orientados
//  Retorna 0 caso sejam colineares, 1 para sentido horário, -1 para sentido anti-horário
int verificaOrientacao(Ponto, Ponto, Ponto);
//  Retorna o ponto de intersecção entre duas retas, NULL caso não intersectem
//  CHAMAR A FUNÇÃO pontoFinalizar CASO O RETORNO NÃO SEJA NULL
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
//Retorna true caso 'r' seja menor que 's'
bool retaMenor(Reta r, Reta s);
double comparaReta(Reta, Reta);
void* retaFinalizar(Reta);
void retaPrint(Reta);
void retaPrintSvg(Reta, FILE*);
//  Retorna um ponto (A ou B) de uma reta
Ponto getRetaA(Reta);
Ponto getRetaB(Reta);
//  Altera um ponto (A ou B) de uma reta
void setRetaA(Reta r, double x, double y);
void setRetaB(Reta r, double x, double y);
//Retorna o tamanho da reta
double getRetaTamanho(Reta r);

//Para cada reta do poligono, verifica se há interseccao com a reta dada
bool retaInterPoligono(Reta rr, Reta poligono[], int tamPolig);
bool retaDentroPoligono(Reta rr, Reta poligono[], int tampoligono);
//Verifica se o ponto (x,y) está contido no dado poligono
bool pontoDentroPoligono(double x, double y, Reta poligono[], int qtsLadosPoligono);

//Verifica se um dado retangulo está inteiramente dentro do polígono
//Retorna true caso esteja, false caso contrário
bool retanguloTotalDentroPoligono(Reta retangulo[], Reta poligono[], int qtdRetasDoPoligono);

//Verifica se alguma dos lados do retangulo intersecta o poligno
bool retanguloIntersectaPoligono(Reta retangulo[], Reta poligono[], int qtdRetasDoPoligono);
#endif
