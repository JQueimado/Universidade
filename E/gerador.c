#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define F_NAME "teste.txt"

int main ( int argc, char const *argv[])
{

    if( argc != 2  && argc != 3 ){

        puts("Invalid Arguments");
        return 0;

    }

    FILE * file = fopen(F_NAME, "w");

    int n = atoi(argv[1]);

    srand(time(NULL));

    fprintf(file, "%d\n", n);

    short a = 0;
    short b = 0;
    short c = 0;

    for ( int i = 0; i < n; i++){

        short inf = (unsigned char) rand() % 255;
    
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

    if (argc == 2){

        fclose(file);

        return 0;
    }

    int f = atoi(argv[2]);

    puts("");

    a = 0;
    b = 0;
    c = 0;

    for( int i = 0; i<f; i++){

        short inf = (unsigned char) rand() % 255;
    
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

        fprintf(file, "%d.%d.%d.%d\n", a, b, c, inf);

        printf("ip n:%d-> %d.%d.%d.%d\r", i, a, b, c, inf);

    }

    puts("");

    fclose(file);

    return 0;

}