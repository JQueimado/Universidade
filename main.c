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

/*main*/
int main() {
 
 FILE * file_pointer;
 file_pointer = fopen ("input_b.xpto","r");

 if (file_pointer == NULL) {
     printf("Erro: Does not exist\n");
 }
	 
 int line = 0;
 char Array[300];

 while(fgets(Array, 300 , file_pointer)) {
	line = line + 1;
        printf("Line:%d -> %s",line, Array);
 }

 fclose(file_pointer);

 return 0;

    
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
