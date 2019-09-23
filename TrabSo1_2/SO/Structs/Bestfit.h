#ifndef _BESTFIT_
#define _BESTFIT_
/* Memory Manager */
#include "Process.h"

#define MEM_SIZE 300

typedef struct Frame
{
    struct Frame *next;
    Process* process;
}Frame;

Frame* new_frame(Process* process);

Frame* add_to_frame_list(Frame* head, Frame* item );

int find_pos(Process** processes, int p_size, int insert_size, int* Memory);

#endif