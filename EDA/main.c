#include <stdio.h>
#include <stdlib.h>

#include "Struct/trie.h"
#include "Struct/User.h"

void criar_utilizador(struct trie *tnick,struct trie *tnome,char nick[],char nome[],struct User *user)
{
    printf("consegui!\n");
    if(trie_find(tnick,nick)) //retorna 1 se o nick ja existir
    {
        //printf("+ nick %s usado previamente",nick);
    }
    else 
    {
        // verifica as condicoes do nick e do nome
        printf("tb consegui!\n");
        if(set_nick(user , nick) && set_name(user, nome))

        {
            printf("eu tb!");
            trie_insert(tnick,nick);
            trie_insert(tnome,nome);
          //  printf("+ utilizador %s criado",nick); 
        }
        else {
            printf("Eu sou um conas!");
        }
    }


}


int main()
{
	//char input;
	char nick[6]="miguel";
	char name[7]="joaquim";
	struct User *user=new_User(nick,name);
   
    struct trie *tnick=trie_new();
    struct trie *tnome=trie_new();

    criar_utilizador(tnick,tnome,nick,name,user);
    /*
    trie_insert(nick,"miguel");
    trie_insert(nick,"joaquim");
    trie_insert(nick,"asd");
    printf("%d\n",trie_find(nick,"miguel"));
    printf("%d\n",trie_find(nick,"asd"));
    printf("%d\n",trie_find(nick,"cona"));
    printf("%d\n",trie_count(nick));
    printf("%d\n",trie_count(nick));
    printf("Apagou:%d\n",trie_delete(nick,"joaquim"));
    */


    


}
