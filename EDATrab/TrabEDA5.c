#include <stdio.h>
#define NotFound 0
#define Found 1

//findX
int findX(int n, char arr[n][n], int x, int y){ 
    
    for(int i =-1; i <= 1; i+=1){
        
        if( y+i < 0)
            continue;
        
        if( y+i >= n )
            continue;
        
        for(int j =-1; j <= 1; j+=1){
            
            if( x+j < 0)
                continue;
        
            if( x+j >= n )
                continue;
            
            if (i==0 && j==0)
                continue;
            
            if(arr[x+j][y+i] == 'X'){
                return Found;
            }
        }
    }
    return NotFound;
}

int main(void){
    
    //read
    int n = 0;
    scanf("%d",&n);
    
    char arr[n][n];
    
    for (int i = 0; i<n; i++){
        for (int j = 0; j<n; j++){
            scanf(" %c", &arr[j][i]);
        }
    }
    
    //find
    int s = 0;
    int max_s = (n/2)*(n/2)*2;
    int res[max_s];
    for (int a = n-1; a>=0; a--){
        for (int b = 0; b<n; b++){
            if (arr[b][a]=='X'){
                if (findX(n, arr, b, a)==NotFound){
                    s+=2;
                    res[s-2] = n-a;
                    res[s-1] = b+1;
                }
            }
        }
    }
    
    //print
    if (s != 0){
        printf("existem %d habitacoes isoladas:",s/2);
        for (int c =0; c<s; c+=2){
            printf(" (%d,%d)", res[c], res[c+1]);
        }
        puts("");
    }else{
        puts("nao existem habitacoes isoladas");
    }

    return 0;
}
