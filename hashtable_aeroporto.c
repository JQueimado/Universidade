#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "hashtable_aeroporto.h"

// numero primo seguinte 1833333 que permite menter o factor de carga abaixo de 0,6 para 1100000 utilizadores
#define MAX_UTL 1833341  
#define PRIME 1833319

/* time_to_char */
void time_to_char( char* time, char* h, char* m )
{
	char hours[3];
	char minutes[3];
	memcpy(hours, &time[0], 2);
	memcpy(minutes, &time[3], 2);
	*h = atoi(hours);
	*m = atoi(minutes);
}

int hashtable_aeroportos_open(char*name)
{
	temp *tempp = malloc(sizeof(struct temp));

	int fd = open(name,O_RDWR,S_IRUSR | S_IWUSR);

	if(fd == -1)
	{
		tempp -> fd = open(name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

		lseek(tempp -> fd, 0,SEEK_SET);
		write(tempp -> fd, NULL,sizeof(struct hashtable_aeroportos));
		
		return tempp -> fd;
	}
	else
	{
		tempp -> fd = fd;
		return tempp -> fd;
	}
}
	

aeroportos read_aeroportos_at_hash(int fd ,char *codigo)
{
	aeroportos novo_aeroporto;
	int hash1 = hash_function_aeroportos1(codigo);
	int hash2 = hash_function_aeroportos2(codigo);
	
	lseek(fd, hash1 * sizeof(struct aeroportos),SEEK_SET); // posiciona na posicao do disco 
	read(fd,&novo_aeroporto,sizeof(struct aeroportos)); 
	
	while(strcmp(novo_aeroporto.codigo, "")!=0)  
	{
		if(strcmp(novo_aeroporto.codigo, codigo	)==0)
		{
			return novo_aeroporto;  
		}

		hash1 += hash2;     
		hash1 %= MAX_UTL;  

		lseek(fd,hash1* sizeof(struct aeroportos),SEEK_SET);      
		read(fd,&(novo_aeroporto),sizeof(struct aeroportos));
	}  
	return novo_aeroporto;
}

void write_aeroportos(int fd,aeroportos novoAeroporto)
{
	aeroportos novo_Aeroportos;
	int hash1 = hash_function_aeroportos1(novoAeroporto.codigo); //faz hash para encontrar a posiçao do aeroporto 
	int hash2 = hash_function_aeroportos2(novoAeroporto.codigo); //faz duplo hash, na eventualidade da posiçao esta ocupada
	
	lseek(fd, hash1 * sizeof(struct aeroportos),SEEK_SET);  // posiciona na posicao do disco 
	read(fd, &novo_Aeroportos,sizeof(struct aeroportos)); // le do disco a informaçao do aeroporto

	
	while(strcmp(novo_Aeroportos.codigo,"")!=0) 
 	{
		if(strcmp(novo_Aeroportos.codigo,novoAeroporto.codigo)==0)  
		{
			lseek(fd, hash1 *sizeof(struct aeroportos),SEEK_SET);  	
			write(fd,&novoAeroporto,sizeof(struct aeroportos)); 
			return;
		} 
		hash1 += hash2; 	
		hash1 %= MAX_UTL;

		lseek(fd, hash1 * sizeof(struct aeroportos),SEEK_SET); 
		read(fd,&novo_Aeroportos,sizeof(struct aeroportos));
	}
	lseek(fd, hash1 *sizeof(struct aeroportos),SEEK_SET);	
	write(fd,&novoAeroporto,sizeof(struct aeroportos)); 
}

int find_aeroporto(int fd, char* codigo)
{
	aeroportos novo_aeroporto;
	int hash1 = hash_function_aeroportos1(codigo);
	int hash2 = hash_function_aeroportos2(codigo);
	
	lseek(fd, hash1 * sizeof(struct aeroportos),SEEK_SET); // posiciona na posicao do disco 
	read(fd,&novo_aeroporto,sizeof(struct aeroportos)); 
	
	while(strcmp(novo_aeroporto.codigo, "")!=0)  
	{
		if(strcmp(novo_aeroporto.codigo, codigo)==0)
		{
			return hash1;  
		}

		hash1 += hash2;     
		hash1 %= MAX_UTL;  

		lseek(fd,hash1* sizeof(struct aeroportos),SEEK_SET);      
		read(fd,&(novo_aeroporto),sizeof(struct aeroportos));
	}  
	return -1;
	
}

// liberta a hashtable de memoria
void free_hash_aeroportos(aeroportos *hash_aeroportos)
{
	free(hash_aeroportos);
}

//funcao de hash djb2 
//http://www.cse.yorku.ca/~oz/hash.html
//https://en.wikipedia.org/wiki/List_of_hash_functions#cite_note-2
int hash_function_aeroportos(char *codigo)
{
	int hash = 5381;
	int c;
	while ((c = *codigo++))
		hash = ((hash << 5) + hash) + c;  /*hash * 33 + c */	
	return hash%MAX_UTL;
}

//primeira funcao de duplo hashing de EDA1
int hash_function_aeroportos1(char *codigo) {
	unsigned long hashcode = hash_function_aeroportos(codigo);
	hashcode %= MAX_UTL;

	int hash = (int) hashcode;

	if (hash < 0)
		hash += MAX_UTL;

	return hash;
}

//segunda funcao de duplo hashing de EDA1
int hash_function_aeroportos2(char *codigo) {
	unsigned long hashcode = hash_function_aeroportos(codigo);
	hashcode %= MAX_UTL;

	int hash = (int) hashcode;

	if (hash < 0)
		hash += MAX_UTL;
	return PRIME - hash % PRIME;
}

/* Adicionar Voo */
/*void criar_voo(int fd, char* codigo, aeroportos partida, aeroportos chegada, char* hora, unsigned char duracao)
{


	voos novo_voo;
	int hash1 = hash_function_aeroportos1(novoAeroporto.codigo); //faz hash para encontrar a posiçao do aeroporto 
	int hash2 = hash_function_aeroportos2(novoAeroporto.codigo); //faz duplo hash, na eventualidade da posiçao esta ocupada
	
	lseek(fd, hash1 * sizeof(struct aeroportos),SEEK_SET);  // posiciona na posicao do disco 
	read(fd, &novo_Aeroportos,sizeof(struct aeroportos)); // le do disco a informaçao do aeroporto

	
	while(strcmp(novo_Aeroportos.codigo,"")!=0) 
 	{
		if(strcmp(novo_Aeroportos.codigo,novoAeroporto.codigo)==0)  
		{
			lseek(fd, hash1 *sizeof(struct aeroportos),SEEK_SET);  	
			write(fd,&novoAeroporto,sizeof(struct aeroportos)); 
			return;
		} 
		hash1 += hash2; 	
		hash1 %= MAX_UTL;

		lseek(fd, hash1 * sizeof(struct aeroportos),SEEK_SET); 
		read(fd,&novo_Aeroportos,sizeof(struct aeroportos));
	}
	lseek(fd, hash1 *sizeof(struct aeroportos),SEEK_SET);	
	write(fd,&novoAeroporto,sizeof(struct aeroportos)); 
}*/

