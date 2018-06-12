#ifndef hash
#define hash

/*Includes*/
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "User.h"

#define SIZE 100000

struct userdados
{
	struct User *user;
	int key;

};
//hash construtor

struct userdados *new_hash(){

	struct userdados *temp= malloc (sizeof(struct userdados));
    
    return temp;
}

struct userdados *hashArray[SIZE];
struct userdados *usuario;
struct userdados *tempdelete;
struct userdados *dummyItem;

int hashcode(int key)
{
	return key % SIZE;
}

struct userdados *search(int key,char ni[])
{
	//index para a hash
	int hashIndex = hashcode(key);

	while(hashArray[hashIndex]!=NULL)
	{
		if(hashArray[hashIndex]->user->nick==ni)
			return hashArray[hashIndex];

		//vai para a proxima cela
		++hashIndex;

		hashIndex%=SIZE;
	}

	return NULL;


}

void insert(struct User *user,int key)
{
	struct userdados *usuario = (struct userdados*) malloc(sizeof(struct userdados));
	usuario->user=user;
	usuario->key=key;

	int hashIndex = hashcode(key);

	while(hashArray[hashIndex]!= NULL)
	{
		++hashIndex;

		hashIndex%=SIZE;
	}

	hashArray[hashIndex]=usuario;
}


struct userdados *delete(struct userdados *usuario)
{
	int key=usuario->key;

	int hashIndex=hashcode(key);

	while(hashArray[hashIndex]!=NULL)
	{
		if(hashArray[hashIndex]->key==key)
		{
			struct userdados *temp = hashArray[hashIndex];
			hashArray[hashIndex]=tempdelete;
			return temp;
		}

		//vai para a proxima cela
		++hashIndex;

		hashIndex%=SIZE;
	}
	return NULL;
}

void display() {
   int i = 0;
	
   for(i = 0; i<SIZE; i++) {
	
      if(hashArray[i] != NULL)
         printf(" (%d,%s)",hashArray[i]->key,hashArray[i]->user->nick);
      else
         printf(" ~~ ");
   }
	
   printf("\n");
}



#endif