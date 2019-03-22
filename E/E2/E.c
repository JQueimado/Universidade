#include <stdio.h>
#include <stdlib.h>

/******************** header ************************/

/** <Const> **/

#define HASH(e, i, s) (e+i) % s;
#define HASH_SIZE(s) s + (s * 0.25);

/** </Const> **/

/** <Route> **/

struct route
{

    unsigned char s1;
    unsigned char s2;
    unsigned char s3;

    unsigned char i;

};

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

/** </Route> **/

/** <Hash> **/

/** hash_code( route ) **/
int hash_code_1( struct route * in )
{

    return ( in->s1 * in->s2 * in->s3 );

}

int hash_code_2( struct route * in )
{

    return ( in->s1 + in->s2 + in->s3 );

}

/** hash_insert( hash, size, element ) **/

void hash_insert (struct route ** hash, int s, struct route *elm ){

    int i = 0;

    int raw_h = hash_code_1(elm);

    int h = HASH( raw_h, i, s );

    int fh = h;

    for (i = 0; hash[h] != NULL; i++){
     
        if ( h == fh && i > 0){
         
            raw_h = hash_code_2(elm);

            fh = HASH( raw_h, i, s );

        }

        h = HASH( raw_h, i, s );
    
    }

    printf("hashed at: %d\n", h);

    hash[h] = elm;

}

/** </Hash> **/


/***************************************************/

int main ( void )
{

    int n = 0;

    scanf("%d",&n);

    short a, b, c, intf;

    int hash_size = HASH_SIZE(n);

    printf("hash_size: %d\n", hash_size);

    struct route ** hash = malloc( sizeof(struct route) * hash_size );

    short def_inf = -1;

    for (int i = 0; i<n; i++){

        scanf("%hu.%hu.%hu.0 %hu", &a, &b, &c, &intf);

        if( a==0 && b==0 && c==0)
            def_inf = intf;

        struct route * temp = new_route((unsigned char) a, (unsigned char) b, (unsigned char) c, intf);

        hash_insert(hash, hash_size, temp);

    }

    //scanf("%hu.%hu.%hu.0 %hu", &a, &b, &c, &intf);

    return 0;

}