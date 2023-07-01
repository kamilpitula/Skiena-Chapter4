#include <stdio.h>
#include "heap.h"

int main(int, char **)
{
    printf("Hello, from Chapter4!\n");
    Heap *heap = NULL;

    init_heap(&heap, 10);

    int array[] = {4, 7, 2, 1, 3, 12};

    make_heap(heap, array, 6);

    for (int i = 0; i <= 10; i++)
    {
        int element = extract_min(heap);
        printf("Extracted element: %i\n", element);
    }

    printf("End\n");
}
