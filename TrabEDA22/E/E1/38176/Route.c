#include "Route.h"

/* Route Constructor */

struct route * new_route( unsigned char n1, unsigned char n2, unsigned char n3, unsigned char intf)
{

    struct route * temp = malloc( sizeof( struct route ) );

    temp->s1 = n1;
    temp->s2 = n2;
    temp->s3 = n3;

    temp->i = intf;

    return temp;

}

/* Route Compare */

short route_compare( struct route * r1, struct route * r2 )
{

    /* eval sector 1 */

    if( r1->s1 > r2->s1 )
        
        return 1;
    
    else if ( r1 ->s1 < r2->s1)
    
        return -1;

    /* eval sector 2 */

    if( r1->s2 > r2->s2 )
    
        return 1;
    
    else if ( r1 ->s2 < r2->s2)
    
        return -1;

    /* eval sector 3 */

    if( r1->s3 > r2->s3 )
    
        return 1;
    
    else if ( r1 ->s3 < r2->s3)
    
        return -1;

    return 0;
    
}

/* Route Swap */

void route_swap( struct route ** list, int i, int j )
{

    struct route * temp = list[i];

    list[i] = list[j];

    list[j] = temp;

}

/* Route Sorter */

int part (struct route ** list, int s, int f)
{

    int pivot = f;

    int sml = s -1;

    for( int i = s; i <= f-1; i++){

        if( route_compare(list[i], list[pivot]) != 1 ){

            sml++;
            route_swap(list, sml, i);

        }

    }

    route_swap(list, sml+1, f);
    return sml + 1;

}

void quick_sorter (struct route ** list, int s, int f )
{

    if ( s < f ){

        int pivot = part(list, s, f);

        quick_sorter(list, s, pivot-1);
        quick_sorter(list, pivot+1, f);

    }

}

/* Route Search */

struct route * binary_search( struct route * in , struct route ** list, int i , int j) 
{

    int n =  i + ( j - i )/2;

    struct route * temp = list[n];

    if ( j >= i){

        switch ( route_compare(in, temp) )
        {
            case 1:
                return binary_search(in, list, n + 1, j);
        
            case 0:
                return temp;

            case -1:
                return binary_search(in, list, i, n - 1);

        }

    }

    return NULL;    

}
