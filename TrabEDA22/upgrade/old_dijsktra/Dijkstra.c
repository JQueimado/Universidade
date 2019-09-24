#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "Dijkstra.h"
#include "basedados.h"
#include "hashtable.h"

#define CACHE 879 //perto do numero de paginas

/* AUX OP */

short time_min(char hora, char min)
{
	return (hora*60) + min;
}

void translate_time(short mins, char *hora, char *min)
{
	*hora = 0;
	while (mins >= 60)
	{
		*hora += 1;
		mins -= 60;
	}
	*min = mins;
}

void add_times(char hora1, char min1, char hora2, char min2, char *hora_res, char *min_res)
{
	translate_time( time_min(hora1,min1) + time_min(hora2,min2), hora_res, min_res );
}

/* f_comp */
char t_compare( char hora1, char min1, char hora2, char min2 )
{
	int t1_min = time_min(hora1, min1);
	int t2_min = time_min(hora2, min2);

	if( t1_min > t2_min )
		return 1;
	else if( t1_min < t2_min )
		return -1;
	else
		return 0;
}

/* Sorted Linked List */
struct SLL
{
	char *node;
	char *current;
	short peso;
	char f_pos;
	char hora;
	char min;
	struct SLL *next;
} 
typedef SLL;

struct LL
{
	char *node;
	char f_pos;
	struct LL *next;

} typedef LL;

/* Cria um no do tipo SLL */
SLL *new_SLL(char *add, char *current, char f_pos, char hora, char min)
{
	SLL *temp = malloc(sizeof(SLL));
	temp->next = NULL;
	
	temp->node = add;
	temp->current = current;

	temp->f_pos = f_pos;
	temp->hora = hora;
	temp->min = min;
	return temp;
}

/* Adiciona um no a SLL e retorna a Head */
SLL *add_sll(SLL *self, char *add_name, char *current_name, char f_pos, char hora, char min, hashtable *hash, FILE *disk)
{
	/* Create Node */
	SLL *n_node = new_SLL(add_name, current_name, f_pos, hora, min);

	aeroportos* add = get_aeroporto(hash, disk, add_name);
	aeroportos* node = get_aeroporto(hash, disk, self->node);

	/* Se vazio adiciona ao Inicio */
	if (self == NULL)
		return n_node;

	/* Se for menor que a head adiciona no inicio */

	if (node->peso > add->peso)
	{
		n_node->next = self;
		return n_node;
	}

	/* Procurar posicao */
	SLL *head = self;
	while (self->next != NULL)
	{
		free( node );
		node = get_aeroporto(hash, disk, self->next->node );
		
		if (node->peso >= add->peso)
			break;

		self = self->next;
	}

	if (self->next != NULL)
		n_node->next = self->next;
	self->next = n_node;

	free( add );
	free( node );

	return head;
}

/* Add LL */
LL *add_ll(LL *self, char *add)
{
	LL *n_node = malloc(sizeof(LL));
	n_node->node = add;
	n_node->next = self;
	return n_node;
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
		//free(self->node);
		free(self->current);
		self = pop(self);
	}
}

/* construtor do caminho */
Caminho *build_caminho(aeroportos *aero, hashtable *hash, FILE *disk)
{
	if (aero == NULL)
		return NULL;

	Caminho *caminho = NULL;

	char voo = aero->vesitado;
	aero = get_aeroporto(hash, disk, aero->pai);

	while (strcmp(aero->pai, "") != 0)
	{
		Caminho *n_caminho = malloc(sizeof(Caminho));
		n_caminho->voo = voo;
		n_caminho->aero = aero;
		n_caminho->next = caminho;
		n_caminho->dur = aero->peso;

		caminho = n_caminho;
		voo = aero->vesitado;
		aero = get_aeroporto(hash, disk, aero->pai);
	}

	Caminho *n_caminho = malloc(sizeof(Caminho));
	n_caminho->voo = voo;
	n_caminho->aero = aero;
	n_caminho->next = caminho;
	n_caminho->dur = aero->peso;

	caminho = n_caminho;

	return caminho;
}

