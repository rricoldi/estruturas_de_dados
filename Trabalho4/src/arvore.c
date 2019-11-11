#include <stdio.h>
#include <stdlib.h>
#include<stdarg.h>
#include "arvore.h"
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
  int op;
  int tamanho = 1;
  while(no != arvore->nil) /* se a árvore não for vazia... */
  {
    /* Mostra os elementos em pré-ordem */
    print(no->info);
    printf("cor = %d posicao = %d\nEsquerda(1) Direita(2) Pai(0)\n",  no->cor, tamanho); /* mostra a raiz */
    scanf("%d", &op);

    if (op == 1)
    {
      no = no->esquerda;
      tamanho++;
    }
    else if (op == 2)
    {
      no = no->direita;
      tamanho++;
    }
    else if (op == 0)
    {
      no = no->pai;
      tamanho--;
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

Node* buscaNaArvore(Tree tree, Info info, char* (*retornaId) (Info))
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
    free(z);
    printf("\ncor original = %d", corOriginal);
    if(corOriginal == PRETA)
        reparaDelecao(arvore, x);
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

    // free(no->info);
    free(no);
    no = NULL;
}

void desalocaArvore(Tree tree)
{
    Arvore* arvore = (Arvore*) tree;

    desalocaNo(arvore->raiz, arvore->nil);
}