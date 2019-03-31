#include <stdio.h>
#include <stdlib.h>

int main (){
    
    int n_l = 0;
    int n_c = 0;
    
    if (scanf("%d %d", &n_l, &n_c) == EOF)
        return 0;

    char arr[n_l][n_c];
            
    for (int i = 0; i < n_c; i++){
        for(int j = 0; j<n_l; j++){
            char c = 0;
            
            if(scanf("%c",&c) == EOF)    
                return 0;
                
            arr[i][j] = c;
                            
        }
    }
    
    int x = 0;
    int y = 0;
    
    while (x != n_l && y != n_c){
        
        
        
    }
    
    return 0;
 
}
