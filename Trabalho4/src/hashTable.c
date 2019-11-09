#include"hashTable.h"
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<stdio.h>
#include"comercioPessoas.h"

struct registrado{
    char* key;
    Info info;
    struct registrado *next;    //
};

struct registros{
    struct registrado *reg;
    // struct registros *next;
};

struct tabela{
    int tamanho;
    struct registros *reg;
};

int hashFunction(char* a, int tabSize){
    int primos[] = {2, 3, 5, 7, 11, 13, 17, 23, 29, 31, 37, 41, 43, 47,53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449};
    int sum = 0;
    for(unsigned int i=0;i<strlen(a);i++){
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
        // registros[i].next = NULL;
        registros[i].reg = NULL;
    }

    tabela->tamanho = tam;
    tabela->reg = registros;

    for(int i=0;i<tam;i++){
        tabela->reg[i].reg = NULL;
        // tabela->reg[i].next = NULL;
    }
    
    return tabela;
}

int insereRegistro(HashTable tab, char* key, Info info){
    struct tabela *essa = tab;
    int posic = hashFunction(key, essa->tamanho);
    // if(existeChave(tab, key)){
    //     struct registrado *aux = essa->reg[posic].reg;
    //     while(aux->next != NULL){
    //         aux = aux->next;
    //     }
    //     aux->next = malloc(sizeof(struct registrado));
    //     aux = aux->next;

    //     aux->key = malloc(strlen(key));

    //     strcpy(aux->key, key);
    //     aux->info = info;
    //     aux->next = NULL;
    //     return posic;
    // }
    // essa->reg[posic].reg = malloc(sizeof(struct registrado));

    // essa->reg[posic].reg->key = malloc(strlen(key));

    // strcpy(essa->reg[posic].reg->key, key);
    // essa->reg[posic].reg->info = info;
    // essa->reg[posic].reg->next = NULL;
    // return posic;

    struct registrado* aux = malloc(sizeof(struct registrado));
    if(!aux){
        printf("ERRO AO ALOCAR MEMÓRIA PARA O REGISTRO\n");
        return -1;
    }
    aux->key = malloc(strlen(key)+1);
    if(!aux->key){
        printf("ERRO AO ALOCAR MEMÓRIA PARA A CHAVE\n");
        return -1;
    }
    strcpy(aux->key, key);
    aux->info = info;
    aux->next = essa->reg[posic].reg;
    essa->reg[posic].reg = aux;
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

Info getPrimeiroRegistro(HashTable tabela, char* key){
    if(!existeChave(tabela, key)){
        return NULL;
    }
    struct tabela *essa = tabela;
    int posic = hashFunction(key, essa->tamanho);
    struct registrado *aux = essa->reg[posic].reg;
    while(strcmp(aux->key, key) != 0){
        aux = aux->next;
        if(aux == NULL || aux->key == NULL)     //
            return NULL;
    }

    return essa->reg[posic].reg->info;
}
Info* getVetorRegistros(HashTable tabela, char* key, int *tamanhoVetor){
    if(!existeChave(tabela, key)){
        return NULL;
    }
    struct tabela *essa = tabela;
    int posic = hashFunction(key, essa->tamanho);
    
    Info *infoArray = NULL;
    int listSize=0;
    struct registrado *aux = essa->reg[posic].reg;
    while(aux != NULL){
        listSize++;
        aux = aux->next;
    }
    infoArray = malloc(sizeof(Info)*listSize);
    aux = essa->reg[posic].reg;
    *tamanhoVetor = 0;
    for(int i=0;i<listSize;i++){
        if(strcmp(aux->key, key)==0){
            infoArray[*tamanhoVetor] = aux->info;
            *tamanhoVetor = *tamanhoVetor +1;
        }
        aux = aux->next;
    }
    return infoArray;
}

int removeChave(HashTable tabela, char* key){
    if(!existeChave(tabela, key)){
        return -1;
    }
    struct tabela *essa = tabela;
    int posic = hashFunction(key, essa->tamanho);

    struct registrado *aux = essa->reg[posic].reg;
    struct registrado *aux2 = aux;
    while(strcmp(aux->key, key) != 0){
        aux2 = aux;
        aux = aux->next;
        if(aux == NULL){
            return -1;
        }
    }

    aux2->next = aux->next;
    free(aux->key);
    aux->key = NULL;
    free(aux);
    aux = NULL;

    return posic;
}

void hashtableFinalizar(HashTable tabela){
    struct tabela *essa = (struct tabela*)tabela;
    if(essa == NULL){
        return;
    }
    struct registrado *aux, *aux2;
    int posic;
    for(posic=0;posic<essa->tamanho;posic++){
        struct registros registro = essa->reg[posic];
        if(registro.reg != NULL){
            aux2 = registro.reg;
            do{
                aux = aux2;
                aux2 = aux->next;
                if(aux->key)
                    free(aux->key);
                // if(aux->info)
                    // free(aux->info);
                free(aux);
                aux = NULL;
            }while(aux2 != NULL);
        }
    }
    free(essa->reg);
    essa->reg = NULL;
    free(essa);
    essa = NULL;
}