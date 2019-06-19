
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "aeroporto.h"
#include "basedados.h"

#define MAX_SIZE 400009
#define CACHE 879  //perto do numero de paginas 
#define MAX_VOO 150
#define FILE_DB "db.cache"

FILE *disk;
struct hashtable *hash;
int pos;
int ae_size = 0;
struct aeroportos buffer[CACHE];


/*FUncoes auxiliares*/


int pesquisabinaria(char *codigo,struct voos arr[], int i, int j)
{
	
	if (i > j)
    	return -1;                  // vector vazio

  int m = (i + j) / 2;          // posição central


  if (strcmp(codigo,arr[m].aero_chegada) < 0) 
    // Restringe a pesquisa ao intervalo i..m - 1
    return pesquisabinaria(codigo, arr, i, m - 1);

  if (strcmp(codigo,arr[m].aero_chegada) > 0)
    // Restringe a pesquisa ao intervalo m + 1..j
    return pesquisabinaria(codigo, arr, m + 1, j);

  return m;                     // n == v[m]
}

void arrayordenado(struct voos voo, int size, struct voos array[])	
{
	short i;
	//Percorre a lista a partir do fim, se nick na posição i for maior do que o nick dado
	//move i para i+1
	for (i = size-1; ( i >= 0  && strcmp(array[i].aero_chegada,voo.aero_chegada) > 0); i--)
       array[i+1] = array[i];
	
	//Coloca o user seguido no esapaço criado
    array[i+1] = voo;
}




bool criar_aeroporto(char *codigo)
{
	//int pos = hash_function_aeroportos(codigo);
	//printf("%d\n",pos);
	//Procura o aeroporto na hashtable
	if(find_aeroporto(hash,codigo))
	{
		printf("+ aeroporto %s existe\n",codigo);
		return true;
	}

	//Cria um aeroporto
	struct aeroportos *novoaeroporto = malloc(sizeof(struct aeroportos));
	if(novoaeroporto == NULL)
		return false; // caso nao consiga alocar
	strcpy(novoaeroporto->codigo,codigo);
	novoaeroporto->ocupado=0;
	//Guarda a informação no disco
	if(inserir_aeroporto(hash,codigo,pos))
	{

		//write(disk,novoaeroporto,pos);
		strcpy( buffer[ae_size].codigo, codigo );

		ae_size++;
		//printf("%d\n",ae_size);
		pos++;
		
		if(ae_size >= CACHE)
			{
				fseek(disk, pos*sizeof(struct aeroportos), SEEK_SET);
				fwrite( &buffer ,sizeof(struct aeroportos), CACHE, disk);
				ae_size = 0;
				//printf("aqui\n");
			}
		printf("+ novo aeroporto %s\n",codigo);
		free(novoaeroporto);
		return true;
	}

	free(novoaeroporto);
	return false;
}


bool criarVoo(char *codigo_partida, char *codigo_chegada, char *hora_partida, short duracao)
{
	//aeroportos* temp_partida;
	//aeroportos temp_chegada;
	//temp_partida = read_aeroportos_at_hash(fd,codigo_partida);

	if(!find_aeroporto(hash,codigo_partida) )
	{
		printf("+ aeroporto %s desconhecido\n",codigo_partida);
		return true;
	}
	if(find_aeroporto(hash,codigo_partida) && !find_aeroporto(hash,codigo_chegada))
	{
		printf("+ aeroporto %s desconhecido\n",codigo_chegada);
		return true;
	}
	struct aeroportos *aeroporto1 = malloc(sizeof(struct aeroportos)); 
	int pos1=find_aeroportoid(hash,codigo_partida);
	//printf("aqui1");
	if(aeroporto1 == NULL)
	{
		//printf("aqui2");
		return false;
	}

	read(disk,aeroporto1,pos1);
	short i=pesquisabinaria(codigo_chegada,aeroporto1->voosDecorrer,0,aeroporto1->ocupado-1);
	if (i!=-1) //Encontrou voos iguais
	{
		//printf("%d\n",i);
		//printf("%s\n",aeroporto1->voosDecorrer[i].hora_partida);
		if(strcmp(aeroporto1->voosDecorrer->hora_partida,hora_partida) == 0 )
		{
			printf("+ voo %s %s %s existe\n", codigo_partida, codigo_chegada, hora_partida);
			return true;
		}
		
	}
	//cria voo-
	//strcpy(aeroporto1->voosDecorrer[0].aero_chegada,codigo_chegada); //RESOLVER BUG DE QUANDO CRIA DEVIA IMPRIMIR JÁ EXISTE
	struct voos voo;
	strcpy(voo.aero_chegada,codigo_chegada);
	strcpy(voo.hora_partida,hora_partida);
	voo.duracao = duracao;
	arrayordenado(voo, aeroporto1->ocupado, aeroporto1->voosDecorrer);
	
	//1. ordenar array de voos
	//qsort(aeroporto1->voosDecorrer, 150, sizeof(struct voos), compare);
	/*for(int i=0;i<=aeroporto1->ocupado-1;i++)
	{
		printf("cod: %s\n",aeroporto1->voosDecorrer[i].aero_chegada);
	}*/

	//add_voo(fd, &temp_partida, codigo_chegada, hora,minutos, duracao);
	
	printf("+ novo voo %s %s %s\n",codigo_partida,codigo_chegada, hora_partida);
	aeroporto1->ocupado+=1;
	//guarda no disco
	write(disk, aeroporto1, pos1);
	
	free(aeroporto1);

	return true;
	
}




int main(void)
{
	//struct aeroportos buffer[CONA];
	//int ae_size = 0;
	pos=0;
	disk = openFile(FILE_DB);
	hash = newhash();
	if(hash == NULL)
		return 1;

	//carrega os aeroportos para a hashtable
	pos=loadDb(disk,hash);	

	//Interface do utilizador
	char modo[3];
	while(scanf("%s",modo) != EOF)
	{
		char codigo_aero1[5];
		char codigo_aero2[5];
		char hora_partida[6];

		if(strcmp(modo,"AI")==0)
		{
			scanf(" %s",codigo_aero1);
			criar_aeroporto(codigo_aero1);
		//	printf("ae:%d\n",ae_size);


/*			if(find_aeroporto(hash,codigo_aero1))
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
			printf("+ novo aeroporto %s\n",codigo_aero1);*/	

		}
		else if ( strcmp(modo,"FI") == 0 )
		{		
			short duracao;	
			
			scanf(" %s %s %s %hd",codigo_aero1, codigo_aero2, hora_partida, &duracao);
			criarVoo(codigo_aero1,codigo_aero2,hora_partida,duracao);
		}/*
		else if( strcmp(modo,"FD") == 0 )
		{
			scanf("%s %s %s", codigo_aero1, codigo_aero2, hora_partida);
			if( elimina_voo(ficheiro, codigo_aero1, codigo_aero2, hora_partida) )
				printf("+ voo %s %s %s removido\n", codigo_aero1, codigo_aero2, hora_partida);
			else
				printf("+ voo %s %s %s inexistente\n", codigo_aero1, codigo_aero2, hora_partida);
		}
		
		*/
		if(strcmp(modo,"X") == 0)
		{
			if(ae_size < CACHE)
			{
				fseek(disk, pos*sizeof(struct aeroportos), SEEK_SET);
				fwrite( &buffer ,sizeof(struct aeroportos), CACHE, disk);
				
				
			}
			hash_free(hash);
			//fseek(disk,0, SEEK_END);
			//fwrite( &buffer ,sizeof(struct aeroportos), ae_size, disk);
			fclose(disk);
			return 0;
			
		}
	}

	return 0;
}