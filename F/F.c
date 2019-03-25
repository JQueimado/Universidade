#include <stdio.h>
#include <stdlib.h>

/** funcs **/

void add( unsigned long n, char * senssors, unsigned long senssor1, unsigned long senssor2 )
{

	char * temp = senssors + senssor1 * ( n * sizeof( char ) );

	*(temp + (senssor2 * sizeof( char ) )) = 1;

}

void rem( unsigned long n, char * senssors, unsigned long senssor1, unsigned long senssor2 )
{

	char * temp = senssors + senssor1 * ( n * sizeof( char ) );

	*(temp + (senssor2 * sizeof( char ) )) = 0;


}

char find_com( unsigned long n, char * senssors, unsigned long senssor1, unsigned long senssor2 )
{

	char * temp = senssors + senssor1 * ( n * sizeof( char ) );

	return *(temp + (senssor2 * sizeof( char ) ));  


}

void clean_arr( unsigned long n, char senssors[n][n] )
{

	for( unsigned long i = 0; i < n; i++ )
		for( unsigned long j = 0; j < n; j++ )
			senssors[i][j] = 0;

}

/** main **/

int main( void )
{

	char op;
	unsigned long m;

	unsigned long a;
	unsigned long b;

	unsigned long s;
	unsigned long c;
	unsigned long p;

	unsigned long ft;

	char flag = 0;

	scanf("%lu", &m);

	char * array = calloc(m, m * sizeof( char ) );
	
	while( scanf("%c", &op) != EOF )

	switch (op)
	{
		case '+':

			scanf("%lu %lu", &a, &b);

			add(m, array, a, b);

			break;
	
		case '-':

			scanf("%lu %lu", &a, &b);

			rem(m, array, a, b);

			break;

		case '?':

			flag = 0;

			scanf("%lu", &s);

			scanf("%lu", &p);

			ft = p;

			for( int i = 0; i<s; i++){

				scanf("%lu", &c);

				if( !find_com( m, array, p, c ) ){

					flag = 1;

				}else{

					p = c;

				}

			}

			if( flag )
			{

				printf("no [%lu..%lu]\n", ft, c);

			}
			else
			{

				printf("yes [%lu..%lu]\n", ft, c);

			}

			break;

	}

	return 0;

}