
#include "../Struct/SocialNet.h"
#include "../Struct/User.h"

void Dump_test()
{

	struct SocialNet *socialnet_test = new_SocialNet();

	struct User *u0 = new_User("test0", "t0");
	struct User *u1 = new_User("test1", "t1");
	struct User *u2 = new_User("test2", "t2");
	struct User *u3 = new_User("test3", "t3");
	struct User *u4 = new_User("test4", "t4");
	struct User *u5 = new_User("test5", "t5");
	struct User *u6 = new_User("test6", "t6");
	struct User *u7 = new_User("test7", "t7");
	struct User *u8 = new_User("test8", "t8");
	struct User *u9 = new_User("test9", "t9");

	criar_utilizador(socialnet_test, "test0", "t0", u0);
	criar_utilizador(socialnet_test, "test1", "t1", u1);
	criar_utilizador(socialnet_test, "test2", "t2", u2);
	criar_utilizador(socialnet_test, "test3", "t3", u3);
	criar_utilizador(socialnet_test, "test4", "t4", u4);
	criar_utilizador(socialnet_test, "test5", "t5", u5);
	criar_utilizador(socialnet_test, "test6", "t6", u6);
	criar_utilizador(socialnet_test, "test7", "t7", u7);
	criar_utilizador(socialnet_test, "test8", "t8", u8);
	criar_utilizador(socialnet_test, "test9", "t9", u9);

	seguir_utilizador(socialnet_test ,"test0","test1","t0","t1",u0,u1);

	dump(socialnet_test);
}

int main()
{
	
	Dump_test();

	return 0;
}