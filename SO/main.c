//Libs
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Classes
#include "Structs/Queue.h"
#include "Structs/Process.h"
#include "Structs/Pre_Process.h"
#include "Structs/Disk.h"
#include "Structs/MemoryManager.h"

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

    //printf("process %d inst: %d %d %d\n", process->id, inst0, inst1, inst2);

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
    int file_pos = ftell(file);
    while ( fgets( line, SIZE_FILE_LINE, file) != NULL )
    {
        char* token = strtok(line, " ");
        Pre_Process* temp = new_Pre_Process( atoi(token), file_pos);
        enqueue(pre_process, temp);
        file_pos = ftell(file);
    }
    fclose( file );
    return true;
}

/************************************ main ************************************/
int main(int arg_n, char** args)
{
    //File Acess
    Queue * pre_processess = new_Queue();
    char* fname = args[1];
    if(!read_file(fname, pre_processess))
        printf("file %s not found\n", args[1]);

    Queue* ready = new_Queue();
    Queue* blocked = new_Queue();
    Process* new = NULL;
    Process* run = NULL;
    Process* ext = NULL;

    Disk* disk = new_Disk();
    int MEM[MEM_SIZE];
    memset(MEM, 0, MEM_SIZE * sizeof(int));
    int timer = 0;
    int count = 0;
    int ids = 1;

    //Processor loop**
    int n_procesess = 0;
    Process * processes[MAX_PROCESS];

    while (!(is_empty(pre_processess) && is_empty(ready) && is_empty(blocked) && run == NULL && ext == NULL && new == NULL))
    {

        //Check Exit Process*
        if( ext != NULL )
        {
            processes [ext->id - 1] = NULL;
            free(ext);
            ext = NULL;
        }

        //Scheduling Call
        if ((timer == QUANTUM) || (run == NULL))
        {
            timer = 0;
            //RUN -> READY
            if( run != NULL)
            {
                if( ready->size < MAX_READY_SIZE )
                {
                    enqueue(ready, run);
                    set_state(run, READY_WAIT);
                }
                else
                {
                    enqueue(blocked, run);
                    set_state(run, BLOCKED);
                }
            }

            /* Apply Rule: all prosses in the ready queue must be loaded*/
            for( int point = 0; point < ready->size; point++)
            {
                Process* temp = dequeue(ready);
                //printf("addrs in:%d\n", temp->id);

                if( !temp->in_memory )
                {
                    int p = find_pos(processes, n_procesess, get_size(temp, fname), MEM);
                    load_process(temp, MEM, p, fname);
                }
                //printf("addrs out:%d\n", temp->id);
                enqueue(ready, temp);
            }

            //READY -> RUN
            run = dequeue(ready);
            set_state(run, RUN);
        }

        //CPU
        if (run != NULL)
        {
            int code = CPU(run, MEM, disk);

            if( code == 0)
            {
                /*normal*/
                set_pc(run, 3);
            }
            else if (code == 1)
            {
                /* fork */
                Process* temp = fork_process(run, ids);
                ids++;
                processes[n_procesess] = temp;
                n_procesess++;
                if( ready->size != MAX_READY_SIZE )
                    enqueue(ready, temp);

                set_pc(run, 3);
            }
            else if( code == 2)
            {
                /* disk */
                enqueue(blocked, run);
                set_state(run, BLOCKED);
                run->timer = DISCK_SAVE_TIME;
                run = NULL;
            }
            else if( code == 3)
            {
                /* exit */
                ext = run;
                run = NULL;
                set_state(ext, _EXIT_);
            }
        }

        //NEW -> READY
        if( new != NULL)
        {
            enqueue(ready, new);
            set_state(new, READY_WAIT);
            new = NULL;
        }

        //BLOCKED -> READY
        if( !is_empty(blocked) )
        {
            for( int i = 0; i < blocked->size; i++ )
            {
                Process* temp = dequeue(blocked);
                if(temp == NULL)
                    continue;
                // timer
                if( temp->timer != -1 )
                {
                    if( temp->timer == 0 )
                    {
                        if( ready->size < MAX_READY_SIZE )
                        {
                            enqueue(ready, temp);
                            set_state(temp, READY_WAIT);
                        }
                        continue;
                    }
                    temp->timer--;
                }
                //Proceses that didnt had space in ready 
                else if(ready->size < MAX_READY_SIZE)
                {
                    enqueue(ready, temp);
                    set_state(temp, READY_WAIT);
                    continue;
                }
                
                enqueue(blocked, temp);
            }
        }

        //check arrivals 
        Pre_Process* temp2 = get(pre_processess);
        if( temp2 != NULL)
            if( count == temp2->arrival )
            {
                Pre_Process* pre_new = dequeue(pre_processess);
                new = new_Process(ids, pre_new->file_pos);
                processes[n_procesess] = new;
                n_procesess++;
                ids++;
            }

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
                printf("|%2d %10s", temp->id, "new");
            }
            else if (temp->state == READY_WAIT )
            {
                printf("|%2d %10s",temp->id, "ready");
            }
            else if (temp->state == RUN)
            {
                printf("|%2d %10s",temp->id, "run");
            }
            else if (temp->state == BLOCKED)
            {
                printf("|%2d %10s",temp->id, "blocked");
            }
            else if (temp->state == _EXIT_)
            {
                printf("|%2d %10s",temp->id, "exit");
            }
        }
        printf("|");
        puts("");

        //for(int i = 0; i < MEM_SIZE; i++ )
        //    printf("%d\n", MEM[i]);

        timer += 1;
        count += 1;

    }

    return 0;
}
