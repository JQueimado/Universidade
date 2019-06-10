#include "Process.h"
#include "MemoryManager.h"

/*Constructors*/
Process *new_Process(int i, int fpos)
{
	Process *temp = malloc(sizeof(Process));
	/*PCB*/
	temp->id = i;
	temp->pc = -1;
	temp->state = NEW;
	temp->inst_pos = fpos;
	temp->var_pos = -1;
	temp->timer = -1;
	return temp;
}

Process *fork_process(Process *process, int id)
{
	return new_Process(id, process->inst_pos);
}

/*Methods*/
/* loaders and unloaders*/
bool load_inst(Process *self, char *fname, int *Memory, int mpos)
{
	FILE *file = fopen(fname, "r");
	if (file == NULL)
		return false;

	fseek(file, self->inst_pos, SEEK_SET);
	char line[300];
	if (fgets(line, 300, file) == NULL)
		return false;

	self->process_pointer = mpos;

	char *point = strtok(line, " ");
	int p = self->process_pointer + 10;
	while (point != NULL)
	{
		Memory[p] = atoi(point);
		point = strtok(NULL, " ");
		p++;
	}
	self->in_memory = true;
	self->end_pointer = p - 1;
	fclose(file);
	return true;
}
/* loads varibles */
bool load_var(Process *self, int *Memory)
{
	if (self->var_pos == -1)
		return false;

	FILE *file = fopen(_FNAME_, "r");
	if (file == NULL)
		return false;

	fseek(file, self->var_pos, SEEK_SET);
	char line[300];
	if (fgets(line, 300, file) == NULL)
		return false;

	int p = self->process_pointer;
	char *point = strtok(line, " ");
	while (point != NULL)
	{
		Memory[p] = atoi(point);
		point = strtok(NULL, " ");
		p++;
	}

	fclose(file);
	return true;
}

bool load_process(Process *self, int *Memory, int mem_pos, char *fname)
{
	return load_inst(self, fname, Memory, mem_pos) && load_var(self, Memory);
}

bool unload(Process *self, int *Memory)
{
	if (!self->in_memory)
		return false;

	FILE *file = fopen(_FNAME_, "w+");
	if (file == NULL)
		return false;

	if (self->var_pos == -1)
	{
		fseek(file, 0, SEEK_END);
		self->var_pos = ftell(file);
	}
	else
	{
		fseek(file, self->var_pos, 0);
	}

	for (int p = self->process_pointer; p < self->process_pointer + 10; p++)
		fprintf(file, "%d ", Memory[p]);

	fprintf(file, "\n");
	self->in_memory = false;
	fclose(file);
	return true;
}

/* Set State */
void set_state(Process *process, int nstate)
{
	if (process != NULL)
		process->state = nstate;
}

/* Get Size */
int get_size(Process *self, char* fname)
{
	if (self->in_memory)
	{
		/* processo em memoria */
		return self->end_pointer - self->process_pointer + 1;
	}
	else
	{
		/* processo no disco */
		FILE *file = fopen(fname, "r");
		if (file == NULL)
			return -1;

		fseek(file, self->inst_pos, SEEK_SET);
		
		char line[300];
		if (fgets(line, 300, file) == NULL)
			return -1;
		fclose(file);

		char *point = strtok(line, " ");
		int p = 10;
		while (point != NULL)
		{
			point = strtok(NULL, " ");
			p++;
		}
		return p - 1;
	}
}

/* Vars */
/* Get Var */
int get_var(Process *self, int *Memory, int var)
{
	if (!self->in_memory)
		return -1;

	return Memory[self->process_pointer + var];
}

/* Set Var */
bool set_var(Process *self, int *Memory, int var, int val)
{
	if (var > 10 || var <= 0 || !self->in_memory)
		return false;

	Memory[self->process_pointer + var - 1] = val;
	return true;
}

/* PC */
void set_pc(Process *self, int N)
{
	self->pc += N;
}

/**************test_main**************/
/*
int main()
{
	Process *process = new_Process(1, 0);
	int *Memory = calloc(sizeof(int), 300);

	load_process(process,Memory,0, "input1.txt");

	set_var(process, Memory, 10, 10);
	set_var(process, Memory, 1, 10);

	printf("mem:%d\n", get_size(process, "input1.txt"));

	unload(process, Memory);

	printf("disk:%d\n", get_size(process, "input1.txt"));

	load_process(process,Memory,0, "input1.txt");

	set_var(process, Memory, 2, 20);

	unload(process, Memory);

	load_process(process,Memory,0, "input1.txt");

	set_var(process, Memory, 2, 30);
	
	for (int i = 0; i < 25; i++)
		printf("%d\n", Memory[i]);

	printf("%d %d\n", process->process_pointer, process->end_pointer);
	
}
*/