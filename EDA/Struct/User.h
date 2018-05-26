		
/*Comflit avoider*/
#ifndef _Process_
#define _Process_

#include <stdlib.h>
#include <stdbool.h>

#define MAX_NICK_SIZE 5
#define MAX_USER_SIZE 25

#define ERROR 1
#define NORMAL 0

/**Class**/
struct User
{
	
	char nick[MAX_NICK_SIZE +1];
	char name[MAX_USER_SIZE];

};

/**Methods**/
int set_nick( struct User *user , char ni[] ){

	/*Checks input nickname*/
	int count = 0;


	for (int i = 0; i <=MAX_NICK_SIZE ; i++)
	{

		if ( (ni[ i ] == '\0') && ( i == MAX_NICK_SIZE  ) )
		{

			return 1;

		}

	for (int i = 0; ni[ i ] != '\0'; i++)
	{
		
		if ( !( ( ni[ i ] >= 97 && ni[ i ] <= 122) || ( ni[ i ] >= 65 && ni[ i ] <= 90) || ( ni[ i ] >= 48 && ni[ i ] <= 57) ) )
		{
			
			return ERROR;

		}

		count += 1;

	}

	/*sets User Nick*/
	for( int i = 0; ni[ i ] != '\0'; i++ )
	{

		user->nick[ i ] = ni[ i ];

	}

	return NORMAL;

}

int set_name( struct User *user , char na[] )
{

	/*Checks username size*/
	for (int i = 0; na[ i ] != '\0' ; i++)
	{
		
		if ( i > MAX_USER_SIZE)
		{
		
			return ERROR;
		
		}

	}

	/*Sets Username*/
	for( int i = 0; na[ i ] != '\0'; i++ )
	{

		user->name[ i ] = na[ i ];

	}

	return NORMAL;

}

struct User *new_User( char ni[] , char na[] )
{

	struct User *temp = malloc( sizeof( struct User ) );

	if( set_nick( temp , ni ) != 0 )
		return NULL;

	if( set_name( temp , na ) != 0 )
		return NULL;

	return temp;  

}


#endif
