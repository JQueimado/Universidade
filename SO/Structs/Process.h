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
struct Process *new_Process(int i, int inst_size, int file);

/*Methods*/
void set_process_ready(struct Process *process, int mem_pos, int size);

void set_pc(struct Process *process, int val);

void set_state(struct Process * process, int nstate);

#endif
