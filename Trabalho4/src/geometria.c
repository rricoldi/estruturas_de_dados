#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include"geometria.h"

#define SvgXMax 5000

struct ponto{
    double x;
    double y;
};

struct reta{
    double ca;           //coeficiente angular
    double cl;           //coeficiente linear
    struct ponto A;
    struct ponto B;
};

int retaSizeof(void){
  return sizeof(struct reta);
}

bool nearlyEqual(double a, double b, double epsilon){
    double absA = fabs(a);
    double absB = fabs(b);
    double dif = fabs(absA - absB);

    if(absA == absB)
        return true;
    else
        if(dif < epsilon)
            return true;
        else
            return false;
}
double distanciaPontos(Ponto aa, Ponto bb){
    struct ponto *a = aa;
    struct ponto *b = bb;
    return sqrt((a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y));
}

bool pontosIguais(Ponto aa, Ponto bb){
    struct ponto *a = aa;
    struct ponto *b = bb;
    if(a->x == b->x  && a->y == b->y){
        return true;
    }else{
        return false;
    }
}
struct ponto *interCasoA(struct reta *r, struct reta *s){
    struct ponto *c = malloc(sizeof(struct ponto));     //ponto de intersecção das retas
    c->x = (s->cl - r->cl)/(r->ca - s->ca);
    c->y = (r->cl*s->ca - s->cl*r->ca)/(s->ca - r->ca);
    if(pontosIguais(&r->A, c) || pontosIguais(&r->B, c) || pontosIguais(&s->A, c) || pontosIguais(&s->B, c)){
        pontoFinalizar(c);
        return NULL;
    }
    if(estaEntre(&(r->A), &(r->B), c) && estaEntre(&(s->A), &(s->B), c)){
        pontoFinalizar(c);
        return c;
    }
    else{
        pontoFinalizar(c);
        return NULL;
    }
}
struct ponto *interCasoB(struct reta *r, struct reta *s){
    struct ponto *c = malloc(sizeof(struct ponto));
    c->x = r->cl;
    c->y = s->ca*r->cl + s->cl;
    if(pontosIguais(&r->A, c) || pontosIguais(&r->B, c) || pontosIguais(&s->A, c) || pontosIguais(&s->B, c)){
        pontoFinalizar(c);
        return NULL;
    }
    if(estaEntre(&(r->A), &(r->B), c) && estaEntre(&(s->A), &(s->B), c)){
        pontoFinalizar(c);
        return c;
    }
    else{
        pontoFinalizar(c);
        return NULL;
    }
}
Ponto intersecta(Reta rr, Reta ss){
    struct reta *r = rr;
    struct reta *s = ss;
    if(nearlyEqual(r->ca, s->ca, double_BAIXO)){
        return NULL;
    }
    else{
        if(r->ca != INFINITY && s->ca != INFINITY){
            return interCasoA(r, s);
        }
        else{
            if(r->ca == INFINITY){
                return interCasoB(r, s);
            }
            else{
                return interCasoB(s, r);
            }
        }
    }
}
bool estaEntre(Ponto aa, Ponto bb, Ponto cc){
    if(pontosIguais(aa, bb)){
        return false;
    }
    struct ponto *a = aa;
    struct ponto *b = bb;
    struct ponto *c = cc;
    double distAB = distanciaPontos(a, b);
    double distAC = distanciaPontos(a, c);
    double distBC = distanciaPontos(b, c);
    if(nearlyEqual(distAB, distAC+distBC, double_BAIXO))
        return true;
    else
        return false;
}

void* criarPonto(double x, double y){
    struct ponto *a = malloc(sizeof(struct ponto));
    a->x = x;
    a->y = y;
    return a;
}
void* pontoFinalizar(Ponto ponto){
    struct ponto *p = (struct ponto*) ponto;
    free(p);
    p = NULL;
    return p;
}

void printPonto(Ponto aa){
    struct ponto *a = aa;
    printf("%lf %lf\n", a->x, a->y);
}
void setPonto(Ponto aa, double x, double y){
    struct ponto *a = aa;
    a->x = x;
    a->y = y;
}
double getPontoX(Ponto aa){
  struct ponto *a = aa;
  return a->x;
}
double getPontoY(Ponto aa){
  struct ponto *a = aa;
  return a->y;
}

struct reta *setRetaCoeficientes(struct reta *r, double x1, double y1, double x2, double y2){
    if(nearlyEqual(x1, x2, double_BAIXO)){
        r->ca = INFINITY;
        r->cl = x1;
    }
    else{
        r->ca = (y1 - y2)/(x1 - x2);
        r->cl = y1 - (x1*r->ca);
    }
    return r;
}
Reta criarReta(double x1, double y1, double x2, double y2){
    struct reta *r = malloc(sizeof(struct reta));
    r->A.x = x1;
    r->A.y = y1;
    r->B.x = x2;
    r->B.y = y2;
    setRetaCoeficientes(r, x1, y1, x2, y2);
    return r;
}
void* retaFinalizar(Reta rr){
    struct reta* r = (struct reta*) rr;
    free(r);
    r = NULL;
    return r;
}
void retaPrint(Reta rr){
    struct reta *r = (struct reta*)rr;
    printf("%lf %lf, %lf %lf\n", r->A.x, r->A.y, r->B.x, r->B.y);
}
void setRetaA(Reta rr, double x, double y){
    struct reta *r = rr;
    setRetaCoeficientes(r, x, y, r->B.x, r->B.y);
    setPonto(&(r->A), x, y);
}
void setRetaB(Reta rr, double x, double y){
    struct reta *r = rr;
    setRetaCoeficientes(r, r->A.x, r->A.y, x, y);
    setPonto(&(r->B), x, y);
}
Ponto getRetaA(Reta rr){
    struct reta *r = rr;
    return &(r->A);
}
Ponto getRetaB(Reta rr){
    struct reta *r = rr;
    return &(r->B);
}
double getRetaTamanho(Reta rr){
  struct reta *r = rr;
  return distanciaPontos(&(r->A), &(r->B));
}

//Para cada reta do poligono, verifica se há interseccao com a reta dada
bool retaInterPoligono(Reta rr, Reta poligono[], int tamPolig){
    for(int i=0;i<tamPolig;i++){
        if(intersecta(rr, poligono[i]) != NULL){
            return true;
        }
    }
    return false;
}
bool retanguloTotalDentroPoligono(Reta retangulo[], Reta poligono[], int tamPolig){
    //Se qualquer reta do retangulo intersectar o poligono ao menos uma vez,
    //isso indica que o retangulo nao esta totalmente contido no poligono
    for(int i=0;i<4;i++){
        if(retaInterPoligono(retangulo[i], poligono, tamPolig)){
            return false;
        }
    }
    //Cria uma reta de um ponto qualquer do retangulo até o "infinito",
    //e conta quantas vezes ela intersecta o poligono
    int qtdInterseccoes;
    for(int j=0;j<4;j++){
        qtdInterseccoes=0;
        struct reta *r = (struct reta*)retangulo[j];
        struct reta *s = criarReta(r->A.x, r->A.y, SvgXMax, r->A.y);
        for(int i=0;i<tamPolig;i++){
            if(intersecta(s, poligono[i])){
                qtdInterseccoes++;
            }
        }
        retaFinalizar(s);
        if(qtdInterseccoes%2==1)
            return true;
    }
    return false;
}
bool retanguloIntersectaPoligono(Reta retangulo[], Reta poligono[], int tamPolig){
    for(int i=0;i<4;i++){
        if(retaInterPoligono(retangulo[i], poligono, tamPolig)){
            return true;
        }
    }
    return false;
}