/* ALGO */
void reset_visistados(LL *visistados, hashtable *hash, FILE *disk)
{
	while (visistados != NULL)
	{
		aeroportos* temp1 = get_aeroporto(hash, disk, visistados->node);
		temp1->peso = INF;
		temp1->vesitado = -2;
		write_aero(hash, disk, temp1);
		free( temp1 );

		LL* temp = visistados;
		visistados = visistados->next;
		free(temp);
	}
}

aeroportos *dijkstra_rec(hashtable *hash, FILE *disk, char *current_name, char hora_currente, char min_currente, char *pai_name, char f_code, char *final, SLL **helper, LL **visitados, short *retdur)
{
	aeroportos *current = get_aeroporto(hash, disk, current_name);

	current->vesitado = f_code;
	strcpy(current->pai, pai_name);
	write_aero(hash, disk, current);

	if (strcmp(current->codigo, final) == 0)
	{
		*retdur = current->peso;
		return current;
	}

	voos *voo;
	aeroportos *aero;

	/* precore as ligacoes */
	/************************ */
	//printf("current %s -> %d\n", current->codigo, current->ocupado);
	/************************ */
	for (int i = 0; i < current->ocupado; i++)
	{
		voo = &current->voosDecorrer[i];

		aero = get_aeroporto(hash, disk, voo->aero_chegada);

		/* ingnora se ja foi vesitado */
		if (aero->vesitado >= -1)
			continue;

		/* calculo do peso */
		int t_espera;
		
		if( t_compare(voo->hora, voo->min, hora_currente, min_currente) == -1 )
			t_espera = time_min(24, 0) - time_min(hora_currente, min_currente) + time_min(voo->hora, voo->min);
		else
			t_espera = time_min(voo->hora, voo->min) - time_min(hora_currente, min_currente);

		int calc = current->peso + voo->duracao + t_espera;

		/* alteracao de peso */
		if (aero->peso == INF || aero->peso > calc)
		{
			char hora = 0; 
			char min = 0;
			
			translate_time(voo->duracao, &hora, &min);
			//printf("hora: %s min: %s\n",hora,min);
			/* adiciona duracao a tempo  */
			add_times(voo->hora, voo->min, hora, min, &hora, &min);

			aero->peso = calc;
			write_aero(hash, disk, aero);

			*helper = add_sll(*helper, aero->codigo, current_name, i, hora, min, hash, disk);
			*visitados = add_ll( *visitados, aero->codigo );
		}
	}
	/* nao ha mais caminhos logo n e possivel chegrar ao destino */
	if (*helper == NULL)
		return NULL;
	
	int fpos = -1;

	char* aero_name = current_name;

	while( aero->vesitado >= -1 )
	{
		SLL* h1 = *helper;
		aero_name = h1->node;
		
		current_name = h1->current;
		fpos = h1->f_pos;

		hora_currente = h1->hora;
		min_currente = h1->min;

		*helper = pop( *helper);
	}

	free(current);

	return dijkstra_rec(hash, disk, aero_name, hora_currente, min_currente, current_name, fpos, final, helper, visitados, retdur);
}

/* MAIN DIJKSTRA */
Caminho *dijkstra(hashtable *hash, FILE *disk, char *init_code, char hora_chegada, char min_chegada, char *final, short* retdur)
{
	aeroportos *curr = get_aeroporto(hash, disk, init_code);
	curr->peso = 0;
	write_aero(hash, disk, curr);
	free( curr );

	LL *visitados = NULL;
	visitados = add_ll( visitados, init_code);
	
	LL **pt_visitados = &visitados;
	SLL *helper = NULL;
	SLL **pt_helper = &helper;

	/* run recursion */
	aeroportos *result = dijkstra_rec(hash, disk, init_code, hora_chegada, min_chegada, "", -1, final, pt_helper, pt_visitados, retdur);

	/* reconstroi o caminho */
	Caminho *caminho = build_caminho(result, hash, disk);

	/* reseta os nos e liberta os*/
	reset_visistados(*pt_visitados, hash, disk);

	/* liberta o helper */
	//kill(*pt_helper);

	return caminho;
}