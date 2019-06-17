#ifndef _Grafo_
#define _Grafo

#include "hashtable_aeroporto.h"

#define MAX_NOS 200000
struct grafo
{
    int nos_point;
    int nos[MAX_NOS];
}
typedef Grafo;

Grafo* new_grafo();

void new_no(Grafo* self, char* code, int fd );

void get_conects( Grafo* self, int pos, int fd, int* _return);

#endif // _Grafo_
