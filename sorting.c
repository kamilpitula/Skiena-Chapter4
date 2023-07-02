#include "sorting.h"

int partition(int *input, int low, int high);
void do_quick_sort(int *input, int low, int high);

void quick_sort(int *input, size_t size)
{
    do_quick_sort(input, 0, size - 1);
}

void do_quick_sort(int *input, int low, int high)
{
    if (high <= low)
        return;
    int p = partition(input, low, high);
    do_quick_sort(input, low, p - 1);
    do_quick_sort(input, p + 1, high);
}

int partition(int *input, int low, int high)
{
    int firstHigh = low;
    int p = high;

    for (int i = low; i <= high; i++)
    {
        if (input[i] < input[p])
        {
            int temp = input[i];
            input[i] = input[firstHigh];
            input[firstHigh] = temp;
            firstHigh++;
        }
    }

    int temp = input[firstHigh];
    input[firstHigh] = input[p];
    input[p] = temp;

    return firstHigh;
}