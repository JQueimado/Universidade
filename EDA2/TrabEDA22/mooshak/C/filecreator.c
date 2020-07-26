#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define File_NAME "GeratedFile.txt"

int main ( int argc, char *argv[] )
{

    short nTeams = atoi( argv[1] );

    short nMatch;

    if (argc == 2)
        nMatch = (nTeams - 1) * nTeams;
    else
        nMatch = atoi( argv[2] );


    FILE *file = fopen(File_NAME, "w");

    fprintf(file, "%d %d\n", nTeams, nMatch);

    for ( int i = 0; i < nTeams; i++)
    {

        fprintf(file, "Team%d\n", i);

    }

    short adv = 1;
    short cct = 0;

    short g1 = 1; 
    short g2 = 1;

    for ( int i = 0; i < nMatch; i++ )
    {
        
        if(adv >= nTeams)
            adv = 0;

        if(cct >= nTeams)
            cct = 0;

        fprintf(file, "Team%d %d - Team%d %d\n", cct, g1, adv, g2);

        adv += 1;

        cct += 1;

    }

    fclose(file);

}