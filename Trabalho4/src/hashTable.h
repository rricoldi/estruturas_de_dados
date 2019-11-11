#ifndef HASH_TABLE
#define HASH_TABLE

//	Funções referentes à Tabela de Espalhamento

#include<stdbool.h>

typedef void* HashTable;	//Ponteiro genérico para uma tabela de espalhamento
typedef void* Info;		//Ponteiro genérico para um dado qualquer

//Retorna um ponteiro para a tabela criada, com n registros disponíveis
//Caso não consiga criar a tabela, retorna NULL
HashTable criaTabela(int n);

//Insere um registro em uma posição determinada por uma função interna (hashFunction)
//Retorna o índice onde o registro foi inserido
int insereRegistro(HashTable, char* chave, Info);

//Retorna o registro referente a 'key'
//Retorna NULL caso o registro não exista
Info getPrimeiroRegistro(HashTable, char* key);

//Retorna um vetor com todos os registros referentes à 'key'
//tamanhoDoVetor é a quantidade de registros encontrados
Info* getVetorRegistros(HashTable, char* key, int* tamanhoDoVetor);

//Exclui a chave 'key' da tabela, e retorna a posição excluída
//Retorna -1 caso a chave não esteja registrada
int removeChave(HashTable, char* key);

//Retorna TRUE caso a chave esteja registrada, FALSE caso contrário
bool existeChave(HashTable, char* key);

//Libera todos os registros da HashTable, além da pŕopria tabela
//A tabela passada recebe NULL, e fica inutilizável
void HshTblMap(HashTable, void (*func)(Info));
void* hashtableFinalizar(HashTable);
#endif