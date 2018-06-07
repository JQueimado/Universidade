/* trie implementation, with arrays */
/* Fonte: slides do prof */

#ifndef _trie_
#define _trie_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_MIN_HC 'A'
#define ALPHABET_MAX_HC 'Z'

#define ALPHABET_MIN_LC 'a'
#define ALPHABET_MAX_LC 'z'

#define ALPHABET_SIZE (ALPHABET_MAX_LC - ALPHABET_MIN_LC + 1)

#define NUMBERS_MIN '0'
#define NUMBERS_MAX '9'
#define NUMBERS_SIZE (NUMBERS_MAX - NUMBERS_MIN + 1)

#define NUMBER_MIN_POINT 0
#define ALPHABET_MIN_LC_POINT 10
#define ALPHABET_NIM_HC_POINT 26

#define ARRAY_SIZE (NUMBERS_SIZE + 2*ALPHABET_SIZE)

/* trie node */
struct node {
  struct node *child[ARRAY_SIZE];
  bool word;
  bool apagou;
  struct node *parent;
  struct User *user;
};

/* trie */
struct trie {
  struct node *root;
};


static struct node *node_new()
{
  struct node *node = malloc(sizeof(*node));

  node->word = false;
  for (int i = 0; i < ALPHABET_SIZE; ++i)
    node->child[i] = NULL;

  return node;
}

int pos(char c)
{

	if( c <= NUMBERS_MAX && c >= NUMBERS_MIN)
		return c - NUMBERS_MIN;

	if( c <= ALPHABET_MAX_LC && c >= ALPHABET_MIN_LC)
		return (c - ALPHABET_MIN_LC) + NUMBERS_SIZE;

	if( c <= ALPHABET_MAX_HC && c >= ALPHABET_MIN_HC)
		return (c - ALPHABET_MIN_HC) + NUMBERS_SIZE +ALPHABET_SIZE;

	return -1;

}

char to_char(int i)
{

	if( i >= NUMBER_MIN_POINT && i < ALPHABET_MIN_LC_POINT)
		return i + NUMBERS_MIN;

	if( i >= ALPHABET_MIN_LC_POINT && i < ALPHABET_NIM_HC_POINT)
		return (i - NUMBERS_SIZE) + ALPHABET_MIN_LC;

	if( i >= ALPHABET_NIM_HC_POINT && i < ARRAY_SIZE)
		return (i - NUMBERS_SIZE - ALPHABET_SIZE) + ALPHABET_MIN_HC;

	return '\0';

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
void trie_insert(struct trie *t, char p[],struct User *user)
{
  struct node *n;
  int i = 0;

  if (t->root == NULL)
    t->root = node_new();

  n = t->root;
  //user=new_User(user->nick,user->name);

  // follow the word down the trie as long as possible,
  // taking care not to go to a nonexisting node
  while (p[i] != '\0' && n->child[pos(p[i])] != NULL)
    {
      n = n->child[pos(p[i])];
      i++;
    }

  // insert the new suffix into the trie
  while (p[i] != '\0')
    {
      n->child[pos(p[i])] = node_new();
      n = n->child[pos(p[i])];

      i++;
    }

  n->word = true;
  n->user=user;
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
    n = n->child[pos(p[i])];
      

    i++;
  }

  return (n!=NULL && n->word);

}

struct User * trie_find_user(struct trie *t,char p[])
{
  struct node *n;
  int i=0;

  n=t->root;

  while(n!=NULL && p[i]!='\0')
  {
    n = n->child[pos(p[i])];
      

    i++;
  }


  return (n->user);

}
 //Returns true if it finds a word that already was removed
 bool trie_find_removed(struct trie *t,char p[])
{
  struct node *n;
  int i=0;

  n=t->root;

  while(n!=NULL && p[i]!='\0')
  {
    n = n->child[pos(p[i])];
      

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

  while (p[i] != '\0' && n->child[pos(p[i])] != NULL)
    {
      n = n->child[pos(p[i])];
      i++;
    }

  if(n!=NULL && n->word)
  {
    n->word=true;
    n->apagou=true;

  }
  
  return n->apagou;

}

void my_strcat(char dest[], char src[])
{

  int i = 0, j = 0;

  // percorre a primeira string até ao fim
  while (dest[i] != '\0')
    i++;

  // copia a segunda para o fim da primeira
  while (src[j] != '\0')
    {

      dest[i] = src[j];

      i++; j++;
    }

  // acrescenta o terminador
  dest[i] = '\0';

}

void trie_dump_visit(struct node *n , char name[], FILE *file)
{

  

}

void trie_dump(struct trie *t , FILE *file)
{

  struct node *n = t->root; 

  for (int i = 0; i < ALPHABET_SIZE; ++i)
  {
    /* code */
  }

}


#endif