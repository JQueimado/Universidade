#include <stdlib.h>
#include <stdio.h>

#include "routing_table.h"

int main( void )
{

    int n = 0;

    scanf("%d",&n);

    short interface[n];

    char n1, n2, n3, n4;
    short intf;

    for (int i = 0; i<n; i++){

        scanf("%c.%c.%c.%c %hu", &n1, &n2, &n3, &n4, &intf);

        interface[i] = intf;

    }

    for (int i = 0; i<n; i++){

        printf("%lu\n", routs[i]);

    }

    return 0;

}