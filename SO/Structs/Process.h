/**Class Process**/
#ifndef _Process_
#define _Process_

/*Includes*/
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

/*States*/
#define NEW 0
#define READY_WAIT 1
#define RUN 2
#define BLOCKED 3
#define _EXIT_ 4

#define _FNAME_ "process.cache"

/*Define*/
typedef struct Process
{
	/*PCB*/
	int id;
	int pc;
	int state;

	/*file*/
	int fpos;

	/*memory*/
	bool in_mememory;
	int process_pointer;
	int var_pointer;

} Process;

/*Constructors*/
Process *new_Process(int i, int fpos);

/*Methods*/
bool load(Process* self, int* Memory, int mpos);

bool unload(Process* self, int* Memory);

void set_state(Process * process, int nstate);

#endif
