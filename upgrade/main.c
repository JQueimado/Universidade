#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "aeroporto.h"
#include "hashtable.h"
#include "basedados.h"
#define MAX_SIZE 400009
#define MAX_VOO 150
#define FILE_DB "db.cache"

 FILE *disk;
struct hashtable *hash;
bool criar_aeroporto(char *codigo)
{
	int pos = hash_function_aeroportos(codigo);
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
	if(inserir_aeroporto(hash,codigo))
	{
		write(disk,novoaeroporto,pos);
		printf("+ novo aeroporto %s\n",codigo);
		free(novoaeroporto);
		return true;
	}

	free(novoaeroporto);
	return false;


}

int main(void)
{
	hash = newhash();
	disk = openFile(FILE_DB);

	if(hash == NULL)
		return 1;

	//carrega os aeroportos para a hashtable
	loadDb(disk,hash);	

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
			hash_free(hash);
			fclose(disk);
			return 0;
			
		}
	}

	return 0;
}