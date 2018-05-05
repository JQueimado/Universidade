/*Libs*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*Classes*/
#include "Structs/Queue.h"
#include "Structs/Process.h"

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

	static int process[SIZE_FILE_lINE];
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
    int *to_do_list;

    struct Queue *ready = new_Queue();
    struct Queue *blocked = new_Queue();
    struct Process *run = NULL;

    int timer = 0;

    /*Extract file*/
    to_do_list = extract("input_b.xpto");

    /*Processor loop*/
    while(true){



    }

    return 0;

}