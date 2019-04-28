/*Libs*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Structs/Process.h"
#include "Structs/Pre_Process.h"
#include "Structs/Queue.h"

/*Vars*/
#define MAX_PROCESS 5
#define DISCK_SAVE_TIME 3
#define MEM_SIZE 300
#define LINE_SIZE 300
#define FILE_NAME "input1.txt"

/*Scheduling*/
#define QUANTUM 4
#define MAX_READY_SIZE 4

/*Functions*/
#define SET_X 0
#define SET_N 1
#define INC_X 2
#define DEC_X 3
#define BACK_N 4
#define FORW_N 5
#define IF_X_N 6
#define FORK_X 7
#define DISCK_SAVE_X 8
#define DISCK_LOAD_X 9
#define PRINT_X 10
#define EXIT 11

/**CPU**/
struct Process *CPU(struct Process *process, int MEM[])
{

    int inst = MEM[process->pc];

    int i = inst / 10;
    int v = inst - i * 10;

    printf("%d %d\n", i, v);

    if (i == SET_X)
    {
        int var2;
        scanf("%d", &var2);
        MEM[process->mem_str + v] = var2;
    }

    if (i == SET_N)
    {
        int N;
        scanf("%d", &N);
        MEM[process->mem_str + v] = N;
    }

    if (i == INC_X)
    {
        MEM[process->mem_str + v] += 1;
    }

    if (i == DEC_X)
    {
        MEM[process->mem_str + v] -= 1;
    }
    if (i == IF_X_N)
    {
        if (MEM[process->mem_str + v] != 0)
        {
            set_pc(process, process->pc + 1);
        }
    }

    set_pc(process, process->pc + 1);

    return process;
}

/***main***/
int main(void)
{

    /**File Acess**/
    FILE *file_pointer;
    file_pointer = fopen(FILE_NAME, "r");

    if (!file_pointer)
    {
        perror("Error");
        exit(0);
    }

    int output_arr_pointer = 0;
    static int output_arr[(MAX_PROCESS * 2)];

    int i;
    int line = 0;

    int Arrival_Time;

    char Instants_Array[LINE_SIZE];

    while (fgets(Instants_Array, LINE_SIZE, file_pointer))
    {
        line = line + 1;

        char arrival_str[5];

        for (i = 0; Instants_Array[i] != ' '; i++)
        {
            arrival_str[i] = Instants_Array[i];
        }

        Arrival_Time = atoi(arrival_str);

        output_arr[output_arr_pointer] = Arrival_Time;
        output_arr_pointer += 1;

        i += 1;

        int Instantes_size = 0;

        while (Instants_Array[i] != '\n')
        {
            if (Instants_Array[i] == ' ')
            {
                Instantes_size += 1;
            }
            i++;
        }

        output_arr[output_arr_pointer] = Instantes_size;
        output_arr_pointer += 1;
    }

    fclose(file_pointer);
    output_arr[output_arr_pointer] = -1;

    /*Prepare arrival_process*/

    int arrival_process_end = 0;
    int arrival_process_count = 0;
    struct Pre_Process *arrival_process[MAX_PROCESS];

    for (int i = 0; output_arr[i] != -1; i += 2)
    {
        arrival_process[arrival_process_end] = new_Pre_Process(output_arr[i], arrival_process_end, output_arr[i + 1]);
        arrival_process_end += 1;
    }

    arrival_process_count = arrival_process_end;

    /*prepare scheduel*/
    puts("start");
    int mem_str = 0;
    int mem_end = 0;
    int mem_cur_size = 0;

    /*MEM*/
    static int MEM[MEM_SIZE];

    /*Lists*/

    struct Queue *new = new_Queue();

    struct Queue *ready = new_Queue();

    struct Queue *blocked = new_Queue();

    struct Process *run = NULL;

    int timer = 0;
    int count = 0;
    int ids = 0;

    /***Processor loop***/
    while (!(arrival_process_count == 0 && is_empty(new) && is_empty(ready) && run == NULL))
    {
        /**Check Process Entry**/
        for (int i = 0; i < arrival_process_end; ++i)
        {
            struct Pre_Process *pre_temp = arrival_process[i];

            if (pre_temp->arrival <= count && pre_temp->done == 0)
            {
                ids += 1;

                struct Process *temp = new_Process(ids, pre_temp->size, pre_temp->file_pos);

                enqueue(new, temp);

                arrival_process_count -= 1;

                pre_temp->done = 1;
            }
        }

        /**Scheduling Call**/
        if ((timer == QUANTUM) || (run == NULL))
        {
            puts("process changed");
            timer = 0;

            /*Process for Ready*/
            if (ready->size < MAX_READY_SIZE && !is_empty(new))
            {
                enqueue(ready, dequeue(new));
            }

            if (run != NULL)
            {

                if (ready->size < MAX_READY_SIZE)
                {
                    enqueue(ready, run);
                }
                else
                {
                    enqueue(blocked, run);
                }

                run = NULL;
            }

            if (run == NULL)
            {
                if (!is_empty(ready))
                {
                    run = dequeue(ready);
                }
            }

            /**Check for Blocked Mesages**/
            if ((!is_empty(blocked)) && ready->size < MAX_READY_SIZE)
            {
                for (int count = 0; count < blocked->size; count++)
                {
                    struct Process *cur_pro = dequeue(blocked);

                    /*Check for processes to place in ready*/
                    if (ready->size < MAX_READY_SIZE && cur_pro->block_time == -1)
                    {
                        enqueue(blocked, cur_pro);
                    }
                    else
                    {
                        enqueue(new, cur_pro);
                    }
                }
            }
        }

        /*Disk acesses*/
        if (!is_empty(blocked))
        {
            for (int count = 0; count < blocked->size; count++)
            {
                struct Process *cur_pro = dequeue(blocked);

                if (cur_pro->block_time != -1)
                {
                    if (cur_pro->block_time >= DISCK_SAVE_TIME)
                    {
                        cur_pro->block_time = -1;
                    }
                    else
                    {
                        cur_pro->block_time += 1;
                    }
                }
                enqueue(blocked, cur_pro);
            }
        }

        /**CPU**/
        if (run != NULL)
        {
            run = CPU(run, MEM);

            printf("%d : %d\n", count, run->id);

            /*Check if process is waiting for a message*/
            if (run->block_time != -1)
            {
                enqueue(blocked, run);
                run = NULL;
            }

            /*Check if process ended*/

            /*Testing*/
            run->pc_aux += 1;

            if (run->pc_aux >= run->size)
            {
                run = NULL;
            }
        }
        else
        {
            printf("%d : empty\n", count);
        }

        timer += 1;
        count += 1;
    }

    return 0;
}