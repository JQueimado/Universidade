/**Class Process**/
#ifndef _Process_
#define _Process_

/*Includes*/
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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
	int inst_pos;
	int var_pos;

	/*memory*/
	bool in_memory;
	int process_pointer;
	int end_pointer;

	/* helper */
	short timer;

} Process;

/*Constructors*/
Process *new_Process(int i, int fpos);

/*Methods*/
/* loader and unloaders*/
bool load_inst(Process* self, char* fname, int* Memory, int mpos);

bool load_var(Process* self, int* Memory);

bool load_process(Process *self, int *Memory, int mem_pos, char *fname);

bool unload(Process* self, int* Memory);

/* Set State */
void set_state(Process * process, int nstate);

/* Get Size */
int get_size(Process* self, char* fname);

/* Vars */
/* Get Var */
int get_var(Process* self, int* Memory, int var);

/* Set Var */
bool set_var(Process* self, int* Memory, int var, int val);

/* pc */
void set_pc(Process* self, int N);

#endif
