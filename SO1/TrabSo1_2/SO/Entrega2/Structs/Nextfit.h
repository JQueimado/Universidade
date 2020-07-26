#ifndef _NEXTFIT_
#define _NEXTFIT_

#include "Process.h"
#include "Bestfit.h"

typedef struct Fit
{
    int prev;
}Fit;

Fit* new_fit();

int find_next_pos(Fit* fit, Process** processes, int ps_size, int p_size);

#endif