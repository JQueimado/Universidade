#include "Process.h"

/*Constructors*/
Process *new_Process(int i, int fpos)
{
	Process *temp = malloc(sizeof(Process));
	/*PCB*/
	temp->id = i;
	temp->pc = -1;
	temp->state = NEW;
	temp->fpos = fpos;
	return temp;
}

/*Methods*/
/*
void set_process_ready(Process *process, int mem_pos, int size)
{
	process->pc = mem_pos + INST_POINTER;
	process->mem_str = mem_pos;
	process->mem_end = mem_pos + INST_POINTER + size;
}

void set_pc(Process *process, int val)
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
*/
void set_state(Process * process, int nstate)
{
	if( process != NULL)
		process->state = nstate;
}