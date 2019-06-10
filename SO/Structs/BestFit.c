#include "MemoryManager.h"
#include "Process.h"

/* Best Fit implementation */
#define MEM_SIZE 300
#define MAX_FRAME MEM_SIZE/2

/* New Frame */
Frame* new_frame(Process* process)
{
    Frame* temp = malloc(sizeof(Frame));
    temp->process = process;
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
    if(head->process->process_pointer > item->process->process_pointer)
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
    while (head->next->process->process_pointer < item->process->process_pointer)
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
        head = add_to_frame_list(head, new_frame(curr));
    }

    /* if no process */
    if(head == NULL)
        return 0;

    /* if 1 process */
    if(head->next == NULL)
        return head->process->end_pointer + 1;

    /* if > 1 */

    /* test */
    /* 
    Frame* temp = head;
    while (temp != NULL)
    {
        printf("ids:%d\n", temp->process->id);
        temp = temp->next;
    }
    */
    int diference;
    Frame* seleced_frame;

    while(head->next != NULL)
    {
        /* Calc free Space */
        int free_space = head->next->process->process_pointer - head->process->end_pointer - 1;
        /* Check if fit */
        if( free_space > insrt_size )
        {
            /* Calc free Space after allocasion */
            free_space = free_space - insrt_size;
            /* Check for Best fit */
            if( free_space < diference )
            {
                diference = free_space;
                seleced_frame = head;
            }
        }
        
        /* move list */
        head = head->next;
    }

    int free_to_end = MEM_SIZE - head->process->end_pointer;
    if( free_to_end > insrt_size )
    {
        free_to_end = free_to_end - insrt_size;
        if( free_to_end < diference)
            return head->process->end_pointer + 1;
    }
    return seleced_frame->process->end_pointer + 1;
}

/**************test_main**************/
#include <stdio.h>
int main()
{
    char* fname = "input1.txt";

    Process *process = new_Process(1, 0);
    Process *process1 = new_Process(2, 40);    
    Process *process2 = new_Process(3, 76);
    int p_size = 3;
    Process* processes[p_size];
    processes[0] = process;
    processes[1] = process1;
    processes[2] = process2;

	int *Memory = calloc(sizeof(int), 300);

    printf("mem1:%d\n", get_size(process, fname));
    printf("mem2:%d\n", get_size(process1, fname));

    load_process(process1, Memory, 0, fname);
    set_var(process1, Memory, 10, 200);
    set_var(process1, Memory, 1, 22);

    int p = find_pos(processes, p_size, get_size(process, fname), Memory);
    printf("pos:%d\n", p);
    load_process(process, Memory, p, fname);
    set_var(process, Memory, 10, 300);
    set_var(process, Memory, 1, 33);

    p = find_pos(processes, p_size, get_size(process2, fname), Memory);
    printf("pos:%d\n", p);
    load_process(process2, Memory, p, fname);
    set_var(process, Memory, 10, 400);
    set_var(process, Memory, 1, 44);

    puts("mem");
    for (int i = 0; i < 100; i++)
		printf("%d\n", Memory[i]);
    puts("nomeme");

}