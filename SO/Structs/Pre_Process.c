#include "Pre_Process.h"

/* Pre_Process Constructer Body */
Pre_Process *new_Pre_Process(int a , int fp , int s ){

	Pre_Process *temp = malloc(sizeof(Pre_Process));

	temp->arrival = a;
	temp->file_pos = fp;
	temp->size = s;
	temp->done = 0;

	return temp;

}