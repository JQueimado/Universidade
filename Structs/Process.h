/**Class Process**/

/*Comflit avoider*/
#ifndef _Process_
#define _Process_

/*Includes*/
#include <stdlib.h>
#include "Instruction_Queue.h"

/*Define*/
struct Process{
	
	int id;
	int arrival_time;
	struct Instruction_Queue *script;

};

/*Constructors*/
struct Process *new_Process(int i, int arr_time, int inst[], int arr_size){
	
	struct Process *temp = malloc(sizeof(struct Process));

	temp->id = i;
	temp->arrival_time = arr_time;
	temp->script = new_Instruction_Queue_2( inst , arr_size);	

	return temp;

}

/*Methods*/
int run(struct Process *process){

	struct Instruction_Queue *script = process->script;

	return IQ_dequeue(script);

}

#endif
