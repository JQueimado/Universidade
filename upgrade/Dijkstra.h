#ifndef Dijkstra
#define Dijkstra

#include <string.h>
#include "hashtable.h"
#include "aeroporto.h"

#define INF -1

struct Caminho
{
    aeroportos* aero;
    char voo;
    struct Caminho* next;
}
typedef Caminho;

void add_times(char hora1, char min1, char hora2, char min2, char *hora_res, char *min_res);

void translate_time( short mins, char* hora, char* min);

Caminho* dijkstra( hashtable* hash, FILE* disk, char* init_code, char* final );

#endif
