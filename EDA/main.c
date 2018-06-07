#include <stdio.h>
#include <stdlib.h>

#include "Struct/User.h"
#include "Struct/SocialNet.h"

int main()
{
    struct SocialNet *socialnet = new_SocialNet();
	//char input;
	//char nick[5];
	char name[25];
    char nametemp[25];
    char nick[5];
    char nicktemp[25];
	//struct User *user=new_User(nick,name);
    char entrada;

    while(scanf("%c",&entrada))
    {
        if(entrada=='U')
        {
            scanf("%s %[^\n]s",nick,name);
            //printf("Nick: %s Name:%s\n",nick,name);
            struct User *user=new_User(nick,name);
            criar_utilizador( socialnet,user); 
            //printf("Nick: %s Name:%s\n",nick,name);
        }
        if(entrada=='R')
        {
            //printf("cona\n");
            scanf("%s",nick);
            struct User *user=new_User(nick,name);
            remover_utilizador(socialnet,user);
        }
        if(entrada=='S')
        {
            scanf("%s %s",nick,nicktemp);
            struct User *user1=new_User(nick,name);
            struct User *user2=new_User(nicktemp,nametemp);
            seguir_utilizador(socialnet,user1,user2);
        }
        if(entrada=='D')
        {
            scanf("%s %s",nick,nicktemp);
            struct User *user1=new_User(nick,name);
            struct User *user2=new_User(nicktemp,nametemp);
            deixarseguir_utilizador(socialnet,user1,user2);

        }
        if(entrada=='P')
        {
            scanf("%s",nick);
            struct User *user=new_User(nick,name);
            enviar_mensagem(socialnet,user);
        }
        if(entrada=='L')
        {
            scanf("%s",nick);
            struct User *user=new_User(nick,name);
            ler_mensagem(socialnet,user);
        }
        if (entrada=='X')
        {
            return 1;
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
