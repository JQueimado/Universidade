#include <stdio.h>

int main ()
{
    /* read array size */

    int n;

    scanf("%d", &n);

    /* read array values */

    int piles[n];

    for(int i = 0; i < n; i++)
    {

        scanf("%d", &(piles[i]) );
        
    }

    /* play the game */

    int lftpointer = 0;

    int rgtpointer = n - 1 ;

    int lftval;

    int rgtval;

    int bela = 0;

    int alex = 0;

    for ( int i = 1; i < n + 1; i++)
    {

        lftval = piles[lftpointer];

        rgtval = piles[rgtpointer];

        if ( i % 2 == 0 )
        {

            /* Bela's turn */

            if ( i % 4 == 0 )
            {

                /* choses bigger pile */

                if ( lftval > rgtval )
                {

                    /* choses left pile */

                    bela += lftval;

                    lftpointer++;

                }
                else
                {
                    
                    /* choses right pile */

                    bela += rgtval;

                    rgtpointer--;

                }

            }
            else
            {
                
                /* choses smaller pile */

                if ( lftval < rgtval )
                {

                    /* choses left pile */

                    bela += lftval;

                    lftpointer++;

                }
                else
                {
                    
                    /* choses right pile */

                    bela += rgtval;

                    rgtpointer--;

                }

            }
            

        }
        else
        {

            /* Alex's turn */

            if ( lftval > rgtval )
            {

                /* choses left pile */

                alex += lftval;

                lftpointer++;

            }
            else
            {
                
                /* choses right pile */

                alex += rgtval;

                rgtpointer--;

            }
            
        
        }

    }

    /* output */

    if (alex > bela)
    {

        printf("Alex ganha com %d contra %d\n", alex, bela);

    }
    else if (alex < bela)
    {
        
        printf("Bela ganha com %d contra %d\n", bela, alex);

    }
    else
    {
       
       printf("Alex e Bela empatam a %d\n", alex);
    
    }

}