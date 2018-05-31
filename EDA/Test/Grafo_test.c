#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../Struct/Grafos.h"
#include "../Struct/User.h"
void Grafo_Testing()
{

	struct Grafo *grafo_test = new_Grafo();

	/*insert users*/

	struct User *user1 = new_User( "Cona1" , "cona" );
	struct User *user2 = new_User( "Cona2" , "cona" );
	struct User *user3 = new_User( "Cona3" , "cona" );
	struct User *user4 = new_User( "Cona4" , "cona" );
	struct User *user5 = new_User( "Cona5" , "cona" );

	int i = grafo_insert_vertice( grafo_test , user1);
	i += grafo_insert_vertice( grafo_test , user2);
	i += grafo_insert_vertice( grafo_test , user3);
	i += grafo_insert_vertice( grafo_test , user4);
	i += grafo_insert_vertice( grafo_test , user5);


	if (i != 0)
	{
		puts("something went wrong");
	}

	grafo_print_all(grafo_test);

	/*Create conections*/
	struct Vertice *v1 = grafo_get_vertice_at(grafo_test , 0);
	struct Vertice *v2 = grafo_get_vertice_at(grafo_test , 1);
	struct Vertice *v3 = grafo_get_vertice_at(grafo_test , 2);
	struct Vertice *v4 = grafo_get_vertice_at(grafo_test , 3);

	grafo_insert_conection(grafo_test , v1 ,v2 );
	grafo_insert_conection(grafo_test , v1 ,v3 );
	grafo_insert_conection(grafo_test , v1 ,v4 );
	grafo_insert_conection(grafo_test , v2 ,v1 );
	grafo_insert_conection(grafo_test , v3 ,v2 );

	grafo_print_conections_at(grafo_test, 0);
	grafo_print_conections_at(grafo_test, 1);
	grafo_print_conections_at(grafo_test, 2);
	grafo_print_conections_at(grafo_test, 3);
	grafo_print_conections_at(grafo_test, 4);

	/*find user*/
	puts("");
	struct Vertice *v5 =  grafo_get_vertice_by_name( grafo_test, "Cona1");
	printf("%s\n", v5->user->nick );


}

int main()
{

	Grafo_Testing();

}
