#include <stdio.h>

int main(void){
	int n=0;
	scanf("%d",&n);
	if (n<0 || n >100000)
		return 0;
	
	int v[n];
	int c;
	for(int i=1;i<=n;i++){
		c=0;
		scanf("%d",&c);
		v[i-1]=c;
	}
	
	int s=0;
	scanf("%d",&s);
	if (s<0 || s >100000)
		return 0;
	
	int p[s];
	for(int j=1;j<=s;j++){
		c=0;
		scanf("%d",&c);
		p[j-1]=c;
	}

	for(int a=0;a<s;a++){
		c=p[a];
		if (c>0 && c<=n)
			printf("valor @ %d = %d\n",c,v[c-1]);

		else
			printf("valor @ %d = -\n",c);
	}
}
