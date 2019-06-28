#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable_aeroporto.h"

/* Compare */
/* Compara 2 voos */
bool compare_voo( voos voo, char* codigo, char hora, char minutos)
{
	return (strcmp(voo.aero_chegada, codigo) == 0) && (voo.hora_partida == hora) && (voo.minuto_partida == minutos);
}

//função VERIFICA se o aeroporto já foi criado
// função recebe o FD e o codigo para aceder ao disco
// e devolve TRUE se o aeroporto existir ou FALSE se o contrario 
bool verifica_aero(int fd,char *codigo)
{
	aeroportos* temp;
	temp = read_aeroportos_at_hash(fd,codigo);
	if(strcmp(temp->codigo,codigo)==0) //verificação se codigo já existe
		return true;
	return false;
}

bool verifica_voo( aeroportos partida, char* chegada, char h, char m)
{
	//printf("cona\n");
	for(int i = 0; i<partida.index_voo; i++)
	{
		voos curr = partida.voosDecorrer[i];
		//printf("%s %d %d\n",curr.aero_chegada,curr.hora_partida,curr.minuto_partida);

		if( compare_voo( curr, chegada, h, m) )
		{ //caso encontre
			//printf("h: %d\n hora_partida: %d\n",h,curr.hora_partida); 
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

void criarVoo(int fd, char *codigo_partida, char *codigo_chegada, char hora, char minutos, short duracao)
{
	aeroportos* temp_partida;
	//aeroportos temp_chegada;
	temp_partida = read_aeroportos_at_hash(fd,codigo_partida);

	/* 
	hora = strtok(line, ":"); //first_part points to "user"
	minutos = strtok(NULL, ":");   //sec_part points to "name"
	*/

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
}

/* Remover Voo:
	Voos Removidos tem a flag hora = -1
*/
bool retirar_voo(int fd, aeroportos aeroporto, char* codigo_chegada, char hora, char minutos)
{
	for(unsigned char i = 0; i<aeroporto.index_voo; i++)
	{
		voos* voo = &aeroporto.voosDecorrer[i];
		if( voo->hora_partida != -1 )
			if( compare_voo(*voo, codigo_chegada, hora, minutos) )
			{
				voo->hora_partida = -1; //Remoção
				//printf("flag:%d\n",voo.hora_partida);
				write_aeroportos(fd, aeroporto);
				return true; //Successfull
			}
	}
	return false; //Não encontrado
}

bool elimina_voo(int fd,char *codigo_partida,char *codigo_chegada, char hora, char minutos)
{
	aeroportos* temp_partida;
	temp_partida = read_aeroportos_at_hash(fd,codigo_partida);
	if( verifica_aero(fd,codigo_partida) && verifica_aero(fd, codigo_chegada))
	{
		if( retirar_voo( fd, *temp_partida, codigo_chegada, hora, minutos) )
		{
			return true;
		}
	}
	return false;
}
/*
void calcula_viagem(int fd,char *codigo_partida,char *codigo_chegada,char *hora_partida)
{
	aeroportos temp_partida;
	temp_partida = read_aeroportos_at_hash(fd,codigo_partida);
	if(!verifica_aero(fd,codigo_partida))
	{
		printf("+ aeroporto %s desconhecido\n",codigo_partida);
	}
	if(verifica_aero(fd,codigo_partida))
	{

	}

}*/

// na funçao MAIN recebe os comandos a executar e chama as respectivas funções 	
int main()
{
	int ficheiro;
	ficheiro = hashtable_aeroportos_open("ficheiro.cache");

	char modo[3];
	while(scanf("%s",modo) != EOF)
	{
		char codigo_aero1[5];
		char codigo_aero2[5];
		char hora_partida[6];
		
		char hora, minutos;

		if(strcmp(modo,"AI")==0)
		{
			scanf(" %s",codigo_aero1);
			criarAeroportos(ficheiro,codigo_aero1);
		}
		else if ( strcmp(modo,"FI") == 0 )
		{		
			short duracao;	
			scanf(" %s %s %d:%d %hd",codigo_aero1, codigo_aero2, hora, minutos, &duracao);

			criarVoo( ficheiro, codigo_aero1, codigo_aero2, hora, minutos, duracao );
		}
		else if( strcmp(modo,"FD") == 0 )
		{
			scanf("%s %s %d:%d", codigo_aero1, codigo_aero2, hora, minutos);
			if( elimina_voo(ficheiro, codigo_aero1, codigo_aero2, hora, minutos ) )
				printf("+ voo %s %s %d:%d removido\n", codigo_aero1, codigo_aero2, hora_partida);
			else
				printf("+ voo %s %s %d:%d inexistente\n", codigo_aero1, codigo_aero2, hora, minutos);
		}
		

		if(strcmp(modo,"X") == 0)
		{
			close(ficheiro);
			return 0;
		}
		
	}
}

