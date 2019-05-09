<<<<<<< HEAD
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

=======
/**Class Pre_Process**/
#ifndef _Pre_Process_
#define _Pre_Process_
#include <stdlib.h>

/* Struct */
typedef struct Pre_Process{
	int arrival;
	int file_pos;
	int size;
	int done;
} Pre_Process;

/* Pre_Process Constructer */
/*
	Desc: Creates New Pre_Process Object

	Input: 	a	-> process arrival time
		   	fp 	-> instruction posicion in file
			s	-> number of instructions

	Output:	object of type Pre_Process 
*/
Pre_Process *new_Pre_Process(int a , int fp , int s );

>>>>>>> 2e6249faf9be84aa91dba7e62866ad8ffd030373
#endif