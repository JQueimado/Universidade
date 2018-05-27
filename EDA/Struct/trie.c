/* trie implementation, with arrays */
/* Fonte: slides do prof */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "trie.h"

#define ALPHABET_MIN 'a'
#define ALPHABET_MAX 'z'
#define ALPHABET_SIZE (ALPHABET_MAX - ALPHABET_MIN + 1)

#define POS(c)  ((c) - ALPHABET_MIN)	// character position in alphabet
#define CHAR(n) ((n) + ALPHABET_MIN)	// n-th alphabet character


/* trie node */
struct node {
  struct node *child[ALPHABET_SIZE];
  bool        word;
  bool apagou;
  struct node *parent;
};

/* trie */
struct trie {
  struct node *root;
};


/*
  Allocates and returns a new trie node.

  Assumes it is always possible to allocate memory for a new node.
*/
static struct node *node_new()
{
  struct node *node = malloc(sizeof(*node));

  node->word = false;
  for (int i = 0; i < ALPHABET_SIZE; ++i)
    node->child[i] = NULL;

  return node;
}


/* Frees a trie NODE. */
static void node_free(struct node *node)
{
  free(node);
}


/* Destroys the sub-trie with root NODE. */
static void node_destroy(struct node *node)
{
  if (node == NULL)
    return;

  for (int i = 0; i < ALPHABET_SIZE; ++i)
    node_destroy(node->child[i]);

  node_free(node);
}


/* Creates a new, empty trie. */
struct trie *trie_new()
{
  struct trie *trie = malloc(sizeof(struct trie));

  if (trie)
    trie->root = NULL;

  return trie;
}


/* Destroys trie T, freeing the memory it occupies. */
void trie_destroy(struct trie *t)
{
  node_destroy(t->root);

  free(t);
}


/* Checks whether trie T is empty. */
bool trie_empty(struct trie *t)
{
  return t->root == NULL;
}


/* Inserts word P into trie T. */
void trie_insert(struct trie *t, char p[])
{
  struct node *n;
  int i = 0;

  if (t->root == NULL)
    t->root = node_new();

  n = t->root;

  // follow the word down the trie as long as possible,
  // taking care not to go to a nonexisting node
  while (p[i] != '\0' && n->child[POS(p[i])] != NULL)
    {
      n = n->child[POS(p[i])];
      i++;
    }

  // insert the new suffix into the trie
  while (p[i] != '\0')
    {
      n->child[POS(p[i])] = node_new();
      n = n->child[POS(p[i])];

      i++;
    }

  n->word = true;
}
/*
Searches for word P in trie T.

   Returns true if it finds it, false otherwise.*/
bool trie_find(struct trie *t,char p[])
{
  struct node *n;
  int i=0;

  n=t->root;

  while(n!=NULL && p[i]!='\0')
  {
    n = n->child[POS(p[i])];
      

    i++;
  }

  return (n!=NULL && n->word);

}
 //Returns true if it finds a word that already was removed
 bool trie_find_removed(struct trie *t,char p[])
{
  struct node *n;
  int i=0;

  n=t->root;

  while(n!=NULL && p[i]!='\0')
  {
    n = n->child[POS(p[i])];
      

    i++;
  }

  return (n!=NULL && n->apagou);

}
/* Counts and returns the number of words in trie T */
int trie_count(struct trie *t) 
{
  struct node *n;
  int i;
  int count=0;
  n=t->root;
  for(i=0;i<ALPHABET_SIZE;i++)
    {
      if(n->child[i])
        count++;
    }
    return count;
}




/* Removes word P from trie T. */

bool trie_delete(struct trie *t, char p[])
{
  struct node *n;
  int i=0;


  n = t->root;

  while (p[i] != '\0' && n->child[POS(p[i])] != NULL)
    {
      n = n->child[POS(p[i])];
      i++;
    }

  if(n!=NULL && n->word)
  {
    n->word=true;
    n->apagou=true;

  }
  
  return n->apagou;



}







