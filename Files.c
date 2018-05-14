#include <stdio.h>
#include <stdlib.h>

int main() {	
	
 FILE * file_pointer;
 file_pointer = fopen ("input_b.xpto","r");

 if (file_pointer == NULL) {
     printf("Erro: Does not exist\n");
 }

 int i;	 
 int line = 1;
 int count = 0;
 char Array[300];

/*
 while(fgets(Array, 300 , file_pointer)) {
    while(line < 8) {
        for(i=0;Array[i];i++) {
     		if(Array[i] != ' ') {
        		Array[count] = Array[i];
        		count++;
     	        }
        } 
        Array[count] = '\0';
        printf("Processo: %d  ||  Instante: %s \n", line, Array); 

        line = line + 1;
		while(Array[i] != '\0') { 
			if(!(Array[i] == ' ' && Array[i+1] != ' ')) {
				Insts[k] = Array[i];
				k++;
			}
			i++;
		}
		Insts[k]= '\0';
        printf("Processo: %d  ||  Instante: %s \n", line, Insts); 	
	}      
 }
*/

 while ( fgets( Array , 300 , file_pointer ) ){
    
    count +=1;

    char arr_time[3];

    for ( i = 0; Array[i] != ' '; i++){

        arr_time[i] = Array[i];

    }

    printf("Processo: %d || t_chegada->%s :", count, arr_time );

    while ( Array[i] != '\n' ){

        if ( Array[i] != ' ' ){

            printf("%c", Array[i]);

        }

        i+=1;

    }
    printf("\n");

 }

 fclose(file_pointer);

 return 0;

}
