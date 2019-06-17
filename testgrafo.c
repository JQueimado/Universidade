#include "Grafo.h"
#include "hashtable_aeroporto.h"

int main()
{
    int ficheiro;
	ficheiro = hashtable_aeroportos_open("ftest.cache");
    Grafo* grafo = new_grafo();

    char* a1 = "LIS";
    char* a2 = "MAD";
    char* a3 = "BAR";
    char* a4 = "ALG";
    short duracao = 33;

    new_aeroporto(a1, ficheiro);
    new_aeroporto(a2, ficheiro);
    new_aeroporto(a3, ficheiro);
    new_aeroporto(a4, ficheiro);

    aeroportos ae1 = read_aeroportos_at_hash(ficheiro, a1);
    //printf("%d\n",ae1.voosDecorrer[0]);
    //aeroportos ae2 = read_aeroportos_at_hash(ficheiro, a2);
    //aeroportos ae3 = read_aeroportos_at_hash(ficheiro, a3);
    //aeroportos ae4 = read_aeroportos_at_hash(ficheiro, a4);


    add_voo(ficheiro, &ae1, a2, 22, 33, duracao);
    add_voo(ficheiro, &ae1, a3, 22, 33, duracao);
    add_voo(ficheiro, &ae1, a4, 22, 33, duracao);
    //printf("%d\n",ae1.voosDecorrer[0].duracao);

    new_no(grafo, a1, ficheiro);
    new_no(grafo, a2, ficheiro);
    new_no(grafo, a3, ficheiro);
    new_no(grafo, a4, ficheiro);

    ae1 = read_aeroportos_at_hash(ficheiro, a1);
    //ae2 = read_aeroportos_at_hash(ficheiro, a2);
    //ae3 = read_aeroportos_at_hash(ficheiro, a3);
    //ae4 = read_aeroportos_at_hash(ficheiro, a4);

    int cona[100];

    get_conects(grafo, 0, ficheiro, cona);

    printf("size: %d\n", ae1.index_voo);

    for( int i = 0; i<ae1.index_voo; i++)
    {
        printf("itsme: %s\n", read_aeroportos_at(ficheiro, cona[i])->codigo );
    }

}