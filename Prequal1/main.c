#include "Anel.h"
#include <stdio.h>

int main()
{
    Anel* anel = anel_novo();
    anel_insere(anel, 1);
    anel_insere(anel, 2);
    anel_insere(anel, 3);
    anel_insere(anel, 4);
    anel_insere(anel, 5);
    anel_insere(anel, 6);
    anel_insere(anel, 7);
    anel_insere(anel, 8);
    anel_insere(anel, 9);
    anel_insere(anel, 10);

    int i;
    scanf("%d", &i);

    if( anel_procura(anel, i) )
        printf("%d\n", anel_proximo(anel));
    puts("bam");
    anel_destroi(anel);

}