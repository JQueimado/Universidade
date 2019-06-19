
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "aeroporto.h"
#include "hashtable.h"
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


/*void criarVoo(char *codigo_partida, char *codigo_chegada, char hora, char minutos, short duracao)
{
	//aeroportos* temp_partida;
	//aeroportos temp_chegada;
	//temp_partida = read_aeroportos_at_hash(fd,codigo_partida);

	
	if(!verifica_aero(fd,codigo_partida))
	{
		printf("+ aeroporto %s desconhecido\n",codigo_partida);
	}
	else if(verifica_aero(fd,codigo_partida) && !verifica_aero(fd,codigo_chegada))
	{
		printf("+ aeroporto %s desconhecido\n",codigo_chegada);
	}
	else if (verifica_voo(*temp_partida, codigo_chegada, hora, minutos) ) //ja existe voo
	{
		printf("+ voo %s %s %d:%d existe\n", codigo_partida, codigo_chegada, hora, minutos);
	}
	else //cria voo
	{
		add_voo(fd, &temp_partida, codigo_chegada, hora,minutos, duracao);
		printf("+ novo voo %s %s %d:%d\n",codigo_partida,codigo_chegada, hora, minutos);
	}
}*/




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
		//char codigo_aero2[5];
		//char hora_partida[6];

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
		/*else if ( strcmp(modo,"FI") == 0 )
		{		
			short duracao;	
			
			scanf(" %s %s %s %hd",codigo_aero1, codigo_aero2, hora_partida, &duracao);
			criarVoo(ficheiro,codigo_aero1,codigo_aero2,hora_partida,duracao);
		}
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