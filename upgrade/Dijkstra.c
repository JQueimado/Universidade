#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "Dijkstra.h"
#include "basedados.h"
#include "hashtable.h"

#define CACHE 879 //perto do numero de paginas

/* AUX OP */

void add_times(char hora1, char min1, char hora2, char min2, char *hora_res, char *min_res)
{
	*min_res = min1 + min2;
	
	while(*min_res >= 60)
	{
		hora1++;
		*min_res -= 60;
	}	

	*hora_res = hora1 + hora2;

	while(*hora_res >= 24)
	{
		*hora_res -= 24;
	}
}

void translate_time( short mins, char* hora, char* min)
{
	while( mins >= 60 )
	{
		*hora += 1;
		mins -= 60;
	}
	*min = mins;
}

/* Sorted Linked List */
struct SLL
{
	aeroportos* node;
	aeroportos* current;
	int f_pos;
	struct SLL* next;
} typedef SLL;

/* Cria um no do tipo SLL */
SLL *new_SLL(aeroportos *add, aeroportos* current, char f_pos)
{
	SLL *temp = malloc(sizeof(SLL));
	temp->next = NULL;
	temp->node = add;
	temp->current = current;
	temp->f_pos = f_pos;
	return temp;
}

/* Adiciona um no a SLL e retorna a Head */
SLL *add_sll(SLL *self, aeroportos *add, aeroportos* current, char f_pos)
{
	/* Create Node */
	SLL *n_node = new_SLL(add, current, f_pos);

	/* Se vazio adiciona ao Inicio */
	if (self == NULL)
		return n_node;

	/* Se for menor que a head adiciona no inicio */

	if (self->node->peso > add->peso)
	{
		n_node->next = self;
		return n_node;
	}

	/* Procurar posicao */
	SLL *head = self;
	while (self->next != NULL)
	{
		if (self->next->node->peso >= add->peso)
			break;

		self = self->next;
	}

	if (self->next != NULL)
		n_node->next = self->next;
	self->next = n_node;
	return head;
}

/* Remove Head */
SLL *pop(SLL *self)
{
	SLL *n_head = self->next;
	free(self);
	return n_head;
}

/* Mata a SLL */
void kill(SLL *self)
{
	while (self != NULL)
	{
		self = pop(self);
	}
}

/* ALGO */
aeroportos *dijkstra_rec(hashtable *hash, FILE *disk, aeroportos *current, char *pai, char f_code, char *final, SLL *helper)
{
	current->vesitado = f_code;
	strcpy(current->pai, pai);
	write_aero(hash, disk, current);

	if (strcmp(current->codigo, final) == 0)
	{
		return current;
	}

	voos *voo;
	aeroportos *aero;

	/* precore as ligacoes */
	for (int i = 0; i < current->ocupado; i++)
	{
		voo = &current->voosDecorrer[i];
		aero = get_aeroporto(hash, disk, voo->aero_chegada);

		/* ingnora se ja foi vesitado */
		if (aero->vesitado >= -1)
			continue;

		/* calculo do peso */
		int calc = current->peso + voo->duracao;

		/* alteracao de peso */
		if (aero->peso == INF || aero->peso > calc)
		{
			aero->peso = calc;
			write_aero(hash, disk, aero);
			helper = add_sll(helper, aero, current, i);
		}
	}
	/* nao ha mais caminhos logo n e possivel chegrar ao destino */
	if( helper == NULL )
		return NULL;

	aero = helper->node;
	current = helper->current;
	int fpos = helper->f_pos;
	helper = pop(helper);

	return dijkstra_rec(hash, disk, aero, current->codigo, fpos, final, helper);
}

/* MAIN DIJKSTRA */
aeroportos *dijkstra(hashtable *hash, FILE *disk, char *init_code, char *final)
{
	aeroportos *curr = get_aeroporto(hash, disk, init_code);

	curr->peso = 0;

	/* run recursion */
	aeroportos *caminho = dijkstra_rec(hash, disk, curr, "", -1, final, NULL);

	return caminho;
}