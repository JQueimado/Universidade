/**Class Process**/

/*Comflit avoider*/
#ifndef _Process_
#define _Process_

/*Includes*/
#include <stdlib.h>

#define VAR_SIZE 10
#define MEM_SIZE 300

/*Define*/
struct Process{
	
	/*PCB*/
	int id;
	int arrival_time;
	int inst_time;
	int PC;
	
	/*Memory*/
	int VAR[VAR_SIZE];
	int MEM[MEM_SIZE];

};

/*Constructors*/
struct Process *new_Process(int i, int arr_time, int inst[], int arr_size){
	
	struct Process *temp = malloc(sizeof(struct Process));

	temp->id = i;
	temp->arrival_time = arr_time;
	temp->inst_time = 0;
	temp->PC = 0;

	for (int i = 0; i < arr_size; ++i){
		
		temp->MEM[i] = inst[i];
	
	}

	return temp;

}


#endif
