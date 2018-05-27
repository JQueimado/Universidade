/* trie interface */

#include <stdbool.h>

struct trie;

struct trie *trie_new(void);
void trie_destroy(struct trie *);

bool trie_empty(struct trie *);

bool trie_find(struct trie *, char []);
void trie_insert(struct trie *, char []);
bool trie_delete(struct trie *, char []);
bool trie_find_removed(struct trie *t,char p[]);

int trie_count(struct trie *);


