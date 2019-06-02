#include "Anel.h"
#include <stdlib.h>
/* Contructor */
Anel* anel_novo()
{
    Anel* temp = malloc(sizeof(Anel));
    temp->current = NULL;
    return temp;
}

/* Metodos */
bool anel_vazio(Anel* self)
{
    return self->current == NULL;
}

void anel_insere(Anel* self, short i)
{
    Node* temp = malloc(sizeof(Node));
    temp->item = i;

    if(anel_vazio(self))
    {
        temp->next = temp;
        temp->prev = temp;
        self->current = temp;
        return;
    }
    temp->next = self->current;
    temp->prev = self->current->prev;

    self->current->prev->next = temp;
    self->current->prev = temp;
    self->current = temp;
}

short anel_corrente(Anel* self)
{
    return self->current->item;
}

short anel_proximo(Anel* self)
{
    self->current = self->current->next;
    return anel_corrente(self);
}

bool anel_procura(Anel* self, short i)
{
    if( anel_vazio(self) )
        return false;

    Node* point_1 = self->current;
    Node* point_2 = self->current->prev;

    while ( point_1->item != i && point_2->item != i )
    {
        if( point_1 == point_2 )
            return false;
        point_1 = point_1->next;
        point_2 = point_2->prev;
    }

    if( point_1->item == i)
        self->current = point_1;
    else
        self->current = point_2;
    
    return true;
}

void anel_remove_current(Anel* self)
{
    if(self->current->next == self->current )
    {
        free(self->current);
        self->current = NULL;
        return;
    }
    Node* temp = self->current;
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    self->current = temp->next;
    free(temp);
}

void anel_destroi(Anel* self)
{
    while ( !anel_vazio(self) )
    {
        anel_remove_current(self);
    }
    free(self);
}