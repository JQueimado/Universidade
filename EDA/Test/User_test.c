#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>




#include "../Struct/User.h"

void User_Testing(){

	struct User *test_sub_1 = new_User( "miguel" , "i dont know" );

	struct User *test_sub_2 = new_User( "Mige3" , "i dont know" );

	struct User *test_sub_3 = new_User( "Hw" , "i dont know" );

	struct User *test_sub_4 = new_User( "HWR69" , "i dont know" );

	struct User *test_sub_5 = new_User( "&&££@" , "i dont know" );

	//struct User *test_sub_7 = new_User( "miguel32" , "i dont know" );
	
	new_User( "Puta1" , "Cona1" );
	new_User( "Puta2" , "Cona2" );
	new_User( "Puta3" , "Cona3" );
	new_User( "Puta4" , "Pila1" );
	new_User( "Puta5" , "Cona4" );
	new_User( "Puta6" , "Cona5" );
	new_User( "Puta7" , "Pila2" );
	new_User( "Puta8" , "Cona6" );


	struct User *test_sub_6 = new_User( "Hwr69" , "i dont know and i dont care AHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH" );

	if ( test_sub_1 != NULL)
	{

		printf("%s\n" , test_sub_1->nick);
 
	}
	else
	{

		puts("Something Went Wrong");
		
	}

	if ( test_sub_2 != NULL)
	{

		printf("%s\n" , test_sub_2->nick);
 
	}
	else
	{

		puts("Something Went Wrong");

	}

	if ( test_sub_3 != NULL)
	{

		printf("%s\n" , test_sub_3->nick);
 
	}
	else
	{

		puts("Something Went Wrong");

	}

	if ( test_sub_4 != NULL)
	{

		printf("%s\n" , test_sub_4->nick);
 
	}
	else
	{

		puts("Something Went Wrong");
	
	}

	if ( test_sub_5 != NULL)
	{

		printf("%s\n" , test_sub_5->nick);
 
	}
	else
	{

		puts("Something Went Wrong");

	}

	if ( test_sub_6 != NULL)
	{

		printf("%s\n" , test_sub_6->nick);
 
	}
	else
	{

		puts("Something Went Wrong");

	}

}

int main()
{

	User_Testing();
	return 0;

}
