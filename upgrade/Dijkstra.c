#include "Dijkstra.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/* Sorted Linked List */

struct SLL
{
    aeroportos* node;
    struct SLL* next;
} typedef SLL;

/* Cria um no do tipo SLL */
SLL* new_SLL( aeroportos* add )
{
    SLL* temp = malloc( sizeof(SLL) );
    temp->next = NULL;
    temp->node = add;
    return temp;
}

/* Adiciona um no a SLL e retorna a Head */
SLL* add_sll( SLL* self, aeroportos* add )
{
    /* Create Node */
    SLL* n_node = new_SLL(add);

    /* Se vazio adiciona ao Inicio */
    if( self == NULL )
        return n_node;

    /* Se for menor que a head adiciona no inicio */
    if( self->node->peso > add->peso )
    {
        n_node->next = self;
        return n_node;
    }

    /* Procurar posicao */
    SLL* head = self;
    while( self->next != NULL )
    {
        if( self->next->node->peso > add->peso )
            break;

        self = self->next;
    }

    if( self->next != NULL)
        n_node->next = self->next;
    self->next = n_node;
    return head;
}

/* Remove Head */
SLL* pop(SLL* self)
{
    SLL* n_head = self->next;
    free(self);
    return n_head;
}

/* Mata a SLL */
void kill(SLL* self)
{
    while (self != NULL)
    {
        self = pop(self);
    }
}


/* ALGO */
aeroportos* dijkstra_rec( int fd, aeroportos* current, aeroportos* pai, char* final, SLL* helper )
{
    current->vesitado = 1;
    current->pai = pai;

    if( strcmp(current->codigo, final) == 0 )
    {
        return current;
    }

    voos* voo;
    aeroportos* aero;
    
    /* precore as ligacoes */
    for( int i=0; i<current->index_voo; i++ )
    {
        voo = &current->voosDecorrer[i];
        aero = read_aeroportos_at_hash(fd, voo->aero_chegada);

        /***************************/

        printf("conection:%s->%s\n",current->codigo, aero->codigo);

        /***************************/

        /* ingnora se ja foi vesitado */
        if( aero ->vesitado )
            continue;

        /* calculo do peso */
        int calc = current->peso + voo->duracao;

        /* alteracao de peso */
        if( aero->peso == INF || aero->peso > calc )
        {
            aero->peso = calc;
            helper = add_sll(helper, aero);
        }
    }

    aero = helper->node;
    helper = pop(helper);

    return dijkstra_rec(fd, aero, current, final, helper);
}

/* MAIN DIJKSTRA */
aeroportos* dijkstra( int fd, char* init_code, char* final )
{
    aeroportos* curr = read_aeroportos_at_hash( fd, init_code );
    curr->peso = 0;

    puts("test");
    /* run recursion */
    aeroportos* caminho = dijkstra_rec( fd, curr, NULL, final, NULL );

    return caminho;
}


/****************************************************main*****************************************************************************************/
int main()
{
    int ficheiro;
	ficheiro = hashtable_aeroportos_open("ftest.cache");
   
    char* a1 = "LIS";
    char* a2 = "MAD";
    char* a3 = "BAR";
    char* a4 = "ALG";
    short duracao = 33;

    new_aeroporto(a1, ficheiro);
    new_aeroporto(a2, ficheiro);
    new_aeroporto(a3, ficheiro);
    new_aeroporto(a4, ficheiro);

    aeroportos* ae1 = read_aeroportos_at_hash(ficheiro, a1);
    //printf("%d\n",ae1.voosDecorrer[0]);
    //aeroportos ae2 = read_aeroportos_at_hash(ficheiro, a2);
    //aeroportos ae3 = read_aeroportos_at_hash(ficheiro, a3);
    //aeroportos ae4 = read_aeroportos_at_hash(ficheiro, a4);


    add_voo(ficheiro, ae1, a2, 22, 33, duracao);
    add_voo(ficheiro, ae1, a3, 22, 33, duracao);
    add_voo(ficheiro, ae1, a4, 22, 33, duracao);
    //printf("%d\n",ae1.voosDecorrer[0].duracao);


    ae1 = read_aeroportos_at_hash(ficheiro, a1);
    //ae2 = read_aeroportos_at_hash(ficheiro, a2);
    //ae3 = read_aeroportos_at_hash(ficheiro, a3);
    //ae4 = read_aeroportos_at_hash(ficheiro, a4);

    aeroportos* cona = dijkstra( ficheiro, a1, a2 );

    while (cona->pai != NULL)
    {
        printf("aero: %s\n", cona->codigo );
        cona = cona->pai;
    }
}