
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "aeroporto.h"
#include "basedados.h"
#include "Dijkstra.h"

#define MAX_SIZE 20477
#define MAX_VOO 150
#define INF -1
#define FILE_DB "db.cache"

/** GLOBAIS **/
FILE *disk;
struct hashtable *hash;
int pos;


/** Funcoes auxiliares **/
/* 
pesquisabinaria:

Descrição:
	Função recursiva que pesquisa um voo(codigo, hora_partida, min_partida) em um array de voos(arr)

Argumentos:
	codigo 			->codigo de chegada
	hora_partida	->hora de partida do voo
	min_partida		->minutos da partida do voo
	arr				->array a pesquisar 
	i				-> inicio do array
	j				-> fim do array


Return:
	-1	->se o voo nao for encontrado
	int -> representa a posição do voo no array caso encontre o voo

*/
int pesquisabinaria(char *codigo, char hora_partida, char min_partida, struct voos arr[], int i, int j)
{

	if (i > j)
		return -1; // vector vazio

	int m = (i + j) / 2; // posição central

	if (hora_partida < arr[m].hora )
	{
		// Restringe a pesquisa ao intervalo i..m - 1
		return pesquisabinaria(codigo, hora_partida, min_partida, arr, i, m - 1);
	}
	else if (hora_partida == arr[m].hora && min_partida < arr[m].min)
	{
		return pesquisabinaria(codigo, hora_partida, min_partida, arr, i, m - 1);
	}
	else if (hora_partida == arr[m].hora && min_partida == arr[m].min && strcmp(codigo, arr[m].aero_chegada) < 0)
	{
		return pesquisabinaria(codigo, hora_partida, min_partida, arr, i, m - 1);
	}

	if (hora_partida > arr[m].hora )
	{
		// Restringe a pesquisa ao intervalo i..m - 1
		return pesquisabinaria(codigo, hora_partida, min_partida, arr, m+1, j);
	}
	else if (hora_partida == arr[m].hora && min_partida > arr[m].min)
	{
		return pesquisabinaria(codigo, hora_partida, min_partida, arr, m+1, j);
	}
	else if (hora_partida == arr[m].hora && min_partida == arr[m].min && strcmp(codigo, arr[m].aero_chegada) > 0)
	{
		return pesquisabinaria(codigo, hora_partida, min_partida, arr, m+1, j);
	}

	return m; // n == v[m]
}


/*
cmp:
Descrição:
	Comparador de voos que é utilizado no quick sort

Argumentos:
	p1	->voo a comparar 1
	p2	->voo a comparar 2

Return:
	-1	-> se p1 < p2
	1	-> se p1 > p2
	0	-> se p1 = p2
*/
int cmp(const void *p1, const void *p2)
{
	char *a1 = ((struct voos *)p1)->aero_chegada;
	char *a2 = ((struct voos *)p2)->aero_chegada;
	char b1 = ((struct voos *)p1)->hora;
	char b2 = ((struct voos *)p2)->hora;
	char c1 = ((struct voos *)p1)->min;
	char c2 = ((struct voos *)p2)->min;
	if (b1 < b2)
		return -1;
	else if (b1 > b2)
		return 1;
	else // se a1 for igual a a2 prossegue
	{
		if (c1 < c2)
			return -1;
		else if (c1 > c2)
			return 1;
		else // b1==b2
		{
			if (a1 < a2)
				return -1;
			else if (a1 > a2)
				return 1;
			else // c1==c2
				return 0;
		}
	}
}

/*
eliminaarray:
Descrição:
	elimina um voo(codigo, hora_partida, min_partida) de um array(array)

Argumentos:
	codigo			->codigo do areporto de chegada
	hora_partida	->hora de partida do voo
	min_partida		->minutos de partida do voo
	size			->tamanho do array
	array			->array

Return:
	true	->se removeu
	false	->se não removeu
*/
bool eliminaarray(char *codigo, char hora_partida, char min_partida, int size, struct voos array[])
{
	short pos = pesquisabinaria(codigo, hora_partida, min_partida, array, 0, size - 1);
	if (pos == -1)
	{
		return false;
	}
	else
	{
		for (int i = pos; i < size; i++)
			array[i] = array[i + 1];
		return true;
	}
}


