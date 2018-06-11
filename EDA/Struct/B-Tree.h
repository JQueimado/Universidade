
#ifndef _BTree_
#define _BTree_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "User.h"

#define FILE_NAME "Cache.txt"
#define M 32

/*Structs*/
struct Node
{
	
	int n;
	struct User *key[M-1];
	//struct User *ḱey[M - 1];
	struct Node *c[M];
	bool leaf;

};
struct BTree
{
	struct Node *root;
};
/*struct BTree 
{

	struct Node *root;

};*/

/*Disk Acsses*/

void Disk_Write(struct Node *x)
{
	FILE *file_pointer = fopen(FILE_NAME , "wb");

	fwrite(x ,1,sizeof(struct Node), file_pointer);

	fclose(file_pointer);


}

/*struct Node *Disk_Read()
{


}*/

/*Constructors*/
struct BTree *new_BTree()
{
	struct BTree *tree=malloc(sizeof(struct BTree));
	struct Node *x = malloc(sizeof(struct Node));

	x->leaf=true;
	x->n=0;

	Disk_Write(x);

	tree->root=x;

	return tree;
}

struct BTree *insert_BTree(struct BTree *tree,)
{
	r=tree->root;
	//if(r->n==s)
}


#endif