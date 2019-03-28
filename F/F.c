#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/** <Header> **/

/** Cpnnections **/
struct connections
{
	int elem;
	struct connections * next;
};

/* Constructor */
struct connections * new_connection( int e, struct connections * next )
{
	struct connections * temp = malloc( sizeof( struct connections ) );
	temp->elem = e;
	temp->next = next;

	return temp;
}

/******************/

/** funcs **/
char find( int n, struct connections * senssors[], int senssor1, int senssor2 )
{
	/* Gets connections form senssor1 */
	struct connections * temp = senssors[senssor1];

	/* Searches for senssor2 in the connections */
	while( temp != NULL )
	{
		if( temp->elem == senssor2 )
			return 1;

		temp = temp->next;
	}

	return 0;
}

void add( int n, struct connections * senssors[], int senssor1, int senssor2 )
{
	struct connections * temp = senssors[senssor1];

	senssors[senssor1] = new_connection( senssor2, temp );
}

void rem( int n, struct connections * senssors[], int senssor1, int  senssor2 )
{
	struct connections * temp = senssors[senssor1];

	if( temp == NULL )
		return;

	if(temp->elem == senssor2)
	{
		senssors[senssor1] = temp->next;
		free(temp);

		return;
	}

	struct connections * pev = temp;

	temp = temp->next; 

	while( temp->next != NULL )
	{
		if( temp->elem == senssor2 )
		{	
			break;
		}

		pev = temp;
		temp = temp->next;
	}

	pev->next = temp->next;
	free(temp);
}

/** </Header> **/

/** main **/

int main( void )
{

	char op;

	int m;
	int a;
	int b;

	scanf("%d", &m);

	struct connections * array[m];

	memset(array, 0, m * sizeof( array[0] ) );

	while( scanf("%c", &op) != EOF )

		switch (op)
		{
			case '+':
			{
				scanf("%d %d", &a, &b);
				add(m, array, a, b);

				break;
			}

			case '-':
			{
				scanf("%d %d", &a, &b);
				rem(m, array, a, b);
				
				break;
			}

			case '?':
			{
				int s, p;
				scanf("%d %d", &s, &p);

				int ft;
				int c;
				bool flag = false;

				ft = p;

				for( int i = 0; i<s; i++)
				{
					scanf("%d", &c);
					if( !flag )
					{
						if( !find( m, array, p, c ) )
						{
							flag = true;
						}
						else
						{
							p = c;
						}
					}
				}

				if( flag )
				{
					printf("no [%d..%d]\n", ft, c);
				}
				else
				{
					printf("yes [%d..%d]\n", ft, c);
				}

				break;
			}

		}

	return 0;

}