#include <stdio.h>
#include <stdlib.h>
#include<stdarg.h>
#include <string.h>
#include "arvore.h"
#include <math.h>

#define PRETA 1
#define VERMELHA 0

typedef struct no
{
  Info info;
  int cor;
  struct no *direita;
  struct no *esquerda;
  struct no *pai;
} No;

typedef struct arvore
{
    No *raiz;
    No *nil;
    double (*comparaInfo) (Info, Info);
    int tamanho;
} Arvore;

Tree criaArvore(double (*comparaInfo) (Info, Info))
{
    Tree tree = (Arvore*)malloc(sizeof(Arvore));
    Arvore* arvore = (Arvore*) tree;
    No* no = (No*)malloc(sizeof(No)); /* Aloca memória para a estrutura */
    no->esquerda = no; /* Subárvore à esquerda é NULL */
    no->direita = no; /* Subárvore à direita é NULL */
    no->pai = no;
    no->cor = 1;
    arvore->nil = no;
    arvore->raiz = no;
    arvore->comparaInfo = comparaInfo;
    arvore->tamanho = 0;
  /* Uma árvore é representada pelo endereço do nó raiz,
     essa função cria uma árvore com nenhum elemento,
     ou seja, cria uma árvore vazia, por isso retorna NULL. */
  return arvore;
}

No* criaNo(Info info)
{
    No* no = (No*)malloc(sizeof(No)); /* Aloca memória para a estrutura */
    no->esquerda = NULL; /* Subárvore à esquerda é NULL */
    no->direita = NULL; /* Subárvore à direita é NULL */
    no->pai = NULL;
    no->info = info; /* Armazena a informação */
    no->cor = 1;

    return no;
}

void rotacionaAEsquerda(Arvore* arvore, No *no)
{
    No *aux = no->direita;
    no->direita = aux->esquerda;
    
    if (aux->esquerda != arvore->nil)
        aux->esquerda->pai = no;

    aux->pai = no->pai;

    if (no->pai == arvore->nil)
        arvore->raiz = aux;
    else if(no == no->pai->esquerda)
        no->pai->esquerda = aux;
    else
        no->pai->direita = aux;
    
    aux->esquerda = no;
    no->pai = aux;
}

void rotacionaADireita(Arvore* arvore, No *no)
{
    No *aux = no->esquerda;
    no->esquerda = aux->direita;
    
    if (aux->direita != arvore->nil)
        aux->direita->pai = no;

    aux->pai = no->pai;

    if (no->pai == arvore->nil)
        arvore->raiz = aux;
    else if(no == no->pai->direita)
        no->pai->direita = aux;
    else
        no->pai->esquerda = aux;
    
    aux->direita = no;
    no->pai = aux;
}

void reparaInsercao(Arvore* arvore, No* no)
{
    No *aux;
    while (no->pai->cor == VERMELHA)
    {
        if (no->pai == no->pai->pai->esquerda)
        {
            aux = no->pai->pai->direita;
            if (aux->cor == VERMELHA)
            {
                no->pai->cor = PRETA;
                aux->cor = PRETA;
                no->pai->pai->cor = VERMELHA;
                no = no->pai->pai;
            }
            else
            {
                if (no == no->pai->direita)
                {
                    no = no->pai;
                    rotacionaAEsquerda(arvore, no);
                }
                no->pai->cor = PRETA;
                no->pai->pai->cor = VERMELHA;
                rotacionaADireita(arvore, no->pai->pai);
            }
        }
        else
        {
            aux = no->pai->pai->esquerda;
            if (aux->cor == VERMELHA)
            {
                no->pai->cor = PRETA;
                aux->cor = PRETA;
                no->pai->pai->cor = VERMELHA;
                no = no->pai->pai;
            }
            else
            {
                if (no == no->pai->esquerda)
                {
                    no = no->pai;
                    rotacionaADireita(arvore, no);
                }
                no->pai->cor = PRETA;
                no->pai->pai->cor = VERMELHA;
                rotacionaAEsquerda(arvore, no->pai->pai);
            }
        }
    }
    arvore->raiz->cor = PRETA;
}

