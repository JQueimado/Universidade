#include "Dijkstra.h"

int* dijkstra_rec( int fd, aeroportos* current, int final )
{
    int min = 0;
    int i = -1;
    voos* voo;
    aeroportos* aero;
    aeroportos* min_dis;
    do
    {
        voo = &current->voosDecorrer[i];
        aero = read_aeroportos_at_hash( fd, voo->aero_chegada );
        int calc = voo->duracao + current->peso;

        if( calc < aero->peso )
        {
            aero->peso = calc;
        }
        else
        {
            calc = aero->peso;
        }
        
        if( calc < min || min == -1 )
        {
            min = calc;
            min_dis = aero;
        }

        i++;
    }
    while ( i < current->index_voo );
    
    return dijkstra_rec(fd, min_dis, final);

}

int* dijkstra( int fd, char* init_code, char* final )
{
    aeroportos* curr = read_aeroportos_at_hash( fd, init_code );
    curr->peso = 0;
    int* ret = dijkstra_rec( fd, curr, find_aeroporto(fd, final) );
    curr->peso = INF;
    return ret;
}