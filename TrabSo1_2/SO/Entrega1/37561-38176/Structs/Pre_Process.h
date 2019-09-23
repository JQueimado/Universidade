/**Class Pre_Process**/

/*Comflit avoider*/
#ifndef _Pre_Process_
#define _Pre_Process_

/*Includes*/
#include <stdlib.h>

struct Pre_Process{
	int arrival;
	int file_pos;
	int size;
	int done;
};

struct Pre_Process *new_Pre_Process(int a , int fp , int s ){

	struct Pre_Process *temp = malloc(sizeof(struct Pre_Process));

	temp->arrival = a;
	temp->file_pos = fp;
	temp->size = s;
	temp->done = 0;

	return temp;

}

#endif