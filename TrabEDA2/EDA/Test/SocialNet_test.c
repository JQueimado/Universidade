
#include <stdlib.h>
#include <stdio.h>

#include "../Struct/SocialNet.h"
/*#include "../Struct/User.h"*/
/*#include "../Struct/trie.h"*/

void Dump_test()
{

	struct SocialNet *socialnet_test = new_SocialNet();
	
	criar_utilizador(socialnet_test, "Test0", "t0");
	criar_utilizador(socialnet_test, "Test1", "t1");
	criar_utilizador(socialnet_test, "Test2", "t2");
	criar_utilizador(socialnet_test, "Test3", "t3");
	criar_utilizador(socialnet_test, "Test4", "t4");
	criar_utilizador(socialnet_test, "Test5", "t5");
	criar_utilizador(socialnet_test, "Test6", "t6");
	criar_utilizador(socialnet_test, "Test7", "t7");
	criar_utilizador(socialnet_test, "Test8", "t8");
	criar_utilizador(socialnet_test, "Test9", "t9");

	criar_utilizador(socialnet_test, "Test0", "t0");

	puts("CONAS");

	seguir_utilizador(socialnet_test , "Test0", "Test1");
	seguir_utilizador(socialnet_test , "Test0", "Test2");
	seguir_utilizador(socialnet_test , "Test0", "Test3");
	seguir_utilizador(socialnet_test , "Test0", "Test4");
	seguir_utilizador(socialnet_test , "Test0", "Test5");
	seguir_utilizador(socialnet_test , "Test0", "Test6");
	seguir_utilizador(socialnet_test , "Test0", "Test7");
	seguir_utilizador(socialnet_test , "Test0", "Test8");
	seguir_utilizador(socialnet_test , "Test0", "Test9");
	seguir_utilizador(socialnet_test , "Test1", "Test2");
	seguir_utilizador(socialnet_test , "Test1", "Test4");
	seguir_utilizador(socialnet_test , "Test2", "Test3");
	seguir_utilizador(socialnet_test , "Test3", "Test1");
	seguir_utilizador(socialnet_test , "Test4", "Test1");
	seguir_utilizador(socialnet_test , "Test5", "Test1");
	seguir_utilizador(socialnet_test , "Test6", "Test1");


	puts("\n");

}

int main()
{
	
	Dump_test();

	return 0;
}