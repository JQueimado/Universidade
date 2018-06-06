
#ifndef _SocialNet_
#define _SocialNet_

/*includes*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "Grafos.h"
#include "trie.c"

/*consts*/
#define NET_FILE_NAME "Net.txt"
#define NICK_FILE_NAME "Nick_data.txt"
#define NAME_FILE_NAME "Name_data.txt"

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
            trie_insert(tnick,user->nick);
            trie_insert(tnome,user->name);
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



bool dump(struct SocialNet *socialnet)
{

    if (socialnet == NULL)
    {

        return false;

    }

    struct Grafo *grafo = socialnet->grafo;
    struct trie *t_nick = socialnet->tnick;
    struct trie *t_nome = socialnet->tnome;

    /*Dump Data*/
    /*
    FILE *file_nick = fopen(NICK_FILE_NAME , "w");
    trie_dump(t_nick , file_nick);
    fclose(file_nick);
    */

    FILE *file_name = fopen(NAME_FILE_NAME , "w");
    trie_dump(t_nome , file_name);
    fclose(file_name);

    /*Dump net*/
    FILE *file_net = fopen(NET_FILE_NAME , "w");
    grafo_dump_folows(grafo, file_net);
    fclose(file_net);

    return true;

}

#endif
