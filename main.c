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
#define FILE_NAME "input_b.xpto"

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
struct Process *CPU(struct Process *process , int MEM[]){

    int inst = MEM[process->pc];

    int i = inst / 10;
    int v = inst - i*10;

    printf("%d %d\n", i , v );

    if (i == ZERO){

       MEM[ process->mem_str + v ] = 0;

    }

    if (i == ADD){
        
        MEM[ process->mem_str + v ] += 1;
        
    }

    if (i == SUB){

       MEM[ process->mem_str + v ] -= 1;
        
    }

    if (i == IF){

        if ( MEM[ process->mem_str + v ] != 0 ){

            set_pc(process , process->pc + 1);

        }
        
    }

    if (i == BACK){

       set_pc(process , process->pc - MEM[ process->mem_str + v ]);
        
    }

    if (i == FORW){

       set_pc(process , process->pc + MEM[ process->mem_str + v ]);
        
    }

    if (i == FORK){

       //2ª parte do trabalho
        
    }

    if (i == DISCK_SAVE){

      process->block_time = 0;

    }

    if (i == COPY){

        MEM[ process->mem_str ] = MEM[ process->mem_str + v ];

    }

    if (i == EXIT){

        /*Tetsting*/
        process->pc_aux = process->size;
        
    }

    set_pc( process , process->pc+1 );

    return process;

}

/***main***/
int main() {	

    /**File Acess**/
    FILE * file_pointer;
    file_pointer = fopen ( FILE_NAME ,"r");
 
    if (!file_pointer) {
        perror("Error");
        exit(0);
    }

    int output_arr_pointer = 0;
    static int output_arr[(MAX_PROCESS * 2)];

     int i;  
     int line = 0;

     int Arrival_Time;

     char Instants_Array[SIZE_FILE_LINE];

     while(fgets(Instants_Array, SIZE_FILE_LINE , file_pointer)) {

        line = line + 1;

        char arrival_str[5];

        for( i=0; Instants_Array[i] != ' '; i++ ) { 
            arrival_str[i] = Instants_Array[i];  
        }

        Arrival_Time = atoi(arrival_str);

        output_arr[output_arr_pointer] = Arrival_Time;
        output_arr_pointer += 1;
        
        i += 1;

        int Instantes_size = 0;

        while( Instants_Array[i] != '\n' ){
            
            if ( Instants_Array[i] == ' ' ){
            
                Instantes_size += 1;
            
            }

            i++;

        }

        output_arr[output_arr_pointer] = Instantes_size;
        output_arr_pointer += 1;

     }
     
     fclose(file_pointer);
     output_arr[output_arr_pointer] = -1;

     
     /*Prepare arrival_process*/

     int arrival_process_end = 0;
     int arrival_process_count = 0;
     struct Pre_Process *arrival_process[MAX_PROCESS];

     for (int i = 0; output_arr[i] != -1 ; i += 2){

        arrival_process[arrival_process_end] = new_Pre_Process( output_arr[i], arrival_process_end, output_arr[i + 1] );
        arrival_process_end += 1;
     
     }

     arrival_process_count = arrival_process_end;
    


    /*prepare scheduel*/
    puts("start");
    int mem_str = 0;
    int mem_end = 0;
    int mem_cur_size = 0;
    
    /*MEM*/
    static int MEM[MEM_SIZE];

    /*Lists*/

    struct Queue *new = new_Queue();

    struct Queue *ready = new_Queue();
    
    struct Queue *blocked = new_Queue();
    
    struct Process *run = NULL;

    int timer = 0;
    int count = 0;
    int ids = 0;

    /***Processor loop***/
    while( !(arrival_process_count == 0 && is_empty( new ) && is_empty( ready ) && run == NULL) ){

        /**Check Process Entry**/
        for (int i = 0; i < arrival_process_end; ++i){

            struct Pre_Process *pre_temp = arrival_process[i];

            if ( pre_temp->arrival <= count && pre_temp->done == 0){

                ids += 1;

                struct Process *temp = new_Process( ids , pre_temp->size , pre_temp->file_pos );

                enqueue( new , temp );

                arrival_process_count -= 1;

                pre_temp->done = 1;

            }

        }
        
        /**Scheduling Call**/
        if( (timer == QUANTUM) || (run == NULL)){

            puts("process changed");
            timer = 0;

            /*Process for Ready*/
            if ( ready->size < MAX_READY_SIZE && !is_empty(new) ){

                enqueue( ready , dequeue( new ) );

            }
            
            if ( run != NULL ){

                if ( ready->size < MAX_READY_SIZE ){
                    
                    enqueue( ready , run );

                }else{
                    
                    enqueue( blocked, run );

                }

                run = NULL;

            }
            
            /*NEXT*/
            if( run == NULL){

                if ( !is_empty(ready) ){

                    run = dequeue(ready);

                }

            }
            
            /**Check for Blocked Mesages**/
            if ( ( !is_empty( blocked ) ) && ready->size<MAX_READY_SIZE ){

                for ( int count = 0; count < blocked->size; count++ ){

                    struct Process *cur_pro = dequeue( blocked );

                    /*Check for process to place in ready*/
                    if ( ready->size < MAX_READY_SIZE && cur_pro->block_time == -1){
                        
                        enqueue( ready , cur_pro );

                    }else{

                        enqueue( blocked , cur_pro );

                    }

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

        /*Disk acesses*/
        if ( !is_empty(blocked) ){
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
        }

        /**CPU**/
        if (run != NULL){

            run = CPU(run , MEM);

            printf("%d : %d\n" , count , run->id );

            /*Check if process is waiting for a message*/
            if (run->block_time != -1){

                enqueue(blocked, run);
                run = NULL;

            }

            /*Check if process ended*/

            /*Testing*/
            run->pc_aux += 1;

            if( run->pc_aux >= run->size ){

                run = NULL;

            }

            /*
            if ( run->pc >= run->mem_end ){

                run = NULL;

            }
            */

        }else{

            printf("%d : empty\n", count );

        }

        timer += 1;
        count += 1;

    }

    return 0;

}
