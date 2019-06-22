#ifndef Dijkstra
#define Dijkstra

#include <string.h>
#include "hashtable.h"
#include "aeroporto.h"

#define INF -1

aeroportos* dijkstra( hashtable* hash, FILE* disk, char* init_code, char* final );

#endif // _Grafo_
