#include <stddef.h>

extern void quick_sort(void *input, size_t typeSize, size_t numberOfElements, int (*compare)(const void *, const void *));