void insereNaArvore(Tree** tree, Info info)
{
    
    Arvore** arvore = (Arvore**) tree;
    No *no = criaNo(info);
    No *folha = (*arvore)->nil;
    No *raiz = (*arvore)->raiz;
    (*arvore)->tamanho = (*arvore)->tamanho+1;
    (*arvore)->comparaInfo(no->info, no->info);
    while(raiz != (*arvore)->nil)
    {
        folha = raiz;
        if((*arvore)->comparaInfo(no->info, raiz->info) < 0)
            raiz = raiz->esquerda;
        else
            raiz = raiz->direita;
    }
    no->pai = folha;
    if(folha == (*arvore)->nil)
        (*arvore)->raiz = no;
    else if((*arvore)->comparaInfo(no->info, folha->info) < 0)
        folha->esquerda = no;
    else
        folha->direita = no;
    
    no->esquerda = (*arvore)->nil;
    no->direita = (*arvore)->nil;
    no->cor = VERMELHA;
    reparaInsercao((*arvore), no);
}

void imprimeArvore(Tree tree, void (*print) (Info))
{
    Arvore* arvore = (Arvore*) tree;
    No* no = arvore->raiz;
    /* Essa função imprime os elementos de forma recursiva */
    char op = 'a';

    while(op != 'x') /* se a árvore não for vazia... */
    {
        if (no != arvore->nil)
            print(no->info);
        else
            printf("Folha nil");
        /* Mostra os elementos em pré-ordem */
        
        if(no->cor == 1)
            printf(" cor = Preta\n"); /* mostra a raiz */
        else
            printf(" cor = Vermelha\n"); /* mostra a raiz */
        scanf(" %c", &op);
        if (op == 'e')
        {
            if(no->esquerda == arvore->nil && no != arvore->nil)
                arvore->nil->pai = no;
            no = no->esquerda;
        }
        else if (op == 'd')
        {
            if(no->direita == arvore->nil && no != arvore->nil)
                arvore->nil->pai = no;
            no = no->direita;
        }
        else if (op == 'p')
        {
            if(no->pai != arvore->nil)
            {
                no = no->pai;
            }
            if(no == arvore->raiz)
                printf("\nRaiz ");
        }
    }
}

No* minimoDaArvore(Arvore* arvore, No* no)
{
    while(no->esquerda != arvore->nil)
        no = no->esquerda;
    return no;
}

No* maximoDaArvore(Arvore* arvore, No* no)
{
    while(no->direita != arvore->nil)
        no = no->direita;
    return no;
}

void transplante(Arvore* arvore, No* no, No* no2)
{
    if(no->pai == arvore->nil)
        arvore->raiz = no2;
    else if (no == no->pai->esquerda)
        no->pai->esquerda = no2;
    else
        no->pai->direita = no2;
    no2->pai = no->pai;
}

Node buscaNaArvore(Tree tree, Info info, char* (*retornaId) (Info))
{
    Arvore* arvore = (Arvore*) tree;
    No* no = arvore->raiz;

    while(no != arvore->nil)
    {
         if(arvore->comparaInfo(info, no->info) < 0)
            no = no->esquerda;
        else if(arvore->comparaInfo(info, no->info) > 0)
            no = no->direita;
        else
        {
            if(retornaId(info) == retornaId(no->info))
                return no;
        }
    }
    printf("\nNao foi possivel encontrar um no com esse numero");
    return NULL;
}

