#include <stdlib.h>
#include <stdio.h>

#define MAX_ROUTES 100000

#include "Route.h"

void print( struct route ** list, int s)
{

    puts("----------------------------");

    for( int i = 0; i < s; i++){

        struct route * temp = list[i];

        printf("%d.%d.%d.0 -> %d\n", temp->s1, temp->s2, temp->s3, temp->i);

    }

    puts("----------------------------");

}

int main( void )
{

    int n = 0;

    scanf("%d",&n);

    short intf;
    int a, b, c;

    struct route * array[n];

    for (int i = 0; i<n; i++){

        scanf("%d.%d.%d.0 %hu", &a, &b, &c, &intf);
        
        array[i] = new_route((unsigned char) a, (unsigned char) b, (unsigned char) c,intf);

    }

    sorter(n, array);

    print(array, n);

    return 0;

}