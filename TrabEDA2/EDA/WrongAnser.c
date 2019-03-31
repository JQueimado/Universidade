
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FILE1 "Testes/C_out.txt"
#define FILE2 "Testes/C_cor.txt"

int main(int argc, char const *argv[])
{
	FILE *pointer1 = fopen(FILE1, "r");
	FILE *pointer2 = fopen(FILE2, "r");

	if (pointer1 == NULL)
	{
		puts("1 n existe");
	}

	if (pointer2 == NULL)
	{
		puts("2 n existe");
	}

	char out1[100];
	char out2[100];
	int count = 0;

	while(fgets(out1, 100, pointer1) && fgets(out2, 100, pointer2))
	{

		count++;
		if (strcmp(out1, out2) != 0)
		{
			printf("WrongAnser %d\n", count);
			return 0;
		}

	}

	return 0;
}