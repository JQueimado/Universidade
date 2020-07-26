#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_NOS 750001

struct Node
{   
    int peso;
}
typedef Node;

Node* new_node(int i)
{
    Node* temp = calloc(1, sizeof(Node));
    temp->peso = i;
    return temp;
}

/* Adaptado de https://www.geeksforgeeks.org/binary-heap/ */
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

void heap_add( Heap* self, Node* node)
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

Node* heap_pop(Heap* self)
{
    Node* ret = self->array[0];

    if( self->end == 0 )
    {
        return ret;
    }

    self->array[0] = self->array[self->end-1];
    self->array[self->end-1] = NULL;
    self->end--;

    int i = 0;
    while( 1 )
    {
        Node* left = NULL;
        if( (2*i+1) < self->end )
            left = self->array[2 * i + 1];

        Node* right = NULL;
        if( (2*i+2) < self->end )
            right = self->array[2 * i + 2];

        int min = i;   
        if( left != NULL && left->peso < self->array[min]->peso )
        {
            min = 2*i+1;
        }
        
        if( right != NULL && right->peso < self->array[min]->peso )
        {
            min = 2*i+2;
        }

        if( min != i )
        {
            Node* temp = self->array[i];
            self->array[i] = self->array[min];
            self->array[min] = temp;
            i = min;
        }
        else
        {
            break;
        }
    }
    return ret;
}
/*
int main()
{
    Heap* heap = new_heap();
    heap_add(heap, new_node(10));
    heap_add(heap, new_node(20));
    heap_add(heap, new_node(30));
    heap_add(heap, new_node(40));
    heap_add(heap, new_node(100));
    heap_add(heap, new_node(200));
    heap_add(heap, new_node(1));

    while( heap->end > 0)
    {
        for(int i = 0; i < heap->end; i++)
            printf("->form add -> %d\n", heap->array[i]->peso);
        
        printf(" from pop -> %d\n", heap_pop(heap)->peso);
    }

    return 0;
}
*/