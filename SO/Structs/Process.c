#include "Process.h"

/*Constructors*/
Process *new_Process(int i, int fpos)
{
	Process *temp = malloc(sizeof(Process));
	/*PCB*/
	temp->id = i;
	temp->pc = -1;
	temp->state = NEW;
	temp->inst_pos = fpos;
	return temp;
}

/*Methods*/
/* loader and unloaders*/
bool load_inst(Process* self, char* fname, int* Memory, int mpos)
{
	FILE* file = fopen(fname, "r");
	if( file == NULL )
		return false;

	fseek(file,SEEK_SET, self->inst_pos);
	char line[300];
	if( fgets(line, 300, file) == NULL )
		return false;

	self->process_pointer = mpos;

	char* point = strtok(line, " ");
	int p = self->process_pointer + 10;
	while( point != NULL )
	{
		Memory[p] = atoi( point );
		point = strtok(NULL, " ");
		p++;
	}
	self->in_memory = true;
	self->end_pointer = p - 1;
	fclose(file);
	return true;
}

bool load_var(Process* self, int* Memory)
{
	FILE* file = fopen( _FNAME_, "r");
	if( file == NULL )
		return false;

	fseek( file, SEEK_SET, self->var_pos);
	char line[300];
	if( fgets(line, 300, file) == NULL )
		return false;

	int p = self->process_pointer;
	char* point = strtok(line, " ");
	while( point != NULL )
	{
		Memory[p] = atoi( point );
		point = strtok(NULL, " ");
		p++;
	}

	self->end_pointer = self->process_pointer + 10;
	fclose(file);
	return true;
}

bool unload(Process* self, int* Memory)
{
	if( !self->in_memory )
		return false;

	FILE* file = fopen( _FNAME_, "a");
	if( file == NULL )
		return false;

	self->var_pos = ftell(file);
	
	for( int p = self->process_pointer; p < self->process_pointer + 10 ; p++ )
		fprintf( file,"%d ", Memory[p]);
	fprintf(file, "\n");

	self->in_memory = false;
	fclose(file);
	return true;
}

/* Set State */
void set_state(Process * process, int nstate)
{
	if( process != NULL)
		process->state = nstate;
}

/* Vars */
/* Get Var */
int get_var(Process* self, int* Memory, int var)
{
	if( !self->in_memory )
		return -1;

	return Memory[self->process_pointer + var];
}

/* Set Var */
bool set_var(Process* self, int* Memory, int var, int val)
{
	if( var > 10 || var < 0 || !self->in_memory)
		return false;

	Memory[self->process_pointer + var] = val;
	return true;
}

/**************test_main**************/
int main()
{
	Process* process = new_Process(1, 0);
	int* Memory = calloc(sizeof( int ), 300);

	load_inst(process, "test1.txt", Memory, 0);

	set_var(process, Memory, 0, 10);

	unload(process,Memory);

	load_var(process, Memory);

	for( int i = 0; i < 100; i++)
		printf("%d\n", Memory[i]);

	printf("%d %d\n", process->process_pointer, process->end_pointer);
}