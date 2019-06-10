#include "MemoryManager.h"
#include "Process.h"

/* Best Fit implementation */
#define MEM_SIZE 300
#define MAX_FRAME MEM_SIZE/2

/* New Frame */
Frame* new_frame(short init, short end)
{
    Frame* temp = malloc(sizeof(Frame));
    temp->init = init;
    temp->end = end;
    temp->next = NULL;
    return temp;
}

/* Add Frame to list */
Frame* add_to_frame_list(Frame* head, Frame* item )
{
    /* if empty */
    if ( head == NULL )
        return item;

    /* if head */
    if(head->init < item->init)
    {
        item->next = head;
        return item;
    }

    /* if second is empty */
    if( head->next == NULL )
    {
        head->next = item;
        return head;
    }

    /* find place */
    Frame* header = head;
    while (head->next->init < item->init)
    {
        head = head->next;
        
        if( head->next == NULL)
        {
            head->next = item;
            return header;
        }
    }
    item->next = head->next;
    head->next = item;
    return header;
}

/* Find pos */
int find_pos(Process** processes, int p_size, int insrt_size,  int* Memory)
{
    Frame* head = NULL;

    /* Project ocupied memory in Frames */
    for(int i = 0; i < p_size; i++)
    {
        Process* curr = processes[i];
        if(!curr->in_memory)
            continue;
        head = add_to_frame_list(head, new_frame(curr->process_pointer, curr->process_pointer));
    }

    /* if no process */
    if(head == NULL)
        return 0;

    /* if 1 process */
    if(head->next == NULL)
        return head->end + 1;

    /* if > 1 */
    int diference;
    Frame* seleced_frame;

    while(head != NULL)
    {
        /* Calc free Space */
        int free_space = head->next->init - head->end - 1;
        
        /* Check if fit */
        if( free_space > p_size )
        {
            /* Calc free Space after allocasion */
            free_space = free_space - p_size;

            /* Check for Best feet */
            if( diference > free_space )
            {
                diference = free_space;
                seleced_frame = head;
            }
        }
        
        /* move list */
        head = head->next;
    }

    return seleced_frame->end + 1;

}

/**************test_main**************/
#include <stdio.h>
int main()
{
    char* fname = "input1.txt";

    Process *process = new_Process(1, 0);
    Process *process1 = new_Process(2, 28);
    Process* processes[2];
    processes[0] = process;
    processes[1] = process1;

	int *Memory = calloc(sizeof(int), 300);

    printf("mem1:%d\n", get_size(process, fname));
    printf("mem2:%d\n", get_size(process1, fname));

    load_process(process1, Memory, 0, fname);

    int p = find_pos(processes, 2, get_size(process, fname), Memory);

    printf("pos:%d\n", p);

    puts("mem");
    for (int i = 0; i < 40; i++)
		printf("%d\n", Memory[i]);
    puts("nomeme");

}