/*
hash_code:
Descrição:
	Devolve um possivel hash code para uma string

Argumentos:
	str	->string

Return:
	unsigned long ->hash code
*/
const unsigned long hash_code(const char *str)
{
	unsigned long hash = 5381;
	int c;

	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;
	return hash;
}

/*
criar_aeroporto:
Descrição:
	adiciona um aeroporto ao sistema

Argumentos:
	codigo	->codigo do aeroporto

Return:
	true	->se adicionou
	false	->se não adicionou
	valores no std-out
*/
bool criar_aeroporto(char *codigo)
{
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
	
	//Guarda a informação no disco
	if (inserir_aeroporto(hash, codigo, pos))
	{
		write(disk, novoaeroporto, pos);

		pos++;

		printf("+ novo aeroporto %s\n", codigo);
		free(novoaeroporto);
		return true;
	}

	free(novoaeroporto);
	return false;
}


/*
criarVoo:
Descrição:
	adiciona um voo a um aeroporto

Argumentos:
	codigo_partida	->codigo do aeroporto de partida
	codigo_chegada	->codigo do aeroporto de chegada
	hora			->hora de partida
	min				->minutos de partida
	duracao			->duração do voo

Return:
	true	->se adicionou
	false	->se não adicionou
	valores no std-out
*/
bool criarVoo(char *codigo_partida, char *codigo_chegada, char hora, char min, short duracao)
{
	int pos1 = find_aeroportopos(hash, codigo_partida);

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

	if (aeroporto1 == NULL)
		return false;

	read(disk, aeroporto1, pos1); //le para o aeroporto a informacao do disco

	short i = pesquisabinaria(codigo_chegada, hora, min, aeroporto1->voosDecorrer, 0, aeroporto1->ocupado - 1);

	if (i != -1) //Encontrou voos iguais
	{
		printf("+ voo %s %s %02d:%02d existe\n", codigo_partida, codigo_chegada, hora, min);

		free(aeroporto1);
		return true;		
	}

	//cria voo
	struct voos voo;
	strcpy(voo.aero_chegada, codigo_chegada);
	voo.hora = hora;
	voo.min = min;
	voo.duracao = duracao;
	
	aeroporto1->voosDecorrer[aeroporto1->ocupado] = voo;
	qsort(aeroporto1->voosDecorrer, aeroporto1->ocupado + 1, sizeof(*aeroporto1->voosDecorrer), cmp); //quick sort do standart

	printf("+ novo voo %s %s %02d:%02d\n", codigo_partida, codigo_chegada, hora, min);

	//guarda no disco
	aeroporto1->ocupado += 1;
	write(disk, aeroporto1, pos1);
	free(aeroporto1);
	return true;
}

/*
elimina_voo:
Descrição:
	elimina um voo do sistema

Argumentos:
	codigo_partida	->codigo do aeroporto de partida
	codigo_chegada	->codigo do aeroporto de chegada
	hora_partida	->hora de partida do voo
	min_partida		->minutos de partida do voo

Return:
	true	->se removeu
	false	->se não removeu
	valores no std-out
*/
bool elimina_voo(char *codigo_partida, char *codigo_chegada, char hora_partida, char min_partida)
{
	struct aeroportos *aeroporto1;
	int pos1, pos2;

	pos1 = find_aeroportopos(hash, codigo_partida);

	aeroporto1 = malloc(sizeof(struct aeroportos));
	if (aeroporto1 == NULL)
		return false;

	//tenta encontrar voo
	if (pos1 == -1)
	{

		printf("+ voo %s %s %02d:%02d inexistente\n", codigo_partida, codigo_chegada, hora_partida, min_partida);
		return true;
	}
	pos2 = find_aeroportopos(hash, codigo_chegada);
	if (pos1 == -1 && pos2 == -1)
	{

		printf("+ voo %s %s %02d:%02d inexistente\n", codigo_partida, codigo_chegada, hora_partida, min_partida);
		return true;
	}

	read(disk, aeroporto1, pos1);
	short i = pesquisabinaria(codigo_chegada, hora_partida, min_partida, aeroporto1->voosDecorrer, 0, aeroporto1->ocupado - 1);

	if (pos1 != -1 && i == -1)
	{

		printf("+ voo %s %s %02d:%02d inexistente\n", codigo_partida, codigo_chegada, hora_partida, min_partida);
		return true;
	}

	//tenta remover do array
	eliminaarray(codigo_chegada, hora_partida, min_partida, aeroporto1->ocupado, aeroporto1->voosDecorrer);

	printf("+ voo %s %s %02d:%02d removido\n", codigo_partida, codigo_chegada, hora_partida, min_partida);
	aeroporto1->ocupado -= 1;
	//colocar no disco
	write(disk, aeroporto1, pos1);
	free(aeroporto1);
	return true;
}

