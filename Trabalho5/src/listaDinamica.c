#include <stdio.h>
#include <stdlib.h>
#include "listaDinamica.h"

typedef struct no {
    struct no *prox;
    char id[100];
    double x, y;
} No;

typedef struct lista {
    struct no *inicio;
    int tamanho;
} Listaligada;

List* criaLista() {
    Listaligada *lista = (Listaligada*)malloc(sizeof(Listaligada));
    lista->inicio = NULL;
    lista->tamanho = 0;
    return lista;
}

void criaNoListaDinamica(List* list, char id[], double x, double y) {
    Listaligada* lista = (Listaligada*) list;
    No *no = (No*)malloc(sizeof(No));
    strcpy(no->id, id);
    no->x = x;
    no->y = y;
    no->prox = NULL;

    if (lista->inicio == NULL){        
        lista->inicio = no;
    }
    else
    {
        No* aux = lista->inicio;
        while(1){
            if(aux->prox == NULL){
                aux->prox = no;
                break;
            }
            else{
                aux = aux->prox;
            }
        }
    }   

    lista->tamanho++;
}

void excluirLista(List* list) {
    Listaligada* lista = (Listaligada*) list;
    No* no = lista->inicio;
    No* aux;
    
    while(no != NULL) {
        aux = no->prox;
        free(no);
        no = aux;
    }

    free(lista);
}

int getTamanho(List* list) {
    Listaligada* lista = (Listaligada*) list;
    return lista->tamanho;
}

void insereVertice(Graph grafo, List list) {
    Listaligada* lista = (Listaligada*) list;
    No* no = lista->inicio;
    int i = 0;
    
    while(no != NULL) {
        defineInfoVertice(grafo, i, no->id, no->x, no->y);
        i++;
        no = no->prox;
    }

    excluirLista(list);
}