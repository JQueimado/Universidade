/*Grafos*/

#ifndef _Grafos_
#define _Grafos_

/*Includes*/
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "User.h"
#include "hash.h"
#include "SocialNet.h"

/**Consts**/

#define MAX_USERS 10000000
#define NORMAL 0
#define ERROR 1
#define LEN 100

/*

Implementação de Grafos como uma listas de adjacências

*/

/****Class Vertice****/
struct Vertice 
{

	int pos;
	struct User *user;
	unsigned short msg_send;

};

/*Constructor*/
struct Vertice *new_Vertice(struct User *user , int p )
{

	struct Vertice *temp = malloc( sizeof( struct Vertice ) );

	temp->pos = p;
	temp->user = user;
	temp->msg_send=0;

	return temp;

}

/*Methods*/
bool vertice_compare ( struct Vertice *v1 , struct Vertice *v2 )
{

	if (v1 == NULL || v2 == NULL)
	{
		return false;
	}

	return compare_user(v1->user , v2->user);

}

/****Class Node****/
struct Node
{

	struct Node *next_node;
	struct Vertice *ver;
	unsigned short msg_rcv;

};

/*Constructor*/
struct Node *new_Node(struct Vertice *ver)
{

	struct Node *temp = malloc(sizeof(struct Node));

	temp->next_node = NULL;
	temp->ver = ver;
	temp->msg_rcv = 0;
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

/*Get Vertice from a given position*/
struct Vertice *grafo_get_vertice_at( struct Grafo *grafo , int position )
{

	return grafo->nodes[ position ]->ver;	

}

/*Find user*/

struct Vertice *grafo_get_vertice_by_name(struct Grafo *grafo, char *name)
{
	int sp = 0;
	for (int i = 0; sp < grafo->size; ++i)
	{	
		if (grafo->nodes[i] != NULL)
		{
			
			sp++;

			struct Vertice *v = grafo_get_vertice_at(grafo , i);

			if( strcmp( v->user->nick , name ) == 0 )
			{

				return v;

			}
		}

	}

	return NULL;

}

/*Checks if v is in grafo*/
bool grafo_check_if_exists (struct Grafo *grafo , struct Vertice *v)
{

	if (grafo == NULL)
	{
		return NULL;
	}

	if (v == NULL)
	{
		return NULL;
	}
	int sp = 0;
	for (int i = 0; sp < grafo->size; ++i)
	{
		
		if (grafo->nodes[i] != NULL)
		{
		
			if (vertice_compare( grafo_get_vertice_at(grafo , i) , v) )
			{
				return true;
			}

			sp += 1;
		
		}

	}

	return false;

}

/*Checks if v1 is connected to v2*/
bool grafo_check_connection(struct Grafo * grafo, struct Vertice *v1 , struct Vertice *v2)
{

	if (grafo == NULL)
	{
		return NULL;
	}

	if (v1 == NULL)
	{
		return NULL;
	}

	if (v2 == NULL)
	{
		return NULL;
	}

	struct Node *n = grafo->nodes[ v1->pos ];

	n = n->next_node;

	while( n != NULL )
	{

		if ( vertice_compare (n->ver , v2) )
		{
			return true;
		}

		n = n->next_node;

	}

	return false;

}

bool grafo_connection_count_check(struct Grafo * grafo,struct Vertice *v1)
{
	
	int count=0;
	if(grafo==NULL)
		return false;
	if(v1==NULL)
		return false;
	if(grafo->nodes[ v1->pos ]==NULL)
		return false;

	struct Node *n = grafo->nodes[ v1->pos ];

	//printf("%s\n", n->ver->user->nick);




	n = n->next_node;

	while(n != NULL)
	{

		//printf("%s\n", n->ver->user->nick);

		n = n->next_node;
		count++;

	}

	if(count>=100)
		return true;
	else 
		return false;

} 

/*counts all conections to a vertice*/
int grafo_connection_count(struct Grafo * grafo,struct Vertice *v1)
{
	
	int count=0;
	if(grafo==NULL)
		return false;
	if(v1==NULL)
		return false;
	if(grafo->nodes[ v1->pos ]==NULL)
		return false;

	struct Node *n = grafo->nodes[ v1->pos ];

	//printf("%s\n", n->ver->user->nick);

	
	
	n=n->next_node;
	while(n != NULL)
	{
	
		//printf("%s\n", n->ver->user->nick);
		//n = n->next_node;
		
		if(n->ver->user==NULL)
			{
				return false;
			}
		
		//if(n->ver->user->removed==false)
			count++;
		n=n->next_node;
		
		/*if (!n->ver->user->removed)
		{
			count++;
			
		}*/
		
		//if(!(n->ver->user->removed))
			
		//count++;
		

	}

	return count;

} 

/*Add Vertice*/
struct Vertice *grafo_insert_vertice(struct Grafo *grafo , struct User *user)
{	

