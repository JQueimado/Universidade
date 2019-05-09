#include "Queue.h"

/*Constructor*/
Queue *new_Queue(){
	Queue *temp = malloc(sizeof(Queue));

	temp->header = 0;
	temp->footer = 0;
	temp->size = 0;

	return temp;
}

/*Methods*/
bool is_empty(Queue *queue){
	return queue->header == queue->footer;
}

void enqueue(Queue *queue, Process *item){
	queue->arr[queue->footer] = item;
	queue->footer += 1;
	queue->size += 1;

	if ( queue->footer >=STD_QUEUE_SIZE ){

		queue->footer = 0;

	}

}

Process *dequeue(Queue *queue){
	if (is_empty(queue))
		return NULL;

	queue->header += 1;
	queue->size -= 1;

	if ( queue->header >=STD_QUEUE_SIZE ){

		queue->header = 0;
		
	}

	return queue->arr[queue->header - 1];
}

Process *next(Queue *queue){
	return queue->arr[queue->header];
}