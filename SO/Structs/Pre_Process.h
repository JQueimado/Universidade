/**Class Pre_Process**/
#ifndef _Pre_Process_
#define _Pre_Process_
#include <stdlib.h>
#include <stdio.h>
#include "Process.h"

/* Struct */
typedef struct Pre_Process{
	int arrival;
	int file_pos;
} Pre_Process;

/* Pre_Process Constructer */
/*
	Desc: 	Creates New Pre_Process Object
	Input: 	a	-> process arrival time
		   	fp 	-> instruction posicion in file
	Output:	object of type Pre_Process 
*/
Pre_Process* new_Pre_Process(int a , int fp );

/* Process maker */
/*
	Desc: 	Creates Process object
	Input: 	self: self object
			fname: file where the instructions are
	Output: Process object
*/
Process* make_Process(Pre_Process* self, char* fname, int id);

#endif