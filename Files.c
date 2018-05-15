#include <stdio.h>
#include <stdlib.h>

int main() {	
	
 FILE * file_pointer;
 file_pointer = fopen ("input_b.xpto","r");
 
 if (file_pointer == NULL) {
	printf("Erro: Does not exist\n");
 }

 int i;	 
 int line = 0;

 char Arrival_Time[3];
 char Instants_Array[300];
 
 if (file_pointer != NULL) {
	puts("\nProcesso:   ** Tempo de Chegada:  ** Instantes:     \n");
 	puts("**********************************************************");
 }

 

 while(fgets(Instants_Array, 300 , file_pointer)) {

	line = line + 1;

	for(i=0;Instants_Array[i] != ' ';i++) {	
		Arrival_Time[i] = Instants_Array[i];
        
	}

	printf("\nP%d          **   %d              **  Instants: ", line, atoi(Arrival_Time));
	
	while(Instants_Array[i] != '\n') {

		if(Instants_Array[i] != ' ') {
			printf("%c",Instants_Array[i]);
		}
		
		i+=1;
       	
	} 
	printf("\n");
 }
 
 fclose(file_pointer);

 return 0;

}
