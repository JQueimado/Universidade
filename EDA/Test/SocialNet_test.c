
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
	seguir_utilizador(socialnet_test ,"test0","test2","t0","t2",u0,u2);
	seguir_utilizador(socialnet_test ,"test0","test3","t0","t3",u0,u3);
	seguir_utilizador(socialnet_test ,"test0","test4","t0","t4",u0,u4);
	seguir_utilizador(socialnet_test ,"test0","test5","t0","t5",u0,u5);
	seguir_utilizador(socialnet_test ,"test0","test6","t0","t6",u0,u6);
	seguir_utilizador(socialnet_test ,"test0","test7","t0","t7",u0,u7);
	seguir_utilizador(socialnet_test ,"test0","test8","t0","t8",u0,u8);
	seguir_utilizador(socialnet_test ,"test0","test9","t0","t9",u0,u9);
	seguir_utilizador(socialnet_test ,"test1","test2","t1","t2",u1,u2);
	seguir_utilizador(socialnet_test ,"test1","test4","t1","t4",u1,u4);
	seguir_utilizador(socialnet_test ,"test2","test3","t2","t3",u2,u3);
	seguir_utilizador(socialnet_test ,"test3","test1","t3","t1",u3,u1);
	seguir_utilizador(socialnet_test ,"test4","test1","t4","t1",u4,u1);
	seguir_utilizador(socialnet_test ,"test5","test1","t5","t1",u5,u1);
	seguir_utilizador(socialnet_test ,"test6","test1","t6","t1",u6,u1);


	dump(socialnet_test);
}

int main()
{
	
	Dump_test();

	return 0;
}