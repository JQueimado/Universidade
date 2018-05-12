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
#define MAX_READY_SIZE 4

/*Funcs*/

/*Extract Input File*/
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
    struct Queue *to_do_list = new_Queue();

    int ready_size = 0;
    struct Queue *ready = new_Queue();
    
    struct Queue *blocked = new_Queue();
    
    struct Process *run = NULL;

    int timer = 0;

    /*Extract file*/
    extract("input_b.xpto");

    /*Processor loop*/
    while( !( is_empty( to_do_list ) && is_empty(ready) && run == NULL) ){
        
        /*Check Process Entry*/
        struct Queue *temp = new_Queue();
        struct Process *cur_pro = NULL;

        while (!is_empty(to_do_list)){

            cur_pro = dequeue(to_do_list);
            
            if (cur_pro->arrival_time <= timer){

                if(ready_size >= MAX_READY_SIZE){
                    
                    enqueue(blocked , cur_pro);
                
                }else{
                
                    enqueue(ready , cur_pro);
                
                }

            }else{

                enqueue(temp, cur_pro);

            }

        }

        while (!is_empty(temp)){

            cur_pro = dequeue(temp);
            enqueue(to_do_list , cur_pro);

        }


    }

    return 0;

}