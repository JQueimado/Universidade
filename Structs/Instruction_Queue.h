/**Class Instruction_Queue**/

/*Comflit avoider*/
#ifndef _Instruction_Queue_
#define _Instruction_Queue_

/*Includes*/
#include <stdlib.h>

/*Consts*/
#define Instruction_Queue_STD_SIZE 200

/*Define*/
struct Instruction_Queue{
	int footer;
	int size;
	int script[Instruction_Queue_STD_SIZE];
};

/*Constructors*/
struct Instruction_Queue *new_Instruction_Queue_1(){

	struct Instruction_Queue *temp = malloc(sizeof(struct Instruction_Queue));
	
	temp->footer = 0;
	temp->size = 0;
	/*temp->script = EMPY*/

	return temp;

}

struct Instruction_Queue *new_Instruction_Queue_2(int Instruction[],int n_inst){

	struct Instruction_Queue *temp = new_Instruction_Queue_1();
	
	for (int i = 0; i < n_inst; ++i){
		
		temp->script[i] = Instruction[i];
	
	}

	temp->size = n_inst;

	return temp;

}

/*Methods*/
void is_empty(struct Instruction_Queue *queue){
	
	return queue->footer == queue->size;

}

int dequeue(struct Instruction_Queue *queue){

	int ret = queue->script[queue->footer];
	queue->footer += 1;
	return ret;

}

int next(struct Instruction_Queue *queue){

	return queue->script[queue->footer];

}

#endif