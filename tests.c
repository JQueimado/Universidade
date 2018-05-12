/**Tests**/

/*Includes*/
#include <stdio.h>
#include <stdbool.h>
#include "Structs/Instruction_Queue.h"
#include "Structs/Process.h"
#include "Structs/Queue.h"

/*Instruction Testing*/
void Instruction_Queue_Testing(){
	
	int test_arr[] = {3,4,1,5};

	struct Instruction_Queue *temp = new_Instruction_Queue_2( test_arr, 4 );

	/*Is Empty*/
	puts("is_empty test:");
	int res = 0;

	if (IQ_is_empty(temp)){
		res = 1;
	}

	printf("0 -> %d\n",res);

	/*Next*/
	puts("next test:");
	printf("3 -> %d\n",IQ_next( temp ));

	/*Dequeue*/
	puts("dequeue test:");
	printf("3 -> %d\n",IQ_dequeue( temp ));
	printf("4 -> %d\n",IQ_dequeue( temp ));
	printf("1 -> %d\n",IQ_dequeue( temp ));
	printf("5 -> %d\n",IQ_dequeue( temp ));
	printf("-1 -> %d\n",IQ_dequeue( temp ));
}

void Process_Testing(){
	
	/*Setup*/
	int id = 325;
	int t_arrival = 2;
	int insts[] = {3,4,1,5};
	int size = 4;

	struct Process *temp = new_Process( id , t_arrival , insts , size );

	/*Creaton*/
	puts("Creaton test:");
	printf("325 -> %d\n", temp->id );
	printf("2 -> %d\n", temp->arrival_time );

	/*Run*/
	puts("run test:");
	printf("3 -> %d\n", run( temp ) );
	printf("4 -> %d\n", run( temp ) );
	printf("1 -> %d\n", run( temp ) );
	printf("5 -> %d\n", run( temp ) );
	printf("-1 -> %d\n", run( temp ) );

}

void Queue_Testing(){
	
	/*Setup*/
	int id = 325;
	int t_arrival = 2;
	int insts_1[] = {3,4,1,5};
	int size = 4;

	struct Process *temp_1 = new_Process( id , t_arrival , insts_1 , size );

	id = 433;
	t_arrival = 1;
	int insts_2[] = {4,4,4,4};
	size = 4;

	struct Process *temp_2 = new_Process( id , t_arrival , insts_2 , size );

	struct Queue *temp = new_Queue();

	/*Is Empty*/
	puts("is_empty test:");
	int res = 0;

	if (is_empty(temp)){
		res = 1;
	}

	printf("1 -> %d\n",res);

	/*Enqueue*/
	enqueue(temp , temp_1);
	enqueue(temp , temp_2);

	/*Dequeue*/
	printf("325 -> %d\n", dequeue(temp)->id );
	printf("433 -> %d\n", dequeue(temp)->id );

	/*Next*/
	struct Process *temp_3 = next(temp);
	
	res = 0;
	
	if (temp_3 == NULL)
		res = 1;

	printf("1 -> %d\n", res);

}

/*Main*/
int main()
{
	/*
	Instruction_Queue_Testing();
	Process_Testing();
	*/
	Queue_Testing();
	return 0;
}