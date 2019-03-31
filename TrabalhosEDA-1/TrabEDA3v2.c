#include <stdio.h>

long long max(int v[], int n, int s){
    long long sum =0;
    for(int i = 0; i<n; i+=s){
        long long max = v[i];
        for(int j = 0; j<s; j++){
            if(i + j >= n){
                break;
            }
            if (v[i+j] > max){
                max = v[i+j];
            }
        }
        sum+=max;
    }
    return sum;
}

long long min(int v[], int n, int s){
    long long sum =0;
    for(int i = 0; i<n; i+=s){
        long long min = v[i];
        for(int j = 0; j<s; j++){
            if(i + j >= n){
                break;
            }
            if (v[i+j] < min){
                min = v[i+j];
            }
        }
        sum+=min;
    }
    return sum;
}

int main(void){

	int n=0;
	
	scanf("%d",&n);
	
	if (n < 1 || n > 10000)
		return 0;
		
	int v[n];
	
	for(int i=0;i<n;i++){
		long long c=0;
		scanf("%lli",&c);
		v[i]=c;
	}
	
	long long s = 0;
	char c = 0;
    while(scanf(" %c %lli", &c, &s) != EOF){
        if(s>n){
            return 0;
        }
        if (c =='m')
	        printf("+ min %lli\n",min(v, n, s));
	    else
	        printf("+ max %lli\n",max(v, n, s));
    }

}
