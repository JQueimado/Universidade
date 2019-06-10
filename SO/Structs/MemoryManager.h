/* Memory Manager */
#include "Process.h"

typedef struct Frame
{
    struct Frame *next;
    short init;
    short end;
}Frame;

Frame* new_frame(short init, short end);

int find_pos(Process** processes, int p_size, int insert_size, int* Memory);