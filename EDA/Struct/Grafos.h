/*Grafos*/

#ifndef _Grafos_
#define _Grafos_

/*Includes*/
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

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

/*Get Vertice from a given position*/
struct Vertice *grafo_get_vertice_at( struct Grafo *grafo , int position )
{

	return grafo->nodes[ position ]->ver;	

}

/*Depth search*/
struct Vertice *grafo_depth_visit(struct Grafo *grafo , struct Vertice *u , char *name[] )
{

	//time += 1;
	//u->d = time;
	u->color = GRAY;

	struct Node *temp = grafo->nodes [ u->pos ]->next_node;

	while ( temp != NULL)
	{

		struct Vertice *v = temp->ver;
		char *v_name = v->user->nick;

		if ( strcmp(v_name , name) != 0)
		{
			return v;
		}

		if (v->color == WHITE)
		{	
			
			v->p = u;
			
			struct Vertice *check = grafo_depth_visit(grafo , v , name);
			
			if( check != NULL )
			{

				return check;

			}

		}

		temp = temp->next_node;

	}
	
	u->color = BLACK;
	//time += 1;
	//u->f = time;
	return NULL;

}

struct User *grafo_depth_search( struct Grafo *grafo , char *name[] )
{	

	for (int i = 0; grafo->nodes[ i ] != NULL; ++i)
	{
		
		grafo->nodes[ i ]->ver->color = WHITE;
		grafo->nodes[ i ]->ver->p = NULL;
	
	}

	//static int time = 0;

	for (int i = 0; grafo->nodes[ i ] != NULL; ++i)
	{
		
		if ( grafo->nodes[i]->ver->color == WHITE )
		{

			struct Vertice *check = grafo_depth_visit(grafo, grafo->nodes[ i ]->ver, name);
			
			if (check != NULL)
			{
				return check->user;
			}

		}
	
	}

	return NULL;

}


/*Width search*/

#endif