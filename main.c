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
//função verifica se o voo já foi criado para aquele codigo
//funçao recebe o FD e o codigo para aceder ao disco
// e devolve TRUE se o voo existir ou FALSE caso contrario
bool verifica_voo(int fd,char *codigo)
{
	aeroportos temp;
	temp = read_aeroportos_at_hash(fd,codigo);

}
//função CriarAeroportos cria um novo aeroporto
//recebe o FD, o codigo e o fuso horario do aeroporto
//verifica se o aeroporto ja esta na hashtable, se nao
//preenche os campos da struct e escreve em disco 
void criarAeroportos(int fd,char *codigo,char *fuso_horario)
{	
		if(verifica_aero(fd,codigo))
		{
			printf("+ aeroporto %s existe\n",codigo);
		}
		else
		{
			aeroportos temp;
			strcpy(temp.codigo,codigo);
			strcpy(temp.fuso_horario,fuso_horario);
			write_aeroportos(fd,temp); //passa para o disco
			printf("+ novo aeroporto %s\n", codigo);
		}
}
void criarVoos(int fd,char *codigoVoo,char *aeroPartida,char *aeroChegada,char *horaPartida,short duracao)
{
	if(verifica())
}
// na funçao MAIN recebe os comandos a executar e chama as respectivas funções 	
int main()
{
	int ficheiro;
	ficheiro = hashtable_aeroportos_open("ficheiro");

	char modo[3];
	while(scanf(" %s",modo) != EOF)
	{
		char codigo_aero1[4];
		char codigo_aero2[4];
		char fuso_horario[5];
		char codigo_voo[7];
		short duracao;
		if(strcmp(modo,"AI")==0)
		{
			scanf(" %s %s",codigo_aero1,fuso_horario);
			criarAeroportos(ficheiro,codigo,fuso_horario);
		}
		if(strcmp(modo,"FI")==0)
		{
			scanf(" %s %s %s %s %hi",codigo_voo,codigo_aero1,codigo_aero2,fuso_horario,duracao);
			criarVoos(ficheiro,codigo_voo,codigo_aero1,codigo_aero2,fuso_horario,duracao);

		}
	}
	return 0;
}	