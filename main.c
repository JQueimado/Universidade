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
#define DISCK_SAVE_TIME 3;

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

    int inst = get_inst( process );

    int i = inst / 10;
    int v = inst - i*10;

    if (i == ZERO){

        set_var( process , v , 0 );

    }

    if (i == ADD){
        
        int var = get_var( process , v);

        var += 1;

        set_var( process , v , var ); 
        
    }

    if (i == SUB){

        int var = get_var( process , v);

        var -= 1;

        set_var( process , v , var );
        
    }

    if (i == IF){

        if( get_var( process , v ) != 0 ){
            
            set_pc( process , process->pc+1 );
        
        }
        
    }

    if (i == BACK){

        set_pc( process , process->pc - v );
        
    }

    if (i == FORW){

        set_pc( process , process->pc + v );
        
    }

    if (i == FORK){

        
        
    }

    if (i == DISCK_SAVE){

        if ( process->block_time == -1 ){

            process->block_time = 0;

        }
        
    }

    if (i == COPY){

        
        
    }

    if (i == EXIT){

        set_pc( process , process->inst_end );
        
    }

    set_pc( process , process->pc+1 );

    return process;

}

/***main***/
int main() {

 /*Extract From Input File*/
 
 FILE * file_pointer;
 file_pointer = fopen ("input_b.xpto","r");
 
 if (!file_pointer) {
	perror("Error");
	exit(0);
 }

 int i;	 
 int line = 0;

 int Arrival_Time[3];
 int Instants[SIZE_FILE_LINE];

 char Arrival[3];
 char Instants_Array[SIZE_FILE_LINE];
 
 if (file_pointer != NULL) {
	puts("\nProcesso:   ** Tempo de Chegada:  ** Instantes:     \n");
 	puts("**********************************************************");
 }

 
 while(fgets(Instants_Array, SIZE_FILE_LINE , file_pointer)) {

	line = line + 1;

	for(i=0;Instants_Array[i] != ' ';i++) {	
		Arrival[i] = Instants_Array[i];
		Arrival_Time[i] = atoi(Arrival);	  
	}

	printf("\nP%d          **   %d              **  Instants: ", line, Arrival_Time[i]);
	
	while(Instants_Array[i] != '\n') {

		if(Instants_Array[i] != ' ') {
			// Converter os instnates para int. Não dá de nenhuma forma pela função atoi
			printf("%c", Instants_Array[i]);
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

                if ( !is_empty(blocked) ){

                    int i = 0;
                    bool flag = FALSE;
                    
                    while(next(blocked)->block_time != -1){

                        enqueue(blocked , dequeue(blocked));

                        if ( i > blocked->size ){

                            flag = TRUE;

                            break;

                        }

                        i += 1;

                    }

                    if (!flag){
                    
                        enqueue(ready , dequeue(blocked));

                    }
                
                }

            }

        }

        /**Check for Blocked Mesage**/
        for ( int count = 0; count < blocked->size; count++ ){

            cur_pro = dequeue( blocked );

            if( cur_pro >= DISCK_SAVE_TIME ){

                cur_pro->block_time = -1;

                if( ready->size >= MAX_READY_SIZE ){

                    enqueue( blocked , cur_pro );

                }else{

                    enqueue( blocked , cur_pro );

                }

            }else{

                if (cur_pro->block_time != -1){

                    cur_pro->block_time += 1;
                
                }


            }

        }

        /**CPU**/
        if (run != NULL){

            run = CPU(run);

            if (run->block_time != -1){

                enqueue(blocked, run);
                run = NULL;

            }


            /*Check if process ended*/
            if ( run->pc > run->inst_end ){

                run = NULL;

            }
        }

        timer += 1;

    }

    return 0;

}
