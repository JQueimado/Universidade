/* Disk */
#include <stdlib.h>

struct Disk
{
    int val;
}
typedef Disk;

Disk* new_Disk();

void set_disk(Disk* self, int val);

int get_disk(Disk* self);