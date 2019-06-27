#ifndef Dijkstra
#define Dijkstra

#include <string.h>
#include "hashtable.h"
#include "aeroporto.h"

#define INF -1

struct Caminho
{
    char aero[6];
    short peso;
    struct Caminho* next;
}
typedef Caminho;

short time_min(char hora, char min);

void add_times(char hora1, char min1, char hora2, char min2, char *hora_res, char *min_res);

void translate_time( short mins, char* hora, char* min);

char t_compare( char hora1, char min1, char hora2, char min2 );

Caminho *dijkstra(hashtable *hash, FILE *disk, char *init_code, char hora_chegada, char min_chegada, char *final, short* retdur);

#endif
