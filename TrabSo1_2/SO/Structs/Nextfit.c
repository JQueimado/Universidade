#include "Nextfit.h"

Fit* new_fit()
{
    return calloc(1, sizeof(Fit));
}

int find_next_pos(Fit* fit, Process** processes, int ps_size, int p_size)
{
    /* analizer (same as bestfit) */
    Frame* head = NULL;
    /* Project ocupied memory in Frames */
    for(int i = 0; i < ps_size; i++)
    {
        Process* curr = processes[i];
        if( curr == NULL )
            continue;
        if( !curr->in_memory )
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
    Frame* curr = head;
    /* find curr frame */
    while( curr->process->end_pointer < fit->prev )
        curr = curr->next;
    
    /* find fit */
    Frame* selected_frame = NULL;

    /* cycle frames */
    do
    {
        int free_space;
        /* Null frame */
        if( curr == NULL )
        {
            /* from beguin to firts process */
            curr = head;
            free_space = head->process->process_pointer;
        }
        /* last frame */
        else if( curr->next == NULL)
        {
            free_space = MEM_SIZE - curr->process->end_pointer;
        }
        else
        {
            free_space = curr->next->process->process_pointer - curr->process->end_pointer;
        }
        if( free_space >= p_size )
        {
            selected_frame = curr;
            break;
        }
        curr = curr->next;
    }
    while ( curr != head );

    if( selected_frame == NULL)
        return -1;
    else
    {
        fit->prev = selected_frame->process->end_pointer;
        return selected_frame->process->end_pointer + 1;
    }
    
}
/* 
int main()
{
    char* fname = "input1.txt";

    Process *process = new_Process(1, 0);
    Process *process1 = new_Process(2, 31);    
    Process *process2 = new_Process(3, 86);
    int p_size = 3;
    Process* processes[p_size];
    processes[0] = process;
    processes[1] = process1;
    processes[2] = process2;

    int *Memory = calloc(sizeof(int), 300);

    Fit* fit = new_fit();

    int p = find_next_pos(fit, processes, p_size, get_size(process, fname));
    printf("1 %d\n", p);
    load_process(process,Memory, p, fname);
    set_var(process, Memory, 1, 10);


    //p = find_next_pos(fit, processes, p_size, get_size(process1, fname));
    printf("2 %d\n", p);
    //load_process(process1,Memory, 40, fname);
    set_var(process1, Memory, 1, 20);


    p = find_next_pos(fit, processes, p_size, get_size(process2, fname));
    printf("3 %d\n", p);
    load_process(process2,Memory, p, fname);

    set_var(process2, Memory, 1, 30);

    puts("");

    for (int i = 0; i < 80; i++)
		printf("%3d : %d\n", i, Memory[i]);
}
*/