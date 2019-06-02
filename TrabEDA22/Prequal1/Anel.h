#include <stdbool.h>

/* Node */
struct Node
{
    struct Node* next;
    struct Node* prev;
    short item;
}
typedef Node;

/* Anel */
struct Anel
{
    Node* current;
}
typedef Anel;

/* Contructor */
Anel* anel_novo();

/* Metodos */
bool anel_vazio(Anel* self);

void anel_insere(Anel* self, short i);

short anel_corrente(Anel* self);

short anel_proximo(Anel* self);

bool anel_procura(Anel* self, short i);

void anel_destroi(Anel* self);