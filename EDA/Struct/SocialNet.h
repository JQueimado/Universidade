
#ifndef _SocialNet_
#define _SocialNet_

/*includes*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "Grafos.h"
#include "trie.h"

/*consts*/
#define NET_FILE_NAME "Net.txt"
#define USER_FILE_NAME "User_data.txt"

/****Class SocialNet****/
struct SocialNet
{
	
	struct Grafo *grafo;
	struct trie *tnome;
	struct trie *tnick;

};
/*Constructor*/
struct SocialNet *new_SocialNet(){

    struct SocialNet *temp = malloc( sizeof( struct SocialNet ) );
    temp->grafo = new_Grafo();
    temp->tnome = trie_new();
    temp->tnick = trie_new();
    return temp;
}

//falta corrigir o segmentation fault qd se mete U Zero7 Spectre
void criar_utilizador(struct SocialNet *socialnet,struct User *user)
{
	struct trie *tnick = socialnet->tnick;
	struct trie *tnome = socialnet->tnome;

    user=new_User(user->nick,user->name);
    if(trie_find(tnick,user->nick)) //retorna 1 se o nick ja existir
    {
        printf("+ nick %s usado previamente\n",user->nick);
    }
    else 
    {
        // verifica as condicoes do nick e do nome
        if(user!=NULL)

        {
            //printf("eu tb!\n");
            trie_insert(tnick,user->nick,user);
            trie_insert(tnome,user->name,user);
            printf("+ utilizador %s criado\n",user->nick); 
        }
        else {
            printf("Verifica se o nick e o nome estao dentro das condições!\n");
        }
    }


}


void remover_utilizador(struct SocialNet *socialnet,struct User *user)
{
    struct trie *tnick = socialnet->tnick;
    user=new_User(user->nick,user->name);
    if(trie_find_removed(tnick,user->nick)||!trie_find(tnick,user->nick))
    {
        printf("+ utilizador %s inexistente\n",user->nick);
    }
    else 
    {
        printf("+ utilizador %s removido\n",user->nick);
        trie_delete(tnick,user->nick);
    }
}

void seguir_utilizador(struct SocialNet *socialnet,struct User *user1,struct User *user2)
{
    struct trie *tnick=socialnet->tnick;
    struct Grafo *grafo=socialnet->grafo;
    user1=new_User(user1->nick,user1->name);
    user2=new_User(user2->nick,user2->name);
    struct Vertice *vertice1;
    struct Vertice *vertice2;
    vertice1=grafo_get_vertice_by_name(grafo,user1->nick);
    vertice2=grafo_get_vertice_by_name(grafo,user2->nick);
    if(trie_find_removed(tnick,user1->nick) || !trie_find(tnick,user1->nick))
    {
        printf("+ utilizador %s inexistente\n",user1->nick);
    }
    else if(trie_find_removed(tnick,user2->nick) || !trie_find(tnick,user2->nick))
    {
        printf("+ utilizador %s inexistente\n",user2->nick);
    }
   // else if() //falta fazer uma função para verficar se há conexao entre o vertice 1 e o vertice 2
    else if(grafo_check_connection(grafo,vertice1,vertice2))
    {
        //cria vertice para nick1 e vertice para nick2
       /* grafo_insert_vertice(grafo,user1);
        grafo_insert_vertice(grafo,user2);
        
        grafo_insert_conection(grafo,vertice1,vertice2);
        printf("+ utilizador %s segue %s\n",nick1,nick2);*/
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
        //grafo_print_connections_at(grafo,0);
        
    }
    //grafo_print_conections_at(grafo,0);
    //printf("%d\n",grafo_connection_count_check(grafo,vertice1));
   // grafo_connection_count(grafo,vertice1);



}

void deixarseguir_utilizador(struct SocialNet *socialnet,struct User *user1,struct User *user2)
{
    struct trie *tnick=socialnet->tnick;
    struct Grafo *grafo=socialnet->grafo;
    user1=new_User(user1->nick,user1->name);
    user2=new_User(user2->nick,user2->name);
    struct Vertice *vertice1;
    struct Vertice *vertice2;
    vertice1=grafo_get_vertice_by_name(grafo,user1->nick);
    vertice2=grafo_get_vertice_by_name(grafo,user2->nick);
    if(trie_find_removed(tnick,user1->nick))
    {
        printf("+ utilizador %s inexistente\n",user1->nick);
    }
    else if(trie_find_removed(tnick,user2->nick))
    {
        printf("+ utilizador %s inexistente\n",user2->nick);
    }
    else if(grafo_check_connection(grafo,vertice1,vertice2))
    {
        grafo_remove_conection(grafo, vertice1, vertice2);
        printf("+ %s deixou de seguir %s\n",user1->nick,user2->nick);
    }
    else {
        printf("+ utilizador %s nao segue %s\n",user1->nick,user2->nick);
    }
   
   
}

void enviar_mensagem(struct SocialNet *socialnet,struct User *user)
{
    printf("user->nick: %s\n",user->nick);
    printf("trie_find_user: %s\n",trie_find_user(socialnet->tnick,user->nick)->nick);
    if( trie_find_removed(socialnet->tnick,user->nick) || !trie_find(socialnet->tnick,user->nick))
    {
        printf("+ utilizador %s inexistente\n",user->nick);
    }
    else 
    {
        trie_find_user(socialnet->tnick,user->nick)->mensagem++;
    }

    printf("trie_find_user->mensagem: %d\n",trie_find_user(socialnet->tnick,user->nick)->mensagem);
}


void ler_mensagem(struct SocialNet *socialnet,struct User *user)
{
    if(trie_find_removed(socialnet->tnick,user->nick)) //falta fazer esta parte
    {
        printf("utilizador %s desativado\n",user->nick);
    }
    else if(!trie_find(socialnet->tnick,user->nick))
    {
        printf("+ utilizador %s inexistente\n",user->nick);
    }
    else if(grafo_connection_count(socialnet->grafo,grafo_get_vertice_by_name(socialnet->grafo, user->nick))==0)
    {
        printf("+ utilizador %s sem seguidos\n",user->nick);
    }
}


bool dump(struct SocialNet *socialnet)
{

    if (socialnet == NULL)
    {

        return false;

    }

    struct Grafo *grafo = socialnet->grafo;
    struct trie *t_nick = socialnet->tnick;

    /*Dump Data*/

    FILE *file_nick = fopen(USER_FILE_NAME , "w");
    trie_dump(t_nick , file_nick);
    fclose(file_nick);

    /*Dump net*/
    FILE *file_net = fopen(NET_FILE_NAME , "w");
    grafo_dump_folows(grafo, file_net);
    fclose(file_net);

    return true;

}

struct SocialNet *unpack()
{

    struct SocialNet *temp = new_SocialNet();

    /*Unpack Trie*/

    FILE *file_user = fopen(USER_FILE_NAME , "r");

    if (file_user == NULL)
    {
        return temp;
    }

    trie_unpack(temp->tnick , file_user);

    fclose(file_user);

    /*Unpack Grafo*/

    FILE *file_net = fopen(NET_FILE_NAME , "r" );

    if (file_net == NULL)
    {
        return new_SocialNet();
    }

    grafo_unpack(temp->grafo , file_net , temp->tnick);

    fclose(file_net);

    return temp;
}

#endif
