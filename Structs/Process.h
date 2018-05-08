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
	int run_time;
	struct Instruction_Queue *script;

};

/*Constructors*/
struct Process *new_Process_1(){

	struct Process *temp = malloc(sizeof(struct Process));

	return temp;

}

struct Process *new_Process_2(int i, int arr_time, int inst[]){
	
	struct Process *temp = new_Process_1();

	return temp;

}

/*Methods*/
int run(struct Process *process){

	return 0;

}

#endif
