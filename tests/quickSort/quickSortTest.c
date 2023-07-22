#include "../../sorting.h"

int compare_int(const void *a, const void *b)
{
    int *p = (int *)a;
    int *q = (int *)b;

    if (*p < *q)
        return -1;

    if (*p > *q)
        return 1;

    return 0;
}

int main()
{
    int inputArray[] = {1, 4, 9, 2};
    quick_sort(inputArray, sizeof(int), 4, compare_int);

    int expectedArray[] = {1, 2, 4, 9};

    for (int i = 0; i < 4; i++)
    {
        if (inputArray[i] != expectedArray[i])
            return 1;
    }

    return 0;
}