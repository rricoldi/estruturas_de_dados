#ifndef COMERCIOPESSOAS_H
#define COMERCIOPESSOAS_H

/** As funções desse header tratam da criação e controle
 *   de pessoas, estabelecimentos comerciais e tipos de estabelecimentos
 * */

//Tipo abstrato: tipo de estabelcimeto comercial
typedef void* ComercioTipo;

//Cria um novo tipo de estabelecimento comercial;
//Pré-requisito: tipo e descrição existem;
//Pós condição: tipo criado
ComercioTipo tipoComercioNovo(char* tipo, char* descricao);

//Getters dos tipos de estabelecimentos comerciais;
//Pré-requisito: ComercioTipo existe;
//Pós condição: -.
char* comercioGetTipo(ComercioTipo);
char* comercioGetDescricao(ComercioTipo);

//Libera a memória do Tipo de Comércio, e seta o ponteiro para NULL;
//Pré-requisito: ComercioTipo existe;
//Pós condição: ComercipTipo não existe mais;
void* comercioFinalizar(ComercioTipo);

//Todas as funções são analogas às funções de ComercioTipo

typedef void* EstabelecimentoComercial;

EstabelecimentoComercial estabelecimentoNovo(char* cnpj, char* cpf, char* tipo, char* cep, char face, int num, char* nome);

char* estabelecimentoGetCnpj(EstabelecimentoComercial);
char* estabelecimentoGetCpf(EstabelecimentoComercial);
char* estabelecimentoGetTipo(EstabelecimentoComercial);
char* estabelecimentoGetCep(EstabelecimentoComercial);
char* estabelecimentoGetNome(EstabelecimentoComercial);
char estabelecimentoGetFace(EstabelecimentoComercial);
int estabelecimentoGetNum(EstabelecimentoComercial);

void* estabelecimentoFinalizar(EstabelecimentoComercial);


typedef void* Pessoa;

Pessoa pessoaNovo(char* cpf, char* nome, char* sobrenome, char* nascimento, char sexo);

char* pessoaGetCpf(Pessoa);
char* pessoaGetNome(Pessoa);
char* pessoaGetSobrenome(Pessoa);
char* pessoaGetNascimento(Pessoa);
char pessoaGetSexo(Pessoa);

void* pessoaFinalizar(Pessoa);


typedef void* Moradia;

Moradia moradiaNovo(char* cep, char face, int num, char* complemento);

char* moradiaGetCep(Moradia);
char* moradiaGetComplemento(Moradia);
char moradiaGetFace(Moradia);
int moradiaGetNum(Moradia);

void moradiaSetCep(Moradia, char* cep);
void moradiaSetComplemento(Moradia, char* complemento);
void moradiaSetFace(Moradia, char face);
void moradiaSetNum(Moradia, int num);

void* moradiaFinalizar(Moradia);

#endif