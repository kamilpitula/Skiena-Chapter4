#include <stdio.h>
#include "heap.h"
#include "sorting.h"
#include "exercises.h"

int main(int, char **)
{
    // printf("Hello, from Chapter4!\n");
    // int array[] = {4, 7, 2, 1, 3, 12};

    // Heap *heap = NULL;
    // init_heap(&heap, 10);
    // make_heap(heap, array, 6);

    // for (int i = 0; i <= 10; i++)
    // {
    //     int element = extract_min(heap);
    //     printf("Extracted element: %i\n", element);
    // }

    // int arrayToSort[] = {4, 7, 2, 5, 1, 3};

    // quick_sort(arrayToSort, 6);

    // printf("Sorted array:\n");
    // for (int i = 0; i < 6; i++)
    // {
    //     printf("Element %i: %i\n", i, arrayToSort[i]);
    // }

    // printf("End\n");

    maximize_unsorted();
    maximize_sorted();
    minimize_unsorted();
    minimize_sorted();
}
