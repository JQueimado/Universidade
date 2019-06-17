#ifndef _HASH_
#define _HASH
#include <stdbool.h>
#define MAX_SIZE 200003
#define MAX_VOO 150



struct hashtable;
struct hashtable *newhash();
void hash_free(struct hashtable *ht);
int hash_function_aeroportos(char *codigo);
bool find_aeroporto(struct hashtable *ht,char *codigo);
bool inserir_aeroporto(struct hashtable *ht,char *codigo);
#endif
