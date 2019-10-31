#include"hashTable.h"
#include<stdlib.h>
#include<stdbool.h>

struct registrado{
    char* key;
    Info info;
};

struct registros{
    struct registrado *reg;
    struct registros *next;
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

    for(int i=0;i<tam;i++){
        registros[i].next = NULL;
        registros[i].reg = NULL;
    }

    tabela->tamanho = tam;
    tabela->reg = registros;

    for(int i=0;i<tam;i++){
        tabela->reg[i].reg = NULL;
        tabela->reg[i].next = NULL;
    }
    
    return tabela;
}

int insereRegistro(HashTable tab, char* key, Info info, size_t infoSize){
    struct tabela *essa = tab;
    int posic = hashFunction(key, essa->tamanho);
    if(existeChave(tab, key)){
        struct registros *aux = essa->reg;
        while(aux != NULL){
            aux = aux->next;
        }
        aux->reg = malloc(sizeof(struct registrado));
        strcpy(aux->reg->key, key);
        memcpy(aux->reg->info, info, infoSize);
        aux->next = NULL;

        return posic;
    }
    
    essa->reg->reg = malloc(sizeof(struct registrado));

    strcpy(essa->reg->reg->key, key);
    memcpy(essa->reg[posic].reg->info, info, infoSize);
    return posic;
}

bool existeChave(HashTable tab, char* key){
    struct tabela *essa = tab;
    int posic = hashFunction(key, essa->tamanho);
    if(essa->reg[posic].reg == NULL){
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
    
    struct registros *aux = essa->reg;
    while(strcmp(aux->reg->key, key) != 0){
        aux = aux->next;
        if(aux->reg == NULL)
            return NULL;
    }

    return essa->reg[posic].reg->info;
}

int removeChave(HashTable tabela, char* key){
    if(!existeChave(tabela, key)){
        return -1;
    }
    struct tabela *essa = tabela;
    int posic = hashFunction(key, essa->tamanho);

    struct registros *aux = essa->reg;
    struct registros *aux2 = aux;
    while(strmp(aux->reg->key) != 0){
        aux2 = aux;
        aux = aux->next;
        if(aux->reg == NULL)
            return NULL;
    }

    aux2->next = aux->next;
    free(aux->reg);
    free(aux);

    return posic;
}