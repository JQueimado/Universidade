
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "aeroporto.h"
#include "basedados.h"
#include "Dijkstra.h"

#define MAX_SIZE 20477
#define MAX_VIAGEM 150000
#define CACHE 879 //perto do numero de paginas
#define MAX_VOO 150
#define AI 5862127
#define FI 5862292
#define FD 5862287
#define TR 5862763
#define X 177661
#define INF -1
#define FILE_DB "db.cache"

/** GLOBAIS **/
FILE *disk;
struct hashtable *hash;
int pos;
int ae_size = 0;
struct aeroportos buffer[CACHE];

/* Funcoes auxiliares */
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

Comparador que e utilizado no quick sort

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

const unsigned long hash_code(const char *str)
{
	unsigned long hash = 5381;
	int c;

	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;
	return hash;
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

bool criarVoo(char *codigo_partida, char *codigo_chegada, char hora, char min, short duracao)
{
	//printf("partida:%s chegada: %s hora_partida: %s duracao: %d\n",codigo_partida,codigo_chegada,hora_partida,duracao);
	//aeroportos* temp_partida;
	//aeroportos temp_chegada;
	//temp_partida = read_aeroportos_at_hash(fd,codigo_partida);
	//printf("%02d %02d\n",hora,min);
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

	short i = pesquisabinaria(codigo_chegada, hora, min, aeroporto1->voosDecorrer, 0, aeroporto1->ocupado - 1);
	//printf("Indice do array: %d\n",i);
	if (i != -1) //Encontrou voos iguais
	{
		printf("+ voo %s %s %02d:%02d existe\n", codigo_partida, codigo_chegada, hora, min);
		/*for(int i=0;i<=aeroporto1->ocupado-1;i++)
	{
		printf("X:%s %s\n",aeroporto1->voosDecorrer[i].aero_chegada,aeroporto1->voosDecorrer[i].hora_partida);
	}*/
		free(aeroporto1);
		return true;
		
	}
	//cria voo-

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
elimina voo

*/

bool elimina_voo(char *codigo_partida, char *codigo_chegada, char hora_partida, char min_partida)
{
	struct aeroportos *aeroporto1;
	int pos1, pos2;

	pos1 = find_aeroportopos(hash, codigo_partida);
	//printf("Pos1:%d\n",pos1);
	//printf("Pos1: %d pos2: %d\n",pos1,pos2);
	aeroporto1 = malloc(sizeof(struct aeroportos));
	if (aeroporto1 == NULL)
		return false;

	//printf("Encontrou: %d\n",i);
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

	//read(disk, aeroporto1, pos1);
	//tenta remover do array
	eliminaarray(codigo_chegada, hora_partida, min_partida, aeroporto1->ocupado, aeroporto1->voosDecorrer);

	printf("+ voo %s %s %02d:%02d removido\n", codigo_partida, codigo_chegada, hora_partida, min_partida);
	aeroporto1->ocupado -= 1;
	//colocar no disco
	write(disk, aeroporto1, pos1);
	free(aeroporto1);
	return true;
}

bool tempo_voo(char *codigo_partida, char *codigo_chegada, char hora_chegada, char min_chegada)
{
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

	unsigned short duracao = 0;

	Caminho *caminho = dijkstra(hash, disk, codigo_partida, hora_chegada, min_chegada, codigo_chegada, &duracao);
	if (caminho == NULL)
	{
		printf("+ sem voos de %s para %s\n", codigo_partida, codigo_chegada);
		return true;
	}

	puts("De   Para Parte Chega");
	puts("==== ==== ===== =====");
	while (caminho->next != NULL)
	{
		printf("%-4s %-4s %02hhi:%02hhi %02hhi:%02hhi\n",
			caminho->aero, 
			caminho->next->aero, 
			caminho->next->hora_partida, 
			caminho->next->min_partida, 
			caminho->next->hora_chegada, 
			caminho->next->min_chegada);
		
		Caminho *to_free = caminho;
		caminho = caminho->next;
		free( to_free );
	}

	free( caminho );

	printf("Tempo de viagem: %hu minutos\n", duracao );
	return true;
}

int main(void)
{
	//struct aeroportos buffer[CONA];
	//int ae_size = 0;
	pos = 0;
	disk = openFile(FILE_DB);
	hash = newhash();
	if (hash == NULL)
		return 1;

	//carrega os aeroportos para a hashtable
	pos = loadDb(disk, hash);

	//Interface do utilizador
	char modo[3];

	/*char codigo_aero1[5];
	char codigo_aero2[5];
	char hora_partida[6];
	short duracao;
	while(scanf("%s",modo) != EOF)
	{
	switch(hash_code(modo))
	{

		case AI:
			scanf(" %s",codigo_aero1);
			criar_aeroporto(codigo_aero1);
			break;
		case FI:	
			scanf(" %s %s %s %hd",codigo_aero1, codigo_aero2, hora_partida, &duracao);
			criarVoo(codigo_aero1,codigo_aero2,hora_partida,duracao);
			break;
		case FD:
			scanf("%s %s %s", codigo_aero1, codigo_aero2, hora_partida);
			elimina_voo(codigo_aero1,codigo_aero2,hora_partida);
		case X:
			hash_free(hash);
			fclose(disk);
			return 0;
		default:
			
	}
	}*/

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
			//printf("ae:%d\n",ae_size);

			/*
			if(find_aeroporto(hash,codigo_aero1))
			{
				printf("+ aeroporto %s existe\n",codigo_aero1);
				continue;
			}

		 	strcpy( buffer[ae_size].codigo, codigo_aero1 );
			ae_size++;

			if(ae_size >= CONA)
			{
				fseek(disk, -1, SEEK_END);
				fwrite( &buffer ,sizeof(struct aeroportos), CONA, disk);
				ae_size = 0;
			}
			printf("+ novo aeroporto %s\n",codigo_aero1);	

		*/
		}
		else if (strcmp(modo, "FI") == 0)
		{
			short duracao;

			scanf(" %s %s %02hhu:%02hhu %hd", codigo_aero1, codigo_aero2, &hora, &min, &duracao);
			//printf("%02hhu:%02hhu\n",hora,min);
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
			/*	if(ae_size < CACHE)
			{
				fseek(disk, pos*sizeof(struct aeroportos), SEEK_SET);
				fwrite( &buffer ,sizeof(struct aeroportos), CACHE, disk);
				
				
			}*/
			hash_free(hash);
			//fseek(disk,0, SEEK_END);
			//fwrite( &buffer ,sizeof(struct aeroportos), ae_size, disk);
			fclose(disk);
			return 0;
		}
	}

	return 0;
}