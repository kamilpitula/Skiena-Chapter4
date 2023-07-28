#include "leetCode.h"
#include "heap.h"
#include <stdlib.h>
#include <stdio.h>

int heap_compare_tuple(const void *a, const void *b)
{
    struct Tuple *p = (struct Tuple *)a;
    struct Tuple *q = (struct Tuple *)b;

    if (p->sum < q->sum)
        return 1;

    if (p->sum > q->sum)
        return -1;

    return 0;
}

int** kSmallestPairs(int* nums1, int nums1Size, int* nums2, int nums2Size, int k, int* returnSize, int** returnColumnSizes){

    struct Tuple pairs[nums1Size * nums2Size];

    int c = 0;
    for(int i = 0; i < nums1Size; i++){
        for(int j = 0; j < nums2Size; j++){
            
            struct Tuple tp = {
                .sum = nums1[i] + nums2[j],
                .i = i,
                .j = j,
            };

            pairs[c] = tp;
            c++;
        }
    }

    Heap *heap;

    init_heap(&heap, nums1Size * nums2Size, sizeof(struct Tuple), heap_compare_tuple);
    make_heap(heap, pairs, nums1Size * nums2Size); // O(n)

    struct Tuple resTemp[k];
    int resCount = 0;
    
    for(int i = 0; i < k; i++){
        struct Tuple temp;

        int hRes = extract_root(heap, &temp);

        if(hRes == -1)
            break;
        
        resTemp[i] = temp;
        resCount++;
    }
    
    int** res = malloc(sizeof(int*) * resCount);

    for(int i = 0; i < resCount; i++){
        int* temp = malloc(sizeof(int) * 2);
        temp[0] = resTemp[i].i;
        temp[1] = resTemp[i].j;
        

        res[i] = temp;
    }

    *returnColumnSizes = (int *)malloc(sizeof(int) * resCount);

    for(int i = 0; i < resCount; i++){
        (*returnColumnSizes)[i] = 2;
    }

    *returnSize = resCount;
    return res;
}