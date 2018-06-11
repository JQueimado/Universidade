#include "../Struct/hash.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
int main() 
{
	struct User *user=new_User("asd","asd");
	struct User *user1=new_User("asd","asd");
	struct User *user2=new_User("asd","asd");
	struct User *user3=new_User("asd","asd");
	struct User *user4=new_User("asd","asd");
	struct User *user5=new_User("asd","asd");
	struct User *user6=new_User("asd","asd");
	struct User *user7=new_User("asd","asd");
	//struct User *item;
	dummyItem = (struct userdados*) malloc(sizeof(struct userdados));
   	dummyItem->user = user;  
   	dummyItem->key = -1; 

   insert(user,1);
   insert(user1, 2);
   insert(user2, 3);
   insert(user3, 4);
   insert(user4, 5);
   insert(user5, 6);
   insert(user6, 7);
   insert(user7, 8);
  

   display();
   dummyItem = search(1);

   if(dummyItem != NULL) {
      printf("Element found: %s\n", dummyItem->user->nick);
   } else {
      printf("Element not found\n");
   }

   delete(dummyItem);
   dummyItem = search(2);

   if(dummyItem != NULL) {
      printf("Element found: %s\n", dummyItem->user->nick);
   } else {
      printf("Element not found\n");
   }
}