#include <stdlib.h>
#include <stdio.h>

#define MAX_ROUTES 100000

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

/* Route Sorter */

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
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
  
void mergeSort(struct route * arr[], int l, int r) 
{ 
    if (l < r) 
    { 
        int m = l+(r-l)/2; 
  
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
  
        merge(arr, l, m, r); 
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

    puts("sorting...");

    mergeSort(array, 0, n-1);

    print(array, n);

    while(  scanf("%d.%d.%d.%hu", &a, &b, &c, &intf) != EOF );

    return 0;

}