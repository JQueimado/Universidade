#include "MemoryManager.h"
/* Best Fit implementation */
#define MEM_SIZE 300
#define MAX_FRAME MEM_SIZE/2

int find_pos(Process** processes, int p_size,  int* Memory)
{
    /* find empty frames */
    int frame_pointer[MAX_FRAME];
    int frame_size[MAX_FRAME];
    for(int i = 0; i < p_size; i++)
    {
        Process* curr = processes[i];
        
    }
}