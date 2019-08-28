#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
// #include "qry.h"
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
   
   free(lista->v);
   free(lista);
}


void imprimeCirculos(Lista L, char nomeDoArquivoSvg[])
{
   FILE *arq;

   arq = fopen(nomeDoArquivoSvg, "a");
   if (arq == NULL){
      printf("Erro ao abrir o arquivo de saida");
      exit(1);
   }
   List* lista = (List*) L;

   int i = lista->primeiro;
   Circulo circulo;

   while(lista->v[i].prox != -1)
   {
      circulo = lista->v[i].info;

      imprimirCirculo(retornaCR(circulo), retornaCX(circulo), retornaCY(circulo), retornaCCorB(circulo), retornaCCorP(circulo), nomeDoArquivoSvg, retornaCEspessura(circulo));

      i = lista->v[i].prox;
   }

   circulo = lista->v[i].info;

   imprimirCirculo(retornaCR(circulo), retornaCX(circulo), retornaCY(circulo), retornaCCorB(circulo), retornaCCorP(circulo), nomeDoArquivoSvg, retornaCEspessura(circulo));

   fclose(arq);
}


void imprimeRetangulos(Lista L, char nomeDoArquivoSvg[])
{
   FILE *arq;
   arq = fopen(nomeDoArquivoSvg, "a");
   if (arq == NULL){
      printf("Erro ao abrir o arquivo de saida");
      exit(1);
   }
   List* lista = (List*) L;

   int i = lista->primeiro;
   Retangulo retangulo;

   while(lista->v[i].prox != -1)
   {
      retangulo = lista->v[i].info;

    	imprimirRetangulo(retornaReW(retangulo), retornaReH(retangulo), retornaReX(retangulo), retornaReY(retangulo), retornaReCorB(retangulo), retornaReCorP(retangulo), nomeDoArquivoSvg, retornaReEspessura(retangulo));

      i = lista->v[i].prox;
   }

   retangulo = lista->v[i].info;

   imprimirRetangulo(retornaReW(retangulo), retornaReH(retangulo), retornaReX(retangulo), retornaReY(retangulo), retornaReCorB(retangulo), retornaReCorP(retangulo), nomeDoArquivoSvg, retornaReEspessura(retangulo));
    	
   fclose(arq);
}


void imprimeQuadras(Lista L, char nomeDoArquivoSvg[])
{
   List* lista = (List*) L;

   int i = lista->primeiro;
   Quadra quadra;

   while(lista->v[i].prox != -1)
   {
      quadra = lista->v[i].info;

      imprimirRetangulo(retornaQW(quadra), retornaQH(quadra), retornaQX(quadra), retornaQY(quadra), retornaQCorB(quadra), retornaQCorP(quadra), nomeDoArquivoSvg, retornaQEspessura(quadra));

      i = lista->v[i].prox;
   }

   quadra = lista->v[i].info;

   imprimirRetangulo(retornaQW(quadra), retornaQH(quadra), retornaQX(quadra), retornaQY(quadra), retornaQCorB(quadra), retornaQCorP(quadra), nomeDoArquivoSvg, retornaQEspessura(quadra));
}


void imprimeHidrantes(Lista L, char nomeDoArquivoSvg[])
{
   List* lista = (List*) L;

   int i = lista->primeiro;
   Hidrante hidrante;

   while(lista->v[i].prox != -1)
   {
      hidrante = lista->v[i].info;

      imprimirCirculo(2, retornaHX(hidrante), retornaHY(hidrante), retornaHCorB(hidrante), retornaHCorP(hidrante), nomeDoArquivoSvg, retornaHEspessura(hidrante));

      i = lista->v[i].prox;
   }

   hidrante = lista->v[i].info;

   imprimirCirculo(2, retornaHX(hidrante), retornaHY(hidrante), retornaHCorB(hidrante), retornaHCorP(hidrante), nomeDoArquivoSvg, retornaHEspessura(hidrante));
}


void imprimeSemaforos(Lista L, char nomeDoArquivoSvg[])
{
   List* lista = (List*) L;

   int i = lista->primeiro;
   Semaforo semaforo;

   while(lista->v[i].prox != -1)
   {
      semaforo = lista->v[i].info;

      imprimirRetangulo(7, 18, retornaSX(semaforo), retornaSY(semaforo), retornaSCorB(semaforo), retornaSCorP(semaforo), nomeDoArquivoSvg, retornaSEspessura(semaforo));

      i = lista->v[i].prox;
   }

   semaforo = lista->v[i].info;

   imprimirRetangulo(7, 18, retornaSX(semaforo), retornaSY(semaforo), retornaSCorB(semaforo), retornaSCorP(semaforo), nomeDoArquivoSvg, retornaSEspessura(semaforo));
}


void imprimeRadios(Lista L, char nomeDoArquivoSvg[])
{
   List* lista = (List*) L;

   int i = lista->primeiro;
   Radio radio;

   while(lista->v[i].prox != -1)
   {
      radio = lista->v[i].info;

      imprimirElipse(nomeDoArquivoSvg, retornaRX(radio), retornaRY(radio), 5, 15, retornaSCorP(radio), retornaSCorB(radio), retornaSEspessura(radio));

      i = lista->v[i].prox;
   }

   radio = lista->v[i].info;

   imprimirElipse(nomeDoArquivoSvg, retornaRX(radio), retornaRY(radio), 5, 15, retornaSCorP(radio), retornaSCorB(radio), retornaSEspessura(radio));
}

int lenght(Lista L)
{
   List* lista = (List*) L;
   return lista->tamanho;
}

Posic getFirst(Lista L)
{
   List* lista = (List*) L;
   if(lenght(lista) == 0)
      return NULO;
   return lista->primeiro;
}

