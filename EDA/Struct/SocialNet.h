
#ifndef _SocialNet_
#define _SocialNet_

/*includes*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "Grafos.h"
#include "hash.h"
#include "User.h"

/*consts*/
#define NET_FILE_NAME "Net.txt"
#define USER_FILE_NAME "User_data.txt"
#define User_Data_File "User_Cache.txt"

/****Class SocialNet****/
struct SocialNet
{
    FILE *pointer;
	struct Grafo *grafo;
	struct Hash *hashnick;

};
/*Constructor*/
struct SocialNet *new_SocialNet(){

    struct SocialNet *temp = malloc( sizeof( struct SocialNet ) );
    
    temp->grafo = new_Grafo();

    temp->pointer = fopen(User_Data_File, "wb+");

    temp->hashnick = new_hash();

    return temp;
}

//Segmentation fault com o user
void criar_utilizador(struct SocialNet *socialnet , char nick[] , char name[])
{

    if(search(socialnet->hashnick, nick[0] , nick ) != NULL) //retorna 1 se o nick ja existir

    {
        printf("+ nick %s usado previamente\n",nick);
    }
    else 
    {
        struct User *user = new_User(nick , name , socialnet->pointer);
        // verifica as condicoes do nick e do nome
        if(user!=NULL)
        {
            //puts("cona3");

            //printf("eu tb!\n");
            //trie_insert(hashnick, nick, user);
            insert(socialnet->hashnick, user,nick[0]);
            //printf("%s\n",search(socialnet->hashnick, nick[0] , nick )->user->nick);
            printf("+ utilizador %s criado\n",nick); 
        }
        else {
            printf("Verifica se o nick e o nome estao dentro das condições!\n");
        }
    }
        //printf("Nick:%s\n",search(socialnet->hashnick, nick[0] , nick )->user->nick);

    /*
    trie_print(socialnet->tnick);
    */

}



void remover_utilizador(struct SocialNet *socialnet, char nick[])
{
    //struct userdados *hashnick = socialnet->hashnick;

    if( search(socialnet->hashnick, nick[0],nick)!=NULL && (search(socialnet->hashnick, nick[0],nick)->user->removed)==false)
    {
        printf("+ utilizador %s removido\n", nick);
        search(socialnet->hashnick, nick[0],nick)->user->removed=true;
    }
    else 
    {
        printf("+ utilizador %s inexistente\n", nick);
        /*printf("+ utilizador %s removido\n", nick);
        search(socialnet->hashnick, nick[0],nick)->user->removed=true;*/
    }
}

void seguir_utilizador(struct SocialNet *socialnet, char nick1[], char nick2[]) 
{
   // struct userdados *hashnick=socialnet->hashnick;
    struct Grafo *grafo=socialnet->grafo;
        
    struct userdados *ud1=search(socialnet->hashnick, nick1[0], nick1);
    struct userdados *ud2 = search(socialnet->hashnick, nick2[0],nick2);
    if(ud1 == NULL)
        {
            
            printf("+ utilizador %s inexistente\n",nick1);
            return ;

        }
    //struct User *user1 = ud1->user;
    else if(search(socialnet->hashnick, nick1[0], nick1)->user->removed)
    {
        
    
        printf("+ utilizador %s inexistente\n",nick1);
        return;
    }

    //struct userdados *ud2 = search(socialnet->hashnick, nick2[0],nick2);
    if(ud2 == NULL)
        {
            
            printf("+ utilizador %s inexistente\n",nick2);
            return;      

         }

    else if(search(socialnet->hashnick, nick2[0],nick2)->user->removed)
    {
        //struct User *user2 = ud2->user;
        
        printf("+ utilizador %s inexistente\n",nick2);
        return ;
    }



    struct User *user1 = ud1->user;
    struct User *user2 = ud2->user;

    

    struct Vertice *vertice1;
    struct Vertice *vertice2;
    
    vertice1=grafo_get_vertice_by_name(grafo,user1->nick);
    vertice2=grafo_get_vertice_by_name(grafo,user2->nick);
    
   
 
    if(grafo_check_connection(grafo,vertice1,vertice2))
    {
        
        printf("+ utilizador %s segue %s\n",user1->nick,user2->nick);
    }
    else if(grafo_connection_count_check(grafo,vertice1)) 
    {
        printf("+ utilizador %s segue o limite\n",user1->nick);
    }
    else {
        
        grafo_insert_vertice(grafo,user1);
        //printf("%d\n",grafo_insert_vertice(grafo,user1));
        grafo_insert_vertice(grafo,user2);
        //printf("%d\n",grafo_insert_vertice(grafo,user2));
        vertice1=grafo_get_vertice_by_name(grafo,user1->nick);
        vertice2=grafo_get_vertice_by_name(grafo,user2->nick);
        grafo_insert_conection(grafo,vertice1,vertice2);
        printf("+ %s passou a seguir %s\n",user1->nick,user2->nick);
      
    }
    



}

