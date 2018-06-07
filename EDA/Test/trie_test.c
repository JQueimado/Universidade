
#include "../Struct/trie.h"

int main()
{
	

	struct trie *t = trie_new();

	trie_insert(t , "EUQUERO7CONAS");

	if (trie_find(t, "EUQUERO7CONAS"))
	{
		puts("TA BOM CARALHO");
	}


	return 0;
}