void reparaDelecao(Arvore* arvore, No* no)
{
    No *aux;
    while( no != arvore->raiz && no->cor == PRETA)
    {
        if (no == no->pai->esquerda)
        {
            aux = no->pai->direita;
            if(aux->cor == 0)
            {
                aux->cor = PRETA;
                no->pai->cor = VERMELHA;
                rotacionaAEsquerda(arvore, no->pai);
                aux = no->pai->direita;
            }
            if(aux->esquerda->cor == PRETA && aux->direita->cor == PRETA)
            {
                aux->cor = VERMELHA;
                no = no->pai;
            }
            else
            {
                if(aux->direita->cor == PRETA)
                {
                    aux->esquerda->cor = PRETA;
                    aux->cor = VERMELHA;
                    rotacionaADireita(arvore, aux);
                    aux = no->pai->direita;
                }
                aux->cor = no->pai->cor;
                no->pai->cor =  PRETA;
                aux->direita->cor = PRETA;
                rotacionaAEsquerda(arvore, no->pai);
                no = arvore->raiz;
            }
        }
        else
        {
            aux = no->pai->esquerda;
            if(aux->cor == 0)
            {
                aux->cor = PRETA;
                no->pai->cor = VERMELHA;
                rotacionaADireita(arvore, no->pai);
                aux = no->pai->esquerda;
            }
            if(aux->direita->cor == PRETA && aux->esquerda->cor == PRETA)
            {
                aux->cor = VERMELHA;
                no = no->pai;
            }
            else
            {
                if(aux->esquerda->cor == PRETA)
                {
                    aux->direita->cor = PRETA;
                    aux->cor = VERMELHA;
                    rotacionaAEsquerda(arvore, aux);
                    aux = no->pai->esquerda;
                }
                aux->cor = no->pai->cor;
                no->pai->cor =  PRETA;
                aux->esquerda->cor = PRETA;
                rotacionaADireita(arvore, no->pai);
                no = arvore->raiz;
            }
        }
    }
    no->cor = PRETA;
}

void deletaDaArvore(Tree tree, Node* node)
{
    Arvore* arvore = (Arvore*) tree;
    No* z = (No*) node;
    No* y = z;
    No* x;
    int corOriginal = y->cor;
    if(z->esquerda == arvore->nil)
    {
        x = z->direita;
        transplante(arvore, z, z->direita);
    }
    else if (z->direita == arvore->nil)
    {
        x = z->esquerda;
        transplante(arvore, z, z->esquerda);
    }
    else
    {
        y = minimoDaArvore(arvore, z->direita);
        corOriginal = y->cor;
        x = y->direita;
        if(y->pai == z)
            x->pai = y;
        else
        {
            transplante(arvore, y, y->direita);
            y->direita = z->direita;
            y->direita->pai = y;
        }
        transplante(arvore, z, y);
        y->esquerda = z->esquerda;
        y->esquerda->pai = y;
        y->cor = z->cor;
    }
    if(corOriginal == PRETA)
        reparaDelecao(arvore, x);
    arvore->tamanho = arvore->tamanho-1;
}

void percorreArvorePorNo(No* no, void (*funcao) (Info, va_list), No* nil, va_list args)
{
    if(no == nil)
        return;
    funcao(no->info, args);
    if(no->esquerda != nil)
        percorreArvorePorNo(no->esquerda, funcao, nil, args);
    if(no->direita != nil)
        percorreArvorePorNo(no->direita, funcao, nil, args);
}

void percorreArvore(Tree tree, void (*funcao) (Info, va_list), ...)
{
    Arvore* arvore = (Arvore*) tree;
    va_list args;
    va_start(args, funcao);

    percorreArvorePorNo(arvore->raiz, funcao, arvore->nil, args);
    
    va_end(args);
}

int profundidadeMaxima(Arvore* arvore, No* no)  
{
   if (no==arvore->nil)  
       return 0;
   else
   {
       int tamanhoDaEsquerda = profundidadeMaxima(arvore, no->esquerda);
       int tamanhoDaDireita = profundidadeMaxima(arvore, no->direita);
 
       /* use the larger one */
       if (tamanhoDaEsquerda > tamanhoDaDireita)  
           return(tamanhoDaEsquerda+1);
       else return(tamanhoDaDireita+1);
   }
}  


void imprimeNodeNoSvg(Node *node, Tree *tree,void (*imprimeSvg)(void*,FILE*,int,int,char,int),FILE *arquivoSVG,int tamanho,int y,int x)
{
    No *no = (No *)node;
    Arvore *arvore = (Arvore* )tree;
    
    if (no == arvore->nil){
        fprintf(arquivoSVG, "\n\t<polygon points=\"%d,%d %d,%d %d,%d\" style=\"fill:black;stroke:black;stroke-width:1\" />", x, y, x-10, y+20, x+10, y+20);
        return;
    }
    fprintf(arquivoSVG,"\n\t<line x1='%d' y1='%d' x2='%d' y2='%d' stroke-width='2' fill='black' stroke='black'/>",x,y,x-tamanho/2,y+30);
    imprimeNodeNoSvg(no->esquerda,arvore,imprimeSvg,arquivoSVG,tamanho/2,y+30,x-tamanho/2);
    fprintf(arquivoSVG,"\n\t<line x1='%d' y1='%d' x2='%d' y2='%d' stroke-width='2' fill='black' stroke='black'/>",x,y,x+tamanho/2,y+30);
    imprimeNodeNoSvg(no->direita,arvore,imprimeSvg,arquivoSVG,tamanho/2,y+30,x+tamanho/2);
    imprimeSvg(no->info,arquivoSVG,x,y,no->cor,tamanho);
}

