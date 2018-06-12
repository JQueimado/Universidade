#include "../Struct/hash.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
int main() 
{
	FILE *pointer = fopen("Cache.txt", "w+");
	struct User *user0=new_User( "asd12","asd12222", pointer);
	struct User *user1=new_User( "asd13","asd222", pointer);
	struct User *user2=new_User( "asd14","asd333", pointer);
	struct User *user3=new_User( "asd15","asd444", pointer);
	struct User *user4=new_User( "asd16","asd444", pointer);
	struct User *user5=new_User( "asd17","asd3222", pointer);
	struct User *user6=new_User( "asd18","asd322", pointer);
	struct User *user7=new_User( "asd19","asd3222", pointer);
	
   struct Hash *hash = new_hash();

   insert(hash, user0, user0->nick[0]);
   insert(hash, user1, user1->nick[0]);
   insert(hash, user2, user2->nick[0]);
   insert(hash, user3, user3->nick[0]);
   insert(hash, user4, user4->nick[0]);
   insert(hash, user5, user5->nick[0]);
   insert(hash, user6, user6->nick[0]);
   insert(hash, user7, user7->nick[0]);

   display(hash);

   struct userdados *ud1 = search(hash, 'a', "asd24");
   
   if (ud1 != NULL)
   {
      printf("%s\n", ud1->user->nick);
   }
   else
   {
      puts("not found");
   }

}