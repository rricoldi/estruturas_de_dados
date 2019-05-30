#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "qry.h"
#include "svg.h"
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

void printaQuadras(Lista L, char svg[])
{
   List* lista = (List*) L;

   int i = lista->primeiro;
   Quadra quadra;

   while(lista->v[i].prox != -1)
   {
      quadra = lista->v[i].info;

      printaRetangulo(retornaQW(quadra), retornaQH(quadra), retornaQX(quadra), retornaQY(quadra), retornaQCorB(quadra), retornaQCorP(quadra), svg, retornaQEspessura(quadra));

      i = lista->v[i].prox;
   }

   quadra = lista->v[i].info;

   printaRetangulo(retornaQW(quadra), retornaQH(quadra), retornaQX(quadra), retornaQY(quadra), retornaQCorB(quadra), retornaQCorP(quadra), svg, retornaQEspessura(quadra));
}

void printaHidrantes(Lista L, char svg[])
{
   List* lista = (List*) L;

   int i = lista->primeiro;
   Hidrante hidrante;

   while(lista->v[i].prox != -1)
   {
      hidrante = lista->v[i].info;

      printaCirculo(2, retornaHX(hidrante), retornaHY(hidrante), retornaHCorB(hidrante), retornaHCorP(hidrante), svg, retornaHEspessura(hidrante));

      i = lista->v[i].prox;
   }

   hidrante = lista->v[i].info;

   printaCirculo(2, retornaHX(hidrante), retornaHY(hidrante), retornaHCorB(hidrante), retornaHCorP(hidrante), svg, retornaHEspessura(hidrante));
}

void printaSemaforos(Lista L, char svg[])
{
   List* lista = (List*) L;

   int i = lista->primeiro;
   Semaforo semaforo;

   while(lista->v[i].prox != -1)
   {
      semaforo = lista->v[i].info;

      printaRetangulo(7, 18, retornaSX(semaforo), retornaSY(semaforo), retornaSCorB(semaforo), retornaSCorP(semaforo), svg, retornaSEspessura(semaforo));

      i = lista->v[i].prox;
   }

   semaforo = lista->v[i].info;

   printaRetangulo(7, 18, retornaSX(semaforo), retornaSY(semaforo), retornaSCorB(semaforo), retornaSCorP(semaforo), svg, retornaSEspessura(semaforo));
}

void printaRadios(Lista L, char svg[])
{
   List* lista = (List*) L;

   int i = lista->primeiro;
   Radio radio;
   //criaElipse(svg, x, y, 5, 15, corRP, corRB, espessuraR);

   while(lista->v[i].prox != -1)
   {
      radio = lista->v[i].info;

      criaElipse(svg, retornaRX(radio), retornaRY(radio), 5, 15, retornaSCorP(radio), retornaSCorB(radio), retornaSEspessura(radio));

      i = lista->v[i].prox;
   }

   radio = lista->v[i].info;

   criaElipse(svg, retornaRX(radio), retornaRY(radio), 5, 15, retornaSCorP(radio), retornaSCorB(radio), retornaSEspessura(radio));
}

void printaCirculos(Lista L, char svg[])
{
   FILE *arq;

   arq = fopen(svg, "a");
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

      fprintf(arq, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" fill=\"%s\" />", retornaCX(circulo), retornaCY(circulo), retornaCR(circulo), retornaCCorB(circulo), retornaCCorP(circulo));

      i = lista->v[i].prox;
   }

   circulo = lista->v[i].info;

   fprintf(arq, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" fill=\"%s\" />", retornaCX(circulo), retornaCY(circulo), retornaCR(circulo), retornaCCorB(circulo), retornaCCorP(circulo));

   fclose(arq);
}

void printaRetangulos(Lista L, char svg[])
{
   FILE *arq;
   arq = fopen(svg, "a");
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


      fprintf(arq, "\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:%s;stroke:%s\" />", retornaReX(retangulo), retornaReY(retangulo), retornaReW(retangulo), retornaReH(retangulo), retornaReCorP(retangulo), retornaReCorB(retangulo));
    	
      i = lista->v[i].prox;
   }

   retangulo = lista->v[i].info;

   fprintf(arq, "\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:%s;stroke:%s\" />", retornaReX(retangulo), retornaReY(retangulo), retornaReW(retangulo), retornaReH(retangulo), retornaReCorP(retangulo), retornaReCorB(retangulo));
    	
   fclose(arq);
}

