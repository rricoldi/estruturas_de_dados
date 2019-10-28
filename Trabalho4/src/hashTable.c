#include"hashTable.h"
#include<stdlib.h>
#include<stdbool.h>

struct registros{
    char* key;
    Info info;
};

struct tabela{
    int tamanho;
    struct registros *reg;
};

int primos[] = {2, 3, 5, 7, 11, 13, 17, 23, 29, 31, 37};
int hashFunction(char* a, int tabSize){
    int sum = 0;
    for(int i=0;i<11;i++){
        sum += a[i]*primos[i];
    }
    sum = sum%tabSize;
    return sum;
}

HashTable criaTabela(int tam){
    if(tam<=0){
        return NULL;
    }

    struct registros *registros = malloc(sizeof(struct registros) * tam);
    struct tabela *tabela = malloc(sizeof(struct tabela));
    tabela->tamanho = tam;
    tabela->reg = registros;

    for(int i=0;i<tam;i++){
        tabela->reg[i].key = NULL;
        tabela->reg[i].info = NULL;
    }
    
    return tabela;
}

int insereRegistro(HashTable tab, char* key, Info info){
    struct tabela *essa = tab;
    if(existeChave(tab, key)){
        return -1;
    }
    int posic = hashFunction(key, essa->tamanho);
    essa->reg[posic].key = key;
    essa->reg[posic].info = info;
    return posic;
}

bool existeChave(HashTable tab, char* key){
    struct tabela *essa = tab;
    int posic = hashFunction(key, essa->tamanho);
    if(essa->reg[posic].key == NULL){
        return false;
    }
    return true;
}

Info getRegistro(HashTable tabela, char* key){
    if(!existeChave(tabela, key)){
        return NULL;
    }
    struct tabela *essa = tabela;
    int posic = hashFunction(key, essa->tamanho);
    return essa->reg[posic].info;
}

int removeChave(HashTable tabela, char* key){
    if(!existeChave(tabela, key)){
        return -1;
    }
    struct tabela *essa = tabela;
    int posic = hashFunction(key, essa->tamanho);
    essa->reg[posic].key = NULL;
    essa->reg[posic].info = NULL;
    return posic;
}