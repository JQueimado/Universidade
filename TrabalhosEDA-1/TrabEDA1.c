#include <stdio.h>

int main(void){
	int n=15180;
	int a=0;
	for(int c=2;c<n;c++){
		if (n%c==0){
			printf("%d\n",c);
			a++;		
		}
	}
	printf("+ 15180 tem %d divisores\n",a);

}