Posic getLast(Lista L)
{
   List* lista = (List*) L;
   if(lenght(lista) == 0)
      return NULO;
   return lista->ultimo;
}

Posic getNext(Lista L, Posic p)
{
   List* lista = (List*) L;
   if(lista->ultimo == p)
      return NULO;
   return lista->v[p].prox;
}

Posic getPrevious(Lista L, Posic p)
{
   List* lista = (List*) L;
   if(lista->primeiro == p)
      return NULO;
   return lista->v[p].ant;
}

int getLivre(Lista L)
{
   List* lista = (List*) L; //CASTING LISTA para LIST
   int posLivre = lista->livre;
   lista->livre = lista->v[lista->livre].prox; //recebe o próximo livre
   return posLivre;
}

Posic insertBefore(Lista L, Info info, Posic posicao)
{
   List* lista = (List*) lista;
   int iLivre = getLivre(L);

   lista->v[iLivre].info = info;

   lista->v[iLivre].prox = posicao;
   lista->v[iLivre].ant = lista->v[posicao].ant;
   lista->v[lista->v[posicao].ant].prox = iLivre;
   lista->v[posicao].ant = iLivre;

   lista->tamanho++;

   return iLivre;
}

Posic insertAfter(Lista L, Info info, Posic posicao)
{
   List* lista = (List*) lista;
   int iLivre = getLivre(L);

   lista->v[iLivre].info = info;

   lista->v[iLivre].ant = posicao;
   lista->v[iLivre].prox = lista->v[posicao].prox;
   lista->v[lista->v[posicao].prox].ant = iLivre;
   lista->v[posicao].prox = iLivre;

   lista->tamanho++;

   return iLivre;
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

Info get(Lista L, Posic pos)
{
   List* lista = (List*) L;
   return lista->v[pos].info;
}

int procuraCirculo(Lista L, char id[])
{
   List* lista = (List*) L;

   int i = lista->primeiro;
   Info informacao;
   if(lista->primeiro == -1)
      return -1;
      
   while(lista->v[i].prox != -1)
   {
      informacao = lista->v[i].info;
      if(strcmp(retornaCID(informacao), id) == 0)
         return i;
      
      i = lista->v[i].prox;
   }

   informacao = lista->v[i].info;
   if(strcmp(retornaCID(informacao), id) == 0)
      return i;

   return -1;
}



int procuraRetangulo(Lista L, char id[])
{
   List* lista = (List*) L;

   int i = lista->primeiro;
   Info informacao;
   if(lista->primeiro == -1)
      return -1;
   
   while(lista->v[i].prox != -1)
   {
      informacao = lista->v[i].info;

      if(strcmp(retornaReID(informacao), id) == 0)
         return i;
      
      i = lista->v[i].prox;
   }

   informacao = lista->v[i].info;
   if(strcmp(retornaReID(informacao), id) == 0)
      return i;

   return -1;
}

int procuraQuadra(Lista L, char id[])
{
   List* lista = (List*) L;

   int i = lista->primeiro;
   Info informacao;
   if(lista->primeiro == -1)
      return -1;

   while(lista->v[i].prox != -1)
   {
      informacao = lista->v[i].info;

      if(strcmp(retornaQCEP(informacao), id) == 0)
         return i;
      
      i = lista->v[i].prox;
   }
   informacao = lista->v[i].info;
   if(strcmp(retornaQCEP(informacao), id) == 0)
      return i;

   return -1;
}

int procuraHidrante(Lista L, char id[])
{
   List* lista = (List*) L;

   int i = lista->primeiro;
   Info informacao;
   if(lista->primeiro == -1)
      return -1;

   while(lista->v[i].prox != -1)
   {
      informacao = lista->v[i].info;

      if(strcmp(retornaHID(informacao), id) == 0)
         return i;
      
      i = lista->v[i].prox;
   }

   informacao = lista->v[i].info;
   if(strcmp(retornaHID(informacao), id) == 0)
      return i;

   return -1;
}

int procuraSemaforo(Lista L, char id[])
{
   List* lista = (List*) L;

   int i = lista->primeiro;
   Info informacao;
   if(lista->primeiro == -1)
      return -1;

   while(lista->v[i].prox != -1)
   {
      informacao = lista->v[i].info;

      if(strcmp(retornaSID(informacao), id) == 0)
         return i;
      
      i = lista->v[i].prox;
   }

   informacao = lista->v[i].info;
   if(strcmp(retornaSID(informacao), id) == 0)
      return i;

   return -1;
}

int procuraRadio(Lista L, char id[])
{
   List* lista = (List*) L;

   int i = lista->primeiro;
   Info informacao;
   if(lista->primeiro == -1)
      return -1;

   while(lista->v[i].prox != -1)
   {
      informacao = lista->v[i].info;

      if(strcmp(retornaRID(informacao), id) == 0)
         return i;
      
      i = lista->v[i].prox;
   }

   informacao = lista->v[i].info;
   if(strcmp(retornaRID(informacao), id) == 0)
      return i;

   return -1;
}

int procuraPredio(Lista L, char id[], char face[], double num)
{
   List* lista = (List*) L;

   int i = lista->primeiro;
   Info informacao;
   if(lista->primeiro == -1)
      return -1;

   while(lista->v[i].prox != -1)
   {
      informacao = lista->v[i].info;

      if(strcmp(retornaPCep(informacao), id) == 0 && strcmp(retornaPFace(informacao), face) == 0 && retornaPNumero(informacao) == num)
         return i;
      
      i = lista->v[i].prox;
   }

   informacao = lista->v[i].info;
   if(strcmp(retornaPCep(informacao), id) == 0 && strcmp(retornaPFace(informacao), face) == 0 && retornaPNumero(informacao) == num)
      return i;

   return -1;
}
