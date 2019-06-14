#ifndef _Grafo_
#define _Grafo

#include "hashtable_aeroporto.h"

#define MAX_NOS 200000
struct grafo
{
    int nos_point;
    int nos[MAX_NOS];
}typedef grafo;

grafo* new_grafo();

void new_no(grafo self, char* code, int fd );

#endif // _Grafo_
