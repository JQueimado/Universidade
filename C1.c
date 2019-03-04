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

/***** team *****/

struct team
{
    
    char *name;

    int score;
    
    int goals;
    int goals_against;
    
    int wins;
    int draws;
    int losses;

};

/* construct */

struct team *team_const( char *name )
{

    struct team *temp = malloc(sizeof(struct team));

    temp->name = name;

    temp->score = 0;

    temp->goals = 0;
    temp->goals_against = 0;

    temp->wins = 0;
    temp->draws = 0;
    temp->losses = 0;

    return temp;

}

/****************/

struct team *get_team(struct team *tabel[], int s, char *name)
{

    for ( int i = 0; i < s; i++ )
    {

        struct team *temp = tabel[i];

        if ( strcmp(name, temp->name) == 0 )
        {

            return temp;

        }

    }

    return NULL;

}

/* main */

int main ( void )
{

    int n_teams;
    int n_match;

    /* read line 1*/

    scanf("%d %d", &n_teams, &n_match);

    /* read teams */

    struct team *teams[n_teams];

    for ( int i = 0; i < n_teams; i++ )
    {

        char *name = malloc(sizeof(NAME_LIMIT));

        scanf("%s", name);

        teams[i] = team_const(name);

    }

    /* read games */

    char *name1 = malloc(NAME_LIMIT);
    char *name2 = malloc(NAME_LIMIT);
    
    int goal1;
    int goal2;

    for ( int i = 0; i < n_match; i++ ){

        scanf("%s %d - %s %d", name1, &goal1, name2, &goal2);

        struct team *team1 = get_team(teams, n_teams, name1);
        struct team *team2 = get_team(teams, n_teams, name2);

        team1->goals += goal1;
        team1->goals_against += goal2;

        team2->goals += goal2;
        team2->goals_against += goal1;

        if ( goal1 > goal2)
        {

            team1->score += W;
            team1->wins += 1;

            team2->losses += 1;

        }
        else if (goal1 < goal2)
        {
           
            team2->score += W;
            team2->wins += 1;
            
            team1->losses += 1;

        }
        else
        {

            team1->score += D;
            team2->score += D;

            team1->draws += 1;
            team2->draws += 1;

        }
        
    }

    /* Eval */

    struct team *top = teams[0];

    for( int i = 1; i < n_teams; i++)
    {

        struct team *temp = teams[i];

        if ( temp->score > top->score )
        {

            top = temp;

        }
        else if (top->score == temp->score) 
        {
            
            puts("torneio sem vencedora");

            return 0;

        }
        
    }

    printf("a vencedora foi %s, com %d ponto(s)\nganhou %d jogo(s), empatou %d jogo(s) e perdeu %d jogo(s)\nmarcou %d golo(s) e sofreu %d golo(s)\n", top->name, top->score, top->wins, top->draws, top->losses, top->goals, top->goals_against);

    return 0;

}