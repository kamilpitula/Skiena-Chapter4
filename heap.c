#include "heap.h"
#include <stdlib.h>
#include <stdio.h>

void init_heap(Heap **heap, size_t size)
{
    Heap *newHeap = malloc(sizeof(Heap));
    newHeap->buffer = malloc(sizeof(int) * size);
    newHeap->freeSpot = 0;
    newHeap->size = size;
    *heap = newHeap;
}

void bubble_up(Heap *heap, int p);
void bubble_down(Heap *heap, int p);
int pq_parent(int n);
int pq_young_child(int n);

void heap_insert(Heap *heap, int n)
{
    if (heap->freeSpot >= heap->size)
        printf("Cannot insert element. Heap size exceeded");
    else
    {
        // insert to the first free index of the array
        heap->buffer[heap->freeSpot] = n;
        heap->freeSpot += 1;

        // inserted element might have a greater value than its parent
        // so we need to change their positions if that is the case
        bubble_up(heap, heap->freeSpot - 1);
    }
}

int extract_min(Heap *heap)
{
    if (heap->freeSpot <= 0)
    {
        printf("Heap is empty!");
        return -1;
    }

    // the element with the smallest value is always stores at first position
    // which represents the root of the heap
    int min = heap->buffer[0];

    // we replace the element with the rightmost leaf
    heap->buffer[0] = heap->buffer[heap->freeSpot - 1];
    heap->freeSpot--;

    // now, the structure of the tree might be broken so we need to
    // bubble down the replaced element until the heap is valid
    bubble_down(heap, 0);

    return min;
}

void bubble_down(Heap *heap, int p)
{
    int min_index = p;

    int youngest_child_ix = pq_young_child(p);

    // check left and right child
    for (int i = 0; i <= 1; i++)
    {
        // check if we are not out of range of the heap
        if ((youngest_child_ix + i) <= heap->freeSpot - 1)
        {
            if (heap->buffer[min_index] > heap->buffer[youngest_child_ix + i])
            {
                min_index = youngest_child_ix + i;
            }
        }
    }
    // when parent element is not the smallest - swap
    // then repeat recursevely down the heap until it is
    if (min_index != p)
    {
        int temp = heap->buffer[p];
        heap->buffer[p] = heap->buffer[min_index];
        heap->buffer[min_index] = temp;
        bubble_down(heap, min_index);
    }
}

void bubble_up(Heap *heap, int elementIndex)
{
    // current element is a root, we don't need to do anything
    if (pq_parent(elementIndex) == -1)
        return;

    if (heap->buffer[pq_parent(elementIndex)] > heap->buffer[elementIndex])
    {
        // if parent is greater than newly inserted child - swap
        int temp = heap->buffer[pq_parent(elementIndex)];
        heap->buffer[pq_parent(elementIndex)] = heap->buffer[elementIndex];
        heap->buffer[elementIndex] = temp;

        // now the new parent can be bigger then its parent so we need to recursively
        // repeat that operation until we reach the root element
        bubble_up(heap, pq_parent(elementIndex));
    }
}

int pq_parent(int childIndex)
{
    if (childIndex == 0)
        return -1;

    return (childIndex - 1) / 2;
}

int pq_young_child(int parentIndex)
{
    return (2 * parentIndex) + 1;
}