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

    if (argc < 2)
        return 0;

    int c = atoi(argv[2]);

    for(int j = 0; j < c; j++){

        fprintf(file, "? 1000");

        int v = j;

        for(int i = 0; i <= 1000; i++){
            
            if( v == n )
                v = 0;

            fprintf(file," %d", v);

            v++;

        }

        fprintf(file,"\n");

    }

    fclose(file);

}