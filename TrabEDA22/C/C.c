#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* limits */

#define NAME_LIMIT 20
#define TEAM_LIMIT 20

/* score */

#define W 3
#define D 1
#define L 0

/* hash */

#define HASH( x ) x % TEAM_LIMIT

/***** team *****/

struct team
{
    
    char *name;

    int score;

};

/* construct */

struct team *team_const( char *name )
{

    struct team *temp = malloc(sizeof(struct team));

    temp->name = name;

    temp->score = 0;

    return temp;

} 

/****************/

/** hash_table **/

int hash_add( struct team *hash[], char *name )
{

    struct team *temp = team_const(name);

    int i = 0;

    while ( 1 )
    {

        int p = HASH( name[0] + i ) ;

        if ( hash[p] == NULL )
        {

            hash[p] = temp;

            return p;

        }
        else
        {

            i++;

        }

    }

}

struct team *hash_get(struct team *hash[], char *name)
{

    int i = 0;

    while( 1 ){
    
        int p = HASH( name[0] + i );

        struct team *temp  = hash[ p ] ;

        if ( strcmp(temp->name, name ) != 0 )
        {

            i++;

        }
        else
        {
            
            return temp;

        }

    }

}

/****************/

/* main */

int main ( void )
{

    int n_teams;
    int n_match;

    /* read line 1*/

    scanf("%d %d", &n_teams, &n_match);

    struct team *hash[TEAM_LIMIT] = {NULL};

    int pos[n_teams];

    for ( int i = 0; i < n_teams; i++ )
    {

        char *name = malloc(sizeof(NAME_LIMIT));

        scanf("%s", name);

        puts("HASHING");

        pos[i] = hash_add(hash, name);

        puts("HASHED");

    }

    char *name1 = "";
    char *name2 = "";
    
    int goal1;
    int goal2;

    for ( int i = 0; i < n_match; i++ ){

        scanf("%s %d - %s %d", name1, &goal1, name2, &goal2);

        if ( goal1 > goal2)
        {

            struct team *winner = hash_get(hash, name1);

            winner->score += W;

        }
        else if (goal1 < goal2)
        {
           
            struct team *winner = hash_get(hash, name2);

            winner->score += W;

        }
        else
        {
            
            struct team *team1 = hash_get(hash, name1);
            struct team *team2 = hash_get(hash, name2 );

            team1->score += D;
            team2->score += D;

        }
        
    }

    for( int i = 0; i < n_teams; i++)
    {

        struct team *temp = hash[pos[i]];

        printf("%s -> %d", temp->name, temp->score );

    }

}