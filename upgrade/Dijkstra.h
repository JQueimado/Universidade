#ifndef Dijkstra
#define Dijkstra

#include <string.h>
#include "hashtable.h"
#include "aeroporto.h"

#define INF -1

struct Caminho
{
    char aero[6];           //6 bytes
    char hora_partida;      //1 byte
    char min_partida;       //1 byte
    char hora_chegada;      //1 byte
    char min_chegada;       //1 byte
    struct Caminho* next;   //4 bytes
}
typedef Caminho;            //14 bytes + 2bytes(alinhamento) = 4 paginas

unsigned short time_min(char hora, char min);

void translate_time( unsigned short mins, char* hora, char* min);

char t_compare( char hora1, char min1, char hora2, char min2 );

Caminho *dijkstra(hashtable *hash, FILE *disk, char *init_code, char hora_chegada, char min_chegada, char *final, unsigned short* retdur);

#endif