	/*Check if arg are given*/
	if ( grafo == NULL || user == NULL )
	{

		return NULL;
	}

	/*Check for free space*/
	if ( grafo->size >= MAX_USERS )
	{
		
		return NULL;
	}
	if( grafo_check_if_exists (grafo ,grafo_get_vertice_by_name(grafo, user->nick) ))
	{
		return NULL;
	}


	/*adds vertice*/
	struct Vertice *v = new_Vertice( user , grafo->size );
	struct Node *temp = new_Node( v );
	grafo->nodes[ grafo->size ] = temp;
	grafo->size += 1;

	return v;

}

/*Add Conection*/
struct Node *grafo_insert_conection(struct Grafo *grafo , struct Vertice *v1 , struct Vertice *v2 )
{

	/*Check if arg are given*/
	if ( v1 == NULL || v2 == NULL )
	{
		return NULL;
	}
	if ( v1->pos >= MAX_USERS || v1->pos < 0 )
	{
		return NULL;
	}
	if ( v2->pos >= MAX_USERS || v2->pos < 0 )
	{
		return NULL;
	}

	/*vars*/
	int pos = v1->pos;
	struct Node *temp = grafo->nodes[ pos ];

	/*look for last node*/
	while(temp->next_node != NULL)
	{

		if (strcmp(temp->next_node->ver->user->nick, v2->user->nick) > 0)
		{
			break;
		}

		temp = temp->next_node;	

	}

	/*add node*/
	struct Node *n = new_Node(v2);

	if (temp->next_node == NULL)
	{

		temp->next_node = n;

	}
	else
	{
		
		n->next_node = temp->next_node;
		temp->next_node = n;
	
	}
	
	return n;

}

bool grafo_remove_conection(struct Grafo *grafo, struct Vertice *v1, struct Vertice *v2)
{
	
	/*
	if(v1 == NULL || v2 == NULL)
	{
		return false;
	}
	*/

	struct Node *n = grafo->nodes[ v1->pos ];
	struct Node *p;

	if(n->next_node ==NULL)
		return false;

	p = n;
	n = n->next_node;


	while(n != NULL)
	{
		
    	if ( vertice_compare(n->ver , v2))
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
		return ERROR;

	/*remove conections to vertice*/
	int sp = 0;
	for (int i = 0; sp <grafo->size ; ++i)
	{
		if (grafo->nodes != NULL)
		{
			
			//grafo_remove_conection(grafo , grafo->nodes[i]->ver, v);

			sp +=1;
		}

	}

	/*remove node*/
	grafo->nodes[ v->pos ] = NULL;
	grafo->size -= 1;
	return NORMAL;

}


void grafo_get_conected_to(struct Grafo *g , struct Vertice *v,struct User *arr[])
{

	struct Node *n = g->nodes[v->pos];
	
	int i = 0;

	n = n->next_node;
	
	while (n != NULL)
	{

		arr[i] = n->ver->user;

		//puts("conseas");
		n=n->next_node;
		i++;

	}

}

/**DB Storage**/

/*dumps all user information to a file*/
bool grafo_dump_folows(struct Grafo *grafo, FILE *file)
{
	if (file == NULL)
	{
		return false;
	}

	int sp = 0;

	for (int i = 0; sp < grafo->size; ++i)
	{

		if (grafo->nodes[i] != NULL)
		{

			struct Node *n = grafo->nodes[i];
			struct Node *cur_n = n;
			n = n->next_node;

			while (n != NULL)
			{
				struct User *u1 = cur_n->ver->user;
				struct User *u2 = n->ver->user;

				fprintf(file, "%s %s\n", u1->nick , u2->nick);

				n = n->next_node;

			}

			sp += 1;

		}

	}

	return true;
}

int count_conection_seguidores(struct Grafo * grafo,struct Vertice *v1)
{
	int count=0;
	if(grafo==NULL)
		return false;
	if(v1==NULL)
		return false;
	if(grafo->nodes[ v1->pos ]==NULL)
		return false;


	//printf("%s\n", n->ver->user->nick);
	

	int sp = 0;
	for (int i = 0; sp < grafo->size; ++i)
	{
		
		if (grafo->nodes[i] != NULL)
		{
			if(grafo_check_connection(grafo,grafo_get_vertice_at(grafo , i)  , v1) )
			{
				count++;
			}

			sp+=1;

		
		}

	}



	return count;

}



bool send_msg(struct Grafo *grafo, struct User *u)
{

	struct Vertice *ver = grafo_get_vertice_by_name(grafo, u->nick);

	if (ver == NULL)
	{

		ver = grafo_insert_vertice(grafo, u);

	}

	ver->msg_send+=1;

	return true;

}

/**Degug prints**/

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