void deixarseguir_utilizador(struct SocialNet *socialnet, char nick1[], char nick2[])
{
    //struct userdados *hashnick=socialnet->hashnick;
    struct Grafo *grafo=socialnet->grafo;
    struct userdados *ud1=search(socialnet->hashnick, nick1[0], nick1);
    struct userdados *ud2 = search(socialnet->hashnick, nick2[0],nick2);
    if(ud1 == NULL)
        {
            
            printf("+ utilizador %s inexistente\n",nick1);
            return ;

        }
    //struct User *user1 = ud1->user;
    else if(search(socialnet->hashnick, nick1[0], nick1)->user->removed)
    {
        
    
        printf("+ utilizador %s inexistente\n",nick1);
        return;
    }

    //struct userdados *ud2 = search(socialnet->hashnick, nick2[0],nick2);
    if(ud2 == NULL)
        {
        
            printf("+ utilizador %s inexistente\n",nick2);
            return;      

         }

    else if(search(socialnet->hashnick, nick2[0],nick2)->user->removed)
    {
        //struct User *user2 = ud2->user;
        
        printf("+ utilizador %s inexistente\n",nick2);
        return ;
    }


    struct User *user1 = ud1->user;
    struct User *user2 = ud2->user;
    struct Vertice *vertice1;
    struct Vertice *vertice2;
    vertice1=grafo_get_vertice_by_name(grafo,user1->nick);
    vertice2=grafo_get_vertice_by_name(grafo,user2->nick);
    
    if(grafo_check_connection(grafo,vertice1,vertice2))
    {
        grafo_remove_conection(grafo, vertice1, vertice2);
        printf("+ %s deixou de seguir %s\n",user1->nick,user2->nick);
    }
    else {
        printf("+ utilizador %s nao segue %s\n",user1->nick,user2->nick);
    }
   
   
}

void enviar_mensagem(struct SocialNet *socialnet, char ni[])
{
    
    //printf("user->nick: %s user name: %s\n",trie_find_user(socialnet->tnick,user->nick)->nick,trie_find_user(socialnet->tnick,user->nick)->name);
    //printf("trie_find_user: %s\n",trie_find_user(socialnet->tnick,user->nick)->nick);

    struct userdados *ud1 = search(socialnet->hashnick, ni[0], ni);

    if(ud1 == NULL)
    {

        printf("+ utilizador %s inexistente\n", ni);
        return;

    }
    if(search(socialnet->hashnick, ni[0], ni)->user->removed)
    {
        printf("+ utilizador %s inexistente\n",ni);
        return;
    }
    struct User *user = ud1->user;

    send_msg(socialnet->grafo, user);

}

void ler_mensagem(struct SocialNet *socialnet, char nick[])
{   
    
    struct userdados *ud1=search(socialnet->hashnick, nick[0], nick);
    if(ud1 == NULL)
        {

            printf("+ utilizador %s inexistente\n",nick);
            return;

        }
    
    if (!read_msg(socialnet->grafo, ud1->user,socialnet->pointer))
    {
        printf("sem mensagens novas de %s (%s)\n", nick , nick);
    }

    read_msg(socialnet->grafo, ud1->user, socialnet->pointer);

    
}


void informacao(struct SocialNet *socialnet, char nick[])
{
    /*
    struct User arr[100];
    struct Grafo *grafo=socialnet->grafo;
    struct userdados *ud1=search(socialnet->hashnick, nick[0], nick);
    if(ud1 == NULL)
        {

            printf("+ utilizador %s inexistente\n",nick);
            return;

        }

    struct User *user1 = ud1->user;

    struct Vertice *vertice1;
    vertice1=grafo_get_vertice_by_name(grafo,user1->nick);
     grafo_get_conected_to(socialnet->grafo,vertice1,arr);
    struct User *user = NULL; //cona de procura
    
    struct Vertice *ver = grafo_get_vertice_by_name(nick);
    
    struct Vertice *ver = grafo_get_vertice_by_name(nick);

    if ( ver == NULL)
    {
        
    }

*/     
    

}
  

void dump(struct SocialNet *socialnet)
{
/*
    if (socialnet == NULL)
    {

        return false;

    }

    struct Grafo *grafo = socialnet->grafo;
    struct trie *t_nick = socialnet->tnick;

    puts("trie to be writen");
    trie_print(t_nick);
    puts("done");

    FILE *file_nick = fopen(USER_FILE_NAME , "w");
    trie_dump(t_nick , file_nick);
    fclose(file_nick);

    FILE *file_net = fopen(NET_FILE_NAME , "w");
    grafo_dump_folows(grafo, file_net);
    fclose(file_net);

    return true;
*/
}

void unpack()
{
/*
    struct SocialNet *temp = new_SocialNet();

    FILE *file_user = fopen(USER_FILE_NAME , "r");

    if (file_user == NULL)
    {
        return temp;
    }

    trie_unpack(temp->tnick , file_user);

    puts("unpacked trie");
    trie_print(temp->tnick);
    puts("done");

    fclose(file_user);

    FILE *file_net = fopen(NET_FILE_NAME , "r" );

    if (file_net == NULL)
    {
        return new_SocialNet();
    }

    grafo_unpack(temp->grafo , file_net , temp->tnick);

    fclose(file_net);

    return temp;
*/
}

#endif
