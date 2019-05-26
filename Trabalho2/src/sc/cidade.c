#include <stdlib.h>
#include "cidade.h"

typedef struct city
{
    Lista listaQ;
    Lista listaH;
    Lista listaR;
    Lista listaS;
}cidade;

Cidade criaCidade(long int nq, long int nh, long int nr, long int ns)
{
    Cidade c = calloc(1, sizeof(cidade));
    cidade* city = (cidade*) c;
    city->listaQ = iniciaLista(nq);
    city->listaH = iniciaLista(nh);
    city->listaR = iniciaLista(nr);
    city->listaS = iniciaLista(ns);

    return city;
}

void removeCidade(Cidade cid)
{
    cidade* city = (cidade*) cid;
    finalizaLista(city->listaQ);
    finalizaLista(city->listaH);
    finalizaLista(city->listaR);
    finalizaLista(city->listaS);
    
    free(city);
}

int addQuadra(Cidade cid, Info info)
{
    cidade* city = (cidade *) cid;
    return insereLista(city->listaQ, info);
}

Quadra getQuadra(Cidade cid, long int i)
{
    cidade* city = (cidade *) cid;
    return get(city->listaQ, i);
}

int addHidrante(Cidade cid, Info info)
{
    cidade* city = (cidade *) cid;
    return insereLista(city->listaH, info);
}

Hidrante getHidrante(Cidade cid, long int i)
{
    cidade* city = (cidade *) cid;
    return get(city->listaH, i);
}

int addRadio(Cidade cid, Info info)
{
    cidade* city = (cidade *) cid;
    return insereLista(city->listaR, info);
}

Radio getRadio(Cidade cid, long int i)
{
    cidade* city = (cidade *) cid;
    return get(city->listaR, i);
}

int addSemaforo(Cidade cid, Info info)
{
    cidade* city = (cidade *) cid;
    return insereLista(city->listaS, info);
}

Semaforo getSemaforo(Cidade cid, long int i)
{
    cidade* city = (cidade *) cid;
    return get(city->listaS, i);
}
