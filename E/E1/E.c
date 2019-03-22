#include <stdlib.h>
#include <stdio.h>

/** Header **/
/*****************************************************************************************************************/

/* <Route> */

struct route
{

    unsigned char s1;
    unsigned char s2;
    unsigned char s3;

    unsigned char i;

};

/* 
route new_route( val_1, val_2, val_3, interface ) 

Desc: create a route type object

Arg: n1 - first 3 digits form the route
     n2 - second 3 digits from the route
     n3 - third 3 digits from the route
     intf - route's associated interface

Ret: route pointer 

*/

struct route * new_route( unsigned char n1, unsigned char n2, unsigned char n3, unsigned char intf)
{

    struct route * temp = malloc( sizeof( struct route ) );

    temp->s1 = n1;
    temp->s2 = n2;
    temp->s3 = n3;

    temp->i = intf;

    return temp;

}

/* 
route route_compare( route_1, route_2 ) 

Desc: compares 2 route type objects

Arg: r1 - first route object
     r2 - second route object

Ret: 1 - if r1 is bigger than r2
     0 - if r1 is equal to r2
     -1 - if r1 is smaller than r2

*/

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

/* 
void merge( route_array, lowest_position, middle_position , highest_position ) 

Desc: merges 2 arrays by size, sorting them

Arg: arr- main array
     l - left point to sort
     m - middle point to sort
     r - right point to sort

Ret: void

*/

void merge(struct route * arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    struct route * L[n1];
    struct route * R[n2]; 
  
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
        
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1 + j]; 
  
    i = 0; 
    j = 0;  
    k = l; 
    while (i < n1 && j < n2) 
    { 
        if( route_compare( L[i], R[j] ) != 1  ) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
  
/* 
void merge_sorter( route_array , lowest_position, highest_position ) 

Desc: brakes an array in half until each node has 1 element

Arg: arr- main array
     l - left point to sort
     r - right point to sort

Ret: void

*/

void merge_sorter(struct route * arr[], int l, int r) 
{ 
    if (l < r) 
    { 
        int m = l+(r-l)/2; 
  
        merge_sorter(arr, l, m); 
        merge_sorter(arr, m+1, r); 
  
        merge(arr, l, m, r); 
    } 
} 

/*
route binary_search( route_to_search, route_array , lowest_position, highest_position ) 

Desc: dichotomic search algorithm to find a route that matches the input route

Arg: in - route to search
     list - list of routes ( sorted )
     i - lowest array pointer to search
     j - higest array pointer to search

Ret: route - matched route if found
     NULL - if not found

*/

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

/* </Route> */

/** Main **/
/*****************************************************************************************************************/

/* 
int main( void ) 

Arg: 1th: n format
     n - number of routes to store

     2nd: a.b.c.0 i format
     a - first 3 digits from the route ipv4
     b - second 3 digits from the route ipv4
     c - third 3 digits from the route ipv4
     i - designated route interface

     3th a.b.c.d format
     a - first 3 digits from the ipv4 to be searched 
     b - second 3 digits from the route ipv4 to be searched 
     c - third 3 digits from the route ipv4 to be searched 
     d - last 3 digits from the route ipv4 to be searched

Ret: 0 - if it runs with no errors
     1 - if no error occures  

*/

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

    merge_sorter(array, 0, n);

    while(  scanf("%hu.%hu.%hu.%hu", &a, &b, &c, &intf) != EOF )
    {
    
        struct route * temp = new_route((unsigned char) a, (unsigned char) b, (unsigned char) c, 0);

        struct route * find = binary_search(temp, array, 0, n);

        if ( find == NULL){

            if(def_inf != -1)
                
                printf("%d\n", def_inf);
            
            else
            
                puts("no route");

        }
        else
        {

            printf("%d\n", find->i);

        }
        
    }
    
    return 0;

}