		
/*Comflit avoider*/
#ifndef _Process_
#define _Process_

#include <stdlib.h>
#include <stdbool.h>

#define MAX_NICK_SIZE 5
#define MAX_USER_SIZE 25

struct User{
	
	char nick[MAX_NICK_SIZE + 1];
	char name[MAX_USER_SIZE + 1];

};

int set_nick( struct User *user , char ni[] ){

	bool lc_flag = FALSE;
	bool hc_flag = FALSE;
	bool num_flag = FALSE;

	for (int i = 0; i < MAX_NICK_SIZE + 1; i++){

		
		if ( (ni[ i ] == '/0') && ( i != MAX_NICK_SIZE ) ){

			return 1;

		}

		if ( !(lc_flag) && ( ni[ i ] >= 97 && ni[ i ] <= 122) ){

			lc_flag = TRUE;

		}

		if ( !(hc_flag) && ( ni[ i ] >= 65 && ni[ i ] <= 90) ){

			hc_flag = TRUE;

		}

		if ( !(num_flag) && ( ni[ i ] >= 48 && ni[ i ] <= 57) ){

			num_flag = TRUE;

		}

		if ( !( ( ni[ i ] >= 97 && ni[ i ] <= 122) || ( ni[ i ] >= 65 && ni[ i ] <= 90) || ( ni[ i ] >= 48 && ni[ i ] <= 57) ) ){
			
			return 1;

		}

	}

	if ( !( lc_flag && hc_flag && num_flag ) ){

		return 1;

	}

	user->nick = ni;
	return 0;

}

int set_name( struct User *user , char na[] ){

	for (int i = 0; i < MAX_USER_SIZE +1; ++i){

		if ( (ni[ i ] == '/0') && ( i > MAX_USER_SIZE ) ){

			return 1;

		}
	
	}

	user->name = na;
	return 0;

}

struct User *new_User( char ni[] , char na[] ){

	struct User *temp = malloc( sizeof( struct User ) );

	if( set_nick( temp , ni ) != 0 )
		return NULL;

	if( set_name( temp , na ) != 0 )
		return NULL;

	return temp;  

}


#endif