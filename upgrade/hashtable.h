#ifndef _HASH_
#define _HASH_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 20011
#define MAX_VOO 150

struct tabela
{
	char codigo[5]; // 5 bytes
	int pos; 		// 4 bytes                                
	
	//20mil em memoria depois passa para disco(33.18 mb)
	
} typedef tabela; //9 bytes + 3 bytes = 12 bytes = 3 paginas

//definir hashtable
struct hashtable 
{
	struct tabela *arr[MAX_SIZE]; // 4 * MAX_Size
} 
typedef hashtable;

struct hashtable *newhash();

void hash_free(struct hashtable *ht);

int hash_function_aeroportos(char *codigo);

bool find_aeroporto(struct hashtable *ht,char *codigo);

bool inserir_aeroporto(struct hashtable *ht,char *codigo,int pos);

void print_hash(struct hashtable *ht);

int find_aeroportopos(struct hashtable *ht,char *codigo);

#endif