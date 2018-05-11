/**Class Queue**/

/*Comflit avoider*/
#ifndef _Queue_
#define _Queue_

/*Includes*/
#include <stdlib.h>
#include <stdbool.h>

#include "Process.h"

/*Consts*/
#define STD_Queue_size 50;

/*Define*/
struct Queue{
	int header;
	int footer;
	struct Process *arr[STD_Queue_size];
};

/*Constructor*/
struct Queue *new_Queue(/*args*/){
	struct Queue *temp = malloc(sizeof(struct Queue));

	temp->header = 0;
	temp->footer = 0;

	return temp;
}

/*Methods*/
bool is_empty(struct Queue *queue){
	return queue->header == queue->footer;
}

void enqueue(struct Queue *queue, struct Process *item){
	queue->arr[q->footer] = item;
	queue->footer += 1;
}

struct Process *dequeue(struct Queue *queue){
	if (is_empty(queue))
		return NULL;

	queue->header += 1;
	return queue->arr[queue->header - 1];
}

struct Process *next(struct Queue *queue){
	return queue->arr[queue->header];
}

#endif