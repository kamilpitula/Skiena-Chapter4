#include <stdio.h>
#include "heap.h"
#include "sorting.h"
#include "exercises.h"

int heap_compare_int_main(const void *a, const void *b)
{
    int *p = (int *)a;
    int *q = (int *)b;

    if (*p < *q)
        return 1;

    if (*p == *q)
        return 0;

    return -1;
}

int main(int, char **)
{
    printf("Hello, from Chapter4!\n");
    int array[] = {4, 7, 2, 1, 3, 12};

    Heap *heap = NULL;
    init_heap(&heap, 10, sizeof(int), heap_compare_int_main);
    make_heap(heap, array, 6);

    for (int i = 0; i <= 10; i++)
    {
        int element;
        int res = extract_root(heap, &element);
        if (res == -1)
            break;
        printf("Extracted element: %i\n", element);
    }

    free_heap(heap);

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

    pair_with_smallest_sum();

    sort_by_colour();

    find_sum();

    calculate_citations_index();

    does_k_sum_exist();

    find_most_people_present();

    merge_overlapping_intervals();

    find_k_smallest();

    merge_sorted_arrays_nk();

    merge_sorted_arrays_nlogk();

    sort_red_white_blue();

    find_median();

    partition_negatives();
}
