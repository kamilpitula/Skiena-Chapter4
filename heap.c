#include "heap.h"
#include <stdlib.h>

void init_heap(Heap **heap, size_t size)
{
    Heap *newHeap = malloc(sizeof(Heap));
    newHeap->buffer = malloc(sizeof(int) * size);
    newHeap->n = 0;
    newHeap->size = size;
    *heap = newHeap;
}

void heap_insert(Heap *heap, int n)
{
    if (heap->n >= heap->size)
        printf("Cannot insert element. Heap size exceeded");
    else
    {
        heap->n += 1;
        heap->buffer[heap->n - 1] = n;
        bubble_up(heap, heap->n);
    }
}

void bubble_up(Heap *heap, int p)
{
    if (pq_parent(p) == -1)
        return;

    if (heap->buffer[pq_parent(p) - 1] > heap->buffer[p - 1])
    {
        int temp = heap->buffer[pq_parent(p) - 1];
        heap->buffer[pq_parent(p) - 1] = heap->buffer[p - 1];
        heap->buffer[p - 1] = temp;
        bubble_up(heap, pq_parent(p));
    }
}

int pq_parent(int n)
{
    if (n == 1)
        return -1;

    return n / 2;
}

int pq_young_child(int n)
{
    return 2 * n;
}