#include <stdio.h>
#include "Structs/Queue.c"
int *extract(char *name){

	FILE *inputFile;
 	inputFile = fopen(name, "r")  

 	//Read File into array

	int process[size_File_line];
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


int main() {
    
    int *file = extract("input_b.xpto");

    return 0;

}