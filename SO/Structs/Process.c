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
bool load(Process* self, int* Memory, int mpos)
{
	if(self->in_mememory)
		return false;

	FILE* file = fopen(_FNAME_, "r");
	fseek(file, self->fpos, SEEK_SET);
	char read_buffer[300];
	
	if( fgets(read_buffer, 300, file) == NULL)
		return false;
	
	int current = 0;
	int p = mpos;
	while ( read_buffer[current] != '\n' )
	{
		Memory[p] = atoi( read_buffer[current] );
		current++;
		p++;
	}
	
	fclose(file);	
	self->in_mememory = true;
	return true;
}

bool unload(Process* self, int* Memory)
{
	if( !self->in_mememory )
		return false;

	FILE* file = fopen(_FNAME_,'a');

	fclose(file);
	self->in_mememory = false;
	return true;	
}

void set_state(Process * process, int nstate)
{
	if( process != NULL)
		process->state = nstate;
}