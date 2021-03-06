#ifndef _hash_
#define _hash_

/*Includes*/
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "User.h"
#include "SocialNet.h"

#define SIZE 200000

struct userdados
{
	
	struct User *user;
	int key;

};
//hash construtor

struct Hash
{

	struct userdados *hashArray[SIZE];

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
		
		if(strcmp( hashtlb->hashArray[hashIndex]->user->nick, ni) == 0){
			return hashtlb->hashArray[hashIndex];
		}

		//vai para a proxima cela
		++hashIndex;

		hashIndex = hashcode(hashIndex);
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

void insert(struct Hash *hashtlb, struct User *user,int key)
{
	struct userdados *usuario = (struct userdados*) malloc(sizeof(struct userdados));
	usuario->user=user;
	usuario->key=key;

	int hashIndex = hashcode(key);

	while(hashtlb->hashArray[hashIndex]!= NULL)
	{
		++hashIndex;

		hashIndex = hashcode(hashIndex);
	}

	hashtlb->hashArray[hashIndex]=usuario;
	
}

#endif