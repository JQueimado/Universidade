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

void route_swap( struct route * list, int i, int j )
{

    struct route * temp = list[i];

    list[i] = list[j];

    list[j] = temp;

}

/* Route Sorter */

void sorter ( int size, struct route * list )
{

    for( int i = 0; i < size; i++){

        struct route * temp = list[i];

        for ( int j = i + 1, j < size; j++ ){

            short comp = route_compare( temp, list[j]);

            if ( comp == -1){

                route_swap(list, i, j);
                break;

            }

        }

    }

}
