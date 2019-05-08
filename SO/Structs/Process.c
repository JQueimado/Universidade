#include "Process.h"

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