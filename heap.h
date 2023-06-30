#include <stddef.h>

typedef struct
{
    int *buffer;
    size_t size;
    int n;
} Heap;

extern void init_heap(Heap **heap, size_t size);

extern void heap_insert(Heap *heap, int n);

extern int extract_min(Heap *heap);