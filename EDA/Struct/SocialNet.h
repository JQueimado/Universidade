
#ifndef _SocialNet_
#define _SocialNet_

/*includes*/
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "Grafos.h"
#include "trie.c"

/*consts*/

/****Class SocialNet****/
struct SocialNet
{
	
	struct Grafo *grafo;
	struct trie *tnome;
	struct trie *tnick;

};

struct SocialNet *new_SocialNet(){

    struct SocialNet *temp = malloc( sizeof( struct SocialNet ) );
    temp->grafo = new_Grafo();
    temp->tnome = trie_new();
    temp->tnick = trie_new();
    return temp;
}

//falta corrigir o segmentation fault qd se mete U Zero7 Spectre
void criar_utilizador(struct SocialNet *socialnet , char nome[] , char nick[], struct User *user)
{
	struct trie *tnick = socialnet->tnick;
	struct trie *tnome = socialnet->tnome;

    user=new_User(nick,nome);
    if(trie_find(tnick,nick)) //retorna 1 se o nick ja existir
    {
        printf("+ nick %s usado previamente\n",nick);
    }
    else 
    {
        // verifica as condicoes do nick e do nome
        if(user!=NULL)

        {
            //printf("eu tb!\n");
            trie_insert(tnick,nick);
            trie_insert(tnome,nome);
            printf("+ utilizador %s criado\n",nick); 
        }
        else {
            printf("Verifica se o nick e o nome estao dentro das condições!\n");
        }
    }


}

//resolver segmentation fault
void remover_utilizador(struct SocialNet *socialnet, char nick[],char nome[],struct User *user)
{
    struct trie *tnick = socialnet->tnick;

    user=new_User(nick,nome);
    if(trie_find_removed(tnick,nick) || !trie_find(tnick,nick))
    {
        printf("+ utilizador %s inexistente\n",nick);
    }
    else 
    {
        trie_delete(tnick,nick);
        printf("+ utilizador %s removido\n",nick);
    }
}


#endif
