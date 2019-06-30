#include "hashtable.h"

/*
new hash:
Descrição:
	cria uma hash nova

Return:
	hashtable -> nova hash table
*/
hashtable *newhash()
{
	hashtable *new = malloc(sizeof(hashtable));
	if(new == NULL)
		return NULL;

	for(int i=0;i<MAX_SIZE;i++)
		new->arr[i] = NULL;
	return new;
}

/*
hash_free:
Descrição:
	faz free da hashtable

Argumentos:
	ht -> hash a dar free
*/
void hash_free(hashtable *ht)
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

/*
find_aeroporto:
Descrição:
	procura um aeroporto na hashtable

Argumentos:
	ht 		-> hash table
	codigo 	-> codigo a procurar

Return:
	retorna true se foi encontrado e false caso nao encontrado
*/
bool find_aeroporto(hashtable *ht,char *codigo)
{
	/* hash search */
	int hashIndex = hash_function_aeroportos(codigo);
<<<<<<< HEAD

=======
>>>>>>> 48a1ebc91aa3457c410cd614efbbf814ec1daf3f

	while(ht->arr[hashIndex] !=NULL)
	{

		if(strcmp(ht->arr[hashIndex]->codigo,codigo) == 0) //converter codigo para inteiro
		{
			return true;
		}

		hashIndex+=hashIndex;
		hashIndex %= MAX_SIZE;
	}
	return false;
}

/*
inserir_aeroporto:
Descrição:
	insere um aeroporto na hashtable

Argumentos:
	ht 		-> hash table
	codigo 	-> codigo a insserir
	pos 	-> posicao na hash

Return:
	retorna true se foi adicionado e false caso contrario
*/
bool inserir_aeroporto(hashtable *ht,char *codigo,int pos)
{
	int hashIndex = hash_function_aeroportos(codigo);

	struct tabela *tabela = malloc(sizeof(struct tabela));
	if(tabela == NULL)
		return false;
	strcpy(tabela->codigo,codigo);
	tabela->pos=pos;

	while(ht->arr[hashIndex] != NULL && strcmp(ht->arr[hashIndex]->codigo,codigo))
	{
		hashIndex+=hashIndex;
		hashIndex %= MAX_SIZE;
	}

	ht->arr[hashIndex] = tabela;
	return true;
}

/*
find_aeroportopos:
Descrição:
	procura um aeroporto na hash

Argumentos:
	ht 		-> hash table
	codigo 	-> codigo a procurar
Return:
	retorna a posicao do aeroporto na hash
*/
int find_aeroportopos(hashtable *ht,char *codigo)
{
	int hashIndex = hash_function_aeroportos(codigo);
<<<<<<< HEAD

=======
>>>>>>> 48a1ebc91aa3457c410cd614efbbf814ec1daf3f

	while(ht->arr[hashIndex] !=NULL)
	{

		if(strcmp(ht->arr[hashIndex]->codigo,codigo) == 0) //converter codigo para inteiro
		{
			return ht->arr[hashIndex]->pos;
		}

		hashIndex+=hashIndex;
		hashIndex %= MAX_SIZE;
	}
<<<<<<< HEAD

	
	

=======
>>>>>>> 48a1ebc91aa3457c410cd614efbbf814ec1daf3f
	return -1;
}