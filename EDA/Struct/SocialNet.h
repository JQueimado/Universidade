
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
void criar_utilizador(struct SocialNet *socialnet , char nick[] , char nome[], struct User *user)
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
    //printf("asd\n");
    user=new_User(nick,nome);
    if(trie_find_removed(tnick,nick) || !trie_find(tnick,nick))
    {
        printf("+ utilizador %s inexistente\n",nick);
    }
    else 
    {
        printf("+ utilizador %s removido\n",nick);
        trie_delete(tnick,nick);
    }
}

void seguir_utilizador(struct SocialNet *socialnet,char nick1[],char nick2[],char nome1[],char nome2[],struct User *user1,struct User *user2)
{
    struct trie *tnick=socialnet->tnick;
    struct Grafo *grafo=socialnet->grafo;
    user1=new_User(nick1,nome1);
    user2=new_User(nick2,nome2);
    struct Vertice *vertice1;
    struct Vertice *vertice2;
    vertice1=grafo_get_vertice_by_name(grafo,nick1);
    vertice2=grafo_get_vertice_by_name(grafo,nick2);
    if(trie_find_removed(tnick,nick1) || !trie_find(tnick,nick1))
    {
        printf("+ utilizador %s inexistente\n",nick1);
    }
    else if(trie_find_removed(tnick,nick2) || !trie_find(tnick,nick2))
    {
        printf("+ utilizador %s inexistente\n",nick2);
    }
   // else if() //falta fazer uma função para verficar se há conexao entre o vertice 1 e o vertice 2
    else if(grafo_check_connection(grafo,vertice1,vertice2))
    {
        //cria vertice para nick1 e vertice para nick2
       /* grafo_insert_vertice(grafo,user1);
        grafo_insert_vertice(grafo,user2);
        
        grafo_insert_conection(grafo,vertice1,vertice2);
        printf("+ utilizador %s segue %s\n",nick1,nick2);*/
        printf("+ utilizador %s segue %s",nick1,nick2);
    }



}

void deixarseguir_utilizador(struct SocialNet *socialnet,char nick1[],char nick2[],char nome1[],char nome2[],struct User *user1,struct User *user2)
{
    struct trie *tnick=socialnet->tnick;
    struct Grafo *grafo=socialnet->grafo;
    user1=new_User(nick1,nome1);
    user2=new_User(nick2,nome2);
    if(trie_find_removed(tnick,nick1))
    {
        printf("+ utilizador %s inexistente\n",nick1);
    }
    else if(trie_find_removed(tnick,nick2))
    {
        printf("+ utilizador %s inexistente\n",nick2);
    }
    //falta verificar se um utilizador segue outro(funcao da conexao entre 1 vertice e outro)
   
}

bool dump(struct SocialNet *socialnet)
{

    if (socialnet == NULL)
    {

        return false;

    }

    struct Grafo *grafo = socialnet->grafo;

    FILE *file_user = fopen(NET_FILE_NAME , "w");
    grafo_dump_folows(grafo, file_user);
    
    return true;

}

#endif
