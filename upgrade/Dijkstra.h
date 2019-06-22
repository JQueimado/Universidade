#ifndef Dijkstra
#define Dijkstra

#include <malloc.h>
#include "hashtable.h"
#include "aeroporto.h"

#define INF -1

aeroportos* dijkstra( int fd, char* init_code, char* final );

#endif // _Grafo_
