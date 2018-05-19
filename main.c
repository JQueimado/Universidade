/*Libs*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*Classes*/
#include "Structs/Queue.h"
#include "Structs/Process.h"
#include "Structs/Pre_Process.h"

/*Consts*/

/*Vars*/
#define SIZE_FILE_LINE 300
#define DISCK_SAVE_TIME 3
#define MEM_SIZE 300
#define MAX_PROCESS 20

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
    /*
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

        set_pc( process , process->mem_end );
        
    }

    set_pc( process , process->pc+1 );
    */

    return process;

}

/***main***/
int main() {

 /*Extract From Input File*/
 /*
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

 fclose(file_pointer);
    */

    puts("start");
    int mem_str = 0;
    int mem_end = 0;
    int mem_cur_size = 0;
    int MEM[MEM_SIZE];

    /*Lists*/
    int arrival_process_end = 0;
    struct Pre_Process *arrival_process[MAX_PROCESS];

    struct Queue *new = new_Queue();

    struct Queue *ready = new_Queue();
    
    struct Queue *blocked = new_Queue();
    
    struct Process *run = NULL;

    int timer = 0;
    int ids = 0;

    /*Testing*/

    arrival_process[0] = new_Pre_Process( 0 , 0 , 3);
    arrival_process[1] = new_Pre_Process( 2 , 1 , 1);
    arrival_process[2] = new_Pre_Process( 3 , 2 , 4);

    arrival_process_end = 3;

    /***Processor loop***/
    while( !(arrival_process_end == 0 && is_empty( new ) && is_empty(ready) && run == NULL) ){
        
        
        
        /**Check Process Entry**/
        for (int i = 0; i < arrival_process_end; ++i){

            struct Pre_Process *pre_temp = arrival_process[i];

            if ( pre_temp->arrival <= timer && pre_temp->done == 0){

                ids += 1;

                struct Process *temp = new_Process( ids , pre_temp->size , pre_temp->file_pos );

                enqueue( new , temp );

                pre_temp->done = 1;

            }

        }
        
        /**Scheduling Call**/
        if( (timer % QUANTUM == 0) || (run == NULL)){

            if ( run != NULL ){

                if ( ready->size < MAX_READY_SIZE ){

                    enqueue( ready , run );

                }else{

                    enqueue( blocked, run );

                }

                run = NULL;

            }

            /*Process for Ready*/
            if ( ready->size < MAX_READY_SIZE && !is_empty(new) ){

                enqueue( ready , dequeue( new ) );

            }

            /*NEXT*/
            if( run == NULL){

                if ( !is_empty(ready) ){

                    run = dequeue(ready);

                }

            }

            if ( run == NULL )
            {
                puts("is_null");
            } 

            /**Check for Blocked Mesages**/
            for ( int count = 0; count < blocked->size; count++ ){

                struct Process *cur_pro = dequeue( blocked );

                /*Check for process to place in ready*/
                if ( ready->size < MAX_READY_SIZE && cur_pro->block_time == -1){
                    
                    enqueue( ready , cur_pro );

                }else{

                    enqueue( blocked , cur_pro );

                }

            }

            

            /*MEM Management*/
            /*
            if (run->mem_str == -1){
            
                if( MEM_SIZE - mem_cur_size > run->size){

                    struct Process *last_on_ram;

                    for (int i = 0; i < ready->size; ++i){
                    
                        struct Process *cur_pro = dequeue(ready);

                        if ( cur_pro->mem_str != -1 ){
                            
                            last_on_ram = cur_pro;

                        }

                        enqueue(ready, cur_pro);

                    }

                }

            }
            */
            

        }

        

        /*Disck acsses*/
        for (int count = 0; count < blocked->size; count++ ){

            struct Process *cur_pro = dequeue(blocked);

            if ( cur_pro->block_time != -1 ){
                
                if ( cur_pro->block_time >= DISCK_SAVE_TIME ){

                    cur_pro->block_time = -1;

                }else{

                    cur_pro->block_time += 1;

                }

            }

            enqueue(blocked , cur_pro);

        }

        /**CPU**/
        if (run != NULL){

            run = CPU(run);

            /*Check if process is waiting for a message*/
            if (run->block_time != -1){

                enqueue(blocked, run);
                run = NULL;

            }


            /*Check if process ended*/
            if ( run->pc >= run->mem_end ){

                run = NULL;

            }
        }

        if ( run != NULL ){
            
            printf("%d : %d\n" , timer , run->id );
        
        }else{
        
            printf("%d : 0\n", timer );
        
        }

        timer += 1;

        if (timer == 10){

            break;
        
        }

    }

    return 0;

}