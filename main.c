/*Libs*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*Classes*/
#include "Structs/Queue.h"
#include "Structs/Process.h"

/*Consts*/

/*Vars*/
#define SIZE_FILE_lINE 300
#define STANDARD_ARRAY_SIZE 300

/*Scheduling*/
#define QUANTUM 4

/*main*/
int main() {
 
 FILE * file_pointer;
 file_pointer = fopen ("input_b.txt","r");

 int line = 0;
 int Array[300];
 int i;

 while(fscanf(file_pointer, "%d" , Array) && line<=8) {
	line = line + 1;
        for (i=0;i<=300;i++) {
		printf("Line:%d -> %d",line, Array[i]);
	}
 }
    
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
