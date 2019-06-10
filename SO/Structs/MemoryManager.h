/* Memory Manager */
#include "Process.h"

typedef struct Frame
{
    struct Frame *next;
    Process* process;
}Frame;

Frame* new_frame(Process* process);

int find_pos(Process** processes, int p_size, int insert_size, int* Memory);