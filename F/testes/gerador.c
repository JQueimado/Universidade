#include <stdlib.h>
#include <stdio.h>
#define FNAME "teste.txt"

int main( int argc, char const *argv[])
{

    int n = atoi( argv[1] );

    FILE * file = fopen(FNAME, "w");

    fprintf(file, "%d\n", n);

    for(int i = 0; i< n; i++){

        if ( i != n-1)
            fprintf(file, "+ %d %d\n", i, i+1);
        else    
            fprintf(file, "+ %d %d\n", i, 0);

    }

    fclose(file);

}