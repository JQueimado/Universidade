#include <stdio.h>
#include <stdlib.h>

#define SIZE_FILE_LINE 300

int main() {	
	
 FILE * file_pointer;
 file_pointer = fopen ("input_b.xpto","r");
 
 if (!file_pointer) {
	perror("Error");
	exit(0);
 }

 int i;	 
 int line = 0;

 int Arrival_Time[3];
 int Instants[SIZE_FILE_LINE];

 char Arrival[3];
 char Instants_Array[SIZE_FILE_LINE];
 
 if (file_pointer != NULL) {
	puts("\nProcesso:   ** Tempo de Chegada:  ** Instantes:     \n");
 	puts("**********************************************************");
 }

 while(fgets(Instants_Array, SIZE_FILE_LINE , file_pointer)) {

	line = line + 1;

	for(i=0;Instants_Array[i] != ' ';i++) {	
		Arrival[i] = Instants_Array[i];
		Arrival_Time[i] = atoi(Arrival);	  
	}

	printf("\nP%d          **   %d              **  Instants: ", line, Arrival_Time[i]);
	
	while(Instants_Array[i] != '\n') {

		if(Instants_Array[i] != ' ') {
			// Converter os instnates para int. Não dá de nenhuma forma pela função atoi
			printf("%c", Instants_Array[i]);
		}
		
		i+=1;
       	
	} 
	printf("\n");
 }
 
 fclose(file_pointer);

 return 0;

}
