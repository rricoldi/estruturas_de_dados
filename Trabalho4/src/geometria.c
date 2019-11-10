#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include"geometria.h"

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

struct ponto *interCasoA(struct reta *r, struct reta *s){
    struct ponto *c = malloc(sizeof(struct ponto));     //ponto de intersecção das retas
    c->x = (s->cl - r->cl)/(r->ca - s->ca);
    c->y = (r->cl*s->ca - s->cl*r->ca)/(s->ca - r->ca);
    if(estaEntre(&(r->A), &(r->B), c) && estaEntre(&(s->A), &(s->B), c))
        return c;
    else
        return NULL;
}
struct ponto *interCasoB(struct reta *r, struct reta *s){
    struct ponto *c = malloc(sizeof(struct ponto));
    c->x = r->cl;
    c->y = s->ca*r->cl + s->cl;
    if(estaEntre(&(r->A), &(r->B), c) && estaEntre(&(s->A), &(s->B), c))
        return c;
    else
        return NULL;
}
Ponto intersecta(Reta rr, Reta ss){
    struct reta *r = rr;
    struct reta *s = ss;
    if(nearlyEqual(r->ca, s->ca, double_BAIXO))
        return NULL;
    else
        if(r->ca != INFINITY && s->ca != INFINITY)
            return interCasoA(r, s);
        else
            if(r->ca == INFINITY)
                return interCasoB(r, s);
            else
                return interCasoB(s, r);
}
bool estaEntre(Ponto aa, Ponto bb, Ponto cc){
    struct ponto *a = aa;
    struct ponto *b = bb;
    struct ponto *c = cc;
    double distAB = distancia(a, b);
    double distAC = distancia(a, c);
    double distBC = distancia(b, c);
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
    r->B.x = x1;
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
  return distancia(&(r->A), &(r->B));
}
