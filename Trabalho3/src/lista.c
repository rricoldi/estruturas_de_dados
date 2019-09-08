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
   if( lista->tamanho != 0)
   {
      free(lista->v);
      free(lista);
   }
   
}

void imprimeCirculos(Lista L, char nomeDoArquivoSvg[])
{
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
}

void imprimeRetangulos(Lista L, char nomeDoArquivoSvg[])
{
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

void bbcLista(Lista L, char arqout[])
{
   List* lista = (List*) L;

   int i = lista->primeiro;
   Circulo circulo;

   while(lista->v[i].prox != -1)
   {
      circulo = lista->v[i].info;

      imprimirCirculo(retornaCR(circulo), retornaCX(circulo), retornaCY(circulo), retornaCCorB(circulo), retornaCCorP(circulo), arqout, retornaCEspessura(circulo));
      imprimirRetangulo(retornaCR(circulo)*2, retornaCR(circulo)*2, retornaCX(circulo)-retornaCR(circulo), retornaCY(circulo)-retornaCR(circulo), "none", "black", arqout, 2);

      i = lista->v[i].prox;
   }

   circulo = lista->v[i].info;

      imprimirCirculo(retornaCR(circulo), retornaCX(circulo), retornaCY(circulo), retornaCCorB(circulo), retornaCCorP(circulo), arqout, retornaCEspessura(circulo));
      imprimirRetangulo(retornaCR(circulo)*2, retornaCR(circulo)*2, retornaCX(circulo)-retornaCR(circulo), retornaCY(circulo)-retornaCR(circulo), "none", "black", arqout, 2);
}

void bbrLista(Lista L, char arqout[], char cor[])
{
   List* lista = (List*) L;

   int i = lista->primeiro;
   Retangulo retangulo;

   while(lista->v[i].prox != -1)
   {
      retangulo = lista->v[i].info;

      imprimirRetangulo(retornaReW(retangulo), retornaReH(retangulo), retornaReX(retangulo), retornaReY(retangulo), retornaReCorP(retangulo), retornaReCorB(retangulo), arqout, retornaReEspessura(retangulo));
    	imprimirElipse(arqout, retornaReX(retangulo)+(retornaReW(retangulo)/2), retornaReY(retangulo)+(retornaReH(retangulo)/2), retornaReW(retangulo)/2, retornaReH(retangulo)/2, cor, cor, 2);
    	
      i = lista->v[i].prox;
   }

   retangulo = lista->v[i].info;
   imprimirRetangulo(retornaReW(retangulo), retornaReH(retangulo), retornaReX(retangulo), retornaReY(retangulo), retornaReCorP(retangulo), retornaReCorB(retangulo), arqout, retornaReEspessura(retangulo));
   imprimirElipse(arqout, retornaReX(retangulo)+(retornaReW(retangulo)/2), retornaReY(retangulo)+(retornaReH(retangulo)/2), retornaReW(retangulo)/2, retornaReH(retangulo)/2, cor, cor, 2);   	
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

void percorreListaQ(Lista L, double r, double fx, double fy, char tipo[], char svg[], char txt[], char id[], int opcao, char cor[], double largura, double altura, double dx, double dy)
{
   FILE *arqSvg, *arqTxt;
   arqSvg = fopen(svg,"a");
   arqTxt = fopen(txt, "a");
   List* lista = (List*) L;

   if(opcao == 1)
      fprintf(arqTxt, "dq %s %s %lf\n", tipo, id, r);

   int i = lista->primeiro;
   int j;
   Info informacao;
   if(strcmp(tipo, "L1") == 0)
   {
      while(lista->v[i].prox != -1)
      {
         informacao = lista->v[i].info;
         if (informacao == NULL)
         {
            i = lista->v[i].prox;
            continue;
         }
         j = lista->v[i].prox;

         if(retornaDistanciaL1(r, fx, fy, retornaQX(informacao), retornaQY(informacao), retornaQW(informacao), retornaQH(informacao)))
         {
            fprintf(arqSvg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"10\" stroke= \"black\" fill=\"none\" stroke-width=\"4\" stroke-oppacity=\"0.7\" />", fx, fy);
            fprintf(arqSvg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"15\" stroke= \"yellow\" fill=\"none\" stroke-width=\"4\" stroke-oppacity=\"0.7\" />", fx, fy);
            fprintf(arqTxt, "cep: %s\n", retornaQCEP(informacao));            
            removerDaLista(lista, i);
         }

         i = j;
      }

      informacao = lista->v[i].info;
      
      if(retornaDistanciaL1(r, fx, fy, retornaQX(informacao), retornaQY(informacao), retornaQW(informacao), retornaQH(informacao)))
      {
         fprintf(arqSvg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"10\" stroke= \"black\" fill=\"none\" stroke-width=\"4\" stroke-oppacity=\"0.7\" />", fx, fy);
         fprintf(arqSvg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"15\" stroke= \"yellow\" fill=\"none\" stroke-width=\"4\" stroke-oppacity=\"0.7\" />", fx, fy);
         fprintf(arqTxt, "cep: %s\n", retornaQCEP(informacao));
         removerDaLista(lista, i);
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
         j = lista->v[i].prox;
         if(retornaDistanciaL2(r, fx, fy, retornaQX(informacao), retornaQY(informacao), retornaQW(informacao), retornaQH(informacao)) && opcao != 3)
         {
            if(opcao == 1)
            {
               fprintf(arqSvg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"10\" stroke= \"black\" fill=\"none\" stroke-width=\"4\" stroke-oppacity=\"0.7\" />", fx, fy);
               fprintf(arqSvg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"15\" stroke= \"yellow\" fill=\"none\" stroke-width=\"4\" stroke-oppacity=\"0.7\" />", fx, fy);
               fprintf(arqTxt, "cep: %s\n", retornaQCEP(informacao));
               removerDaLista(lista, i);               
            }
            else if (opcao == 2)
            {
               setQCorB(informacao, cor);
               fprintf(arqTxt, "cep: %s\n", retornaQCEP(informacao));
            }
             
         }
         else if (verificaColisao(fx, fy, largura, altura, retornaQX(informacao), retornaQY(informacao), retornaQW(informacao), retornaQH(informacao)) && opcao == 3)
         {
            fprintf(arqTxt, "cep: %s x: %lf y: %lf novo x: %lf novo y: %lf\n", retornaQCEP(informacao), retornaQX(informacao), retornaQY(informacao), retornaQX(informacao)+dx, retornaQY(informacao)+dy);
            setQX(informacao, retornaQX(informacao)+dx);
            setQY(informacao, retornaQY(informacao)+dy);
         }
         
         i = j;
      }
      
      informacao = lista->v[i].info;
      if (informacao != NULL)
      {
         if(retornaDistanciaL2(r, fx, fy, retornaQX(informacao), retornaQY(informacao), retornaQW(informacao), retornaQH(informacao)) && opcao != 3)
         {
            if(opcao == 1)
            {
               fprintf(arqSvg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"10\" stroke= \"black\" fill=\"none\" stroke-width=\"4\" stroke-oppacity=\"0.7\" />", fx, fy);
               fprintf(arqSvg, "\n\t<circle cx=\"%f\" cy=\"%f\" r=\"15\" stroke= \"yellow\" fill=\"none\" stroke-width=\"4\" stroke-oppacity=\"0.7\" />", fx, fy);
               fprintf(arqTxt, "cep: %s\n", retornaQCEP(informacao));
               removerDaLista(lista, i);
            }
            else if (opcao == 2)
            {
               setQCorB(informacao, cor);
               fprintf(arqTxt, "cep: %s\n", retornaQCEP(informacao));
            }             
         }
         if (verificaColisao(fx, fy, largura, altura, retornaQX(informacao), retornaQY(informacao), retornaQW(informacao), retornaQH(informacao)) && opcao == 3)
         {
            fprintf(arqTxt, "cep: %s x: %lf y: %lf novo x: %lf novo y: %lf\n", retornaQCEP(informacao), retornaQX(informacao), retornaQY(informacao), retornaQX(informacao)+dx, retornaQY(informacao)+dy);
            setQX(informacao, retornaQX(informacao)+dx);
            setQY(informacao, retornaQY(informacao)+dy);
         } 
      }      
   }
   fclose(arqSvg);
   fclose(arqTxt);
}

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

void transformaListaEmVetor(Lista L, Info vetor[])
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
}



void resolveSemaforos(Lista L, double xIncendio, double yIncendio, int numeroDeSemaforos, char nomeDoArquivoSvg[], char nomeDoArquivoTxt[])
{
   FILE* arquivoTxt;
   arquivoTxt = fopen(nomeDoArquivoTxt, "a");
   Info vetor[lenght(L)];
   transformaListaEmVetor(L, vetor);
   int inicio = 0;
   int fim = lenght(L) - 1;

   quickSortSemaforo(vetor, inicio, fim, xIncendio, yIncendio);

   imprimirIncendio(xIncendio, yIncendio, nomeDoArquivoSvg);
   fprintf(arquivoTxt, "fi\n");
   for(inicio = 0; inicio<numeroDeSemaforos; inicio++)
   {
      imprimirLinha(xIncendio, yIncendio, retornaSX(vetor[inicio]), retornaSY(vetor[inicio]), nomeDoArquivoSvg);
      fprintf(arquivoTxt, "%s\n", retornaSID(vetor[inicio]));
   }


}

void quickSortSemaforo(Info vetor[], int inicio, int fim, double xIncendio, double yIncendio)
{
   double pivo = distancia(xIncendio, yIncendio, retornaSX(vetor[(inicio + fim) / 2]), retornaSY(vetor[(inicio + fim) / 2]));
   Info aux;
   int fimReal = fim;

   while(inicio <= fim)
   {
      while(distancia(xIncendio, yIncendio, retornaSX(vetor[inicio]), retornaSY(vetor[inicio])) < pivo)
      {
         inicio ++;
      }
      
      while(distancia(xIncendio, yIncendio, retornaSX(vetor[fim]), retornaSY(vetor[fim])) > pivo)
      {
         fim --;
      }

      if(inicio <= fim)
      {
         aux = vetor[inicio];
         vetor[inicio] = vetor[fim];
         vetor[fim] = aux;
         inicio ++;
         fim --;
      }
   }

   if(0 < fim)
   {
      quickSortSemaforo(vetor, 0, fim, xIncendio, yIncendio);
   }

   if(inicio < fimReal)
   {
      quickSortSemaforo(vetor, inicio, fimReal, xIncendio, yIncendio);
   }
}
