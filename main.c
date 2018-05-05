/*Libs*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*Classes*/
#include "Structs/Queue.c"
#include "Structs/Process.c"

/*Consts*/

/*Vars*/
#define SIZE_FILE_lINE 200
#define STANDARD_ARRAY_SIZE	200

/*Scheduling*/
#define QUANTUM 4

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
    
    /*Lists*/
    int *to_do_list = extract("input_b.xpto");
    int ready[STANDARD_ARRAY_SIZE];

    int time = 0;

    while(true){



    }

    return 0;

}