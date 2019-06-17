#include "Grafo.h"

Grafo* new_grafo()
{
    Grafo* temp = malloc(sizeof(Grafo));
    temp->nos_point = 0;
    return temp;
}

void new_no(Grafo* self, char* code, int fd )
{
    self->nos[self->nos_point] = find_aeroporto(fd, code);
    self->nos_point++;
}

void get_conects( Grafo* self, int pos, int fd, int* _return )
{
    aeroportos temp = read_aeroportos_at(fd, self->nos[pos]);
    for( int i = 0; i< temp.index_voo; i++ )
    {
        _return[i] = find_aeroporto(fd, temp.voosDecorrer[i].aero_chegada );
    }
}
