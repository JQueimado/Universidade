#include <stdio.h>
#include <stdlib.h>

#include "Struct/User.h"
#include "Struct/SocialNet.h"
#include "Struct/hash.h"

int main()
{

    struct SocialNet *socialnet = new_SocialNet();

    puts("cona");

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
            criar_utilizador( socialnet , nick , name ); 
            //printf("Nick: %s Name:%s\n",nick,name);
        }
        if(entrada=='R')
        {
            //printf("cona\n");
            scanf("%s",nick);
            remover_utilizador(socialnet , nick);
        }
        if(entrada=='S')
        {
            
            scanf("%s %s",nick,nicktemp);
            
            seguir_utilizador(socialnet, nick, nicktemp);
        
        }
        if(entrada=='D')
        {
            scanf("%s %s",nick,nicktemp);
            deixarseguir_utilizador(socialnet, nick, nicktemp);

        }
        if(entrada=='P')
        {
            scanf("%s",nick);
            enviar_mensagem(socialnet, nick);
        }
        if(entrada=='L')
        {
            scanf("%s",nick);
            ler_mensagem(socialnet, nick);
        }
        if(entrada=='I')
        {
            scanf("%s",nick);
            informacao(socialnet,nick);
        }
        if (entrada=='X')

        {

            dump(socialnet);
            return 0;


        }
        
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






/*
=======
}


int main()
{
    freopen("Testes/C1_in.txt", "r", stdin);
    puts("1");
    main_1();

    freopen("Testes/C2_in.txt", "r", stdin);
    puts("2");
    main_1();

    freopen("Testes/C3_in.txt", "r", stdin);
    puts("3");
    main_1();

    return 0;
}
