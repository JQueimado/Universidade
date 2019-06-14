#include "Grafo.h"

grafo* new_grafo()
{
    grafo* temp = malloc(sizeof(grafo));
    temp->nos_point = 0;
    return temp;
}

void new_no(grafo self, char* code, int fd )
{
    self.nos[self.nos_point] = find_aeroporto(fd, code);
    self.nos_point++;
}

aeroportos get_conects( grafo self, int pos, int fd )
{
    aeroportos temp = read_aeroportos_at(fd, self.nos[pos]);
    int aeros[temp.index_voo];
    for( int i = 0; i< temp.index_voo; i++ )
    {
        
    }
}
