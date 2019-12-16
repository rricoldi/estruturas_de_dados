#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include"geometria.h"
#include"qry.h"

double svgXMax = -1;
double svgYMax = -1;

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
double distanciaPontosD(double x1, double y1, double x2, double y2){
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
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
    return c;
}
struct ponto *interCasoB(struct reta *r, struct reta *s){
    struct ponto *c = malloc(sizeof(struct ponto));
    c->x = r->cl;
    c->y = s->ca*r->cl + s->cl;
    return c;
}
struct ponto *interCasoC(struct reta* r, struct reta* s){
    struct ponto *c = malloc(sizeof(struct ponto));
    if(estaEntre(&(r->A), &(s->B), &(r->B))){
        c = &(s->B);
        return c;
    }
    c = &(s->A);
    return c;
}
//Retorna 0 se colinear, 1 se horário, -1 se anti-horário
int orientacao(struct ponto *a, struct ponto *b, struct ponto *c){
    double val = (b->y - a->y)*(c->x - b->x) - (b->x - a->x)*(c->y - b->y);
    if(val == 0)
        return 0;
    if(val > 0)
        return 1;
    return -1;
}
int verificaOrientacao(Ponto aa, Ponto bb, Ponto cc){
    struct ponto *a=aa, *b=bb, *c=cc;
    return orientacao(a, b, c);
}
bool doIntersect(struct ponto* p1, struct ponto* q1, struct ponto* p2, struct ponto* q2){
    int o1 = orientacao(p1, q1, p2);
    int o2 = orientacao(p1, q1, q2);
    int o3 = orientacao(p2, q2, p1);
    int o4 = orientacao(p2, q2, q1);
    
    if(o1 != o2 && o3 != o4)
        return true;
    if(o1==0 && estaEntre(p1, p2, q1))
        return true;
    if(o2==0 && estaEntre(p1, q2, q1))
        return true;
    if(o3==0 && estaEntre(p2, p1, q2))
        return true;
    if(o4==0 && estaEntre(p2, q1, q2))
        return true;
    return false;
}
Ponto intersecta(Reta rr, Reta ss){
    struct reta *r = rr;
    struct reta *s = ss;
    bool inter = doIntersect(&(r->A), &(r->B), &(s->A), &(s->B));
    if(inter){
        if(r->ca != INFINITY && s->ca != INFINITY)
            return interCasoA(r, s);
        if(r->ca == INFINITY && s->ca != INFINITY)
            return interCasoB(r, s);
        if(s->ca == INFINITY && r->ca != INFINITY)
            return interCasoB(s, r);
        return interCasoC(r, s);
    }
    return NULL;
}
bool estaEntre(Ponto aa, Ponto bb, Ponto cc){
    if(pontosIguais(aa, bb)){
        return false;
    }
    struct ponto *a = aa;
    struct ponto *b = bb;
    struct ponto *c = cc;
    if(b->x <= max(a->x, c->x) && b->x >= max(a->x, c->x) &&
       b->y <= max(a->y, c->y) && b->y >= max(a->y, c->y))
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
bool retaMenor(Reta rr, Reta ss){
    struct reta *r=rr;
    struct reta *s=ss;
    if(distanciaPontos(&(r->A), &(r->B)) < distanciaPontos(&(s->A), &(s->B)))
        return true;
    return false;
}
double comparaReta(Reta rr, Reta ss){
    struct reta *r=rr;
    struct reta *s=ss;
    if(r->A.x != s->A.x){
        return (r->A.x - s->A.x);
    }
    return 0;
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
void retaPrintSvg(Reta rr, FILE* svg){
    struct reta *r = rr;
    fprintf(svg, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:rgb(255,0,0);stroke-width:2\" />", r->A.x, r->A.y, r->B.x, r->B.y);
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

bool pontoDentroPoligono(double x, double y, Reta* polig, int tamPolig){
    struct reta *reta = criarReta(x, y, x+svgXMax, y);
    int qtdInterseccoes=0;

    for(int i=0;i<tamPolig;i++){
        if(intersecta(reta, polig[i]))
            qtdInterseccoes++;
    }
    retaFinalizar(reta);

    if(qtdInterseccoes%2 == 1){
        return true;
    }else{
        return false;
    }
    

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
        struct reta *s = criarReta(r->A.x, r->A.y, svgXMax, r->A.y);
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