
#include "../Struct/trie.h"

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

	struct trie *t = trie_new();

	trie_insert(t , "EUQUEROECONASsssss07");

	if (trie_find(t, "EUQUEROECONASsssss07"))
		puts("TA BOM CARALHO");

	return 0;
}