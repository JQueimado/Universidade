#include <fcntl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_AERO 1833341





typedef struct temp
{
	int fd;
}
temp;

//struct dos voos


typedef struct voo
{
	char codigo[7]; // codigo do voo
	char aero_partida[5];
	char aero_chegada[5];
	short hora_partida;
	short duracao;
}
voos;

//Struct AEROPORTOS

typedef struct aeroportos
{	
	char  codigo[5];		// codigo do aeroporto e não e reutilizavel
	//char  fuso_horario[5];		// fuso horario do aeroporto		
	voos voosDecorrer[150]; // array de 150 struct's voos 
}
aeroportos;

typedef struct hashtable_aeroportos
{
	aeroportos aeroporto[MAX_AERO];
}
hashtable_aeroportos;


int hash_function_aeroportos(char *codigo);
int hash_function_aeroportos1(char *codigo);
int hash_function_aeroportos2(char *codigo);
void free_hash_aeroportos(aeroportos *hash_aeroportos);

int  hashtable_aeroportos_open(char*name);
aeroportos read_aeroportos_at_hash(int fd ,char *codigo);
void write_aeroportos(int fd,aeroportos novoAeroporto);

//void criar_voo(int fd, aeroportos partida, aeroportos chegada, char* hora, unsigned char duracao);