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
	/* Preparations */
	if(self->in_mememory)
		return false;

	FILE* file = fopen(_FNAME_, "r");
	fseek(file, self->fpos, SEEK_SET);
	char read_buffer[300];
	
	if( fgets(read_buffer, 300, file) == NULL)
		return false;

	/* loads */
	int current = 0;
	int p = mpos;
	char temp[3];
	int minp = 0;
	char curr;
	while ( (curr = read_buffer[current]) != '\n' )
	{
		if( curr == ' ' )
		{
			temp[minp + 1] = '\0';
			minp = 0;
			int conv = atoi( temp );
			Memory[p] = conv;
			p++;
		}
		else
		{
			temp[minp] = curr;
			minp++;
		}
		
	}
	
	self->end_pointer = p-1;
	fclose(file);	
	self->in_mememory = true;
	return true;
}

bool unload(Process* self, int* Memory)
{
	if( !self->in_mememory )
		return false;

	FILE* file = fopen(_FNAME_,'a');
	self->fpos = ftell(file);

	fclose(file);
	self->in_mememory = false;
	return true;	
}

void set_state(Process * process, int nstate)
{
	if( process != NULL)
		process->state = nstate;
}

/**************test_main**************/
int main()
{
	Process* process = new_Process(1, 0);
	int Memorry[300];

	

	for( int i = 0; i < 300; i++)
		printf("%d\n", Memorry[i]);
}