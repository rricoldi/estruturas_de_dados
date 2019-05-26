#include "struct.h"
#include "svg.h"
#include "qry.h"
#include "leitura.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

No *iniciar(){
	printf("lista inicializada\n");
    return NULL;
}

No *inserir(No *inicio, int id, float raio, float x, float y, float altura, float largura, char cor1[], char cor2[], char type){

    No *aux, *aux2;

	par *parametros = (par*) malloc(sizeof(par));
	parametros->id = id;
	parametros->x = x;
	parametros->y = y;
	parametros->raio = raio;
	parametros->altura = altura;
	parametros->largura = largura;
	strcpy(parametros->cor1,cor1);
	strcpy(parametros->cor2,cor2);
	parametros->type = type;

    if(inicio == NULL)
    {
        inicio = malloc(sizeof(No));
        inicio->par = parametros;
        inicio->prox = NULL;
    }
    else
    {
		aux = inicio;
    
	    while(aux->prox != NULL)
            aux = aux->prox;

        aux2 = malloc(sizeof(No));
        aux2->par = parametros;
        aux2->prox = NULL;
        aux->prox = aux2;
    }

    return inicio;
}

No *buscar(No *inicio, int num){
	No *aux;
	aux = inicio;

	struct parametros *par;
	
	while(aux != NULL){
		par = aux->par;
		if(par->id == num){
			return aux;
		}
		aux = aux->prox;
	}
	
	return NULL;
}

void desalocar(No *inicio){
	No *aux;
	aux = inicio;
	
	while(aux != NULL){
		inicio = inicio->prox;
		free(aux);
		aux = inicio;
	}
}
