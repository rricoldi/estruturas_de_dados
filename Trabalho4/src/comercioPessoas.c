#include"comercioPessoas.h"
#include<string.h>
#include<stdlib.h>

struct tipoEstabelecimento{
    char* tipo;
    char* descricao;
};

ComercioTipo tipoComercioNovo(char* tipo, char* descricao){
    struct tipoEstabelecimento *esse = malloc(sizeof(struct tipoEstabelecimento));

    esse->tipo = malloc(strlen(tipo));
    esse->descricao = malloc(strlen(descricao));

    strcpy(esse->tipo, tipo);
    strcpy(esse->descricao, descricao);

    return esse;
}

char* comercioGetTipo(ComercioTipo ct){
    struct tipoEstabelecimento *esse = (struct tipoEstabelecimento*) ct;
    return esse->tipo;
}
char* comercioGetDescricao(ComercioTipo ct){
    struct tipoEstabelecimento *esse = (struct tipoEstabelecimento*) ct;
    return esse->descricao;
}

struct estabelecimentoComercial{
    char* cnpj;
    // char cpf[11];
    char* tipo;
    char* cep;
    char face;
    int num;
    char* nome;
};

EstabelecimentoComercial estabelecimentoNovo(char* cnpj, char* tipo, char* cep, char face, int num, char* nome){
    struct estabelecimentoComercial *esse = malloc(sizeof(struct estabelecimentoComercial));

    esse->cnpj = malloc(strlen(cnpj));
    // esse->cpf = malloc(strlen(cpf));
    esse->tipo = malloc(strlen(tipo));
    esse->cep = malloc(strlen(cep));
    esse->nome = malloc(strlen(nome));

    strcpy(esse->cnpj, cnpj);
    // strcpy(esse->cpf, cpf);
    strcpy(esse->tipo, tipo);
    strcpy(esse->cep, cep);
    strcpy(esse->nome, nome);
    esse->num = num;
    esse->face = face;

    return esse;
}

char* estabelecimentoGetCnpj(EstabelecimentoComercial ec){
    struct estabelecimentoComercial *esse = (struct estabelecimentoComercial*) ec;
    return esse->cnpj;
}
// char* estabelecimentoGetCpf(EstabelecimentoComercial ec){
//     struct estabelecimentoComercial *esse = (struct estabelecimentoComercial*) ec;
//     return esse->cpf;
// }
char* estabelecimentoGetTipo(EstabelecimentoComercial ec){
    struct estabelecimentoComercial *esse = (struct estabelecimentoComercial*) ec;
    return esse->tipo;
}
char* estabelecimentoGetCep(EstabelecimentoComercial ec){
    struct estabelecimentoComercial *esse = (struct estabelecimentoComercial*) ec;
    return esse->cep;
}
char* estabelecimentoGetNome(EstabelecimentoComercial ec){
    struct estabelecimentoComercial *esse = (struct estabelecimentoComercial*) ec;
    return esse->nome;
}
char estabelecimentoGetFace(EstabelecimentoComercial ec){
    struct estabelecimentoComercial *esse = (struct estabelecimentoComercial*) ec;
    return esse->face;
}
int estabelecimentoGetNum(EstabelecimentoComercial ec){
    struct estabelecimentoComercial *esse = (struct estabelecimentoComercial*) ec;
    return esse->num;
}

struct pessoa{
    char cpf[11];
    char* nome;
    char* sobrenome;
    char sexo;
    char* nascimento;
};

Pessoa pessoaNovo(char cpf[], char* nome, char* sobrenome, char* nascimento, char sexo){
    struct pessoa *essa = malloc(sizeof(struct pessoa));

    essa->nome = malloc(strlen(nome));
    essa->sobrenome = malloc(strlen(sobrenome));
    essa->nascimento = malloc(strlen(nascimento));

    strcpy(essa->cpf, cpf);
    strcpy(essa->nome, nome);
    strcpy(essa->sobrenome, sobrenome);
    strcpy(essa->nascimento, nascimento);
    essa->sexo = sexo;

    return essa;
}

char* pessoaGetCpf(Pessoa p){
    struct pessoa *essa = (struct pessoa*) p;
    return essa->cpf;
}
char* pessoaGetNome(Pessoa p){
    struct pessoa *essa = (struct pessoa*) p;
    return essa->nome;
}
char* pessoaGetSobrenome(Pessoa p){
    struct pessoa *essa = (struct pessoa*) p;
    return essa->sobrenome;
}
char* pessoaGetNascimento(Pessoa p){
    struct pessoa *essa = (struct pessoa*) p;
    return essa->nascimento;
}
char pessoaGetSexo(Pessoa p){
    struct pessoa *essa = (struct pessoa*) p;
    return essa->sexo;
}

void finalizarPessoa(Pessoa p){
    struct pessoa *essa = (struct pessoa*) p;

    if(essa == NULL)
        return;

    free(essa->cpf);
    free(essa->nome);
    free(essa->sobrenome);
    free(essa->nascimento);
    essa->nome = NULL;
    essa->sobrenome = NULL;
    essa->nascimento = NULL;

    free(essa);
    essa = NULL;
}

struct pessoaMoradia{
    // char cpf[11];
    char* cep;
    char face;
    int num;
    char* complemento;
};

Moradia moradiaNovo(char* cep, char face, int num, char* complemento){
    struct pessoaMoradia *esse = malloc(sizeof(struct pessoaMoradia));

    // esse->cpf = malloc(strlen(cpf));
    esse->cep = malloc(strlen(cep));
    esse->complemento = malloc(strlen(complemento));

    // strcpy(esse->cpf, cpf);
    strcpy(esse->cep, cep);
    strcpy(esse->complemento, complemento);
    esse->num = num;
    esse->face = face;

    return esse;
}

char* moradiaGetCep(Moradia m){
    struct pessoaMoradia *essa = (struct pessoaMoradia*) m;
    return essa->cep;
}
char* moradiaGetComplemento(Moradia m){
    struct pessoaMoradia *essa = (struct pessoaMoradia*) m;
    return essa->complemento;
}
char moradiaGetFace(Moradia m){
    struct pessoaMoradia *essa = (struct pessoaMoradia*) m;
    return essa->face;
}
int moradiaGetNum(Moradia m){
    struct pessoaMoradia *essa = (struct pessoaMoradia*) m;
    return essa->num;
}

void moradiaSetCep(Moradia m, char* cep){
    struct pessoaMoradia *essa = (struct pessoaMoradia*) m;
    free(essa->cep);
    essa->cep = malloc(strlen(cep));
    strcpy(essa->cep, cep);
}
void moradiaSetComplemento(Moradia m, char* complemento){
    struct pessoaMoradia *essa = (struct pessoaMoradia*) m;
    free(essa->complemento);
    essa->cep = malloc(strlen(complemento));
    strcpy(essa->complemento, complemento);
}
void moradiaSetFace(Moradia m, char face){
    struct pessoaMoradia *essa = (struct pessoaMoradia*) m;
    essa->face = face;
}
void moradiaSetNum(Moradia m, int num){
    struct pessoaMoradia *essa = (struct pessoaMoradia*) m;
    essa->num = num;
}

void finalizarMoradia(Moradia m){
    struct pessoaMoradia *essa = (struct pessoaMoradia*) m;

    if(essa == NULL)
        return;

    free(essa->cep);
    free(essa->complemento);
    essa->cep = NULL;
    essa->complemento = NULL;

    free(essa);
    essa = NULL;
}