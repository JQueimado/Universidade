
#include "../Struct/trie.h"
#include "../Struct/User.h"
int main()
{
	
/*
	printf(" a pos de %c e %d\n", '1', pos('1'));
	printf(" a pos de %c e %d\n", 'a', pos('a'));
	printf(" a pos de %c e %d\n", 'A', pos('A'));
	printf(" a pos de %c e %d\n", 'D', pos('D'));
	printf(" a pos de %c e %d\n", 'd', pos('d'));
	printf(" a pos de %c e %d\n", '9', pos('9'));

	printf("%d\n" , 'a');

	printf(" a pos de %d e %c\n", 1, to_char(1));
	printf(" a pos de %d e %c\n", 0, to_char(0));
	printf(" a pos de %d e %c\n", 10, to_char(10));
*/
	struct User *user1;
	struct User *user2;
	struct User *user3;
	struct User *user4;
	
	struct trie *t = trie_new();
	user1=new_User("EUQUEROECONASsssss07","cona1");
	user2=new_User("n0000","cona1");
	user3=new_User("vnXJm","cona1");
	user4=new_User("76Tpz","cona1");
	

	trie_insert(t , "EUQUEROECONASsssss07",user1);

	trie_insert(t , "n0000",user2);
	trie_insert(t,"vnXJm",user3);
	trie_insert(t,"76Tpz",user4);


	if (trie_find(t, "EUQUEROECONASsssss07") && trie_find(t,"n0000") && trie_find(t,"vnXJm") && trie_find(t,"76Tpz") )
		puts("TA BOM CARALHO");


	printf(" a pos de %d e %c\n", 10, to_char(10));
	printf(" a pos de %c e %d\n", 't', pos('t'));
	printf("a pos de %c e %d\n",'A',pos('A'));
	printf("a pos de %c e %d\n",'a',pos('a'));




	return 0;
}