#include "Disk.h"

Disk* new_Disk()
{
    Disk* temp = malloc(sizeof(Disk));
    temp->val = 0;
}

void set_disk(Disk* self, int val)
{
    self->val = val;
}

int get_disk(Disk* self)
{
    return self->val;
}