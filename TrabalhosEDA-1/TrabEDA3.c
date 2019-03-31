#include <stdio.h>

int main(void){

	int n=0;
	scanf("%d",&n);
	if (n<1 || n>10000 )
		return 0;
	int v[n];
	
	for(int i=0;i<n;i++){
		int c=0;
		scanf("%d",&c);
		v[i]=c;
	}

	while (1==1){
		
		char m=0;
		long long s=0;
		scanf(" %c %lli", &m , &s );
		if(s>n || s<1)
			return 0;
		int a;
		if (n%s==0)
			a=n/s;
		else
			a=(n/s)+1;
		int sec[s][a];
		
		
		//sec
		int d =0;
		for(int i=0;i<a;i++)
			for(int j=0;j<s;j++){
				sec[j][i]=v[d];
				if(d>=n)
					sec[j][i]=0;
				d++;
			}
	
		//Max e Min
		if (m=='M'){
	        int sum=0;
	        for (int i = 0; i<a; i++){
	        
	            int max = sec[0][i];
	            
	            for (int j = 0; j<s; j++)
	                if(sec[j][i]>max)
	                    max=sec[j][i];
	            
	            sum+=max;
	        }
	        printf("+ max %d\n",sum);
		}

		if (m=='m'){
            int sum=0;
	        for (int i = 0; i<a; i++){
	        
	            int min = sec[0][i];
	            
	            for (int j = 0; j<s; j++)
	                if(sec[j][i] < min && sec[j][i] != 0)
	                    min = sec[j][i];
	            
	            sum += min;
	        }
	        printf("+ min %d\n", sum);
		}
		
	}

}
