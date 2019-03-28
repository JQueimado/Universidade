#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** <Header> **/

struct connections
{

	int elem;

	struct connections * next;


};

/** funcs **/

char find( int n, struct connections * senssors[], int senssor1, int senssor2 )
{

	/* Gets connections form senssor1 */
	struct connections * temp = senssors[senssor1];

	if ( temp == NULL )
		return 0;

	while( temp != NULL ){

		if( temp->elem == senssor2 )
			return 1;

		temp = temp->next;
	
	}
	

	return 0;
	
}

void add( int n, struct connections * senssors[], int senssor1, int senssor2 )
{
	
	struct connections * temp = senssors[senssor1];

	if( temp == NULL ){

		temp = malloc( sizeof( struct connections ) );
		temp->elem = senssor2;
		senssors[senssor1] = temp;
		return;

	}

	while( temp->next != NULL )
		temp = temp->next;

	struct connections * temp2 = malloc( sizeof( struct connections ) );

	temp2->elem = senssor2;

	temp2->next = NULL;

	temp->next = temp2;

}

void rem( int n, struct connections * senssors[], int senssor1, int  senssor2 )
{
	
	struct connections * temp = senssors[senssor1];

	if( temp == NULL )
		return;

	if(temp->elem == senssor2){

		senssors[senssor1] = temp->next;

		free(temp);

		return;

	}

	struct connections * pev = temp;

	temp = temp->next; 

	while( temp->next != NULL ){

		if( temp->elem == senssor2 ){
			
			break;

		}

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

	int s;
	int c;
	int p;

	int ft;

	char flag = 0;

	scanf("%d", &m);

	struct connections * array[m];

	memset(array, 0, m * sizeof( array[0] ) );
	
	while( scanf("%c", &op) != EOF )

		switch (op)
		{
			case '+':

				scanf("%d %d", &a, &b);

				add(m, array, a, b);

				break;
		
			case '-':

				scanf("%d %d", &a, &b);

				rem(m, array, a, b);

				break;

			case '?':

				flag = 0;

				scanf("%d", &s);

				scanf("%d", &p);

				ft = p;

				for( int i = 0; i<s; i++){

					scanf("%d", &c);

					if( !find( m, array, p, c ) ){

						flag = 1;

					}else{

						p = c;

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

	return 0;

}