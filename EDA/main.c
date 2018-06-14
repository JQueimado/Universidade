#include <stdio.h>
#include <stdlib.h>

#include "Struct/User.h"
#include "Struct/SocialNet.h"
#include "Struct/hash.h"

int main()
{

    struct SocialNet *socialnet = new_SocialNet();

    unpack(socialnet);

	//char input;
	//char nick[5];
	char name[25];
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

    return 0;
}

/*int main()
{

    freopen("Testes/A_out.txt", "a", stdout);
    freopen("Testes/A2_in.txt", "r", stdin);

    //freopen("Testes/B_out.txt", "a", stdout);

    main_1();

    return 0;
    
}
*/