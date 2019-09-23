//Libs
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Classes
#include "Structs/Queue.h"
#include "Structs/Process.h"
#include "Structs/Pre_Process.h"
#include "Structs/Disk.h"
#include "Structs/Bestfit.h"
#include "Structs/Nextfit.h"

//Consts

//Vars
#define SIZE_FILE_LINE 300
#define DISCK_SAVE_TIME 3
#define MEM_SIZE 300
#define MAX_PROCESS 100

/* Memory Manager:
    0 -> Best fit
    1 -> Next fit
*/
#define MEMORY_MANAGER 0

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

#define SIMPLE_FILE "scheduler_simples.out"
#define COMPLE_FILE "scheduler_complexo.out"

/************************************ CPU ************************************/
int CPU(Process *process, int MEM[], Disk* disk, FILE* simp_file, FILE* comp_file)
{
    /* return codes
        0 normal
        1 fork
        2 block
        3 exit
        4 jump
        -1 memory error
    */
    int inst0 = MEM[process->pc + 0];
    int inst1 = MEM[process->pc + 1];
    int inst2 = MEM[process->pc + 2];

    //printf("%d-> %d %d %d\n", process->id, inst0,inst1,inst2);

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
        if( !set_pc(process, -inst1))
            return -1;
        return 4;
    }

    if (inst0 == FORW_N)
    {
        if( !set_pc(process, inst1) )
            return -1;
        return 4;
    }

    if (inst0 == IF_X_N)
    {
        if(inst1 == 0)
        {
            if( !set_pc(process, inst2) )
                return -1;
        }
        else
        {
            if( !set_pc(process, 1) )
                return -1;
        }
        
        return 4;
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
        fprintf(simp_file,"%d\n", get_var(process, MEM, inst1));
        fprintf(comp_file,"%d\n", get_var(process, MEM, inst1));
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
/************************************ assistent ************************************/
/* imprime os valores da memoria num ficheiro */
void mem_printer(int* Memory, FILE* comp_file)
{
    for(int i = 0; i<MEM_SIZE; i++)
        fprintf(comp_file,"%3d->%d\n", i, Memory[i]);
}

/************************************ garbadge colector ************************************/
/* limpa a memoria de processos desnecessarios (blocked) */
int gc(Process** processes, int ps_size, int* Memory )
{
    for(int i = 0; i<ps_size; i++ )
    {
        Process* cur = processes[i];
        if(cur == NULL)
            continue;
        if(cur->state == BLOCKED && cur->in_memory)
        {
            unload(cur, Memory);
        }
    }
}

/************************************ main ************************************/
int main(int arg_n, char** args)
{
    //File Acess
    Queue * pre_processess = new_Queue();
    char* fname = args[1];
    if(!read_file(fname, pre_processess))
        printf("file %s not found\n", args[1]);

    FILE* simp_file = fopen(SIMPLE_FILE, "w+");
    FILE* comp_file = fopen(COMPLE_FILE, "w+");

    Queue* ready = new_Queue();
    Queue* blocked = new_Queue();
    Process* new = NULL;
    Process* run = NULL;
    Process* ext = NULL;

    Fit* fit;

    if( MEMORY_MANAGER == 1)
        fit = new_fit();

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
                
                if( !temp->in_memory )
                {
                    int p = find_pos(processes, n_procesess, get_size(temp, fname), MEM);
                    if ( p == -1 )
                    {
                        gc(processes, n_procesess, MEM );
                        mem_printer(MEM, comp_file);
                        if( MEMORY_MANAGER == 0)
                            p = find_pos(processes, n_procesess, get_size(temp, fname), MEM);
                        else
                            p =find_next_pos(fit, processes, n_procesess, get_size(temp, fname));
                    }
                    load_process(temp, MEM, p, fname);
                    mem_printer(MEM, comp_file);
                }
                enqueue(ready, temp);
            }

            //READY -> RUN
            run = dequeue(ready);
            set_state(run, RUN);
        }

        //CPU
        if (run != NULL)
        {
            int code = CPU(run, MEM, disk, simp_file, comp_file);

            if( code == 0)
            {
                /*normal*/
                if(!set_pc(run, 1))
                {
                    ext = run;
                    run = NULL;
                    set_state(ext, _EXIT_);
                    fputs("MEMORY ACCESS VIOLATION\n", simp_file);
                    fputs("MEMORY ACCESS VIOLATION\n", comp_file);
                }
            }
            else if (code == 1)
            {
                /* fork */
                Process* temp = new_Process(ids, run->inst_pos);
                
                /* loads to temp to change pc */
                int* Temp = calloc(100, sizeof(int));
                load_process(temp, Temp, 0, fname);
                
                /* copy vars */
                for(int i = 1; i<= 10;i++)
                {
                    set_var(temp, Temp, i, get_var(run, MEM, i));
                }

                temp-> pc = temp->process_pointer + (run->pc - run->process_pointer);
                if(!set_pc(temp, 1))
                {
                    ext = temp;
                    set_state(ext, _EXIT_);
                    fputs("MEMORY ACCESS VIOLATION\n", simp_file);
                    fputs("MEMORY ACCESS VIOLATION\n", comp_file);
                }
                else
                {
                    /* X = 0 */
                    int inst1 = Temp[temp->pc + 1];
                    set_var(temp, Temp, inst1, 0);
                    
                    /* unloads to store pc */
                    unload(temp, Temp);

                    /* X = PID */
                    set_var(run, MEM, inst1, temp->id);
                    ids++;

                    /* add process to system */
                    processes[n_procesess] = temp;
                    n_procesess++;

                    /* queue to ready */
                    if( ready->size != MAX_READY_SIZE )
                    {
                        enqueue(ready, temp);
                        set_state(temp, READY_WAIT);
                    }   
                    else
                    {
                        enqueue(blocked, temp);
                        set_state(temp, BLOCKED);
                    }
                }
                if(!set_pc(run, 1) )
                {
                    ext = run;
                    run = NULL;
                    set_state(ext, _EXIT_);
                    fputs("MEMORY ACCESS VIOLATION\n", simp_file);
                    fputs("MEMORY ACCESS VIOLATION\n", comp_file);
                }
                
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
            else if( code == -1)
            {
                ext = run;
                run = NULL;
                set_state(ext, _EXIT_);
                fputs("MEMORY ACCESS VIOLATION\n", simp_file);
                fputs("MEMORY ACCESS VIOLATION\n", comp_file);
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
        if( !is_empty(blocked) && ready->size < MAX_READY_SIZE)
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
        fprintf(simp_file,"instante %5d:",count);
        fprintf(comp_file,"instante %5d:",count);
        for( int i = 0; i < n_procesess; i++)
        {
            Process* temp = processes[i];
            char* state;

            if(temp == NULL)
            {
                state = "";
            }
            else
            {
                if( temp->state == NEW )
                {
                state = "new";
                }
                else if (temp->state == READY_WAIT )
                {
                    state = "ready";
                }
                else if (temp->state == RUN)
                {
                    state = "run";
                }
                else if (temp->state == BLOCKED)
                {
                    state = "blocked";
                }
                else if (temp->state == _EXIT_)
                {
                    state = "exit";
                }
            }
            int a = 5+strlen(state)/2;
            int b = 5-strlen(state)/2;
            fprintf(simp_file, "|%*s%*s", a, state, b, "");
            fprintf(comp_file, "|%*s%*s", a, state, b, "");

        }
        fprintf(simp_file, "|\n");
        fprintf(comp_file, "|\n");

        timer += 1;
        count += 1;

    }
    fclose(simp_file);
    fclose(comp_file);

    free( ready );
    free( blocked );

    return 0;
}
