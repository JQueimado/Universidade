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

 while(fgets(Array, 300 , file_pointer)) {
     do{
        for(i=0;Array[i];i++) {
     		if(Array[i] != ' ') {
        		Array[count] = Array[i];
        		count++;
     	        }
        } 
 	Array[count] = '\0';
        printf("Processo: %d  ||  Instante: %s \n", line, Array); 
        line = line + 1;
        } 
     while(line <= 8);     
 }
  
 fclose(file_pointer);

 return 0;

}