void percorreArvoreParaImpressaoNoSvg(Tree *tree,void (*imprimeSvg)(void*,FILE*,int,int,char,int),FILE *arquivoSVG)
{
    Arvore *arvore = (Arvore *)tree;
    int tamanho = pow(2,profundidadeMaxima(arvore, arvore->raiz))*20;
    imprimeNodeNoSvg(arvore->raiz, arvore, imprimeSvg, arquivoSVG, tamanho/2, 30, tamanho - (tamanho/2.3));
}

void percorreArvorePorNo2(No* no, void (*funcao) (Node, Info, va_list), No* nil, va_list args)
{
    if(no == nil)
        return;
    funcao(no, no->info, args);
    if(no->esquerda != nil)
        percorreArvorePorNo2(no->esquerda, funcao, nil, args);
    if(no->direita != nil)
        percorreArvorePorNo2(no->direita, funcao, nil, args);
}

void percorreArvore2(Tree tree, void (*funcao) (Node, Info, va_list), ...)
{
    Arvore* arvore = (Arvore*) tree;
    va_list args;
    va_start(args, funcao);

    percorreArvorePorNo2(arvore->raiz, funcao, arvore->nil, args);
    
    va_end(args);
}

void imprimeArvorePorNo(No* no, void (*funcao) (Info, char[], char[]), No* nil, char nomeDoArquivoSvg[], char cor[])
{
    if(no == nil)
        return;
    funcao(no->info, nomeDoArquivoSvg, cor);
    if(no->esquerda != nil)
        imprimeArvorePorNo(no->esquerda, funcao, nil, nomeDoArquivoSvg, cor);
    if(no->direita != nil)
        imprimeArvorePorNo(no->direita, funcao, nil, nomeDoArquivoSvg, cor);
}

void imprimeNoSvg(Tree tree, void (*funcao) (Info, char[], char[]), char nomeDoArquivoSvg[], char cor[])
{
    Arvore* arvore = (Arvore*) tree;
    imprimeArvorePorNo(arvore->raiz, funcao, arvore->nil, nomeDoArquivoSvg, cor);
}

void desalocaNo(No* no, No* nil)
{
    if(no->esquerda != nil)
        desalocaNo(no->esquerda, nil);
    if(no->direita != nil)
        desalocaNo(no->direita, nil);

    free(no);
    no = NULL;
}

void desalocaArvore(Tree tree)
{
    Arvore* arvore = (Arvore*) tree;

    desalocaNo(arvore->raiz, arvore->nil);
    // free(arvore->nil);
    free(arvore);
    arvore = NULL;
}

int getTamanhoDaArvore(Tree tree){
    Arvore *arvore = tree;
    return arvore->tamanho;
}

Info getInfo(Node node)
{
    No* no = (No*) node;
    return no->info;
}

void heapsort(Info vetor[], int tamanho, double x, double y, double (*retorna)(Info), double (*retorna2)(Info))
{
   int i = tamanho / 2, pai, filho;
   Info t;
   
   while(true) {
      if (i > 0) {
          i--;
          t = vetor[i];
      } else {
          tamanho--;
          if (tamanho <= 0) return;
          t = vetor[tamanho];
          vetor[tamanho] = vetor[0];
      }
      pai = i;
      filho = i * 2 + 1;
        while (filho < tamanho) {
            if ((filho + 1 < tamanho)  &&  distancia(x, y, retorna(vetor[filho+1]), retorna2(vetor[filho+1])) > distancia(x, y, retorna(vetor[filho]), retorna2(vetor[filho])))
                filho++;
            if (distancia(x, y, retorna(vetor[filho]), retorna2(vetor[filho])) > distancia(x, y, retorna(t), retorna2(t)))
            {
                vetor[pai] = vetor[filho];
                pai = filho;
                filho = pai * 2 + 1;
            }
            else 
            {
                break;
            }
      }
      vetor[pai] = t;
   }
}


