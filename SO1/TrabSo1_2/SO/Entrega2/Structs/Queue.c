#include "Queue.h"

/*Constructor*/
Queue *new_Queue(){
	Queue *temp = malloc(sizeof(Queue));

	temp->header = 0;
	temp->footer = 0;
	temp->size = 0;
	memset(temp->arr, 0,sizeof(void*));
	return temp;
}

/*Methods*/
bool is_empty(Queue *queue){
	return queue->header == queue->footer;
}

void enqueue(Queue *queue, void* item){
	queue->arr[queue->footer] = item;
	queue->footer += 1;
	queue->size += 1;

	if ( queue->footer >=STD_QUEUE_SIZE ){

		queue->footer = 0;

	}

}

void* dequeue(Queue *queue){
	if (is_empty(queue))
		return NULL;
	void* head = queue->arr[queue->header];
	queue->header += 1;
	queue->size -= 1;

	if ( queue->header >=STD_QUEUE_SIZE ){

		queue->header = 0;
		
	}

	return head;
}

void* get(Queue *queue)
{
	if(is_empty(queue))
		return NULL;
	
	return queue->arr[queue->header];
}
/* 
int main()
{
	Queue* queue = new_Queue();
	int s = 30;

	for(int i = 0; i <=s; i++)
		enqueue(queue, i);

	for(int i = 0; i<=s-10; i++)
		dequeue(queue);

	for(int i = 0; i<s; i++)
		enqueue(queue, i);

	for(int i = 0; i < s; i++ )
		printf("%d\n", get(queue, i));

	//for(int i = 0; i < s; i++ )
	//	printf("%d\n", dequeue(queue));



}
*/