void bbcLista(Lista L, char arqout[])
{
   FILE *arq;

   arq = fopen(arqout, "a");
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

      fprintf(arq, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" fill=\"%s\" />", retornaCX(circulo), retornaCY(circulo), retornaCR(circulo), retornaCCorB(circulo), retornaCCorP(circulo));
      fprintf(arq, "\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:none;stroke:black\" />", retornaCX(circulo)-retornaCR(circulo), retornaCY(circulo)-retornaCR(circulo), retornaCR(circulo)*2, retornaCR(circulo)*2);

      i = lista->v[i].prox;
   }

   circulo = lista->v[i].info;

   fprintf(arq, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" fill=\"%s\" />", retornaCX(circulo), retornaCY(circulo), retornaCR(circulo), retornaCCorB(circulo), retornaCCorP(circulo));
   fprintf(arq, "\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:%s;stroke:%s\" />", retornaCX(circulo)-retornaCR(circulo), retornaCY(circulo)-retornaCR(circulo), retornaCR(circulo)*2, retornaCR(circulo)*2, retornaCCorB(circulo), retornaCCorP(circulo));
}

void bbrLista(Lista L, char arqout[], char cor[])
{
   FILE *arq;
   arq = fopen(arqout, "a");
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


      fprintf(arq, "\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:%s;stroke:%s\" />", retornaReX(retangulo), retornaReY(retangulo), retornaReW(retangulo), retornaReH(retangulo), retornaReCorP(retangulo), retornaReCorB(retangulo));
    	fprintf(arq, "\n\t<ellipse cx=\"%f\" cy=\"%f\" rx=\"%f\" ry=\"%f\" style=\"fill:%s;stroke:%s\" />", retornaReX(retangulo)+(retornaReW(retangulo)/2), retornaReY(retangulo)+(retornaReH(retangulo)/2), retornaReW(retangulo)/2, retornaReH(retangulo)/2, cor, cor);
    	
      i = lista->v[i].prox;
   }

   retangulo = lista->v[i].info;

   fprintf(arq, "\n\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" style=\"fill:%s;stroke:%s\" />", retornaReX(retangulo), retornaReY(retangulo), retornaReW(retangulo), retornaReH(retangulo), retornaReCorP(retangulo), retornaReCorB(retangulo));
   fprintf(arq, "\n\t<ellipse cx=\"%f\" cy=\"%f\" rx=\"%f\" ry=\"%f\" style=\"fill:%s;stroke:%s\" />", retornaReX(retangulo)+(retornaReW(retangulo)/2), retornaReY(retangulo)+(retornaReH(retangulo)/2), retornaReW(retangulo)/2, retornaReH(retangulo)/2, cor, cor);
    	
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

   lista->tamanho--;
}

Info get(Lista L, Posic pos)
{
   List* lista = (List*) L;
   return lista->v[pos].info;
}

