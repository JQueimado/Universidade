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

#define MAX_USERS 1000000
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
	
	if (n == NULL)
	{
		puts("None");
	}

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




	n = n->next_node;
	
	

	while(n != NULL)
	{

		//printf("%s\n", n->ver->user->nick);

		n = n->next_node;
		count++;

	}

	return count;

} 

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
	if( grafo_check_if_exists (grafo ,grafo_get_vertice_by_name(grafo, user->nick) ))
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

	puts("cona1");

	/*look for last node*/
	while(temp->next_node != NULL)
	{
		
		if (strcmp(temp->ver->user->nick, v2->user->nick) < 0)
		{
			break;
		}

		temp = temp->next_node;	

	}

	/*add node*/
	struct Node *n = temp->next_node;
	temp->next_node = new_Node(v2);
	temp->next_node->next_node = n;

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
			
			grafo_remove_conection(grafo , grafo->nodes[i]->ver, v);

			sp +=1;
		}

	}

	/*remove node*/
	grafo->nodes[ v->pos ] = NULL;
	grafo->size -= 1;
	return NORMAL;

}

void grafo_get_conected_to(struct Grafo *g , struct Vertice *v , struct User *arr[])
{

	struct Node *n = g->nodes[v->pos];
	//puts("coni");
	int i = 0;

	n = n->next_node;
	//puts("con2");
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

/*unpacks a Grafo from a file and links it to a trie*/
void grafo_unpack (struct Grafo *g , FILE *file )
{
/*
	char out[13];

	while(fgets(out , 13 , file))
	{

		int i = 0;

		char u1[6];

		while(out[i] != ' ')
		{

			u1[i] = out[i];

			i++;

		}

		u1[i] = '\0';

		i++;

		int j = 0;

		char u2[6];

		while(out[i] != '\n')
		{

			u2[j] = out[i];

			j++;

			i++;

		}

		u2[j] = '\0';

		if (grafo_get_vertice_by_name(g , u1) == NULL)
		{

			struct User *temp = search(socialnet->hashnick,u1[0] , u1)->user;
			grafo_insert_vertice(g , temp);

		}

		if (grafo_get_vertice_by_name(g , u2) == NULL)
		{

			struct User *temp = search(socialnet->u2[0],u2)->user;
			grafo_insert_vertice(g , temp);

		}

		grafo_insert_conection(g , grafo_get_vertice_by_name(g ,u1) , grafo_get_vertice_by_name(g, u2));

	}
*/
}

bool send_msg(struct Grafo *grafo, struct User *u)
{

	struct Vertice *ver = grafo_get_vertice_by_name(grafo, u->nick);

	if (ver == NULL)
	{

		return false;

	}

	ver->msg_send+=1;

	return true;

}

bool read_msg(struct Grafo *grafo, struct User *u , FILE *pointer)
{
	struct Vertice *v = grafo_get_vertice_by_name(grafo, u->nick);

	struct Node *n = grafo->nodes[v->pos];

	if (n->next_node == NULL)
	{
		printf("+ utilizador %s sem seguidos\n", u->nick);
	}

	while(n->next_node != NULL)
	{

		n = n->next_node;

		if (n->msg_rcv == n->ver->msg_send)
		{
			printf("sem mensagens novas de %s (%s)\n", n->ver->user->nick, get_name(n->ver->user, pointer));
			continue;
		}

		if ( n->ver->msg_send - n->msg_rcv == 1)
		{
			printf("mensagem nova de %s (%s): %d\n", n->ver->user->nick, get_name(n->ver->user, pointer), n->ver->msg_send);
			n->msg_rcv = n->ver->msg_send;
			continue;
		}

		printf("mensagens novas de %s (%s): %d a %d\n", n->ver->user->nick, get_name(n->ver->user, pointer), n->msg_rcv, n->ver->msg_send);
		n->msg_rcv = n->ver->msg_send;
	}

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