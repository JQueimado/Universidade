		
/*Comflit avoider*/
#ifndef _Process_
#define _Process_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NICK_SIZE 5
#define MAX_USER_SIZE 25

#define ERROR 1
#define NORMAL 0

/**Class**/
struct User
{
	
	char nick[MAX_NICK_SIZE +1];
	char name[MAX_USER_SIZE];
	int mensagem;

};

/**Methods**/
int set_nick( struct User *user , char ni[] ){

	/*Checks input nickname*/
	int count = 0;

	for (int i = 0; ni[ i ] != '\0'; i++)
	{
		
		if ( !( ( ni[ i ] >= 97 && ni[ i ] <= 122) || ( ni[ i ] >= 65 && ni[ i ] <= 90) || ( ni[ i ] >= 48 && ni[ i ] <= 57) ) )
		{
			
			return ERROR;

		}
		
		count += 1;

	}

	if(count!=MAX_NICK_SIZE)
		return ERROR;



	/*sets User Nick*/
	int i = 0;

	while( ni[ i ] != '\0' )
	{

		user->nick[ i ] = ni[ i ];

		i++;

	}

	user->nick[i] = '\0'; 

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
	int i = 0;
	while( na[ i ] != '\0' )
	{

		user->name[ i ] = na[ i ];

		i++;

	}

	user->name[i] = '\0';

	return NORMAL;

}

/*compare 2 users*/
bool compare_user(struct User *u1 , struct User *u2)
{

	return strcmp(u1->nick , u2->nick) == 0;
}

/*Construtor*/
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