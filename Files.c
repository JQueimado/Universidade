#include <stdio.h>
#include <stdlib.h>

int main() {	
	
 FILE * file_pointer;
 file_pointer = fopen ("input_b.xpto","r");

 if (file_pointer == NULL) {
     printf("Erro: Does not exist\n");
 }

 int i=0, k=0;	 
 int line = 0;
 char Insts[300], Array[300];

 while(fgets(Array, 300 , file_pointer)) {
	while(line < 8) {
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

 fclose(file_pointer);

 return 0;

}
