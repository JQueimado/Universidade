/**Class Process**/

/*Comflit avoider*/
#ifndef _Process_
#define _Process_

/*Includes*/
#include <stdlib.h>

#define INST_POINTER 10
#define MEM_SIZE 300

/*Define*/
struct Process{
	
	/*PCB*/
	int id;
	int arrival_time;
	int inst_time;
	int PC;
	int inst_end;
	
	/*Memory*/
	int MEM[MEM_SIZE];

};

/*Constructors*/
struct Process *new_Process(int i, int arr_time, int inst[], int inst_size){
	
	struct Process *temp = malloc(sizeof(struct Process));

	/*PCB*/
	temp->id = i;
	temp->arrival_time = arr_time;
	temp->inst_time = 0;
	temp->PC = INST_POINTER;
	temp->inst_end = inst_size + INST_POINTER;

	/*MEM*/
	for (int i = 0; i < inst_size; ++i){
		
		temp->MEM[ i + INST_POINTER ] = inst[ i ];
	
	}

	return temp;

}

/*Methods*/
int get_var(struct Process *process , int var_name){

	if ( (var_name < 0) || (var_name >= INST_POINTER) )
		return -1;

	return process->MEM[var_name];

}

int set_var(struct Process *process , int var_name , int val){

	if ( (var_name < 0) || (var_name >= INST_POINTER) )
		return -1;

	process->MEM[var_name] = val;

	return 0;

}

int get_inst(struct Process *process){
	return process->MEM[process->PC];
}

#endif
