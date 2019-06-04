#include "voo.h"

#include <stdlib.h>
#include <string.h>

/* Constructor Body */
voo* new_voo( char* codigo, char codigo_partida, char codigo_destino, char hora_partida, short duracao)
{
    voo *temp = malloc(sizeof( voo ));
    strcpy(temp->codigo, codigo);
    strcpy(temp->codigo_partida, codigo_partida);
    strcpy(temp->codigo_destino, codigo_destino);
    strcpy(temp->hora_partida, hora_partida);
    temp->duracao = duracao;
    return temp;
}