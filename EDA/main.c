#include <stdio.h>
#include <stdlib.h>

#include "Struct/trie.h"
#include "Struct/User.h"
#include "Struct/SocialNet.h"

int main()
{
    struct SocialNet *socialnet = new_SocialNet();
	//char input;
	//char nick[5];
	char name[25];
    char nick[25];
	//struct User *user=new_User(nick,name);
    char entrada;

    while(scanf("%c",&entrada))
    {
        if(entrada=='U')
        {
            scanf("%s %s",nick,name);
            struct User *user=new_User(nick,name);
            criar_utilizador( socialnet ,nick,name,user); 
        }
        if(entrada=='R')
        {
            scanf("%s",nick);
            struct User *user=new_User(nick,name);
            remover_utilizador(socialnet,nick,name,user);
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
