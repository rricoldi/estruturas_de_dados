#ifndef HASH_TABLE
#define HASH_TABLE

//	Funções referentes à Tabela de Espalhamento

#include<stdbool.h>

typedef void* HashTable;	//Ponteiro genérico para uma tabela de espalhamento
typedef void* Info;		//Ponteiro genérico para um dado qualquer desconhecido pela tabela (char, int, void*, struct, etc)

//Retorna um ponteiro para a tabela criada, com n registros disponíveis
//Caso não consiga criar a tabela, retorna NULL
HashTable criaTabela(int n);

//Insere um registro em uma posição determinada por uma função interna (hashFunction)
//Retorna o índice onde o registro foi inserido, -1 caso já exista registro na posição
int insereRegistro(HashTable, char* chave, Info);

//Retorna o registro referente a 'key'
//Retorna NULL caso o registro não exista
Info getRegistro(HashTable, char* key);

//Exclui a chave 'key' da tabela, e retorna a posição excluída
//Retorna -1 caso a chave não esteja registrada
int removeChave(HashTable, char* key);

//Retorna TRUE caso a chave esteja registrada, FALSE caso contrário
bool existeChave(HashTable, char* key);

#endif