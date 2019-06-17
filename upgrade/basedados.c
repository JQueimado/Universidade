#include <stdio.h>
#include "aeroporto.h"
#include "hashtable.h"
/*Abre o ficheiro com o nome do filename
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

/*Escreve um utilizador user na posição hash do ficheiro
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

