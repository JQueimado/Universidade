#include "Pre_Process.h"

/* Pre_Process Constructer Body */
Pre_Process *new_Pre_Process(int a , int fp )
{
	Pre_Process *temp = malloc(sizeof(Pre_Process));
	temp->arrival = a;
	temp->file_pos = fp;
	return temp;
}

/* Process maker */
Process* make_Process(Pre_Process* self, char* fname, int id)
{
	return new_Process(id, self->file_pos);	
}
