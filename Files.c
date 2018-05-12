#include <stdio.h>
#include <stdlib.h>

int main() {	
	
 FILE * file_pointer;
 file_pointer = fopen ("input_b.xpto","r");

 if (file_pointer == NULL) {
     printf("Erro: Does not exist\n");
 }
	 
 int line = 0;
 char Array[300];

 while(fgets(Array, 300 , file_pointer)) {
	line = line + 1;
        printf("Line:%d -> %s",line, Array);
 }

 fclose(file_pointer);

 return 0;

}

