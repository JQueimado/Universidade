#include <stdio.h>
#include <stdlib.h>

#include "Struct/trie.h"
#include "Struct/User.h"

int main()
{
	char input;
	char nick[10];
	char name[10];
	User *user=new_user(nick,name);
    while(scanf("%c",&input))
    {
    	if(input=='U')
    	{
    		scanf("%d",set_nick(user,nick));
    	}
    	return 0;
}
