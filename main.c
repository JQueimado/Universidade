#include <stdio.h>



int main() {
    
 FILE *inputFile;
 inputFile = fopen("input_b.xpto", "r")  

 //Read File into array

    int process[size_File_line];
    int i;

 if (inputFile == NULL) {
	printf("Erro: Does not exist\n");
 }
 
 for (i = 0; i < 16; i++){
        fscanf(inputFile, "%d,", &process[i] );

 fclose(myFile);
 return 0;    
    
}
