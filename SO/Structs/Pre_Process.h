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

#endif