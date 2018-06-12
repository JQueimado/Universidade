#ifndef _hash_
#define _hash_

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

struct Hash
{

	struct userdados *hashArray[SIZE];
	

	struct userdados *tempdelete;


};

struct Hash *new_hash(){

	struct Hash *temp= malloc (sizeof(struct Hash));

    return temp;
}

/*
struct userdados *hashArray[SIZE];
struct userdados *usuario;
struct userdados *hashtlb->tempdelete;
struct userdados *dummyItem;
*/

int hashcode(int key)
{
	return key % SIZE;
}

struct userdados *search(struct Hash *hashtlb, int key, char ni[])
{

	//index para a hash
	int hashIndex = hashcode(key);

	while(hashtlb->hashArray[hashIndex]!=NULL)
	{
		
		if(hashtlb->hashArray[hashIndex]->user->nick==ni){
			return hashtlb->hashArray[hashIndex];
		}


		//vai para a proxima cela
		++hashIndex;

		hashIndex%=SIZE;
	}

	return NULL;


}

void insert(struct Hash *hashtlb, struct User *user,int key)
{
	struct userdados *usuario = (struct userdados*) malloc(sizeof(struct userdados));
	usuario->user=user;
	usuario->key=key;

	int hashIndex = hashcode(key);

	while(hashtlb->hashArray[hashIndex]!= NULL)
	{
		++hashIndex;

		hashIndex%=SIZE;
	}

	hashtlb->hashArray[hashIndex]=usuario;
}


struct userdados *hash_delete(struct Hash *hashtlb, struct userdados *usuario)
{
	int key=usuario->key;

	int hashIndex=hashcode(key);

	while(hashtlb->hashArray[hashIndex]!=NULL)
	{
		if(hashtlb->hashArray[hashIndex]->key==key)
		{
			struct userdados *temp =hashtlb->hashArray[hashIndex];
			hashtlb->hashArray[hashIndex]=hashtlb->tempdelete;
			return temp;
		}

		//vai para a proxima cela
		++hashIndex;

		hashIndex%=SIZE;
	}
	return NULL;
}

void display(struct Hash *hashtlb) {
   int i = 0;
	
   for(i = 0; i<SIZE; i++) {
	
      if(hashtlb->hashArray[i] != NULL)
         printf(" (%d,%s)", hashtlb->hashArray[i]->key, hashtlb->hashArray[i]->user->nick);
      else
         printf(" ~~ ");
   }
	
   printf("\n");
}



#endif