#include <stdlib.h>
#include <stdio.h>

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

struct Heap_Node
{
    struct Node* elem;

    struct Heap_Node* parent;    //4 bytes
    struct Heap_Node* left;      //4 bytes
    struct Heap_Node* right;     //4 bytes
}
typedef Heap_Node;               //12 bytes = 3 paginas

struct Heap
{
    Heap_Node* head;
    Heap_Node* To_add;
}
typedef Heap;

Heap* new_heap()
{
    Heap* temp = malloc(sizeof(Heap));
    temp->head = NULL;
    temp->To_add = NULL;
    return temp;
}

void Heap_add( Heap* self, Node* node)
{
    Heap_Node* temp = malloc( sizeof( Heap ) );
    temp->elem = node;
    temp->left = NULL;
    temp->right = NULL;
    Heap_Node* head = self->head;

    /* if empty */
    if( self->To_add == NULL )
    {
        self->To_add = temp;
        self->head = temp;
        return;
    }

    /* check left or right */
    if( self->To_add->left == NULL)
        self->To_add->left = temp;
    else
        self->To_add->right = temp;

    /* set parrent To_add */
    temp->parent = self->To_add;

    /* re-sort heap */
    while( temp->parent->elem->peso < temp->elem->peso )
    {
        temp->elem = temp->parent->elem;
        temp->parent->elem = node;
        temp = temp->parent;
    }

    /* new To_add */
    if( self->To_add->right != NULL )
    {
        /* ve a direita da direita do pai */
        if( self->To_add->parent->right->right == NULL)
            self->To_add = self->To_add->parent->right;
        else
        {
            /* procura no mais a esquerda */
            while ( head->left != NULL )
            {
                head = head->left;
            }
            self->To_add = head->parent;
        }  
        
    }

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

    printf(" head -> %d\n", heap->head->elem->peso);

    return 0;
}