int procuraListaC(Lista L, char id[])
{
   List* lista = (List*) L;

   int i = lista->primeiro;
   Info informacao;

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

int procuraListaRe(Lista L, char id[])
{
   List* lista = (List*) L;

   int i = lista->primeiro;
   Info informacao;

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

int procuraListaQ(Lista L, char id[])
{
   List* lista = (List*) L;

   int i = lista->primeiro;
   Info informacao;

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

int procuraListaH(Lista L, char id[])
{
   List* lista = (List*) L;

   int i = lista->primeiro;
   Info informacao;

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

int procuraListaS(Lista L, char id[])
{
   List* lista = (List*) L;

   int i = lista->primeiro;
   Info informacao;

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

int procuraListaR(Lista L, char id[])
{
   List* lista = (List*) L;

   int i = lista->primeiro;
   Info informacao;

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

void percorreListaQ(Lista L, double r, double fx, double fy, char tipo[], char svg[], char txt[], char id[], int opcao, char cor[], double largura, double altura, double dx, double dy)
{
   FILE *arqSvg, *arqTxt;
   arqSvg = fopen(svg,"a");
   arqTxt = fopen(txt, "a");
   List* lista = (List*) L;

   if(opcao == 1)
      fprintf(arqTxt, "dq %s %s %lf\n", tipo, id, r);

   int i = lista->primeiro;
   Info informacao;
   if(strcmp(tipo, "L1") == 0)
   {
      while(lista->v[i].prox != -1)
      {
         informacao = lista->v[i].info;

         if(retornaDistanciaL1(r, fx, fy, retornaQX(informacao), retornaQY(informacao), retornaQW(informacao), retornaQH(informacao)))
         {
            fprintf(arqSvg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"4\" stroke= \"black\" fill=\"none\" stroke-width=\"1\" stroke-oppacity=\"0.7\" />", fx, fy);
            fprintf(arqSvg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"6\" stroke= \"yellow\" fill=\"none\" stroke-width=\"1\" stroke-oppacity=\"0.7\" />", fx, fy);
            fprintf(arqTxt, "cep: %s\n", retornaQCEP(informacao));
            removeLista(lista, i);
         }        
         
         i = lista->v[i].prox;
      }
      
      informacao = lista->v[i].info;
      
      if(retornaDistanciaL1(r, fx, fy, retornaQX(informacao), retornaQY(informacao), retornaQW(informacao), retornaQH(informacao)))
      {
         fprintf(arqSvg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"4\" stroke= \"black\" fill=\"none\" stroke-width=\"1\" stroke-oppacity=\"0.7\" />", fx, fy);
         fprintf(arqSvg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"6\" stroke= \"yellow\" fill=\"none\" stroke-width=\"1\" stroke-oppacity=\"0.7\" />", fx, fy);
         fprintf(arqTxt, "cep: %s\n", retornaQCEP(informacao));
         removeLista(lista, i);
      }  
   }
   else
   {
      while(lista->v[i].prox != -1)
      {
         informacao = lista->v[i].info;
         if (informacao == NULL)
         {
            i = lista->v[i].prox;
            continue;
         }

         if(retornaDistanciaL2(r, fx, fy, retornaQX(informacao), retornaQY(informacao), retornaQW(informacao), retornaQH(informacao)) && opcao != 3)
         {
            if(opcao == 1)
            {
               fprintf(arqSvg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"4\" stroke= \"black\" fill=\"none\" stroke-width=\"1\" stroke-oppacity=\"0.7\" />", fx, fy);
               fprintf(arqSvg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"6\" stroke= \"yellow\" fill=\"none\" stroke-width=\"1\" stroke-oppacity=\"0.7\" />", fx, fy);
               fprintf(arqTxt, "cep: %s\n", retornaQCEP(informacao));
               removeLista(lista, i);
            }
            else if (opcao == 2)
            {
               setQCorB(informacao, cor);
               fprintf(arqTxt, "cep: %s\n", retornaQCEP(informacao));
            }
             
         }
         else if (inRR(fx, fy, largura, altura, retornaQX(informacao), retornaQY(informacao), retornaQW(informacao), retornaQH(informacao)) && opcao == 3)
         {
            fprintf(arqTxt, "cep: %s x: %lf y: %lf novo x: %lf novo y: %lf\n", retornaQCEP(informacao), retornaQX(informacao), retornaQY(informacao), retornaQX(informacao)+dx, retornaQY(informacao)+dy);
            setQX(informacao, retornaQX(informacao)+dx);
            setQY(informacao, retornaQY(informacao)+dy);
         }
         
         i = lista->v[i].prox;
         //printf("opcao: %d\n", opcao);
         //printf("i= %d\n", i);
      }
      
      informacao = lista->v[i].info;
      if (informacao != NULL)
      {
         if(retornaDistanciaL2(r, fx, fy, retornaQX(informacao), retornaQY(informacao), retornaQW(informacao), retornaQH(informacao)) && opcao != 3)
         {
            if(opcao == 1)
            {
               fprintf(arqSvg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"4\" stroke= \"black\" fill=\"none\" stroke-width=\"1\" stroke-oppacity=\"0.7\" />", fx, fy);
               fprintf(arqSvg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"6\" stroke= \"yellow\" fill=\"none\" stroke-width=\"1\" stroke-oppacity=\"0.7\" />", fx, fy);
               fprintf(arqTxt, "cep: %s\n", retornaQCEP(informacao));
               removeLista(lista, i);
            }
            else if (opcao == 2)
            {
               setQCorB(informacao, cor);
               fprintf(arqTxt, "cep: %s\n", retornaQCEP(informacao));
            }             
         }
         if (inRR(fx, fy, largura, altura, retornaQX(informacao), retornaQY(informacao), retornaQW(informacao), retornaQH(informacao)) && opcao == 3)
         {
            fprintf(arqTxt, "cep: %s x: %lf y: %lf novo x: %lf novo y: %lf\n", retornaQCEP(informacao), retornaQX(informacao), retornaQY(informacao), retornaQX(informacao)+dx, retornaQY(informacao)+dy);
            setQX(informacao, retornaQX(informacao)+dx);
            setQY(informacao, retornaQY(informacao)+dy);
         } 
      }
      fclose(arqSvg);
      fclose(arqTxt);
      
   }
}
//percorrelistaH(city->listaH, fx, fy, largura, altura, dx, dy, txt);
void percorreListaH(Lista L, double x, double y, double w, double h, double dx, double dy, char txt[])
{
   FILE* arq;
   arq = fopen(txt, "a");

   List* lista = (List*) L;
   int i = lista->primeiro;
   Info informacao;

   while(lista->v[i].prox != -1)
   {
      informacao = lista->v[i].info;
      if (informacao == NULL)
      {
         i = lista->v[i].prox;
         continue;
      }

      if(pontoInternoRetangulo(retornaHX(informacao), retornaHY(informacao), x, y, h, w))
      {
         fprintf(arq, "id: %s x: %lf y: %lf novo x: %lf novo y: %lf\n", retornaHID(informacao), retornaHX(informacao), retornaHY(informacao), retornaHX(informacao)+dx, retornaHY(informacao)+dy);
         setHX(informacao, retornaHX(informacao)+dx);
         setHY(informacao, retornaHY(informacao)+dy);
      }
      
      i = lista->v[i].prox;
   }

   informacao = lista->v[i].info;
   
   if(pontoInternoRetangulo(retornaHX(informacao), retornaHY(informacao), x, y, h, w))
   {
      fprintf(arq, "id: %s x: %lf y: %lf novo x: %lf novo y: %lf\n", retornaHID(informacao), retornaHX(informacao), retornaHY(informacao), retornaHX(informacao)+dx, retornaHY(informacao)+dy);
      setHX(informacao, retornaHX(informacao)+dx);
      setHY(informacao, retornaHY(informacao)+dy);
   }
   fclose(arq);
}

void percorreListaS(Lista L, double x, double y, double w, double h, double dx, double dy, char txt[])
{
   FILE* arq;
   arq = fopen(txt, "a");

   List* lista = (List*) L;
   int i = lista->primeiro;
   Info informacao;

   while(lista->v[i].prox != -1)
   {
      informacao = lista->v[i].info;
      if (informacao == NULL)
      {
         i = lista->v[i].prox;
         continue;
      }

      if(pontoInternoRetangulo(retornaSX(informacao), retornaSY(informacao), x, y, h, w))
      {
         fprintf(arq, "id: %s x: %lf y: %lf novo x: %lf novo y: %lf\n", retornaSID(informacao), retornaSX(informacao), retornaSY(informacao), retornaSX(informacao)+dx, retornaSY(informacao)+dy);
         setSX(informacao, retornaSX(informacao)+dx);
         setSY(informacao, retornaSY(informacao)+dy);
      }
      
      i = lista->v[i].prox;
   }

   informacao = lista->v[i].info;
   if(pontoInternoRetangulo(retornaSX(informacao), retornaSY(informacao), x, y, h, w))
   {
      fprintf(arq, "id: %s x: %lf y: %lf novo x: %lf novo y: %lf\n", retornaSID(informacao), retornaSX(informacao), retornaSY(informacao), retornaSX(informacao)+dx, retornaSY(informacao)+dy);
      setSX(informacao, retornaSX(informacao)+dx);
      setSY(informacao, retornaSY(informacao)+dy);
   }
   fclose(arq);
}

void percorreListaR(Lista L, double x, double y, double w, double h, double dx, double dy, char txt[])
{
   FILE* arq;
   arq = fopen(txt, "a");

   List* lista = (List*) L;
   int i = lista->primeiro;
   Info informacao;

   while(lista->v[i].prox != -1)
   {
      informacao = lista->v[i].info;
      if (informacao == NULL)
      {
         i = lista->v[i].prox;
         continue;
      }

      if(pontoInternoRetangulo(retornaRX(informacao), retornaRY(informacao), x, y, h, w))
      {
         fprintf(arq, "id: %s x: %lf y: %lf novo x: %lf novo y: %lf\n", retornaRID(informacao), retornaRX(informacao), retornaRY(informacao), retornaRX(informacao)+dx, retornaRY(informacao)+dy);
         setRX(informacao, retornaRX(informacao)+dx);
         setRY(informacao, retornaRY(informacao)+dy);
      }
      
      i = lista->v[i].prox;
   }

   informacao = lista->v[i].info;
   if(pontoInternoRetangulo(retornaRX(informacao), retornaRY(informacao), x, y, h, w))
   {
      fprintf(arq, "id: %s x: %lf y: %lf novo x: %lf novo y: %lf\n", retornaRID(informacao), retornaRX(informacao), retornaRY(informacao), retornaRX(informacao)+dx, retornaRY(informacao)+dy);
      setRX(informacao, retornaRX(informacao)+dx);
      setRY(informacao, retornaRY(informacao)+dy);
   }
   fclose(arq);
}