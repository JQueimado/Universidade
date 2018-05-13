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

/***main***/
int main() {
    
    FILE * file_pointer;
    file_pointer = fopen ("input_b.xpto","r");

    if (file_pointer == NULL) {
        printf("Erro: Does not exist\n");
    }
     
    int i;  
    int line = 1;
    int count = 0;
    char Array[300];

    while(fgets(Array, 300 , file_pointer)) {
     do{
        for(i=0;Array[i];i++) {
            if(Array[i] != ' ') {
                Array[count] = Array[i];
                count++;
                }
        } 
        Array[count] = '\0';
        printf("Processo: %d  ||  Instante: %s \n", line, Array); 
        line = line + 1;
        } 
     while(line <= 8);     
    }

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

                run = NULL;

            }
        }

        timer += 1;

    }

    return 0;

}
