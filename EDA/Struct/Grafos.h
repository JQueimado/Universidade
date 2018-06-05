/*Grafos*/

#ifndef _Grafos_
#define _Grafos_

/*Includes*/
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "User.h"

/**Consts**/
#define SIZE 20
#define MAX_USERS 1000000
#define NORMAL 0
#define ERROR 1

/*Color*/
#define WHITE 1
#define GRAY 0
#define BLACK -1

/*

Implementação de Grafos como uma listas de adjacências

*/

/****Class Vertice****/
struct Vertice 
{

	int pos;
	struct User *user;
	
	int color;
	struct Vertice *p;
	int d;
	int f;

};

/*Constructor*/
struct Vertice *new_Vertice(struct User *user , int p )
{

	struct Vertice *temp = malloc( sizeof( struct Vertice ) );

	temp->color = WHITE;
	temp->pos = p;
	temp->user = user;

	return temp;

}

/****Class Node****/
struct Node
{

	struct Node *next_node;
	struct Vertice *ver;
	bool end;

};

/*Constructor*/
struct Node *new_Node(struct Vertice *ver)
{

	struct Node *temp = malloc(sizeof(struct Node));

	temp->next_node = NULL;
	temp->ver = ver;

	return temp;

}

/****Class Grafo****/
struct Grafo
{
	
	int size;
	struct Node *nodes[MAX_USERS];

};

/*Constructor*/
struct Grafo *new_Grafo()
{

	struct Grafo *temp = malloc(sizeof(struct Grafo));

	temp->size = 0;

	return temp;

}

/*Methods*/

/*Add Vertice*/
int grafo_insert_vertice(struct Grafo *grafo , struct User *user)
{	

	/*Check if arg are given*/
	if ( grafo == NULL || user == NULL )
	{
		return ERROR;
	}

	/*Check for free space*/
	if ( grafo->size >= MAX_USERS )
	{
		return ERROR;
	}

	/*adds vertice*/
	struct Node *temp = new_Node( new_Vertice( user , grafo->size ) );
	grafo->nodes[ grafo->size ] = temp;
	grafo->size += 1;

	return NORMAL;

}

/*Add Conection*/
int grafo_insert_conection(struct Grafo *grafo , struct Vertice *v1 , struct Vertice *v2 )
{

	/*Check if arg are given*/
	if ( v1 == NULL || v2 == NULL )
	{
		return ERROR;
	}

	if ( v1->pos >= grafo->size || v1->pos < 0 )
	{
		return ERROR;
	}

	if ( v2->pos >= grafo->size || v2->pos < 0 )
	{
		return ERROR;
	}

	/*vars*/
	int pos = v1->pos;
	struct Node *temp = grafo->nodes[ pos ];
	
	/*look for last node*/
	while( temp->next_node != NULL )
	{

		temp = temp->next_node;	

	}

	/*add node*/
	temp->next_node = new_Node( v2 );

	return NORMAL;

}

int grafo_remove_conection(struct Grafo *grafo, struct Vertice *v1, struct Vertice *v2)
{

	struct Node *n = grafo->nodes[ v1->pos ];
	struct Node *p;
	
	p = n;
	n = n->next_node;
	
	while(n != NULL)
	{

		if (n->ver->pos == v2->pos)
		{

			p->next_node = n->next_node;
			return NORMAL;

		}

		p = n;
		n = n->next_node;

	}

	return ERROR;

}

int grafo_remove_vertice(struct Grafo *grafo , struct Vertice *v)
{

	if (grafo == NULL)
		return ERROR;

	if (v == NULL)
		return NORMAL;

	/*remove conections to vertice*/
	int sp = 0;
	for (int i = 0; sp <grafo->size ; ++i)
	{
		if (grafo->nodes != NULL)
		{
			
			grafo_remove_conection(grafo , grafo->nodes[i]->ver, v);

			sp +=1;
		}

	}

	/*remove node*/
	grafo->nodes[ v->pos ] = NULL;
	grafo->size -= 1;
	return NORMAL;

}

/*Get Vertice from a given position*/
struct Vertice *grafo_get_vertice_at( struct Grafo *grafo , int position )
{

	return grafo->nodes[ position ]->ver;	

}

/*Find user*/

struct Vertice *grafo_get_vertice_by_name(struct Grafo *grafo, char *name)
{

	for (int i = 0; i < grafo->size; ++i)
	{
		struct Vertice *v = grafo_get_vertice_at(grafo , i);

		if( strcmp( v->user->nick , name ) == 0 )
		{

			return v;

		}

	}

	return NULL;

}

/*print*/
void grafo_print_all(struct Grafo *grafo)
{
	puts("start");
	int sp = 0;
	for (int i = 0; sp < grafo->size; ++i)
	{
		if (grafo->nodes[i] != NULL)
		{
		
			struct Vertice *v = grafo_get_vertice_at(grafo ,i);
	
			printf("user at %d is %s\n", sp+1 , v->user->nick );
		
			sp += 1;
		}

	}
	puts("done");

}

void grafo_print_conections_at (struct Grafo *grafo, int i)
{
	struct Node *n = grafo->nodes[i];

	printf("user %s folows: \n", n->ver->user->nick);

	n = n->next_node;
	
	if (n == NULL)
	{
		puts("None");
	}

	while(n != NULL)
	{

		printf("%s\n", n->ver->user->nick);

		n = n->next_node;

	}

}



#endif