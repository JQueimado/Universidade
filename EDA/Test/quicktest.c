

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void swap_str_ptrs(char const **arg1, char const **arg2)
{
    const char *tmp = *arg1;
    *arg1 = *arg2;
    *arg2 = tmp;
}

void quicksort_strs(char const *args[], unsigned int len)
{
    unsigned int i, pvt=0;

    if (len <= 1)
        return;

    // swap a randomly selected value to the last node
    swap_str_ptrs(args+((unsigned int)rand() % len), args+len-1);

    // reset the pivot index to zero, then scan
    for (i=0;i<len-1;++i)
    {
        if (strcmp(args[i], args[len-1]) < 0)
            swap_str_ptrs(args+i, args+pvt++);
    }

    // move the pivot value into its place
    swap_str_ptrs(args+pvt, args+len-1);

    // and invoke on the subsequences. does NOT include the pivot-slot
    quicksort_strs(args, pvt++);
    quicksort_strs(args+pvt, len - pvt);
}

void print_list(char const *args[], unsigned len)
{
    unsigned i=0;
    for (;i<len;++i)
        puts(args[i]);
}

int main()
{
    char const *args[] =
    {
        "0aaaa","12345","Zyxvu","aBcde","abCde"
    };

    //srand((unsigned)time(NULL));
    quicksort_strs(args, sizeof(args)/sizeof(*args));
    print_list(args, sizeof(args)/sizeof(*args));
    return 0;
}