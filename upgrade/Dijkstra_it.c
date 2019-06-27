#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "Dijkstra.h"
#include "basedados.h"
#include "hashtable.h"

#define CACHE 879 //perto do numero de paginas

/* AUX OP */
short time_min(char hora, char min)
{
	return (hora*60) + min;
}

void translate_time(short mins, char *hora, char *min)
{
	*hora = 0;
	while (mins >= 60)
	{
		*hora += 1;
		mins -= 60;
        if( *hora >=24 )
            *hora = 0;
	}
	*min = mins;
}

void add_times(char hora1, char min1, char hora2, char min2, char *hora_res, char *min_res)
{
	translate_time( time_min(hora1,min1) + time_min(hora2,min2), hora_res, min_res );
}

/* 
t_comp:
    -1 se o 1º for menor que o 2º
     1 se o 1º for maior que o 2º
     0 se o 1º for igual ao 2º
*/
char t_compare( char hora1, char min1, char hora2, char min2 )
{
	int t1_min = time_min(hora1, min1);
	int t2_min = time_min(hora2, min2);

	if( t1_min > t2_min )
		return 1;
	else if( t1_min < t2_min )
		return -1;
	else
		return 0;
} 

struct Node
{
    char name[6];
    short peso;
    struct Node *pai;
    struct Node *next;
}
typedef Node;

Node* add_Nodes( Node* head, char* codigo )
{
    Node * new_node = malloc(sizeof(Node));
    strcpy(new_node->name, codigo);
    new_node->pai = NULL;
    new_node->peso = INF;

    new_node->next = head;
    return new_node;
}

Node* get_node( Node *head, char* codigo )
{
    while ( head != NULL && strcmp(codigo, head->name)!=0 )
        head = head->next;

    return head;
}

struct PQueue
{
    struct Node* elem;
    struct PQueue* next;
}
typedef PQueue;

PQueue* pqueue_add( PQueue* self, Node* node )
{
    PQueue* temp = malloc( sizeof( PQueue ) );
    temp->elem = node;

    if( self == NULL )
    {
        temp->next = NULL;
        return temp;
    }

    if( node->peso < self->elem->peso )
    {
        temp->next = self;
        return temp;
    }

    PQueue* head = self;

    while (self->next != NULL)
    {
        if( self->next->elem->peso < node->peso )
            break;
        self = self->next;
    }
    
    temp->next = self->next;
    self->next = temp;
    return head;
}

PQueue *pop( PQueue *self)
{
    PQueue* head = self->next;
    free( self );
    return head;
}

void free_pqueue( PQueue *heap )
{
    while (heap != NULL)
    {
        PQueue* temp = heap->next;
        free(heap);
        heap = temp;
    }   
}

void free_node( Node* nodes )
{
    while (nodes != NULL)
    {
        Node* temp = nodes->next;
        free(nodes);
        nodes = temp;
    }   
}

/* Caminho */
Caminho *build( Node* node )
{
    Caminho* ret = NULL;

    while ( node != NULL )
    {
        Caminho* n_caminho = malloc(sizeof(Caminho));
        strcpy(n_caminho->aero, node->name);
        n_caminho->next = ret;
        ret = n_caminho;

        node = node->pai;
    }
    return ret;
} 

/* MAIN DIJKSTRA */
Caminho *dijkstra(hashtable *hash, FILE *disk, char *init_code, char hora_chegada, char min_chegada, char *final, short* retdur)
{
    aeroportos* current = NULL;
    char current_name[6];
    Node* pai = NULL;
    Node* cur_node = NULL;
    Node* nodes = add_Nodes(NULL, init_code);
    PQueue* heap = pqueue_add(NULL, nodes);

    do
    {
        /* if heap is empty there are no more ways */
        if( heap == NULL )
        {
            cur_node = NULL;
            break;
        }

        cur_node = heap->elem;
        heap = pop(heap);
        pai = cur_node->pai;

        if( strcmp( cur_node->name, final ) == 0 )
        {
            *retdur = cur_node->peso;
            break;
        }

        /* cycle heap */
        strcpy(current_name, cur_node->name);

        /* cycle */
        if( current != NULL )
            free( current );
        current = get_aeroporto(hash, disk, current_name);

        for( int i = 0; i < current->ocupado; i++ )
        {
            voos voo = current->voosDecorrer[i];

            int t_espera;
		
            char hora;
            char min;
            translate_time(cur_node->peso, &hora, &min);

            if( t_compare(voo.hora, voo.min, hora_chegada, min_chegada) == -1 )
                t_espera = time_min(24, 0) - time_min(hora, min) + time_min(voo.hora, voo.min);
            else
                t_espera = time_min(voo.hora, voo.min) - time_min(hora_chegada, min_chegada);

            int calc_peso = current->peso + voo.duracao + t_espera;

            Node* dest_node = get_node( nodes, voo.aero_chegada);
            if( dest_node == NULL )
            {
                nodes = add_Nodes( nodes, voo.aero_chegada);
                dest_node = nodes;
            }
            
            if( dest_node->peso == INF || dest_node->peso < calc_peso )
            {
                dest_node->peso = calc_peso;
                heap = pqueue_add( heap, dest_node);
            }
        }
    }
    while( 1 );

    Caminho *n_caminho = build( cur_node );
    
    free_pqueue(heap);
    free_node(nodes);

    return n_caminho;
}