void resolveSemaforos(Info vetor[], double xIncendio, double yIncendio, int numeroDeSemaforos, char nomeDoArquivoSvg[], char nomeDoArquivoTxt[], char comando[])
{
   FILE* arquivoTxt;
   arquivoTxt = fopen(nomeDoArquivoTxt, "a");
   int inicio = 0;
   
   char corB[] = "red";
   char corP[] = "none";

   if((strcmp("fi", comando)) == 0)
   {
      imprimirIncendio(xIncendio, yIncendio, nomeDoArquivoSvg);
      fprintf(arquivoTxt, "%s\n", comando);
      for(inicio = 0; inicio<numeroDeSemaforos; inicio++)
      {
         imprimirLinha(xIncendio, yIncendio, retornaSX(vetor[inicio]), retornaSY(vetor[inicio]), nomeDoArquivoSvg);
         imprimirCirculo(2.5, retornaSX(vetor[inicio]), retornaSY(vetor[inicio]), "blue", corP, nomeDoArquivoSvg, 2);
         imprimirCirculo(5.0, retornaSX(vetor[inicio]), retornaSY(vetor[inicio]), corB, corP, nomeDoArquivoSvg, 2);
         fprintf(arquivoTxt, "%s\n", retornaSID(vetor[inicio]));
      }
   }
   else
   {
      fprintf(arquivoTxt, "%s\n", comando);
      for(inicio = 0; inicio<numeroDeSemaforos; inicio++)
      {
         imprimirLinha(xIncendio, yIncendio, retornaSX(vetor[inicio]), retornaSY(vetor[inicio]), nomeDoArquivoSvg);
         imprimirCirculo(2.5, retornaSX(vetor[inicio]), retornaSY(vetor[inicio]), "blue", corP, nomeDoArquivoSvg, 2);
         imprimirCirculo(5.0, retornaSX(vetor[inicio]), retornaSY(vetor[inicio]), corB, corP, nomeDoArquivoSvg, 2);
         fprintf(arquivoTxt, "%s\n", retornaSID(vetor[inicio]));
      }
   }
   

   fclose(arquivoTxt);
}

void resolveFHidrantes(Info vetor[], double x, double y, int numeroDeHidrantes, int fim, int sinal, char nomeDoArquivoSvg[], char nomeDoArquivoTxt[])
{
    FILE* arquivoTxt;
    arquivoTxt = fopen(nomeDoArquivoTxt, "a");
    int inicio = 0;
    char corB[] = "red";
    char corP[] = "none";
    fprintf(arquivoTxt, "fh\n");
    if(sinal == 0)
    {
        for(inicio = 0; inicio<numeroDeHidrantes; inicio++)
        {
            imprimirLinha(x, y, retornaHX(vetor[inicio]), retornaHY(vetor[inicio]), nomeDoArquivoSvg);
            imprimirCirculo(2.5, retornaHX(vetor[inicio]), retornaHY(vetor[inicio]), "blue", corP, nomeDoArquivoSvg, 2);
            imprimirCirculo(5.0, retornaHX(vetor[inicio]), retornaHY(vetor[inicio]), corB, corP, nomeDoArquivoSvg, 2);
            fprintf(arquivoTxt, "%s\n", retornaHID(vetor[inicio]));
        }
    }
    else
    {
        int final = fim - numeroDeHidrantes;
        for(fim = fim-1; fim>=final; fim--)
        {
            printf("\n%d", fim);
            imprimirLinha(x, y, retornaHX(vetor[fim]), retornaHY(vetor[fim]), nomeDoArquivoSvg);
            imprimirCirculo(2.5, retornaHX(vetor[fim]), retornaHY(vetor[fim]), "blue", corP, nomeDoArquivoSvg, 2);
            imprimirCirculo(5.0, retornaHX(vetor[fim]), retornaHY(vetor[fim]), corB, corP, nomeDoArquivoSvg, 2);
            fprintf(arquivoTxt, "%s\n", retornaHID(vetor[fim]));
        }
    }
    
    

    fclose(arquivoTxt);
}  
