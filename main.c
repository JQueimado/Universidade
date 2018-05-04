/*Libs*/
#include <stdio.h>
#include <stdlib.h>

/*Classes*/
#include "Structs/Queue.c"

/*Consts*/
#define SIZE_FILE_lINE 200

/*Funcs*/
int *extract(char *name){

	FILE *inputFile;
 	inputFile = fopen(name, "r");

 	//Read File into array

	int process[SIZE_FILE_lINE];
	int i;

	if (inputFile == NULL) {
		printf("Erro: Does not exist\n");
	}
	 
 	for (i = 0; i < 16; i++){
        fscanf(inputFile, "%d,", &process[i] );
    }

	fclose(inputFile);
    
	return process;

}

/*main*/
int main() {
    
    int *file_array = extract("input_b.xpto");

    return 0;

}