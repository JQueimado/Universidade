//Libs
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Classes
#include "Structs/Queue.h"
#include "Structs/Process.h"
#include "Structs/Pre_Process.h"
#include "Structs/Disk.h"

//Consts

//Vars
#define SIZE_FILE_LINE 300
#define DISCK_SAVE_TIME 3
#define MEM_SIZE 300
#define MAX_PROCESS 20

//Scheduling
#define QUANTUM 4
#define MAX_READY_SIZE 4

//Functions & Var
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

/************************************ CPU ************************************/
int CPU(Process *process, int MEM[], Disk* disk)
{
    /* return codes
        0 normal
        1 fork
        2 block
        3 exit
    */
    int inst0 = MEM[process->pc + 0];
    int inst1 = MEM[process->pc + 1];
    int inst2 = MEM[process->pc + 2];

    if( process->timer == 0)
    {
        process->timer = -1;
        if(inst0 == DISCK_LOAD_X)
        {
            set_disk(disk, inst1);
        }
        else if( inst0 == DISCK_SAVE_X)
        {
            set_var(process, MEM, inst1, get_disk(disk));
        }
        return 0;
    }

    if (inst0 == SET_X)
    {
        int var = get_var(process, MEM, inst2);
        set_var(process, MEM, inst1, var);
        return 0;
    }

    if (inst0 == SET_N)
    {
        set_var(process, MEM, inst1, inst2);
        return 0;
    }

    if (inst0 == INC_X)
    {
        int var = get_var(process, MEM, inst1);
        set_var(process, MEM, inst1, var+1);
        return 0;
    }

    if (inst0 == DEC_X)
    {
        int var = get_var(process, MEM, inst1);
        set_var(process, MEM, inst1, var-1);
        return 0;
    }

    if (inst0 == BACK_N)
    {
        set_pc(process, -inst1);
        return 0;
    }

    if (inst0 == FORW_N)
    {
        set_pc(process, inst1);
        return 0;
    }

    if (inst0 == IF_X_N)
    {
        if(inst1 == 0)
        {
            set_pc(process, inst2);
        }
        return 0;
    }

    if (inst0 == FORK_X)
    {
        //2ª parte do trabalho
        return 1;
    }

    if (inst0 == DISCK_SAVE_X)
    {
        return 2;
    }

    if (inst0 == DISCK_LOAD_X)
    {
        return 2;
    }

    if (inst0 == PRINT_X)
    {
        printf("%d ", get_var(process, MEM, inst1));
        return 0;
    }

    if (inst0 == EXIT)
    {
        return 3;
    }
}
/************************************ file io ************************************/

bool read_file( char* fname, Queue* pre_process )
{
    FILE* file = fopen(fname, "r");
    char line[SIZE_FILE_LINE];

    if(!file)
        return false;

    while ( fgets( line, SIZE_FILE_LINE, file) != NULL )
    {
        int arrival = atoi(line[0]);
        int file_pos = ftell(file);
        Pre_Process* temp = new_Pre_Process( arrival, file_pos);
        enqueue(pre_process, temp);
    }
    fclose( file );
    return true;
}

/************************************ main ************************************/
int main(int arg_n, char** args)
{
    //File Acess
    Queue * pre_processess = new_Queue();

    if(!read_file(args[1], pre_processess))
        printf("file %s not found\n", args[1]);

    Queue* ready = new_Queue();
    Queue* blocked = new_Queue();
    Process* new = NULL;
    Process* run = NULL;
    Process* ext = NULL;

    Disk* disk = new_Disk();
    int MEM[MEM_SIZE];

    int timer = 0;
    int count = 0;
    int ids = 0;

    //Processor loop**
    int n_procesess = 0;
    Process * processes[MAX_PROCESS];

    while (!(is_empty(pre_processess) == 0 && is_empty(new) && is_empty(ready) && run == NULL))
    {

        //Check Exit Process*
        if( ext != NULL )
        {
            processes [ext->id - 1] = NULL;
            free(ext);
            ext = NULL;
        }

        //CPU
        if (run != NULL)
        {
            int code = CPU(run, MEM, disk);

            if( code == 0)
            {
                /*normal*/
                set_pc(run, 4);
            }
            else if (code == 1)
            {
                Process* temp = fork_process(run, ids);
                ids++;
                processes[n_procesess] = temp;
                n_procesess++;
                if( ready->size != MAX_READY_SIZE )
                    enqueue(ready, temp);
            }
            else if( code == 2)
            {
                /*block*/
            }
            else if( code == 3)
            {
                ext = run;
                run = NULL;
                set_state(ext, _EXIT_);
            }
        }

        //Scheduling Call
        if ((timer == QUANTUM) || (run == NULL))
        {
            timer = 0;

            //Process for Ready
            if (ready->size < MAX_READY_SIZE && !is_empty(new))
            {
                if (ready->size < MAX_READY_SIZE && !is_empty(new))
                {
                    Process * temp = dequeue(new);
                    set_state(temp, READY_WAIT);
                    enqueue(ready, temp);
                }

                Process * temp = dequeue(new);
                set_state(temp, READY_WAIT);
                enqueue(ready, temp);
            }

            if (run != NULL)
            {
                if (ready->size < MAX_READY_SIZE)
                {
                    set_state(run, READY_WAIT);
                    enqueue(ready, run);
                }
                else
                {
                    set_state(run, BLOCKED);
                    enqueue(blocked, run);
                }
                run = NULL;
            }

            if (run == NULL)
            {
                if (!is_empty(ready))
                {
                    run = dequeue(ready);
                    set_state(run, RUN);
                }
            }

            //Check for Blocked Mesages*
            if ((!is_empty(blocked)) && ready->size < MAX_READY_SIZE)
            {
                for (int count = 0; count < blocked->size; count++)
                {
                    Process *cur_pro = dequeue(blocked);

                    //Check for processes to place in ready
                    if (ready->size < MAX_READY_SIZE && cur_pro->timer != 0)
                    {
                        enqueue(blocked, cur_pro);
                    }
                    else
                    {
                        set_state(cur_pro, READY_WAIT);
                        enqueue(ready, cur_pro);
                    }
                }
            }
        }

        //NEW -> READY
        if( new != NULL)
        {
            enqueue(ready, new);
            new = NULL;
        }

        //BLOCKED -> READY
        if( ready->size != MAX_READY_SIZE )
        {
            for( int i = 0; i<blocked->size; i++ )
            {
                Process* temp = dequeue(blocked);
                if( temp->timer != -1 && temp->timer != 0)
                    temp->timer--;
                enqueue(blocked, temp);
            }
        }

        //check arrivals 
        Pre_Process* temp = next(pre_processess);
        if( count == temp->arrival )
            new = dequeue(pre_processess);

        //show states 
        printf("%5d",count);
        for( int i = 0; i < n_procesess; i++)
        {
            Process * temp = processes[i];

            if(temp == NULL)
            {
                continue;
            }

            if( temp->state == NEW )
            {
                printf("|%5s", "new");
            }
            else if (temp->state == READY_WAIT )
            {
                printf("|%5s", "ready");
            }
            else if (temp->state == RUN)
            {
                printf("|%5s", "run");
            }
            else if (temp->state == BLOCKED)
            {
                printf("|%5s", "blocked");
            }
            else if (temp->state == _EXIT_)
            {
                printf("|%5s", "exit");
            }

            
        }
        printf("|");
        puts("");

        timer += 1;
        count += 1;

    }

    return 0;
}
