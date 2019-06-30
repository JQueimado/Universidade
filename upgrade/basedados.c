#include "basedados.h"

/*
openFile:
Descrição:
	Abre o ficheiro com o nome do filename
	cria-o se nao existir e devolve o file pointer caso nao consiga abrir

Argumentos:
	filename	-> nome do ficheiro

Return:
	pointer para o ficheiro aberto
*/
FILE *openFile(char *filename)
{
	FILE *temp = fopen(filename, "rb+");
	
	if(temp == NULL)
	{
		temp = fopen(filename, "wb");
		fclose(temp);
		temp = fopen(filename, "rb+");
	}
	
	if(temp == NULL)
	{
		perror("open: ");
	}
	
	return temp;
}

/*
write:
Descrição:
	Escreve um utilizador user na posição hash do ficheiro

Argumentos:
	file		-> pointer para o ficheiro
	aeroportos	-> aeroporto a escrever
	pos			-> posicao no fichero

*/
void write(FILE *file,struct aeroportos *aeroportos,int pos)
{
	fseek(file,pos * sizeof(struct aeroportos), SEEK_SET);
	fwrite(aeroportos,sizeof(struct aeroportos),1,file);
}

/*
read:
Descrição:
	Le um aeroporto da posicao hash do ficheiro

Argumentos:
	file		-> pointer para o ficheiro
	pos			-> posicao no fichero

Return:
	aeroportos	-> aeroporto a ler

*/
void read(FILE *file,struct aeroportos *aeroportos,int pos)
{
	fseek(file,pos*sizeof(struct aeroportos),SEEK_SET);
	fread(aeroportos,sizeof(struct aeroportos),1,file);
}

/*
read:
Descrição:
	carrega todos os utilizadores para a hash

Argumentos:
	file		-> pointer para o ficheiro
	hash		-> hash a carregar

Return:
	devolve o id do ultimo aeroporto encontrado

*/
int loadDb(FILE *file, struct hashtable *hash)
{
	struct aeroportos aeroportos;	
	int pos=0;
	
	while (fread(&aeroportos, sizeof(struct aeroportos), 1, file) != 0)
	{
		inserir_aeroporto(hash, aeroportos.codigo,pos);
		pos++;
							
	}

	return pos;
}

/*
get_aeroporto:
Descrição:
	le um aeroporto do ficheiro malloc

Argumentos:
	hash    -> hash
    disk    -> pointer para o ficheiro
	code	-> codigo a ler

Return:
	um aeroporto novo com a informacao do ficheiro
*/
aeroportos* get_aeroporto(hashtable *hash, FILE *disk, char *code)
{
	aeroportos *temp = malloc(sizeof(aeroportos));
	int pos = find_aeroportopos(hash, code);
	if( pos == -1 )
	{
		return NULL;
	}
	read(disk, temp, pos);

	return temp;
}

/*
aeroporto_to:
Descrição:
	le um aeroporto do ficheiro (reassign)

Argumentos:
	hash    -> hash
    disk    -> pointer para o ficheiro
	code	-> codigo a ler

Return:
	ret 	-> novo aeroporto
*/
void aeroporto_to(hashtable *hash, FILE *disk, char *code, aeroportos** ret )
{
	int pos = find_aeroportopos(hash, code);
	if( pos == -1 )
	{
		*ret = NULL;
	}
	read(disk, *ret, pos);
}

/*
write_aero:
Descrição:
	escreve uma aeroporto no ficheiro

Argumentos:
	hash    -> hash
    disk    -> pointer para o ficheiro
	add		-> codigo a escrever
*/
void write_aero(hashtable* hash, FILE* disk, aeroportos* add)
{
	int pos = find_aeroportopos(hash, add->codigo);
	write(disk, add, pos);
}
