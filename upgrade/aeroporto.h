#ifndef _aeroporto_
#define _aeroporto_

#include <stdbool.h>
#define MAX_VOO 150

//definir voos
struct voos {
	char aero_chegada[5]; // 5 byte
	char hora; // 1 byte //aqui pode ser melhorado
	char min;
	//char minuto_partida; // 1 byte
	short duracao; // 2 byte
	//short ocupado; // 1 byte = 10 bytes
	bool tag;
} 
typedef voos;

//definir aeroportos
struct aeroportos
{
	char  codigo[5];					// codigo do aeroporto e não e reutilizavel 5 bytes
	//int index_voo;					// 1 byte
	int peso;
	struct voos voosDecorrer[MAX_VOO]; 	// array de 150 struct's voos 150*10 = 1500 bytes 
	unsigned char ocupado; 				// 1 byte
	char vesitado; 						// 1 byte
	char pai[5];						// 4 bytes *pointer* 
} 
typedef aeroportos;

#endif