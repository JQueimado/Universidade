/*Libs*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*Classes*/
#include "Structs/Queue.h"
#include "Structs/Process.h"

/*Consts*/

/*Vars*/
#define SIZE_FILE_LINE 300
#define STANDARD_ARRAY_SIZE 300

/*Scheduling*/
#define QUANTUM 4
#define MAX_READY_SIZE 4

/*Functions*/
#define ZERO 0
#define ADD 1
#define SUB 2
#define IF 3
#define BACK 4
#define FORW 5
#define FORK 6
#define DISCK_SAVE 7
#define COPY 8
#define EXIT 9

/**CPU**/
struct Process *CPU(struct Process *process){

    int inst = process->MEM[process->PC];

    int i = inst / 10;
    int v = inst - i*10;

    if (i == ZERO){



    }

    if (i == ADD){

        
        
    }

    if (i == SUB){

        
        
    }

    if (i == IF){

        
        
    }

    if (i == BACK){

        
        
    }

    if (i == FORW){

        
        
    }

    if (i == FORK){

        
        
    }

    if (i == DISCK_SAVE){

        
        
    }

    if (i == COPY){

        
        
    }

    if (i == EXIT){

        
        
    }

    process->PC += 1;

    return process;

}

/***main***/
int main() {

 /*Extract From Input File*/
 
 FILE * file_pointer;
 file_pointer = fopen ("input_b.xpto","r");
 
 if (file_pointer == NULL) {
	printf("Erro: Does not exist\n");
 }

 int i;	 
 int line = 0;

 char Arrival_Time[3];
 char Instants_Array[300];
 
 if (file_pointer != NULL) {
	puts("\nProcesso:   ** Tempo de Chegada:  ** Instantes:     \n");
 	puts("**********************************************************");
 }

 //Inputs from file

 while(fgets(Instants_Array, 300 , file_pointer)) {

	line = line + 1;

	for(i=0;Instants_Array[i] != ' ';i++) {	
		Arrival_Time[i] = Instants_Array[i];
        
	}

	printf("\nP%d          **   %d              **  Instants: ", line, atoi(Arrival_Time));
	
	while(Instants_Array[i] != '\n') {

		if(Instants_Array[i] != ' ') {
			printf("%c",Instants_Array[i]);
		}
		
		i+=1;
       	
	} 
	printf("\n");
 }
 
 /*Close Input File*/
 fclose(file_pointer);

    /*Lists*/
    struct Queue *to_do_list = new_Queue();

    struct Queue *ready = new_Queue();
    
    struct Queue *blocked = new_Queue();
    
    struct Process *run = NULL;

    int timer = 0;

    /***Processor loop***/
    while( !( is_empty( to_do_list ) && is_empty(ready) && run == NULL) ){
        
        /**Check Process Entry**/
        struct Process *cur_pro = NULL;

        for (int i = 0; i < to_do_list->size; i++){

            cur_pro = dequeue(to_do_list);

            if (cur_pro->arrival_time <= timer){

                if(ready->size >= MAX_READY_SIZE){

                    enqueue(blocked, cur_pro);

                }else{

                    enqueue(ready, cur_pro);

                }

            }else{

                enqueue(to_do_list, cur_pro);

            }

        }

        /**Scheduling Call**/
        if( (timer % QUANTUM == 0) || (run == NULL)){

            /*Takes the process from RUN*/
            if(run != NULL){

                if(ready->size >= MAX_READY_SIZE){

                    enqueue(blocked, run);

                }else{

                    enqueue(ready ,run);

                }

                run = NULL;

            }

            /*Puts next in line*/
            if(!is_empty(ready)){

                run = dequeue(ready);

            }

        }

        /**CPU**/
        if (run != NULL){
            
            /*Run*/
            if (run->inst_time != -1){

                /*Inst handler*/


            }

            /*Check if process ended*/
            if ( run->PC > run->inst_end ){

            run = CPU(run);

            if (run->is_blocked){

                enqueue(blocked, run);
                run = NULL;

            }


                run = NULL;

            }
        }

        timer += 1;

    }

    return 0;

}
