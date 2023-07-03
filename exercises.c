#include "exercises.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"

void do_minimize_sorted(int *sortedArray, size_t size);

// Exercise 4.2
void maximize_unsorted()
{
    printf("Exercise 4.2 - a\n");

    int unsortedArray[] = {6, 13, 19, 3, 8};

    int max = INT_MIN;
    int min = INT_MAX;

    for (int i = 0; i < 5; i++)
    {
        if (unsortedArray[i] < min)
            min = unsortedArray[i];

        if (unsortedArray[i] > max)
            max = unsortedArray[i];
    }

    printf("Selected values: %i - %i\n", max, min);
}

void maximize_sorted()
{
    printf("Exercise 4.2 - b\n");

    int sortedArray[] = {3, 6, 8, 13, 19};

    int min = sortedArray[0];
    int max = sortedArray[4];

    printf("Selected values: %i - %i\n", max, min);
}

void minimize_unsorted()
{
    printf("Exercise 4.2 - c\n");

    int unsortedArray[] = {6, 13, 19, 3, 8};

    quick_sort(unsortedArray, 5);

    do_minimize_sorted(unsortedArray, 5);
}

void minimize_sorted()
{
    printf("Exercise 4.2 - d\n");

    int sortedArray[] = {3, 6, 8, 13, 19};

    do_minimize_sorted(sortedArray, 5);
}

void do_minimize_sorted(int *sortedArray, size_t size)
{
    int first_index = INT_MIN;
    int second_index = INT_MAX;
    int min_value = INT_MAX;

    for (int i = 1; i < size; i++)
    {
        int result = abs(sortedArray[i - 1] - sortedArray[i]);
        if (result < min_value)
        {
            min_value = result;
            first_index = i - 1;
            second_index = i;
        }
    }

    printf("Selected values: %i - %i\n", sortedArray[first_index], sortedArray[second_index]);
}

//------------------------------------------------------------------------------------------------------------

// Exercise 4.3

typedef struct
{
    int Item1;
    int Item2;
} Tuple;

void pair_with_smallest_sum()
{
    printf("Exercise 4.3 \n");

    int inputArray[] = {1, 4, 9, 2};
    quick_sort(inputArray, 4);

    Tuple pairs[2];

    for (int i = 0; i < 2; i++)
    {
        Tuple pair = {
            .Item1 = inputArray[i],
            .Item2 = inputArray[3 - i],
        };

        pairs[i] = pair;
    }

    printf("Selected pairs:\n");

    for (int i = 0; i < 2; i++)
    {
        printf("Pair %i: (%i, %i)\n", i, pairs[i].Item1, pairs[i].Item2);
    }
}

//------------------------------------------------------------------------------------------------------------