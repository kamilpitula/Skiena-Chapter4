#include "heap.h"
#include <stdlib.h>
#include <stdio.h>

void init_heap(Heap **heap, size_t bufferSize, size_t typeSize, int (*compare)(const void *, const void *))
{
    Heap *newHeap = malloc(sizeof(Heap));
    newHeap->buffer = malloc(typeSize * bufferSize);
    newHeap->freeSpot = 0;
    newHeap->size = bufferSize;
    newHeap->typeSize = typeSize;
    newHeap->compare = compare;
    *heap = newHeap;
}

void free_heap(Heap *heap)
{
    free(heap->buffer);
    free(heap);
}

void bubble_up(Heap *heap, int p);
void bubble_down(Heap *heap, int p);
int pq_parent(int n);
int pq_young_child(int n);

void heap_swap(Heap *heap, int position_a, int position_b)
{
    unsigned char *ptr = heap->buffer + (heap->typeSize * position_a);
    unsigned char *val = heap->buffer + (heap->typeSize * position_b);

    unsigned char *p = ptr;
    unsigned char *q = val;
    unsigned char temp;

    for (size_t i = 0; i < heap->typeSize; i++)
    {
        temp = p[i];
        p[i] = q[i];
        q[i] = temp;
    }
}

void assignValue(Heap *heap, int position, void *value)
{
    unsigned char *ptr = heap->buffer + (heap->typeSize * position);
    unsigned char *val = value;

    for (int i = 0; i < heap->typeSize; i++)
        ptr[i] = val[i];
}

void *getValue(Heap *heap, int position)
{
    return heap->buffer + (heap->typeSize * position);
}

void getCopy(Heap *heap, int position, void *ret)
{
    unsigned char *r = (unsigned char *)ret;
    unsigned char *ptr = heap->buffer + (heap->typeSize * position);

    for (int i = 0; i < heap->typeSize; i++)
        r[i] = ptr[i];
}

void heap_insert(Heap *heap, void *n)
{
    if (heap->freeSpot >= heap->size)
        printf("Cannot insert element. Heap size exceeded");
    else
    {
        // insert to the first free index of the array
        assignValue(heap, heap->freeSpot, n);
        heap->freeSpot += 1;

        // inserted element might have a greater value than its parent
        // so we need to change their positions if that is the case
        bubble_up(heap, heap->freeSpot - 1);
    }
}

int extract_root(Heap *heap, void *min)
{
    if (heap->freeSpot <= 0)
    {
        printf("Heap is empty!");
        min = NULL;
        return -1;
    }

    // the element with the smallest value is always stored at first position
    // which represents the root of the heap
    getCopy(heap, 0, min);

    // we replace the element with the rightmost leaf
    void *rightMostLeaf = getValue(heap, heap->freeSpot - 1);
    assignValue(heap, 0, rightMostLeaf);
    heap->freeSpot--;

    // now, the structure of the tree might be broken so we need to
    // bubble down the replaced element until the heap is valid
    bubble_down(heap, 0);

    return 0;
}

void make_heap(Heap *heap, void *input, size_t n)
{
    heap->freeSpot = n;

    for (int i = 0; i < n; i++)
    {
        void *value = ((unsigned char *)input) + (heap->typeSize * i);
        assignValue(heap, i, value);
    }

    // after initializing the buffer with the array's elements
    // we need to rearange all elements to make the heap valid.
    // since all leaves are valid heaps (with one element) and there
    // are n/2 leaves it suffice to bubble down elements starting from
    // the first non-leaf element
    for (int i = (n / 2) - 1; i >= 0; i--)
        bubble_down(heap, i);
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
            void *min = getValue(heap, min_index);
            void *youngest = getValue(heap, youngest_child_ix + i);

            if (heap->compare(min, youngest) == -1)
            {
                min_index = youngest_child_ix + i;
            }
        }
    }
    // when parent element is not the smallest - swap
    // then repeat recursevely down the heap until it is
    if (min_index != p)
    {
        heap_swap(heap, p, min_index);
        bubble_down(heap, min_index);
    }
}

void bubble_up(Heap *heap, int elementIndex)
{
    // current element is a root, we don't need to do anything
    if (pq_parent(elementIndex) == -1)
        return;

    void *parent = getValue(heap, pq_parent(elementIndex));
    void *current = getValue(heap, elementIndex);
    if (heap->compare(parent, current) == -1)
    {
        // if parent is greater than newly inserted child
        heap_swap(heap, pq_parent(elementIndex), elementIndex);

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