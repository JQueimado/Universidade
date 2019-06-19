#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 400009
#define MAX_VOO 150



struct tabela
{
	char codigo[5]; // 5 bytes
	int pos; // 4 bytes                                //20mil em memoria depois passa para disco(33.18 mb)
	

};

//definir hashtable
struct hashtable 
{
	struct tabela *arr[MAX_SIZE]; 
};

/*cria uma nova hashtable em memória
*/

struct hashtable *newhash()
{
	struct hashtable *new = malloc(sizeof(struct hashtable));
	if(new == NULL)
		return NULL;

	for(int i=0;i<MAX_SIZE;i++)
		new->arr[i] = NULL;
	return new;
}

/*
*faz free da hashtable
*recebe como argumento um apontador para a hashtable e faz free de cada elemento
*/
void hash_free(struct hashtable *ht)
{
	for(int i=0;i<MAX_SIZE;i++)
		free(ht->arr[i]);
	free(ht);
}

//funcao de hash djb2 
//http://www.cse.yorku.ca/~oz/hash.html
//https://en.wikipedia.org/wiki/List_of_hash_functions#cite_note-2
int hash_function_aeroportos(char *codigo)
{
	unsigned long hash = 5381;
	int c;
	while ((c = *codigo++))
		hash = ((hash << 5) + hash) + c;  /*hash * 33 + c */	
	return hash % MAX_SIZE;
}

/*procura um aeroporto na hashtable
*recebe uma hashtable e um codigo do aeroporto
*retorna true se foi encontrado e false caso nao encontrado
*/

bool find_aeroporto(struct hashtable *ht,char *codigo)
{
	/* hash search */
	int hashIndex = hash_function_aeroportos(codigo);
	//printf("hashIndex");


	while(ht->arr[hashIndex] !=NULL)
	{

		if(strcmp(ht->arr[hashIndex]->codigo,codigo) == 0) //converter codigo para inteiro
		{
			//printf("%s\n",ht->arr[hashIndex]->codigo);	
			//printf("aqui\n");
			return true;
		}

		hashIndex+=hashIndex;
		hashIndex %= MAX_SIZE;
	}

	/* disk search */
	

	return false;
}

/*
insere um aeroporto na hashtable
recebe uma hashtable e o codigo
*/
bool inserir_aeroporto(struct hashtable *ht,char *codigo,int pos)
{
	int hashIndex = hash_function_aeroportos(codigo);

	struct tabela *tabela = malloc(sizeof(struct tabela));
	if(tabela == NULL)
		return false;
	strcpy(tabela->codigo,codigo);
	tabela->pos=pos;

	while(ht->arr[hashIndex] != NULL && strcmp(ht->arr[hashIndex]->codigo,codigo))
	{
		//printf("colisao");
		hashIndex+=hashIndex;
		hashIndex %= MAX_SIZE;
	}

	ht->arr[hashIndex] = tabela;
	return true;
}

int find_aeroportoid(struct hashtable *ht,char *codigo)
{
	/* hash search */
	int hashIndex = hash_function_aeroportos(codigo);
	//printf("hashIndex");


	while(ht->arr[hashIndex] !=NULL)
	{

		if(strcmp(ht->arr[hashIndex]->codigo,codigo) == 0) //converter codigo para inteiro
		{
			//printf("%s\n",ht->arr[hashIndex]->codigo);	
			//printf("aqui\n");
			return ht->arr[hashIndex]->pos;
		}

		hashIndex+=hashIndex;
		hashIndex %= MAX_SIZE;
	}

	/* disk search */
	

	return -1;
}