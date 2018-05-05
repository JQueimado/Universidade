/*Class Instructions_Queue*/

#include "Process.h"

struct Instructions_Queue{

	int *script;

};

/*Class Process*/

struct Process{
	int id;
	struct Instructions_Queue *script;
};