#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
 
#define NULO -1;

typedef struct no
{
   int ant;
   Info info;  
   int prox; 
}No;

typedef struct VetorQ
{
   No *v;
   int primeiro;
   int livre;
   int ultimo;
   int capacidade;
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

   return lista;
}

void finalizaLista(Lista L)
{
   List* lista = (List*) L;
   
   free(lista->v);
   free(lista);
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
     printf("A lista esta cheia, nao e possivel colocar mais elementos!\n !!!!Retornando NULO!!!!\n");
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

  return iLivre;
}

// 1 2 4 5
// 6 3 7 8 9
void removeLista(Lista L, Posic pos)
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
}

Info get(Lista L, Posic pos)
{
   List* lista = (List*) L;
   return lista->v[pos].info;
}



Info procuraLista(Lista L, char cep[])
{
   List* lista = (List*) L;
   
   int i = lista->primeiro;
   

   while(lista->v[i].prox != -1)
   {

      Info informacao = lista->v[i].info;
      
      
      if(strcmp(retornaQCEP(informacao), cep))
      {
         return informacao; 
      }
      else if(strcmp(retornaHID(informacao), cep))
      {
         return informacao; 
      }
      else if(strcmp(retornaSID(informacao), cep))
      {
         return informacao; 
      }
      else if(strcmp(retornaRID(informacao), cep))
      {
         return informacao; 
      }
      else if(strcmp(retornaCID(informacao), cep))
      {
         return informacao; 
      }
      else if(strcmp(retornaReID(informacao), cep))
      {
         return informacao; 
      }
      
      i = lista->v[i].prox;
   }
   printf("Nao foi possivel encontrar o elemento, retornando inicio!!\n");

   return lista->v[lista->primeiro].info;
}
