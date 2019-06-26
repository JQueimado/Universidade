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
	}
	*min = mins;
}

void add_times(char hora1, char min1, char hora2, char min2, char *hora_res, char *min_res)
{
	translate_time( time_min(hora1,min1) + time_min(hora2,min2), hora_res, min_res );
}

/* f_comp */
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

struct PQueue
{
    char codigo;
    short peso;
    struct PQueue* next;
}
typedef PQueue;

PQueue* pqueue_add( PQueue* self, char* codigo, short peso )
{
    PQueue* temp = malloc( sizeof( PQueue ) );
    strcpy( temp->codigo, codigo);
    temp->peso = peso;

    if( self == NULL )
    {
        temp->next = NULL;
        return temp;
    }

    if( peso < self->peso )
    {
        temp->next = self;
        return temp;
    }

    PQueue* temp = self;

    while (self->next != NULL)
    {
        if( self->next->peso < peso )
            break;
        self = self->next;
    }
    
    temp->next = self->next;
    self->next = temp;
    return temp;
}

PQueue *pop( PQueue *self)
{
    PQueue* head = self->next;
    free( self );
    return head;
}

/* MAIN DIJKSTRA */
Caminho *dijkstra(hashtable *hash, FILE *disk, char *init_code, char hora_chegada, char min_chegada, char *final, short* retdur)
{
    aeroportos* current;
    char* current_name;
    PQueue* heap = pqueue_add(NULL, init_code, 0);

    char hora;
    char min;

    do
    {
        /* if heap is empty there are no more ways */
        if( heap == NULL )
            break;

        /* cycle heap */
        strcpy(current_name, heap->codigo);
        short peso = heap->peso;
        heap = pop(heap);

        /* cycle */
        free( current );
        current = get_aeroporto(hash, disk, current_name);

        for( int i = 0; i < current->ocupado; i++ )
        {
            voos voo = current->voosDecorrer[i];


        }
    }
    while( srtcmp( current_name, final ) != 0 );

}