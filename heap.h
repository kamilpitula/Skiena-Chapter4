#include <stddef.h>

typedef struct
{
    void *buffer;
    size_t size;
    size_t typeSize;
    int freeSpot;
    int (*compare)(const void *, const void *);
} Heap;

extern void init_heap(Heap **heap, size_t bufferSize, size_t typeSize, int (*compare)(const void *, const void *));

extern void free_heap(Heap *heap);

extern void heap_insert(Heap *heap, void *n);

extern int extract_root(Heap *heap, void *min);

extern void make_heap(Heap *heap, void *input, size_t n);