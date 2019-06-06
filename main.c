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
void criarVoo(int fd,char *codigo_partida,char *codigo_chegada,short hora_partida,short duracao)
{
	aeroportos temp_partida;
	//aeroportos temp_chegada;
	temp_partida = read_aeroportos_at_hash(fd,codigo_partida);
	if(!verifica_aero(fd,codigo_partida))
	{
		printf("+ aeroporto %s desconhecido\n",codigo_partida);
	}
	else if(!verifica_aero(fd,codigo_chegada) && verifica_aero(fd,codigo_chegada))
	{
		printf("+ aeroporto %s desconhecido\n",codigo_chegada);
	}
	else if (verifica_aero(fd,codigo_partida) && verifica_aero(fd,codigo_chegada) ) //ja existe voo
	{
		/* code */
	}
	else //cria voo
	{
		strcpy(temp_partida.voosDecorrer[temp_partida.index_voo].aero_chegada,codigo_chegada);
	}
}

// verifica_hora


//adicionar_voo

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
			
			scanf(" %s %s %s %d %d",codigo_aero1, codigo_chegada, hora_partida, &duracao);

			criarVoo(ficheiro,codigo_aero1,codigo_chegada,hora_partida,duracao);

		}
		
		if(strcmp(modo,"X") == 0)
		{
			close(ficheiro);
			return 0;
		}
		
	}
}

