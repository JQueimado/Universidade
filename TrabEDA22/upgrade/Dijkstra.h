#ifndef Dijkstra
#define Dijkstra

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"
#include "aeroporto.h"
#include "basedados.h"

#define INF -1

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

unsigned short time_min(char hora, char min);

void translate_time( unsigned short mins, char* hora, char* min);

char t_compare( char hora1, char min1, char hora2, char min2 );

Node *dijkstra(hashtable *hash, FILE *disk, char *init_code, char hora_chegada, char min_chegada, char *final, unsigned short* retdur);

void free_node( Node* nodes );

#endif
