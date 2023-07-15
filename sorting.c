#include "sorting.h"

int partition(input, typeSize, low, high, compare);
void swap(void *a, void *b, size_t len);

void do_quick_sort(void *input, size_t typeSize, int low, int high, int (*compare)(const void *, const void *));

void quick_sort(void *input, size_t typeSize, size_t numberOfElements, int (*compare)(const void *, const void *))
{
    do_quick_sort(input, typeSize, 0, numberOfElements - 1, compare);
}

void do_quick_sort(void *input, size_t typeSize, int low, int high, int (*compare)(const void *, const void *))
{
    if (high <= low)
        return;
        
    int p = partition(input, typeSize, low, high, compare);
    do_quick_sort(input, typeSize, low, p - 1, compare);
    do_quick_sort(input, typeSize, p + 1, high, compare);
}

int partition(void *input, size_t typeSize, int low, int high, int (*compare)(const void *, const void *))
{
    int firstHigh = low;
    int p = high;

    for (int i = low; i <= high; i++)
    {
        unsigned char *current = ((unsigned char *)input) + (typeSize * i);
        unsigned char *part = ((unsigned char *)input) + (typeSize * p);
        if (compare(current, part) == -1)
        {
            unsigned char *firstHighPtr = ((unsigned char *)input) + (typeSize * firstHigh);
            swap(current, firstHighPtr, typeSize);
            firstHigh++;
        }
    }

    unsigned char *firstHighPtr = ((unsigned char *)input) + (typeSize * firstHigh);
    unsigned char *part = ((unsigned char *)input) + (typeSize * p);

    swap(firstHighPtr, part, typeSize);

    return firstHigh;
}

void swap(void *a, void *b, size_t len)
{
    unsigned char *p = a;
    unsigned char *q = b;
    unsigned char temp;

    for (size_t i = 0; i < len; i++)
    {
        temp = p[i];
        p[i] = q[i];
        q[i] = temp;
    }
}