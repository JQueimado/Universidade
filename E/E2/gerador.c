#include <stdlib.h>
#include <time.h>

#include "Route.h"

#define F_NAME "cona.txt"

int main ( int argc, char const *argv[])
{

    if( argc <= 1  || argc > 3){

        puts("Invalid Arguments");
        return 0;

    }

    FILE * file = fopen(F_NAME, "w");

    int n = atoi(argv[1]);
    int cona = atoi(argv[2]);

    srand(time(NULL));

    fprintf(file, "%d\n", n);

    short a = 0;
    short b = 0;
    short c = 0;

    for ( int i = 0; i < n; i++){

        short inf = (unsigned short) rand() % 255;
    
        c++;

        if( c > 255 ){
            
            c = 0;

            b++;
        
        }
        
        if( b > 255 ){
            
            b = 0;
            a++;
        
        }
        
        if( a > 255 ){

            puts("ERRO");
            return 0;
        
        }

        fprintf(file, "%d.%d.%d.0 %d\n", a, b, c, inf);

        printf("ip n:%d-> %d.%d.%d.0 %d\r", i, a, b, c, inf);

    }

    puts("");

    for( int i = 0; i<cona; i++){

        a = (unsigned short) rand() % 255;
        b = (unsigned short) rand() % 255;
        c = (unsigned short) rand() % 255;
        short d = (unsigned short) rand() % 255;

        printf("ip n:%d-> %d.%d.%d.%d\r", i, a, b, c, d);
        fprintf(file, "%d.%d.%d.%d\n", a, b, c, d);

    }

    puts("");

    fclose(file);

    return 0;

}