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
struct Queue{
	int header;
	int footer;
	int size;
	struct Process *arr[STD_QUEUE_SIZE];
};

/*Constructor*/
struct Queue *new_Queue(){
	struct Queue *temp = malloc(sizeof(struct Queue));

	temp->header = 0;
	temp->footer = 0;
	temp->size = 0;

	return temp;
}

/*Methods*/
bool is_empty(struct Queue *queue){
	return queue->size == 0;
}

void enqueue(struct Queue *queue, struct Process *item){
	queue->arr[queue->footer] = item;
	queue->footer += 1;
	queue->size += 1;
}

struct Process *dequeue(struct Queue *queue){
	if (is_empty(queue))
		return NULL;

	queue->header += 1;
	queue->size -= 1;
	return queue->arr[queue->header - 1];
}

struct Process *next(struct Queue *queue){
	return queue->arr[queue->header];
}

#endif