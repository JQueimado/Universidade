#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "Dijkstra.h"
#include "basedados.h"
#include "hashtable.h"

#define CACHE 879 //perto do numero de paginas

/* FILE IO */
aeroportos* get_aeroporto(hashtable *hash, FILE *disk, char *code)
{
	aeroportos *temp = malloc(sizeof(aeroportos));
	int pos = find_aeroportopos(hash, code);
	if( pos == -1 )
	{
		/****************************/
		//puts("not found");
		/****************************/
		return NULL;
	}
	read(disk, temp, pos);

	/****************************/
	//printf("%s = %s\n", temp->codigo, code);
	/****************************/

	return temp;
}

void write_aero(hashtable* hash, FILE* disk, aeroportos* add)
{
	int pos = find_aeroportopos(hash, add->codigo);
	write(disk, add, pos);
}


/* Sorted Linked List */
struct SLL
{
	aeroportos* node;
	aeroportos* current;
	struct SLL* next;
} typedef SLL;

/* Cria um no do tipo SLL */
SLL *new_SLL(aeroportos *add, aeroportos* current)
{
	SLL *temp = malloc(sizeof(SLL));
	temp->next = NULL;
	temp->node = add;
	temp->current = current;
	return temp;
}

/* Adiciona um no a SLL e retorna a Head */
SLL *add_sll(SLL *self, aeroportos *add, aeroportos* current)
{
	/* Create Node */
	SLL *n_node = new_SLL(add, current);

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
aeroportos *dijkstra_rec(hashtable *hash, FILE *disk, aeroportos *current, char *pai, char *final, SLL *helper)
{
	/*****************************/
	//printf("faz %s pai de %s\n", pai, current->codigo );
	/*****************************/
	current->vesitado = 1;
	strcpy(current->pai, pai);
	write_aero(hash, disk, current);
	/*********************************/
	//printf("%s %s\n",current->codigo,final);
	/*********************************/
	if (strcmp(current->codigo, final) == 0)
	{
		/********************************/
		//printf("cona");
		/********************************/
		return current;
	}

	voos *voo;
	aeroportos *aero;

	/* precore as ligacoes */
	/**************************/
	//printf("ocupado %d\n", current->ocupado);
	/**************************/
	for (int i = 0; i < current->ocupado; i++)
	{
		voo = &current->voosDecorrer[i];
		aero = get_aeroporto(hash, disk, voo->aero_chegada);

		/***************************/
		//printf("conection:%s->%s\n", current->codigo, aero->codigo);
		/***************************/

		/* ingnora se ja foi vesitado */
		if (aero->vesitado)
			continue;

		/* calculo do peso */
		int calc = current->peso + voo->duracao;

		/*****************************/
		//printf("calc for %s->%s is %d\n", current->codigo, aero->codigo, calc);
		/*****************************/

		/* alteracao de peso */
		if (aero->peso == INF || aero->peso > calc)
		{
			/*****************************/
			//printf("set %s->%s\n", current->codigo, aero->codigo);
			/*****************************/
			aero->peso = calc;
			write_aero(hash, disk, aero);
			helper = add_sll(helper, aero, current);
		}
	}
	aero = helper->node;
	current = helper->current;
	
	helper = pop(helper);
	
	/*************************/
	//printf("aqui");
	/*************************/
	return dijkstra_rec(hash, disk, aero, current->codigo, final, helper);
}

/* MAIN DIJKSTRA */
aeroportos *dijkstra(hashtable *hash, FILE *disk, char *init_code, char *final)
{
	aeroportos *curr = get_aeroporto(hash, disk, init_code);
	/*struct aeroportos *curr = malloc(sizeof(struct aeroportos));
	int pos1 = find_aeroportopos(hash, init_code);
	read(disk, curr, pos1); //le para o aeroporto a informacao do disco
*/
	curr->peso = 0;
	/*********************************/
	//printf("%d\n",curr->ocupado);
	/*
	for(int i=0;i<curr->ocupado;i++)
	{
		printf("%s\n",curr->voosDecorrer[i].aero_chegada);
	}
	*/
	//puts("test");
	/*********************************/
	/* run recursion */
	aeroportos *caminho = dijkstra_rec(hash, disk, curr, "", final, NULL);

	return caminho;
}
/* ************************************************* AUX TEST ******************************************************* */

FILE *disk;
struct hashtable *hash;
int pos;
int ae_size = 0;
struct aeroportos buffer[CACHE];

/* Funcoes auxiliares */
int pesquisabinaria(char *codigo, char *hora_partida, struct voos arr[], int i, int j)
{

	if (i > j)
		return -1; // vector vazio

	int m = (i + j) / 2; // posição central

	if (strcmp(codigo, arr[m].aero_chegada) < 0)
	{
		// Restringe a pesquisa ao intervalo i..m - 1
		return pesquisabinaria(codigo, hora_partida, arr, i, m - 1);
	}
	else if (strcmp(codigo, arr[m].aero_chegada) == 0 && strcmp(hora_partida, arr[m].hora_partida) < 0)
	{
		return pesquisabinaria(codigo, hora_partida, arr, i, m - 1);
	}

	if (strcmp(codigo, arr[m].aero_chegada) > 0)
	{
		return pesquisabinaria(codigo, hora_partida, arr, m + 1, j);
	}
	else if (strcmp(codigo, arr[m].aero_chegada) == 0 && strcmp(hora_partida, arr[m].hora_partida) > 0)
	{
		// Restringe a pesquisa ao intervalo m + 1..j
		return pesquisabinaria(codigo, hora_partida, arr, m + 1, j);
	}

	return m; // n == v[m]
}

void arrayordenado(struct voos voo, int size, struct voos array[])
{
	short i;
	//Percorre o a partir do fim, se aeroporto na posição i for maior do que o aeroporto dado
	//move i para i+1

	i = size - 1;
	while (i >= 0 && strcmp(array[i].aero_chegada, voo.aero_chegada) > 0)
	{
		array[i + 1] = array[i];
		i--;
	}
	//Coloca o aeroporto seguido no esapaço criado
	array[i + 1] = voo;
}

bool criar_aeroporto(char *codigo)
{
	//int pos = hash_function_aeroportos(codigo);
	//printf("%d\n",pos);
	//Procura o aeroporto na hashtable
	if (find_aeroporto(hash, codigo))
	{
		printf("+ aeroporto %s existe\n", codigo);
		return true;
	}

	//Cria um aeroporto
	struct aeroportos *novoaeroporto = malloc(sizeof(struct aeroportos));
	if (novoaeroporto == NULL)
		return false; // caso nao consiga alocar
	strcpy(novoaeroporto->codigo, codigo);
	novoaeroporto->ocupado = 0;
	novoaeroporto->peso = INF;
	//Guarda a informação no disco
	if (inserir_aeroporto(hash, codigo, pos))
	{

		write(disk, novoaeroporto, pos);
		//strcpy( buffer[ae_size].codigo, codigo );

		//ae_size++;
		//printf("%d\n",ae_size);
		pos++;

		/*if(ae_size >= CACHE)
			{
				fseek(disk, pos*sizeof(struct aeroportos), SEEK_SET);
				fwrite( &buffer ,sizeof(struct aeroportos), CACHE, disk);
				ae_size = 0;
				//printf("aqui\n");
			}*/
		printf("+ novo aeroporto %s\n", codigo);
		free(novoaeroporto);
		return true;
	}

	free(novoaeroporto);
	return false;
}

bool criarVoo(char *codigo_partida, char *codigo_chegada, char *hora_partida, short duracao)
{
	//printf("partida:%s chegada: %s hora_partida: %s duracao: %d\n",codigo_partida,codigo_chegada,hora_partida,duracao);
	//aeroportos* temp_partida;
	//aeroportos temp_chegada;
	//temp_partida = read_aeroportos_at_hash(fd,codigo_partida);

	int pos1 = find_aeroportopos(hash, codigo_partida);

	//printf("posicao em memoria: %d %d\n",pos1,pos2);
	if (pos1 == -1)
	{
		printf("+ aeroporto %s desconhecido\n", codigo_partida);
		return true;
	}
	int pos2 = find_aeroportopos(hash, codigo_chegada);
	if (pos1 != -1 && pos2 == -1)
	{

		printf("+ aeroporto %s desconhecido\n", codigo_chegada);
		return true;
	}
	struct aeroportos *aeroporto1;
	aeroporto1 = malloc(sizeof(struct aeroportos));
	//int pos1=find_aeroportoid(hash,codigo_partida);
	//printf("pos:%d\n",pos1);
	//printf("aqui1");
	if (aeroporto1 == NULL)
	{
		//printf("aqui2");
		return false;
	}

	read(disk, aeroporto1, pos1); //le para o aeroporto a informacao do disco
	//printf("aqui: %d\n",aeroporto1->ocupado);
	/*for(int i=0;i<=aeroporto1->ocupado-1;i++)
	{
		printf("X:%s %s\n",aeroporto1->voosDecorrer[i].aero_chegada,aeroporto1->voosDecorrer[i].hora_partida);
	}*/
	short i = pesquisabinaria(codigo_chegada, hora_partida, aeroporto1->voosDecorrer, 0, aeroporto1->ocupado - 1);
	//printf("Indice do array: %d\n",i);
	if (i != -1) //Encontrou voos iguais
	{
		printf("+ voo %s %s %s existe\n", codigo_partida, codigo_chegada, hora_partida);
		/*for(int i=0;i<=aeroporto1->ocupado-1;i++)
	{
		printf("X:%s %s\n",aeroporto1->voosDecorrer[i].aero_chegada,aeroporto1->voosDecorrer[i].hora_partida);
	}*/
		free(aeroporto1);
		return true;
		//printf("%d\n",i);
		//printf("%s\n",aeroporto1->voosDecorrer[i].hora_partida);
	}
	//cria voo-
	//strcpy(aeroporto1->voosDecorrer[0].aero_chegada,codigo_chegada); //RESOLVER BUG DE QUANDO CRIA DEVIA IMPRIMIR JÁ EXISTE
	struct voos voo;
	strcpy(voo.aero_chegada, codigo_chegada);
	strcpy(voo.hora_partida, hora_partida);
	voo.duracao = duracao;
	//printf("VOO:%s %s %d\n",voo.aero_chegada,voo.hora_partida,voo.duracao);

	arrayordenado(voo, aeroporto1->ocupado, aeroporto1->voosDecorrer);
	//aeroporto1->voosDecorrer[0] = voo;

	//printf("cod: %s\n",aeroporto1->voosDecorrer[0].aero_chegada);

	printf("+ novo voo %s %s %s\n", codigo_partida, codigo_chegada, hora_partida);

	//printf("cona\n");

	
	//guarda no disco
	aeroporto1->ocupado += 1;
	write(disk, aeroporto1, pos1);
	/**************************************/
	/*
	for(int i=0;i<=aeroporto1->ocupado-1;i++)
	{
		printf("cod: %s %s\n",aeroporto1->voosDecorrer[i].aero_chegada,aeroporto1->voosDecorrer[i].hora_partida);
	}
	*/
	/**************************************/
	free(aeroporto1);

	return true;
}

/****************************************************main*****************************************************************************************/

int main()
{
	hash = newhash();
	disk = openFile("test.cache");

	char *a1 = "LIS";
	char *a2 = "MAD";
	char *a3 = "BAR";
	char *a4 = "ALG";
	short duracao = 33;

	criar_aeroporto(a1);
	criar_aeroporto(a2);
	criar_aeroporto(a3);
	criar_aeroporto(a4);

    //  LIS->BAR
	//	 |    |
	//   V    V
	//	MAD<---


	criarVoo(a1, a3, "22:33", duracao);
	criarVoo(a3, a2, "22:33", duracao);
	criarVoo(a1, a2, "22:33", duracao);
	//criarVoo(a3, a4, "22:33", duracao);

	aeroportos *cona = dijkstra(hash, disk, a1, a2);

	while ( strcmp("", cona->pai) != 0)
	{
		printf("aero:%s -> %s\n", cona->pai, cona->codigo);
		cona = get_aeroporto(hash, disk, cona->pai);
	}
	puts("");
	aeroportos* temp = get_aeroporto(hash, disk, a1);
	printf("%s -> %d\n", temp->codigo, temp->peso);
	temp = get_aeroporto(hash, disk, a2);
	printf("%s -> %d\n", temp->codigo, temp->peso);
	temp = get_aeroporto(hash, disk, a3);
	printf("%s -> %d\n", temp->codigo, temp->peso);
	temp = get_aeroporto(hash, disk, a4);
	printf("%s -> %d\n", temp->codigo, temp->peso);

}

/*
int main()
{
	hash = newhash();
	disk = openFile("test.cache");

	char *a1 = "LIS";
	char *a2 = "MAD";
	char *a3 = "BAR";
	char *a4 = "ALG";

	criar_aeroporto(a1);
	criar_aeroporto(a2);
	criar_aeroporto(a3);
	criar_aeroporto(a4);

	aeroportos* ae1 = get_aeroporto(hash, disk, a1);
	aeroportos* ae2 = get_aeroporto(hash, disk, a2);
	aeroportos* ae3 = get_aeroporto(hash, disk, a3);
	aeroportos* ae4 = get_aeroporto(hash, disk, a4);

	ae1->peso = 10;
	ae2->peso = 5;
	ae3->peso = 7;
	ae4->peso = 40;

	SLL* head = add_sll(NULL, ae1);
	printf("%s\n", head->node->codigo);

	head = add_sll(head, ae2);
	printf("%s\n", head->node->codigo);

	head = add_sll(head, ae3);
	printf("%s\n", head->node->codigo);

	head = add_sll(head, ae4);
	printf("%s\n", head->node->codigo);

	puts("pop");

	printf("%s\n", head->node->codigo);
	head = pop(head);

	printf("%s\n", head->node->codigo);
	head = pop(head);

	printf("%s\n", head->node->codigo);
	head = pop(head);

	printf("%s\n", head->node->codigo);
	head = pop(head);
}
*/