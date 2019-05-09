/**Class Process**/

/*Comflit avoider*/
#ifndef _Process_
#define _Process_

/*Includes*/
#include <stdlib.h>

#define INST_POINTER 10
#define MEM_SIZE 300

/*States*/
#define NEW 0
#define READY_WAIT 1
#define RUN 2
#define BLOCKED 3
#define _EXIT_ 4

/*Define*/
typedef struct Process
{
	/*PCB*/
	int id;
	int pc;
	int state;

	/*file*/
	int fpos;

} Process;

/*Constructors*/
Process *new_Process(int i, int fpos);

/*Methods*/
/*
void set_process_ready(Process *process, int mem_pos, int size);

void set_pc(Process *process, int val);
*/
void set_state(Process * process, int nstate);

#endif
