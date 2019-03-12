#include <stdio.h>
#include <stdlib.h>

/* First acceptable letter */
#define CharA 'a'
/* Last acceptable letter */
#define CharZ 'z'

/* Constants */
#define MAX_INPUT 1100 
#define ALFABET_SIZE CharZ - CharA

/* Function Main */
int main( void )
{

    /*** Variables ***/

    char input = 0; 

    char output[ MAX_INPUT ];

    int out_pointer = 0;

    int inpsize = 0;

    short *searched_leters = malloc( sizeof( short[ALFABET_SIZE] ) );

    /*** Input/Processing ***/

    /* Runs and proceses all characters incerted by the user */

    while( inpsize != EOF )
    {

        /** Scan **/

        inpsize = scanf("%c", &input);

        /** EOF **/

        /* If it reaches EOF it means the user doesn't have more values to input so the program goes to the output section */

        if (input == EOF)
        {

            break;

        }

        /** \n (End of  line) **/

        /* When a line ends the program ads \n to the outout and clear the search hash */

        if ( input == '\n' )
        {
         
            output[out_pointer] = '\n';
        
            out_pointer += 1;

            searched_leters = malloc( sizeof( short[ALFABET_SIZE] ) );

            continue;          

        }

        /** Processing **/

        /* Checks if the char is or isnt being searched */

        if ( !searched_leters[input - CharA] )
        {
            
            /* Marks a char for search */

            searched_leters[input - CharA] = 1;
        
        }
        else
        {

            /* When found adds it to the output string and clears the search hash */

            output[out_pointer] = input;

            out_pointer += 1;

            searched_leters = malloc( sizeof( short[ALFABET_SIZE] ) );

        }

    }

    /*** Output ***/

    /* Finalises the output string and prints it to the stdout */

    output[out_pointer - 1] = '\0';

    printf("%s", output);

}

