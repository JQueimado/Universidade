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
	void* arr[STD_QUEUE_SIZE];
} Queue;

/*Constructor*/
Queue *new_Queue();

/*Methods*/
bool is_empty(Queue *queue);

void enqueue(Queue *queue, void* item);

void* dequeue(Queue *queue);

void* next(Queue *queue);

#endif