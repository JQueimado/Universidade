/*Grafos*/

#ifndef _Grafos_
#define _Grafos_

/*Includes*/
#include <stdbool.h>
#include <stdlib.h>

/**Consts**/
#define SIZE 20;

/*Color*/
#define WHITE 1;
#define GRAY 0;
#define BLACK -1;


/****Class Vertice****/
struct Vertice 
{

	int color;
	struct User *user;

};

/*Constructor*/
struct Vertice *new_Vertice(struct User *user)
{

	struct Vertice *temp = malloc(sizeof(struct Vertice));

	temp->color = WHITE;
	temp->user = user;

	return temp;

}

/****Class SecondaryNode****/
struct SecondaryNode
{

	struct SecondaryNode *next_node;
	struct Vertice *ver;
	bool end;

};

/*Constructor*/
struct Vertice *new_SecondaryNode(struct Vertice *ver)
{

	struct SecondaryNode *temp = malloc(sizeof(struct SecondaryNode));

	temp->next_node = NULL;
	temp->ver = ver;

	return temp;

}

/****Class MainNode****/
struct MainNode
{
	
	struct MainNode *next_node;
	struct SecondaryNode *elem;

};

/*Constructor*/
struct Vertice *new_MainNode(struct MainNode *prev , struct Vertice *ver)
{

	struct Vertice *temp = malloc(sizeof(struct MainNode));

	temp->next_node = prev;
	temp->elem = new_SecondaryNode( ver );

	return temp;

}

/****Class Grafo****/
struct Grafo
{
	
	int size;
	struct MainNode *pointer_node;

};

/*Constructor*/
struct Vertice *new_Grafo()
{

	struct Vertice *temp = malloc(sizeof(struct Grafo));

	temp->size = 0;
	temp->pointer_node = new_MainNode(NULL, NULL);

	return temp;

}

/*Methods*/
int grafo_insert_vertice(struct Grafo *grafo , struct User *User)
{

	struct MainLine *last = grafo->pointer_node;

	while( last->next_node != NULL )
	{

		last = last->next_node;

	}

	last->next_node = new_MainNode( NULL , new_Vertice( user ) );

}

#endif