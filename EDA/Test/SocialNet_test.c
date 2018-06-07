
#include "../Struct/SocialNet.h"
#include "../Struct/User.h"
#include "../Struct/trie.h"

void Dump_test()
{

	struct SocialNet *socialnet_test = new_SocialNet();

	struct User *u0 = new_User("Test0", "t0");
	struct User *u1 = new_User("Test1", "t1");
	struct User *u2 = new_User("Test2", "t2");
	struct User *u3 = new_User("Test3", "t3");
	struct User *u4 = new_User("Test4", "t4");
	struct User *u5 = new_User("Test5", "t5");
	struct User *u6 = new_User("Test6", "t6");
	struct User *u7 = new_User("Test7", "t7");
	struct User *u8 = new_User("Test8", "t8");
	struct User *u9 = new_User("Test9", "t9");

	criar_utilizador(socialnet_test, u0);
	criar_utilizador(socialnet_test, u1);
	criar_utilizador(socialnet_test, u2);
	criar_utilizador(socialnet_test, u3);
	criar_utilizador(socialnet_test, u4);
	criar_utilizador(socialnet_test, u5);
	criar_utilizador(socialnet_test, u6);
	criar_utilizador(socialnet_test, u7);
	criar_utilizador(socialnet_test, u8);
	criar_utilizador(socialnet_test, u9);

	seguir_utilizador(socialnet_test , u0, u1);
	seguir_utilizador(socialnet_test , u0, u2);
	seguir_utilizador(socialnet_test , u0, u3);
	seguir_utilizador(socialnet_test , u0, u4);
	seguir_utilizador(socialnet_test , u0, u5);
	seguir_utilizador(socialnet_test , u0, u6);
	seguir_utilizador(socialnet_test , u0, u7);
	seguir_utilizador(socialnet_test , u0, u8);
	seguir_utilizador(socialnet_test , u0, u9);
	seguir_utilizador(socialnet_test , u1, u2);
	seguir_utilizador(socialnet_test , u1, u4);
	seguir_utilizador(socialnet_test , u2, u3);
	seguir_utilizador(socialnet_test , u3, u1);
	seguir_utilizador(socialnet_test , u4, u1);
	seguir_utilizador(socialnet_test , u5, u1);
	seguir_utilizador(socialnet_test , u6, u1);

	struct trie *t = socialnet_test->tnome;

	if(trie_find(t , "t0"))
		puts("found");

	dump(socialnet_test);

	struct SocialNet * socialnet_test_2 = unpack();

	trie_print(socialnet_test_2->tnick);

}

int main()
{
	
	Dump_test();

	return 0;
}