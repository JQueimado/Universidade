
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
#define CONE_FILE_NAME "Conect_data.txt"
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


/*Data User*/
struct DataUser 
{

    unsigned int msg_send;
    char nick[6];
    char name[26];

};

struct DataUser *new_DataUser(struct SocialNet *socialnet, struct User *user)
{

    struct DataUser *temp = malloc(sizeof(struct DataUser));
    
    strcpy(temp->nick, user->nick);
    
    if(user->removed)
    {

        temp->name[0] = '\0';

        temp->msg_send = -1;

    }
    else
    {
        strcpy(temp->name, get_name(user, socialnet->pointer) );
        
        struct Vertice *ver = grafo_get_vertice_by_name(socialnet->grafo, user->nick);

        if (ver == NULL)
        {
            temp->msg_send = 0;
        }
        else
        {
            temp->msg_send = ver->msg_send;
        }

    }

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
        struct User *user = new_User(nick , name , socialnet->pointer, false);
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

}



void remover_utilizador(struct SocialNet *socialnet, char nick[])
{
    //struct userdados *hashnick = socialnet->hashnick;

    if( search(socialnet->hashnick, nick[0],nick)!=NULL && (search(socialnet->hashnick, nick[0],nick)->user->removed)==false)
    {
        //printf("+ utilizador %s removido\n", nick);
        search(socialnet->hashnick, nick[0],nick)->user->removed=true;

        grafo_remove_vertice(socialnet->grafo ,grafo_get_vertice_by_name(socialnet->grafo,nick));
        printf("+ utilizador %s removido\n", nick);

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
    //puts("cona1");
    struct userdados *ud1=search(socialnet->hashnick, nick1[0], nick1);
    //puts("cona4");
    struct userdados *ud2 = search(socialnet->hashnick, nick2[0],nick2);
    //puts("cona5");
    if(ud1 == NULL)
        {
            //puts("cona6");
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
    //puts("cona6");
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

    //puts("cona7");

    struct User *user1 = ud1->user;
    struct User *user2 = ud2->user;
    //puts("cona8");
    

    struct Vertice *vertice1;
    struct Vertice *vertice2;
    //puts("cona9");
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
        struct Node *n = grafo_insert_conection(grafo,vertice1,vertice2);
        n->msg_rcv = vertice2->msg_send;
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
    else if (ud1->user->removed)
    {
        printf("+ utilizador %s inexistente\n",ni);
        return;
    }

    struct User *user = ud1->user;

    send_msg(socialnet->grafo, user);

}

void ler_mensagem(struct SocialNet *socialnet, char nick[])
{   
    
    //grafo_print_conections_at(socialnet->grafo, grafo_get_vertice_by_name(socialnet->grafo,nick)->pos);

    struct userdados *ud1=search(socialnet->hashnick, nick[0], nick);
    if(ud1 == NULL)
        {

            printf("+ utilizador %s inexistente\n",nick);
            return;

        }


    read_msg(socialnet, ud1->user, socialnet->pointer);

    
}

bool infor(struct Grafo *grafo,struct User *user, FILE *pointer)

{
    //puts("cona");
    struct Vertice *v=grafo_get_vertice_by_name(grafo,user->nick);
    if (v == NULL)
    {

        return false;

    }   
    struct Node *n=grafo->nodes[v->pos];
    if(n==NULL)
        return false;

    printf("utilizador %s (%s)\n",user->nick,get_name(n->ver->user, pointer));
    printf("%d mensagens, %d seguidores, segue %d utilizadores\n",n->ver->msg_send,count_conection_seguidores(grafo,n->ver),grafo_connection_count(grafo,n->ver));
    
    while(n->next_node != NULL)
    {

        n = n->next_node;
        
        printf("%s (%d lidas)\n",n->ver->user->nick, n->msg_rcv );
        
    }

    return true;
   

void informacao(struct SocialNet *socialnet, char nick[])
{
    
    struct userdados *ud1=search(socialnet->hashnick, nick[0], nick);
    if(ud1 == NULL)
        {

            printf("+ utilizador %s inexistente\n",nick);
            return;

        }
    if(search(socialnet->hashnick, nick[0], nick)->user->removed)
    {
        printf("+ utilizador %s inexistente\n",nick);
        return;
    }
   infor(socialnet->grafo,ud1->user,socialnet->pointer);

    
    

}
  
void hash_dump (struct Hash *hashtlb , struct SocialNet *socialnet, FILE *pointer){

    struct DataUser *duser;

    for(int i = 0; i<SIZE; i++) {
    
        if(hashtlb->hashArray[i] != NULL)
        {

            duser = new_DataUser(socialnet, hashtlb->hashArray[i]->user);

            fwrite(duser, sizeof(struct DataUser), 1, pointer);

        }
   
    }

}

/*Grafo Dump*/
struct DataConection 
{

    char nick1[6];
    char nick2[6];
    unsigned short msg_rcv;

};

void dump_connections(struct Grafo *grafo , struct Node *n, FILE *pointer)
{
    struct DataConection *Dc = malloc(sizeof(struct DataConection));

    strcpy(Dc->nick1, n->ver->user->nick);

    n = n->next_node;

    while( n != NULL)
    {

        strcpy(Dc->nick2, n->ver->user->nick);
        
        Dc->msg_rcv = n->msg_rcv;

        fwrite(Dc, sizeof(struct DataConection), 1, pointer);
        //printf("%s %s %d\n", Dc->nick1, Dc->nick2, Dc->msg_rcv);

        n = n->next_node;

    }

}

void grafo_dump (struct Grafo *grafo , struct SocialNet *socialnet, FILE *pointer)
{

    //grafo_print_all(grafo);

    int sp = 0;

    for (int i = 0; sp < grafo->size; i++)
    {
        if (grafo->nodes[i] != NULL)
        {
            dump_connections(grafo, grafo->nodes[i], pointer);
            sp++;
        }
    }

}

void dump(struct SocialNet *socialnet)
{

    FILE *userdata = fopen(USER_FILE_NAME, "wb");

    hash_dump(socialnet->hashnick, socialnet, userdata);

    fclose(userdata);

    FILE *conectdata = fopen(CONE_FILE_NAME, "wb");

    grafo_dump(socialnet->grafo, socialnet, conectdata);

    fclose(conectdata);

}

void hash_unpack(struct Hash *hashtlb , struct SocialNet *socialnet, FILE *in_pointer, FILE *cache_pointer)
{

    struct DataUser *temp = malloc(sizeof(struct DataUser)); 
    
    while(fread(temp, sizeof(struct DataUser), 1, in_pointer) == 1)
    {

        struct User *tempU = new_User(temp->nick, temp->name, cache_pointer, temp->msg_send == -1);

        insert(hashtlb, tempU, tempU->nick[0]);

        if (temp->msg_send >=0 )
        {
            struct Vertice *v = grafo_insert_vertice(socialnet->grafo, tempU);
            v->msg_send = temp->msg_send;
        }

    }

}

void grafo_unpack(struct Grafo *grafo , struct SocialNet *socialnet, FILE *pointer)
{

    struct DataConection *Dc = malloc(sizeof(struct DataConection));

    while(fread(Dc, sizeof(struct DataConection), 1, pointer) == 1)
    {
        /*procura 1*/
        
        struct User *u1 = search(socialnet->hashnick, Dc->nick1[0], Dc->nick1)->user;

        struct Vertice *v1 = grafo_get_vertice_by_name(grafo , Dc->nick1);
        
        if(v1 == NULL)
            v1 = grafo_insert_vertice(grafo, u1);

        /*procura 2*/
        struct User *u2 = search(socialnet->hashnick, Dc->nick2[0], Dc->nick2)->user;

        struct Vertice *v2 = grafo_get_vertice_by_name(grafo , Dc->nick2);

        if(v1 == NULL)
            v2 = grafo_insert_vertice(grafo, u2);
        
        /*cria conection*/
        struct Node *n = grafo_insert_conection(grafo, v1, v2);
        n->msg_rcv = Dc->msg_rcv;
       

    }

}

void unpack(struct SocialNet *socialnet)
{

    FILE *userdata = fopen(USER_FILE_NAME, "rb");

    if (userdata == NULL)
    {
        return;
    }

    hash_unpack(socialnet->hashnick, socialnet, userdata, socialnet->pointer);

    fclose(userdata);

    FILE *conectdata = fopen(CONE_FILE_NAME, "rb");

    if (conectdata == NULL)
    {
        return;
    }
    
    grafo_unpack(socialnet->grafo, socialnet, conectdata);
    
    fclose(conectdata);

}

#endif
