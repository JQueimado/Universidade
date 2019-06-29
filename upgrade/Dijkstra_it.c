#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "Dijkstra.h"
#include "basedados.h"
#include "hashtable.h"

#define MAX_NODE 750001 /* numero de nos maximo = numero maximo de voos + 1 */

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

/* Simple hash function */
int hash_node( char* code )
{
    return code[0] + code[1] + code[2];
}

/* Struct for node */
struct Node
{
    char name[5];           //5 bytes
    
    unsigned short peso;    //2 bytes
    bool visitado;          //1 byte
    
    char hora;              //1 byte
    char min;               //1 byte
    unsigned short dur;     //2 byte

    struct Node *pai;       //4 bytes
    struct Node *next;      //4 bytes
}
typedef Node;               //20 bytes = 5 paginas

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

struct PQueue
{
    struct Node* elem;      //4 bytes
    struct PQueue* next;    //4 bytes
}
typedef PQueue;             //8 bytes = 2 paginas

PQueue* pqueue_add( PQueue* self, Node* node)
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
        if( self->next->elem->peso > node->peso )
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
        n_caminho->hora_partida = node->hora;
        n_caminho->min_partida = node->min;

        translate_time( ( time_min(node->hora,node->min) + node->dur ), &n_caminho->hora_chegada, &n_caminho->min_chegada );

        ret = n_caminho;
        node = node->pai;
    }
    return ret;
} 

/* MAIN DIJKSTRA */
Caminho *dijkstra(hashtable *hash, FILE *disk, char *init_code, char hora_chegada, char min_chegada, char *final, unsigned short* retdur)
{
    Node* hash_nos[MAX_NODE] = {NULL};

    aeroportos* current = NULL;
    Node* cur_node = NULL;
    Node* nodes = add_Nodes(NULL, init_code, hash_nos);
    nodes->peso = time_min(hora_chegada, min_chegada);
    PQueue* heap = pqueue_add(NULL, nodes);

    do
    {
        /* if heap is empty there are no more ways */
        if( heap == NULL )
        {
            cur_node = NULL;
            break;
        }

        /* cycle heap */
        cur_node = heap->elem;
        heap = pop(heap);
 
        /* cycle heap */
        if( strcmp( cur_node->name, final ) == 0 )
        {
            *retdur = cur_node->peso - time_min(hora_chegada, min_chegada);
            break;
        }

        cur_node->visitado = true;

        /* cycle */
        if( current != NULL )
            free( current );
        current = get_aeroporto(hash, disk, cur_node->name);

        //printf("voos de %s com peso %d\n",cur_node->name, cur_node->peso);

        for( int i = 0; i < current->ocupado; i++ )
        {
            voos voo = current->voosDecorrer[i];

            /* get no */
            Node* dest_node = get_node( voo.aero_chegada, hash_nos );
            if( dest_node == NULL )
            {
                nodes = add_Nodes( nodes, voo.aero_chegada, hash_nos);
                dest_node = nodes;
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

            //printf(" ve voo %s %d:%d, com peso %d\n", dest_node->name, voo.hora, voo.min, calc_peso );
            
            /* Avaliacao do peso do no */
            if( dest_node->peso == INF || dest_node->peso > calc_peso )
            {
                dest_node->peso = calc_peso;
                dest_node->pai = cur_node;
                dest_node->hora = voo.hora;
                dest_node->min = voo.min;
                dest_node->dur = voo.duracao;
            }

            heap = pqueue_add( heap, dest_node );
        }
        //puts("done.");
    }
    while( 1 );

    Caminho *n_caminho = build( cur_node );
    
    free_pqueue(heap);
    free_node(nodes);
    free( current );

    return n_caminho;
}