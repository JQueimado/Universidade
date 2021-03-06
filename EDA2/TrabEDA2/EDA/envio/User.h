		
/*Comflit avoider*/
#ifndef _Process_
#define _Process_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NICK_SIZE 5
#define MAX_USER_SIZE 25

/**Class**/
struct User
{
	bool removed;
	char nick[MAX_NICK_SIZE +1];
	int pos;

};

/**Methods**/
bool ver_nick( char ni[] ){

	/*Checks input nickname*/
	int count = 0;

	for (int i = 0; ni[ i ] != '\0'; i++)
	{
		
		if ( !( ( ni[ i ] >= 97 && ni[ i ] <= 122) || ( ni[ i ] >= 65 && ni[ i ] <= 90) || ( ni[ i ] >= 48 && ni[ i ] <= 57) ) )
		{
			
			return false;

		}
		
		count += 1;

	}

	if(count!=MAX_NICK_SIZE)
		return false;

	/*Pass*/
	return true;

}

bool ver_name( char na[] )
{

	/*Checks username size*/
	int count = 0;
	while (na[ count ] != '\0')
	{
		
		count++;

	}

	if (count > MAX_USER_SIZE +1)
	{
		return false;
	}

	return true;

}

/*compare 2 users*/
bool compare_user(struct User *u1 , struct User *u2)
{

	return strcmp(u1->nick , u2->nick) == 0;
}

/*Writes User on file and returns file position*/
void write_file(struct User *user, char name[], FILE *pointer)
{
	
	fseek(pointer, 0, SEEK_END);

	user->pos = ftell(pointer);
	
	fwrite(name , MAX_USER_SIZE, 1, pointer);
	

}

char *get_name(struct User *user, FILE *pointer)
{	
	static char name[MAX_USER_SIZE +1];

	fseek(pointer, user->pos, SEEK_SET);

	fread(name , MAX_USER_SIZE + 1, 1, pointer);
	
	fseek(pointer, 0, SEEK_END);

	return name;
}

/*Construtor*/
struct User *new_User( char ni[] , char na[], FILE *pointer, bool remv)
{

	struct User *temp = malloc( sizeof( struct User ) );

	if( ver_nick(ni) )
	{

		strcpy(temp->nick, ni);

	}
	else
	{

		return NULL;

	}
	
	if (ver_name(na))
	{
		if (!remv)
			write_file(temp , na ,pointer);
		else
			temp->pos = -1;

	}
	else
	{

		return NULL;

	}

	temp->removed = remv;
	return temp; 

}


#endif