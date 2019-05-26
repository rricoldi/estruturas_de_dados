#include <stdlib.h>
#include "cidade.h"

typedef struct city
{
    Lista listaC;
    Lista listaRe;
    Lista listaQ;
    Lista listaH;
    Lista listaR;
    Lista listaS;
}cidade;

Cidade criaCidade(int nx, int nq, int nh, int nr, int ns)
{
    Cidade c = calloc(1, sizeof(cidade));
    cidade* city = (cidade*) c;
    city->listaC = iniciaLista(nx);
    city->listaRe = iniciaLista(nx);
    city->listaQ = iniciaLista(nq);
    city->listaH = iniciaLista(nh);
    city->listaR = iniciaLista(nr);
    city->listaS = iniciaLista(ns);

    return city;
}

void removeCidade(Cidade cid)
{
    cidade* city = (cidade*) cid;
    finalizaLista(city->listaC);
    finalizaLista(city->listaRe);
    finalizaLista(city->listaQ);
    finalizaLista(city->listaH);
    finalizaLista(city->listaR);
    finalizaLista(city->listaS);
    
    free(city);
}

int addCirculo(Cidade cid, Info info)
{
    cidade* city = (cidade *) cid;
    return insereLista(city->listaC, info);
}

Circulo getCirculo(Cidade cid, int i)
{
    cidade* city = (cidade *) cid;
    return get(city->listaC, i);
}

int addRetangulo(Cidade cid, Info info)
{
    cidade* city = (cidade *) cid;
    return insereLista(city->listaRe, info);
}

Retangulo getRetangulo(Cidade cid, int i)
{
    cidade* city = (cidade *) cid;
    return get(city->listaRe, i);
}

int addQuadra(Cidade cid, Info info)
{
    cidade* city = (cidade *) cid;
    return insereLista(city->listaQ, info);
}

Quadra getQuadra(Cidade cid, int i)
{
    cidade* city = (cidade *) cid;
    return get(city->listaQ, i);
}

int addHidrante(Cidade cid, Info info)
{
    cidade* city = (cidade *) cid;
    return insereLista(city->listaH, info);
}

Hidrante getHidrante(Cidade cid, int i)
{
    cidade* city = (cidade *) cid;
    return get(city->listaH, i);
}

int addRadio(Cidade cid, Info info)
{
    cidade* city = (cidade *) cid;
    return insereLista(city->listaR, info);
}

Radio getRadio(Cidade cid, int i)
{
    cidade* city = (cidade *) cid;
    return get(city->listaR, i);
}

int addSemaforo(Cidade cid, Info info)
{
    cidade* city = (cidade *) cid;
    return insereLista(city->listaS, info);
}

Semaforo getSemaforo(Cidade cid, int i)
{
    cidade* city = (cidade *) cid;
    return get(city->listaS, i);
}
