#include <stdlib.h>
#include <stdio.h>

#include "Route.h"

int main( void )
{

    int n = 0;

    scanf("%d",&n);

    short a, b, c, intf;

    struct route * array[n];

    short def_inf = -1;

    for (int i = 0; i<n; i++){

        scanf("%hu.%hu.%hu.0 %hu", &a, &b, &c, &intf);

        if( a==0 && b==0 && c==0)
            def_inf = intf;

        array[i] = new_route((unsigned char) a, (unsigned char) b, (unsigned char) c, intf);

    }

    quick_sorter (array, 0, n);

    short out[100000];
    int outp = 0;

    while(  scanf("%hu.%hu.%hu.%hu", &a, &b, &c, &intf) != EOF )
    {
    
        struct route * temp = new_route((unsigned char) a, (unsigned char) b, (unsigned char) c, 0);

        struct route * find = binary_search(temp, array, 0, n);

        if ( find == NULL){

            out[outp] = -1;
            outp += 1;

        }
        else
        {

            out[outp] = find->i;
            outp += 1;

        }
        
    }

    for ( int i = 0; i<outp; i++)
        
        if(out[i] == -1)
        
            if(def_inf != -1)
                
                printf("%d\n", def_inf);
            
            else
            
                puts("no route");
        
        else
        
            printf("%d\n", out[i]);
    
    return 0;

}