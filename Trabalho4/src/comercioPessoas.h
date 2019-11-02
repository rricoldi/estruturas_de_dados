#ifndef COMERCIOPESSOAS_H
#define COMERCIOPESSOAS_H

/** As funções desse header tratam da criação e controle
 *   de pessoas, estabelecimentos comerciais e tipos de estabelecimentos
 * */

//Tipo abstrato: tipo de estabelcimeto comercial
typedef void* ComercioTipo;

//Cria um novo tipo de estabelecimento comercial
ComercioTipo tipoComercioNovo(char* tipo, char* descricao);

//Getters dos tipos de estabelecimentos comerciais
char* comercioGetTipo(ComercioTipo);
char* comercioGetDescricao(ComercioTipo);


//Tipo abstrato: estabelecimento comercial
typedef void* EstabelecimentoComercial;

//Cria um novo estabelecimento comercial
EstabelecimentoComercial estabelecimentoNovo(char* cnpj, char* tipo, char* cep, char face, int num, char* nome);

//Getters dos estabelecimentos comerciais
char* estabelecimentoGetCnpj(EstabelecimentoComercial);
char* estabelecimentoGetCpf(EstabelecimentoComercial);
char* estabelecimentoGetTipo(EstabelecimentoComercial);
char* estabelecimentoGetCep(EstabelecimentoComercial);
char* estabelecimentoGetNome(EstabelecimentoComercial);
char estabelecimentoGetFace(EstabelecimentoComercial);
int estabelecimentoGetNum(EstabelecimentoComercial);


//Tipo abstrato: pessoa
typedef void* Pessoa;

//Cria uma nova pessoa, e a retorna
Pessoa pessoaNovo(char cpf[], char* nome, char* sobrenome, char* nascimento, char sexo);

//Getters dos atributos de Pessoa
char* pessoaGetCpf(Pessoa);
char* pessoaGetNome(Pessoa);
char* pessoaGetSobrenome(Pessoa);
char* pessoaGetNascimento(Pessoa);
char pessoaGetSexo(Pessoa);

//Libera toda a memória alocada para a pessoa, e aponta para NULL
void finalizarPessoa(Pessoa);


//Tipo abstrato: residência da pessoa identificada pelo cpf
typedef void* Moradia;

//Cria e retorna uma nova moradia
Moradia moradiaNovo(char* cep, char face, int num, char* complemento);

//Getters dos atributos das moradias
char* moradiaGetCep(Moradia);
char* moradiaGetComplemento(Moradia);
char moradiaGetFace(Moradia);
int moradiaGetNum(Moradia);

//Setters dos atributos das moradias
void moradiaSetCep(Moradia, char* cep);
void moradiaSetComplemento(Moradia, char* complemento);
void moradiaSetFace(Moradia, char face);
void moradiaSetNum(Moradia, int num);

//Libera toda a memória alocada para a moradia, e aponta para NULL
void finalizarMoradia(Moradia);

#endif