#include <stdlib.h>
#include <stdio.h>

#define MAX_ROUTES 100000

#include "Route.h"

int main( void )
{

    int n = 0;

    struct trie *routes = new_trie();

    scanf("%d",&n);

    short intf;
    unsigned char inp[3];

    for (int i = 0; i<n; i++){

        scanf("%c.%c.%c.0 %hu", &inp[0], &inp[1], &inp[2], &intf);

    }

    return 0;

}