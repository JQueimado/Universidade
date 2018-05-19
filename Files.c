#include <stdio.h>
#include <stdlib.h>

#define SIZE_FILE_LINE 300
/*
int *extract(char arr[]){

	static int ret[2];

	char arrival[5];

	for (int i = 0; arr[i] != ' '; ++i){
		
		arrival[i] = arr[i]

	}

}
*/
int main() {	
	
 FILE * file_pointer;
 file_pointer = fopen ("input_b.xpto","r");
 
 if (!file_pointer) {
	perror("Error");
	exit(0);
 }

 int i;	 
 int line = 0;

 int Arrival_Time;
 int Instantes_size = 0;
 int Instantes[SIZE_FILE_LINE];

 char Instants_Array[SIZE_FILE_LINE];
 
 if (file_pointer != NULL) {
	puts("\nProcesso:   ** Tempo de Chegada:  ** Instantes:     \n");
 	puts("**********************************************************");
 }

 while(fgets(Instants_Array, SIZE_FILE_LINE , file_pointer)) {

 	/*Arrival*/
	line = line + 1;

	char arrival_str[5];

	for( i=0; Instants_Array[i] != ' '; i++ ) {	
		arrival_str[i] = Instants_Array[i];  
	}

	Arrival_Time = atoi(arrival_str);

	printf("\nP%d          **   %d              **  Instants: ", line, Arrival_Time);
	
	char inst[5];
	int inst_point = 0;
	Instantes_size = 0;
	i += 1;

	while( Instants_Array[i] != '\n' ){
		
		if ( Instants_Array[i] == ' ' ){
		
			Instantes[Instantes_size] = atoi(inst);
			Instantes_size += 1;

			inst[0] = '\0';
			inst_point = 0;
		
		}else{

			inst[inst_point] = Instants_Array[i];
			inst_point +=1;

		}

		i++;

	}

	for (int i = 0; i < Instantes_size; ++i){
		printf( "%d " , Instantes[i] );
	}

	puts("");



 }
 
 fclose(file_pointer);

 return 0;

}
