/**Class Queue**/

/*Comflit avoider*/
#ifndef _Queue_
#define _Queue_

/*Includes*/
#include <stdlib.h>
#include <stdbool.h>

#include "Process.h"

/*Consts*/
#define STD_QUEUE_SIZE 50

/*Define*/
typedef struct Queue{
	int header;
	int footer;
	int size;
	struct Process *arr[STD_QUEUE_SIZE];
} Queue;

/*Constructor*/
struct Queue *new_Queue();

/*Methods*/
bool is_empty(struct Queue *queue);

void enqueue(struct Queue *queue, struct Process *item);

struct Process *dequeue(struct Queue *queue);

struct Process *next(struct Queue *queue);

#endif