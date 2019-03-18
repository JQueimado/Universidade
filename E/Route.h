#ifndef ROUTE
#define ROUTE

#include <stdlib.h>

/* Route */

struct route
{

    unsigned char s1;
    unsigned char s2;
    unsigned char s3;

    unsigned char i;

};

/* Route Constructor */

struct route * new_route( unsigned char n1, unsigned char n2, unsigned char n3, unsigned char intf);

/* Route Compare */

short route_compare( struct route * r1, struct route * r2 );

/* Route Swap */

void route_swap( struct route * list, int i, int j );

/* Route Sorter */

void sorter ( int size, struct route * list );

#endif