/*
printcaminho:
Descrição:

	função recursiva que mostra um caminho no std-out


Argumentos:
	curr	->ultimo no do caminho

Return:
	init	->pointer para atribuição do primerio nó do caminho
	valores no std-out
*/
void printcaminho( Node* curr, Node** init )
{
	if( curr->pai == NULL )
	{
		*init = curr;
		return;
	}

	printcaminho( curr->pai, init );

	char hora_chegada;
	char min_chegada;

	translate_time( ( time_min(curr->hora,curr->min) + curr->dur ), &hora_chegada, &min_chegada );
	
	printf("%-4s %-4s %02hhi:%02hhi %02hhi:%02hhi\n",
		curr->pai->name, 
		curr->name, 
		curr->hora, 
		curr->min, 
		hora_chegada, 
		min_chegada);

}

/*
tempo_voo:
Descrição:
	calculo do caminho mais curto entre dois aeroportos

Argumentos:
	codigo_partida	->codigo do aeroporto inicial
	codigo_chegada	->codigo do aeroporto destino
	hora_chegada_in	->hora de chegada ao aeroporto partida
	min_chegada_in	->minutos de chegada ao aeroporto de partida

Return:
	init	->pointer para atribuição do primerio nó do caminho
	valores no std-out
*/
bool tempo_voo(char *codigo_partida, char *codigo_chegada, char hora_chegada_in, char min_chegada_in)
{
	int pos1 = find_aeroportopos(hash, codigo_partida);

	if (pos1 == -1)
	{
		printf("+ aeroporto %s desconhecido\n", codigo_partida);
		return false;
	}

	int pos2 = find_aeroportopos(hash, codigo_chegada);
	if (pos1 != -1 && pos2 == -1)
	{
		printf("+ aeroporto %s desconhecido\n", codigo_chegada);
		return false;
	}

	unsigned short duracao = 0;

	Node *ret = dijkstra(hash, disk, codigo_partida, hora_chegada_in, min_chegada_in, codigo_chegada, &duracao);
	if (ret == NULL)
	{
		printf("+ sem voos de %s para %s\n", codigo_partida, codigo_chegada);
		return false;
	}

	puts("De   Para Parte Chega");
	puts("==== ==== ===== =====");
	Node* init;
	printcaminho( ret, &init );
	printf("Tempo de viagem: %hu minutos\n", duracao );

	free_node( init );

	return true;
}

/** Main **/
int main(void)
{
	pos = 0;
	disk = openFile(FILE_DB);
	hash = newhash();
	if (hash == NULL)
		return 1;

	//carrega os aeroportos para a hashtable
	pos = loadDb(disk, hash);

	//Interface do utilizador
	char modo[3];

	while (scanf("%s", modo) != EOF)
	{
		char codigo_aero1[5];
		char codigo_aero2[5];
		char hora;
		char min;

		if (strcmp(modo, "AI") == 0)
		{
			scanf(" %s", codigo_aero1);
			criar_aeroporto(codigo_aero1);
		}
		else if (strcmp(modo, "FI") == 0)
		{
			short duracao;

			scanf(" %s %s %02hhu:%02hhu %hd", codigo_aero1, codigo_aero2, &hora, &min, &duracao);
			criarVoo(codigo_aero1, codigo_aero2, hora, min, duracao);
		}

		else if (strcmp(modo, "FD") == 0)
		{
			scanf("%s %s %02hhu:%02hhu", codigo_aero1, codigo_aero2, &hora, &min);
			elimina_voo(codigo_aero1, codigo_aero2, hora, min);
		}
		else if (strcmp(modo, "TR") == 0)
		{
			scanf("%s %s %hhu:%hhu", codigo_aero1, codigo_aero2, &hora, &min);

			tempo_voo(codigo_aero1, codigo_aero2, hora, min);
		}
		if (strcmp(modo, "X") == 0)
		{
			hash_free(hash);
			fclose(disk);
			return 0;
		}
	}
	return 0;
}