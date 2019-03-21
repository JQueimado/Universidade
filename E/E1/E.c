#include <stdlib.h>
#include <stdio.h>


/*********************************/

/* Struct Route */

struct route
{

    unsigned char s1;
    unsigned char s2;
    unsigned char s3;

    unsigned char i;

};

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

/*********************************/

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

    short out[10000];
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