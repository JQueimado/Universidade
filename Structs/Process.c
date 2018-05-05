#include "Process.h"

/*Includes*/
#include <stdlib.h>

/*Consts*/
#define Instructions_Queue_STD_SIZE 200

/**Class Instructions_Queue**/

/*Define*/
struct Instructions_Queue{
	int header;
	int footer;
	int *script;
};

/*Constructors*/
struct Instructions_Queue *new_Instructions_Queue(){

	struct Instructions_Queue *temp = malloc(sizeof(Instructions_Queue));
	temp->header = 0;
	temp->footer = 0;
	temp->script = int[Instructions_Queue_STD_SIZE];

}

struct Instructions_Queue *new_Instructions_Queue(int instructions[]){

	struct Instructions_Queue *temp = malloc(sizeof(Instructions_Queue));
	temp->header = 0;
	temp->footer = 0;
	temp->script = instructions;

}

/*Methods*/
void is_empty(struct Instructions_Queue *queue){

}

void add(struct Instructions_Queue *queue, int item){

}

int remove(struct Instructions_Queue *queue){

}

int next(struct Instructions_Queue *queue){

}

/**Class Process**/

/*Define*/
struct Process{
	int id;
	int arrival_time;
	int run_time;
	struct Instructions_Queue *script;

};
