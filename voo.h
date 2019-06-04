/* Type voo */
struct voo
{
    char codigo[4];
    char codigo_partida[4];
    char codigo_destino[4];
    char hora_partida[6];
    short duracao;
}typedef voo;

/* Main Constructor */
voo* new_voo( char* codigo, char codigo_partida, char codigo_destino, char hora_partida, short duracao);