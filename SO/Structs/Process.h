<<<<<<< HEAD
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
struct Process
{
	/*PCB*/
	int id;
	int block_time;
	int pc;
	int size;
	int state;

	/*Testing*/
	int pc_aux;

	/*Memory*/
	int mem_str;
	int mem_end;
	int file_pos;
};

/*Constructors*/
struct Process *new_Process(int i, int inst_size, int file)
{

	struct Process *temp = malloc(sizeof(struct Process));

	/*PCB*/
	temp->id = i;
	temp->block_time = -1;
	temp->pc = -1;
	temp->size = inst_size;
	temp->mem_str = -1;
	temp->mem_end = -1;
	temp->file_pos = file;
	temp->state = NEW;

	/*Testing*/
	temp->pc_aux = 0;

	return temp;
}

/*Methods*/

void set_process_ready(struct Process *process, int mem_pos, int size)
{
	process->pc = mem_pos + INST_POINTER;
	process->mem_str = mem_pos;
	process->mem_end = mem_pos + INST_POINTER + size;
}

void set_pc(struct Process *process, int val)
{

	int inst_pointer_str = process->mem_str + INST_POINTER;
	int inst_pointer_end = process->mem_end;

	if (val < inst_pointer_str)
	{

		process->pc = inst_pointer_str;
		return;
	}

	if (val >= inst_pointer_end)
	{
		process->pc = inst_pointer_end;
		return;
	}

	process->pc = val;
}

void set_state(struct Process * process, int nstate)
{
	if( process != NULL)
		process->state = nstate;
}

#endif
=======
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
	int block_time;
	int pc;
	int size;
	int state;

	/*Testing*/
	int pc_aux;

	/*Memory*/
	int mem_str;
	int mem_end;
	int file_pos;
} Process;

/*Constructors*/
Process *new_Process(int i, int inst_size, int file);

/*Methods*/
void set_process_ready(Process *process, int mem_pos, int size);

void set_pc(Process *process, int val);

void set_state(Process * process, int nstate);

#endif
>>>>>>> 2e6249faf9be84aa91dba7e62866ad8ffd030373
