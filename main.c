#include <stdio.h>
#include "heap.h"

int main(int, char **)
{
    printf("Hello, from Chapter4!\n");
    Heap *heap = NULL;

    init_heap(&heap, 10);
    heap_insert(heap, 4);
    heap_insert(heap, 7);
    heap_insert(heap, 2);
    heap_insert(heap, 1);
    heap_insert(heap, 3);
    heap_insert(heap, 12);

    for (int i = 0; i <= 10; i++)
    {
        int element = extract_min(heap);
        printf("Extracted element: %i\n", element);
    }

    printf("End\n");
}
