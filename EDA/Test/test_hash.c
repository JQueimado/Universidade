#include "../Struct/hash.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
int main() 
{
	
	struct User *user=new_User("asd12","asd12222");
	struct User *user1=new_User("asd13","asd222");
	struct User *user2=new_User("asd14","asd333");
	struct User *user3=new_User("asd15","asd444");
	struct User *user4=new_User("asd16","asd444");
	struct User *user5=new_User("asd17","asd3222");
	struct User *user6=new_User("asd18","asd322");
	struct User *user7=new_User("asd19","asd3222");
	//struct User *item;
	
	dummyItem = (struct userdados*) malloc(sizeof(struct userdados));
 
   	//printf("%s %d\n",dummyItem->user->nick,dummyItem->key);
   //puts("cona");
   insert(user,1);
   //puts("cona");
   insert(user1, 2);
   insert(user2, 3);
   insert(user3, 4);
   insert(user4, 5);
   insert(user5, 6);
   insert(user6, 7);
   insert(user7, 8);
  
   //puts("cona");
   display();
   //puts("cona");
   dummyItem = search(1);
   puts("cona");
   if(dummyItem != NULL) {
   	  puts("cona");
      printf("Element found: %s\n", dummyItem->user->nick);
      puts("cona");
   } else {
      printf("Element not found\n");
   }

   
}