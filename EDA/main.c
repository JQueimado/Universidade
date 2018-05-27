#include <stdio.h>
#include <stdlib.h>

#include "Struct/trie.h"
#include "Struct/User.h"
//falta corrigir o segmentation fault qd se mete U Zero7 Spectre
void criar_utilizador(struct trie *tnick,struct trie *tnome,char nick[],char nome[],struct User *user)
{
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
void remover_utilizador(struct trie *tnick,struct trie *tnome,char nick[],char nome[],struct User *user)
{
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





int main()
{
	//char input;
	//char nick[5];
	char name[25];
    char nick[25];
	//struct User *user=new_User(nick,name);
    char entrada;
    struct trie *tnick=trie_new();
    struct trie *tnome=trie_new();
    while(scanf("%c",&entrada))
    {
        if(entrada=='U')
        {
            scanf("%s %s",nick,name);
            struct User *user=new_User(nick,name);
            criar_utilizador(tnick,tnome,nick,name,user); 
        }
        if(entrada=='R')
        {
            scanf("%s",nick);
            struct User *user=new_User(nick,name);
            remover_utilizador(tnick,tnome,nick,name,user);
        }
        
    } 
    //scanf("%s %s",nick,name);
    //struct User *user=new_User(nick,name);
    //criar_utilizador(tnick,tnome,nick,name,user);

    //printf("%d\n",set_nick(user,nick));
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


    return 0;


}
