#include "Dijkstra.h"

void dijkstra_rec( int fd, aeroportos* current, char* final , int* ret, int s )
{
    int min = -1;
    int i = 0;
    voos* voo;
    aeroportos* aero;
    char* min_dis;
    do
    {
        voo = &current->voosDecorrer[i];
        if( voo->tag != true )
        {
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

            if( (min > calc) || (min = -1) )
            {
                min = calc;
                min_dis = aero->codigo;
            }
            voo->tag = true;

            if( strcmp(current->codigo, final) != 0 )
            {
                dijkstra_rec(fd, aero, final, ret, s);
            }
        }
        i++;
    }
    while ( i < current->index_voo );

    ret[s] = find_aeroporto(fd, min_dis);
    s++;

}

int* dijkstra( int fd, char* init_code, char* final )
{
    aeroportos* curr = read_aeroportos_at_hash( fd, init_code );
    curr->peso = 0;

    int* ret = malloc( (sizeof(int*) * MAX_AERO) );
    int size = 0;

    /* run recursion */
    dijkstra_rec( fd, curr, final, ret, size );

    /* reset peso */
    curr->peso = INF;

    return ret;
}