#include <stdio.h>
#include "aeroporto.h"
#include "hashtable.h"
/*
*Abre o ficheiro com o nome do filename
*cria-o se nao existir e devolve o file pointer caso nao consiga abrir
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
*Escreve um utilizador user na posição hash do ficheiro
*recebe um fp do ficheiro
*/
void write(FILE *file,struct aeroportos *aeroportos,int pos)
{
	fseek(file,pos * sizeof(struct aeroportos), SEEK_SET);
	fwrite(aeroportos,sizeof(struct aeroportos),1,file);
}

/*Le um aeroporto da posicao hash do ficheiro
*recebe um fp do ficheiro 
*/
void read(FILE *file,struct aeroportos *aeroportos,int pos)
{
	fseek(file,pos*sizeof(struct aeroportos),SEEK_SET);
	fread(aeroportos,sizeof(struct aeroportos),1,file);
}

/*carrega todos os utilizadores para a hash
recebe um fp do ficheiro e a hash a preencher
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


