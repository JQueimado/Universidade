#include <stdbool.h>

//definir voos
struct voos {
	char aero_chegada[5];
	char hora_partida;
	char minuto_partida;
	short duracao;
	bool ocupado;
};
//definir aeroportos
struct aeroportos
{
	char  codigo[5];		// codigo do aeroporto e não e reutilizavel
	unsigned char index_voo;		
	struct voos *voosDecorrer[150]; // array de 150 struct's voos 
	bool ocupado;
};
