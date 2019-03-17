#ifndef ROUTING_TABLE
#define ROUTING_TABLE

#include <stdlib.h>

/* route */

struct route
{

    char ip1;
    char ip2;
    char ip3;
    char ip4;

    char intf;

}; 

struct route * route_const(char n1, char n2, char n3, char n4, char i)
{

    struct route *temp = malloc( sizeof( struct route ) );

    temp->ip1 = n1;
    temp->ip2 = n2;
    temp->ip3 = n3;
    temp->ip4 = n4;

    temp->intf = i;

    return temp;

}


#endif
