#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "Dijkstra.h"
#include "basedados.h"
#include "hashtable.h"

#define MAX_NODE 150053 /* numero de nos maximo = numero maximo de voos + 1 */

/* AUX OP */
unsigned short time_min(char hora, char min)
{
	return (hora*60) + min;
}

void translate_time(unsigned short mins, char *hora, char *min)
{
	*hora = (mins / 60) % 24;
	*min = mins % 60;
}

int hash_node( char* code )
{
    unsigned long hash = 5381;
    int c;
    while ((c = *code++))
        hash = ((hash << 5) + hash) + c;  /*hash * 33 + c */    
    return hash % MAX_NODE;
}

/* Add node to system */
Node* add_Nodes( Node* head, char* codigo, Node** hash )
{
    Node * new_node = malloc(sizeof(Node));
    strcpy(new_node->name, codigo);
    new_node->pai = NULL;
    new_node->peso = INF;
    new_node->visitado = false;
    new_node->hora = 0;
    new_node->min = 0;
    new_node->dur = 0;

    /* Add to list */
    new_node->next = head;

    int i = hash_node(codigo);
    if( i >= MAX_NODE )
        i -= MAX_NODE;
    
    /* Add to hash */
    while ( hash[i] != NULL )
    {
        i ++;
        if( i >= MAX_NODE )
            i = 0;
    }
    
    hash[i] = new_node;

    /* return new list head */
    return new_node;
}

Node* get_node(char* codigo, Node** hash )
{
    int i = hash_node(codigo);
    int p = i;
    while( hash[i] != NULL && strcmp(hash[i]->name, codigo ) != 0 )
    {
        i ++;
        if( i >= MAX_NODE )
            i = 0;

        if( i == p )
            return NULL;
    }
    return hash[i];
}

/* Adaptado de https://www.geeksforgeeks.org/binary-heap/ */
struct Heap
{
    Node* array[MAX_NODE];
    int end;
}
typedef Heap;

Heap* new_heap()
{
    Heap* temp = malloc(sizeof(Heap));
    temp->end = 0;
    return temp;
}

void heap_add( Heap* self, Node* node)
{
    self->array[self->end] = node;
    int i = self->end;
    while( i != 0 )
    {   
        //printf("ciclo add\n");
        if( self->array[i]->peso < self->array[(i-1)/2]->peso )    
        {
            Node* temp = self->array[(i-1)/2];
            self->array[(i-1)/2] = self->array[i];
            self->array[i] = temp;
            i = (i-1)/2;
        }
        else
        {
            break;
        }
    }
    self->end ++;
}

void heapify(Heap* self )
{
    int i = 0;
    while( 1 )
    {
        //printf("ciclo pop");
        Node* left = NULL;
        if( (2*i+1) < self->end )
            left = self->array[2 * i + 1];

        Node* right = NULL;
        if( (2*i+2) < self->end )
            right = self->array[2 * i + 2];

        int min = i;   
        if( left != NULL && left->peso < self->array[min]->peso )
        {
            min = 2*i+1;
        }
        
        if( right != NULL && right->peso < self->array[min]->peso )
        {
            min = 2*i+2;
        }

        if( min != i )
        {
            Node* temp = self->array[i];
            self->array[i] = self->array[min];
            self->array[min] = temp;
            i = min;
        }
        else
        {
            break;
        }
    }
}

Node* heap_pop(Heap* self)
{
    Node* ret = self->array[0];

    if( self->end == 0 )
    {
        return ret;
    }

    self->array[0] = self->array[self->end-1];
    self->array[self->end-1] = NULL;
    self->end--;

    heapify(self);

    return ret;
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

/* MAIN DIJKSTRA */
Node *dijkstra(hashtable *hash, FILE *disk, char *init_code, char hora_chegada, char min_chegada, char *final, unsigned short* retdur)
{
    Node* hash_nos[MAX_NODE] = {NULL};

    aeroportos* current = malloc(sizeof( aeroportos ));
    Node* cur_node = NULL;
    Node* nodes = add_Nodes(NULL, init_code, hash_nos);
    nodes->peso = time_min(hora_chegada, min_chegada);
    Heap* heap = new_heap();
    heap_add(heap, nodes);

    do
    {
        /* if heap is empty there are no more ways */
        if( heap->end == 0 )
        {
            cur_node = NULL;
            break;
        }

        /* cycle heap */
        cur_node = heap_pop(heap);
 
        if( strcmp( cur_node->name, final ) == 0 )
        {
            *retdur = cur_node->peso - time_min(hora_chegada, min_chegada);
            break;
        }

        cur_node->visitado = true;

        /* cycle */
        aeroporto_to(hash, disk, cur_node->name, &current);

        for( int i = 0; i < current->ocupado; i++ )
        {
            voos voo = current->voosDecorrer[i];

            bool new = false;

            /* get node */
            Node* dest_node = get_node( voo.aero_chegada, hash_nos );
            if( dest_node == NULL )
            {
                nodes = add_Nodes( nodes, voo.aero_chegada, hash_nos);
                dest_node = nodes;
                new = true;
            }

            if( dest_node->visitado )
                continue;

            /* calculo do peso */
            unsigned short hora_do_voo = time_min(voo.hora, voo.min);
            
            unsigned short helper;

            if( strcmp( init_code, cur_node->name ) == 0 )
                helper = cur_node->peso;
            else
                helper = cur_node->peso + 30;
            
            while ( hora_do_voo < helper )
            {
                hora_do_voo += time_min(24,0);
            }

            int calc_peso = hora_do_voo + voo.duracao;
            
            /* Avaliacao do peso do no */
            if( dest_node->peso == INF || dest_node->peso > calc_peso )
            {
                dest_node->peso = calc_peso;
                dest_node->pai = cur_node;
                dest_node->hora = voo.hora;
                dest_node->min = voo.min;
                dest_node->dur = voo.duracao;
                
                if( new )
                    heap_add( heap, dest_node );
                else
                    heapify(heap);
            }
        }
    }
    while( 1 );

    free( current );

    free( heap );

    return cur_node;
}