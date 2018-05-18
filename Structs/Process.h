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
	int block_time;
	int pc;
	
	/*Memory*/
	int mem_str;
	int mem_end;
	int file_pos;
};

/*Constructors*/
struct Process *new_Process(int i , int inst_size , int mem , int file ){
	
	struct Process *temp = malloc(sizeof(struct Process));

	/*PCB*/
	temp->id = i;
	temp->block_time = -1;
	temp->mem_str = mem;
	temp->mem_end = 

	return temp;

}

/*Methods*/
int get_var(struct Process *process , int var_name){

	return process->MEM[var_name];

}

void set_var(struct Process *process , int var_name , int val){

	process->MEM[var_name] = val;

}

int get_inst(struct Process *process){
	
	return process->MEM[process->pc];

}

void set_pc( struct Process *process , int val ){

	if ( val < INST_POINTER ){

		process->pc = INST_POINTER;
		return;


	}

	if ( val >= process->inst_end ){

		process->pc = process->inst_end;
		return;

	}

	process->pc = val;

}

#endif
