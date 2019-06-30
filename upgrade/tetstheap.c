#include <stdlib.h>
#include <stdio.h>

#define MAX_NOS 750001

struct Node
{   
    int peso;
}
typedef Node;

Node* new_node(int i)
{
    Node* temp = malloc(sizeof(Node));
    temp->peso = i;
    return temp;
}

struct Heap
{
    Node* array[MAX_NOS];
    int end;
}
typedef Heap;

Heap* new_heap()
{
    Heap* temp = malloc(sizeof(Heap));
    temp->end = 0;
    return temp;
}

void Heap_add( Heap* self, Node* node)
{
    self->array[self->end] = node;
    int i = self->end;
    while( i != 0 )
    {
        if( self->array[i]->peso < self->array[(i-1)/2]->peso )    
        {
            Node* temp = self->array[(i-1)/2];
            self->array[(i-1)/2] = self->array[i];
            self->array[i] = temp;
            i = (i-1)/2;
        }
        else
        {
            break;
        }
    }
    self->end ++;
}

int main()
{
    Heap* heap = new_heap();
    Heap_add(heap, new_node(10));
    Heap_add(heap, new_node(1));
    Heap_add(heap, new_node(20));
    Heap_add(heap, new_node(30));
    Heap_add(heap, new_node(40));
    Heap_add(heap, new_node(100));
    Heap_add(heap, new_node(200));

    printf(" head -> %d\n", heap->array[0]->peso);

    return 0;
}