#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "svg.h"
#define NULO -1;


typedef struct no
{
   int ant;
   Info info;
   int prox;
}No;

typedef struct Vetor
{
   No *v;
   int primeiro;
   int livre;
   int ultimo;
   int capacidade;
   int tamanho;
}List;

Lista iniciaLista(int capacidade)
{
   Lista l;    //Colocar _t

   l = (List*) calloc(1, sizeof(List));
   List* lista = (List*) l;
   lista->capacidade = capacidade;
   lista->v = (No *) calloc (capacidade, sizeof(No)); //Aloca a lista

   for(int i = 0; i < capacidade - 1; i++) //Define os proximos do inicio até o penultimo
   {
      lista->v[i].prox = i + 1;
   }

   lista->v[capacidade-1].prox = NULO; //Define o proximo do ultimo

   lista->livre = 0;  //Aponta o primeiro livre
   lista->primeiro = NULO;
   lista->ultimo = NULO;
   lista->tamanho = 0;

   return lista;
}

void finalizaLista(Lista L)
{
   List* lista = (List*) L;
   if( lista->tamanho != 0)
   {
      free(lista->v);
      free(lista);
   }

}

int lenght(Lista L)
{
   List* lista = (List*) L;
   return lista->tamanho;
}

int getLivre(Lista L)
{
   List* lista = (List*) L; //CASTING LISTA para LIST
   int posLivre = lista->livre;
   lista->livre = lista->v[lista->livre].prox; //recebe o próximo livre
   return posLivre;
}

Posic insereLista(Lista L, Info info)
{
  List* lista = (List*) L; //CASTING LISTA para LIST
  int iLivre = getLivre(L); // semelhante ao malloc

  if (iLivre == -1) //verifica se a lista nao esta cheia ao ver se o livre nao e nulo
  {
     printf("A lista esta cheia\n");
     return -1;
  }
  else //se a lista tiver espaço então insere o elemento nela
  {
      lista->v[iLivre].info = info;

      //faz o encadeamento

      lista->v[iLivre].prox = NULO;
      lista->v[iLivre].ant = lista->ultimo;

      if (lista->primeiro == -1) // Se a lista for vazia define o elemento inserido como primeiro
      {
         lista->primeiro = iLivre;
      }
      else  //senao atribui o elemento atual como o proximo do elemento anterior
      {
         lista->v[lista->ultimo].prox = iLivre;
      }

      lista->ultimo = iLivre;
  }
  lista->tamanho++;

  return iLivre;
}

void removerDaLista(Lista L, Posic pos)
{
   List* lista = (List*) L;

   lista->v[pos].info = NULL; //informacao da posicao e removida

   if(lista->primeiro == pos && lista->ultimo != pos)
   {
      lista->primeiro = lista->v[pos].prox;
   }

   if(lista->ultimo == pos && lista->primeiro != pos)
   {
      lista->primeiro = lista->v[pos].ant;
   }

   lista->v[lista->v[pos].ant].prox = lista->v[pos].prox; // o proximo
   lista->v[lista->v[pos].prox].ant = lista->v[pos].ant;

   lista->v[pos].ant = lista->livre;
   lista->v[pos].prox = lista->v[lista->livre].prox;

   lista->v[lista->v[lista->livre].prox].ant = pos;
   lista->v[lista->livre].prox = pos;

   lista->tamanho--;
}

int transformaListaEmVetor(Lista L, Info vetor[])
{
   List* lista = (List*) L;

   int i = lista->primeiro;
   int contador = 0;

   while(lista->v[i].prox != -1)
   {
      vetor[contador] = lista->v[i].info;
      i = lista->v[i].prox;
      contador++;
   }
   vetor[contador] = lista->v[i].info;

   return contador;
}