#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable_aeroporto.h"

//função VERIFICA se o aeroporto já foi criado
// função recebe o FD e o codigo para aceder ao disco
// e devolve TRUE se o aeroporto existir ou FALSE se o contrario 
bool verifica_aero(int fd,char *codigo)
{
	aeroportos temp;
	temp = read_aeroportos_at_hash(fd,codigo);
	if(strcmp(temp.codigo,codigo)==0) //verificação se codigo já existe
		return true;
	return false;
}

bool verifica_voo( aeroportos partida, char* chegada, char h, char m)
{
	printf("cona\n");
	for(int i = 0; i<partida.index_voo; i++)
	{
		voos curr = partida.voosDecorrer[i];
		printf("%s %d %d\n",curr.aero_chegada,curr.hora_partida,curr.minuto_partida);
		if( strcmp(chegada, curr.aero_chegada) == 0 &&  curr.hora_partida == h && curr.minuto_partida == m)
		{ //caso encontre
			printf("h: %d\n hora_partida: %d\n",h,curr.hora_partida); 
			return true;
		}
	}
	return false;
}

//função CriarAeroportos cria um novo aeroporto
//recebe o FD, o codigo e o fuso horario do aeroporto
//verifica se o aeroporto ja esta na hashtable, se nao
//preenche os campos da struct e escreve em disco 
void criarAeroportos(int fd,char *codigo)
{	
		if(verifica_aero(fd,codigo))
		{
			printf("+ aeroporto %s existe\n",codigo);
		}
		else
		{
			aeroportos temp;
			strcpy(temp.codigo,codigo);
			temp.index_voo=0;
			write_aeroportos(fd,temp); //passa para o disco
			printf("+ novo aeroporto %s\n", codigo);
		}
}
/* Criar Voo */
bool add_voo(int fd, aeroportos aeroporto, char* codigo_chegada, char hora, char minutos, short duracao )
{
	if( aeroporto.index_voo < 150 ){
		strcpy(aeroporto.voosDecorrer[aeroporto.index_voo].aero_chegada,codigo_chegada);
		aeroporto.voosDecorrer[aeroporto.index_voo].hora_partida = hora;
		aeroporto.voosDecorrer[aeroporto.index_voo].minuto_partida = minutos;
		aeroporto.index_voo++;
		write_aeroportos(fd,aeroporto);
	}
	else
	{
		for( int i = 0; i < 150; i++ )
		{
			voos* voo = &aeroporto.voosDecorrer[i];
			if( voo->hora_partida == -1 )
			{
				strcpy(voo->aero_chegada, codigo_chegada);
				voo->hora_partida = hora;
				voo->minuto_partida = minutos;
				voo->duracao = duracao;
			}
		}
		return false;
	}
	write_aeroportos(fd,aeroporto);
	return true;
}

void criarVoo(int fd,char *codigo_partida,char *codigo_chegada,char* hora_partida,short duracao)
{
	aeroportos temp_partida;
	//aeroportos temp_chegada;
	temp_partida = read_aeroportos_at_hash(fd,codigo_partida);
	char hora;
	char minutos;
	char *line = strdup(hora_partida); // don't do char *line = "user name"; see Note

	/* 
	hora = strtok(line, ":"); //first_part points to "user"
	minutos = strtok(NULL, ":");   //sec_part points to "name"
	*/
	time_to_char(hora_partida, &hora, &minutos);

	printf("%d %d\n",hora,minutos);

	if(!verifica_aero(fd,codigo_partida))
	{
		printf("+ aeroporto %s desconhecido\n",codigo_partida);
	}
	else if(verifica_aero(fd,codigo_partida) && !verifica_aero(fd,codigo_chegada))
	{
		printf("+ aeroporto %s desconhecido\n",codigo_chegada);
	}
	else if (verifica_voo(temp_partida, codigo_chegada, hora, minutos) ) //ja existe voo
	{
		printf("+ voo %s %s %s existe\n", codigo_partida, codigo_chegada, hora_partida);
	}
	else //cria voo
	{
		add_voo(fd, temp_partida, codigo_chegada, hora,minutos, duracao);
		printf("+ novo voo %s %s %s\n",codigo_partida,codigo_chegada,hora_partida);
	}
}
void retirar_array(int fd,char *codigo_partida,char *codigo_chegada)
{
	
}
void elimina_voo(int fd,char *codigo_partida,char *codigo_chegada, char*hora_partida)
{
	aeroportos temp_partida;
	temp_partida = read_aeroportos_at_hash(fd,codigo_partida);
	if(!verifica_aero(fd,codigo_partida))
	{
		printf("+ voo %s %s %s desconhecido\n",codigo_partida,codigo_chegada,hora_partida);
	}
	else if(verifica_aero(fd,codigo_partida) && !verifica_aero(fd,codigo_chegada))
	{
		printf("+ voo %s %s %s desconhecido\n",codigo_partida,codigo_chegada,hora_partida);
	}
	else //remove voo
	{

	}
}

// na funçao MAIN recebe os comandos a executar e chama as respectivas funções 	
int main()
{
	int ficheiro;
	ficheiro = hashtable_aeroportos_open("ficheiro");

	char modo[3];
	while(scanf("%s",modo) != EOF)
	{
		char codigo_aero1[4];
		//char codigo_aero2[4];
		//char fuso_horario[5];
		
		if(strcmp(modo,"AI")==0)
		{
			scanf(" %s",codigo_aero1);
			criarAeroportos(ficheiro,codigo_aero1);
		}
		
		else if ( strcmp(modo,"FI") == 0 )
		{
			//char codigo_partida[4];
			char codigo_chegada[4];
			char hora_partida[6];			
			short duracao;	
			
			scanf(" %s %s %s %hd",codigo_aero1, codigo_chegada, hora_partida, &duracao);

			criarVoo(ficheiro,codigo_aero1,codigo_chegada,hora_partida,duracao);

		}
		
		if(strcmp(modo,"X") == 0)
		{
			close(ficheiro);
			return 0;
		}
		
	}
}

