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
/*
void route_swap( struct route ** list, int i, int j )
{

    struct route * temp = list[i];

    list[i] = list[j];

    list[j] = temp;

}
*/

/* Route Sorter */

void merge(struct route ** list, int s, int m, int f)
{

    int s1 = m - s + 1;
    int s2 = f - m;

    struct route * temp1[s1];
    struct route * temp2[s2];

    for( int i = 0; i < s1; i++)
        temp1[i] = list[s + i];

    for( int j = 0; j < s2; j++)
        temp2[j] = list[m + 1 + j];

    /*

    puts("--- temp 1 ---");

    for( int i = 0; i < s1; i++){

        struct route * temp = temp1[i];

        printf("%d.%d.%d.0 -> %d\n", temp->s1, temp->s2, temp->s3, temp->i);

    }

    puts("--- temp 2 ---");

    for( int i = 0; i < s2; i++){

        struct route * temp = temp2[i];

        printf("%d.%d.%d.0 -> %d\n", temp->s1, temp->s2, temp->s3, temp->i);

    }

    */

    int p1 = 0;
    int p2 = 0;
    int p3 = 0;


    while (p1 < s1 && p2 < s2){

        if ( route_compare( temp1[p1], temp2[p2] ) == -1 ) 
        { 
        
            list[p3] = temp1[p1]; 
            p1++; 
        
        } 
        else
        { 
            
            list[p3] = temp2[p2]; 
            p2++; 

        } 
        
        p3++; 

    } 

    while (p1 < s1) 
    { 
        
        list[p3] = temp1[p1];

        p1++;
        p3++;

    } 

    while (p2 < s2) 
    { 
        
        list[p3] = temp2[p2];
        
        p2++;
        p3++;

    } 

}

void merge_sorter(struct route ** list, int s, int f)
{

    if ( s < f){

        int m = s + (f-s)/2;

        merge_sorter( list, s, m);
        merge_sorter( list, m+1, f);

        merge( list, s, m, f);

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
