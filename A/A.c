#include <stdio.h>
#include <math.h>

int main(int argc, char const *argv[])
{
    
    long n;
    int out = 0;

    scanf("%ld", &n);

    if ( n > pow( 2, 31 ) - 1 || n < -pow( 2, 31) + 1)
    {

        return 0;

    }

    if ( n < 0 )
    {

        n = -n;

    }

    do
    {
     
        n = n / 10;

        out += 1;
    
    }
    while( n > 0 );
    

    printf("%d\n",out);

    return 0;
}
