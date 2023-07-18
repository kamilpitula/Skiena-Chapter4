#include "exercises.h"
#include "sorting.h"
#include "heap.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int Key;
    char *Value;
} KeyValuePair;

typedef struct
{
    int Item1;
    int Item2;
} Tuple;

void do_minimize_sorted(int *sortedArray, size_t size);
void do_sort_by_colour(KeyValuePair *sortedArray, size_t length);
bool does_sum_exist(int *firstSet, int *secondSet, size_t setsLength, int target, Tuple *result);
int binary_search(int *arr, int l, int h, int x);
void prepare_combinations(int *data, int *counter, int n, int k, int start, int index, int combinations_ix[][k]);

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

// Exercise 4.2
void maximize_unsorted()
{
    printf("Exercise 4.2 - a\n");

    int unsortedArray[] = {6, 13, 19, 3, 8};

    int max = INT_MIN;
    int min = INT_MAX;

    for (int i = 0; i < 5; i++)
    {
        if (unsortedArray[i] < min)
            min = unsortedArray[i];

        if (unsortedArray[i] > max)
            max = unsortedArray[i];
    }

    printf("Selected values: %i - %i\n", max, min);
}

void maximize_sorted()
{
    printf("Exercise 4.2 - b\n");

    int sortedArray[] = {3, 6, 8, 13, 19};

    int min = sortedArray[0];
    int max = sortedArray[4];

    printf("Selected values: %i - %i\n", max, min);
}

void minimize_unsorted()
{
    printf("Exercise 4.2 - c\n");

    int unsortedArray[] = {6, 13, 19, 3, 8};

    quick_sort(unsortedArray, sizeof(int), 5, compare_int);

    do_minimize_sorted(unsortedArray, 5);
}

void minimize_sorted()
{
    printf("Exercise 4.2 - d\n");

    int sortedArray[] = {3, 6, 8, 13, 19};

    do_minimize_sorted(sortedArray, 5);
}

void do_minimize_sorted(int *sortedArray, size_t size)
{
    int first_index = INT_MIN;
    int second_index = INT_MAX;
    int min_value = INT_MAX;

    for (int i = 1; i < size; i++)
    {
        int result = abs(sortedArray[i - 1] - sortedArray[i]);
        if (result < min_value)
        {
            min_value = result;
            first_index = i - 1;
            second_index = i;
        }
    }

    printf("Selected values: %i - %i\n", sortedArray[first_index], sortedArray[second_index]);
}

//------------------------------------------------------------------------------------------------------------

// Exercise 4.3

void pair_with_smallest_sum()
{
    printf("Exercise 4.3 \n");

    int inputArray[] = {1, 4, 9, 2};
    quick_sort(inputArray, sizeof(int), 4, compare_int);

    Tuple pairs[2];

    for (int i = 0; i < 2; i++)
    {
        Tuple pair = {
            .Item1 = inputArray[i],
            .Item2 = inputArray[3 - i],
        };

        pairs[i] = pair;
    }

    printf("Selected pairs:\n");

    for (int i = 0; i < 2; i++)
    {
        printf("Pair %i: (%i, %i)\n", i, pairs[i].Item1, pairs[i].Item2);
    }
}

//------------------------------------------------------------------------------------------------------------

// Exercise 4.4

void sort_by_colour()
{
    printf("\nExercise 4.4\n");
    KeyValuePair sortedArray[] = {
        {.Key = 1, .Value = "blue"},
        {.Key = 3, .Value = "red"},
        {.Key = 4, .Value = "blue"},
        {.Key = 6, .Value = "yellow"},
        {.Key = 9, .Value = "red"},
    };

    do_sort_by_colour(sortedArray, 5);
}

void do_sort_by_colour(KeyValuePair *sortedArray, size_t length)
{
    int blueCount = 0;
    int redCount = 0;
    int yellowCount = 0;

    for (int i = 0; i < length; i++)
    {
        KeyValuePair current = sortedArray[i];
        if (current.Value == "blue")
            blueCount++;

        if (current.Value == "red")
            redCount++;
    }

    KeyValuePair result[length];

    int redIndex = 0;
    int blueIndex = redCount;
    int yellowIndex = blueCount + redCount;
    for (int i = 0; i < length; i++)
    {
        KeyValuePair current = sortedArray[i];
        if (current.Value == "blue")
        {
            result[blueIndex] = current;
            blueIndex++;
        }

        if (current.Value == "red")
        {
            result[redIndex] = current;
            redIndex++;
        }

        if (current.Value == "yellow")
        {
            result[yellowIndex] = current;
            yellowIndex++;
        }
    }

    printf("\nSort by colour result:\n");

    for (int i = 0; i < length; i++)
    {
        printf("Item: %i, key: %i, value: %s\n", i, result[i].Key, result[i].Value);
    }
}

// Exercise 4.6

void find_sum()
{
    printf("\nExercise 4.6\n");
    int set1[] = {2, 8, 4, 13, 1};
    int set2[] = {9, 7, 5, 11, 3};
    int target = 13;

    Tuple values = {.Item1 = -1, .Item2 = -1};
    bool result = does_sum_exist(set1, set2, 5, target, &values);

    printf("%s sum for target: %i\n", result ? "Found" : "Did not find", target);
    if (result)
        printf("Values: (%i, %i)\n", values.Item1, values.Item2);
}

bool does_sum_exist(int *firstSet, int *secondSet, size_t setsLength, int target, Tuple *result)
{
    quick_sort(firstSet, sizeof(int), setsLength, compare_int);
    quick_sort(secondSet, sizeof(int), setsLength, compare_int);

    int firstIndex = 0;
    int secondIndex = setsLength - 1;

    while (firstIndex < setsLength && secondIndex >= 0)
    {
        int currentValue = firstSet[firstIndex] + secondSet[secondIndex];
        if (currentValue == target)
        {
            result->Item1 = firstSet[firstIndex];
            result->Item2 = secondSet[secondIndex];
            return true;
        }

        if (currentValue > target)
            secondIndex--;

        if (currentValue < target)
            firstIndex++;
    }

    return false;
}
//------------------------------------------------------------------------------------------------------------

// Exercise 4.7

void calculate_citations_index()
{
    printf("\nExercise 4.7\n");
    // sorted: 2,3,4,4,4,5,7,8,9,12
    int citations_array[] = {8, 2, 4, 4, 5, 3, 7, 9, 4, 12};
    int length = 10;
    quick_sort(citations_array, sizeof(int), length, compare_int);

    int index = 0;
    for (int i = 9; i >= 0; i--)
    {
        if (citations_array[i] <= length - i)
        {
            index = length - i;
            break;
        }
    }

    printf("Citation index: %i\n", index);
}

//------------------------------------------------------------------------------------------------------------

// Exercise 4.9

void does_k_sum_exist()
{
    int arr[] = {8, 2, 5, 3, 9};
    int arr_length = 5;
    int t = 13;
    int k = 3;

    quick_sort(arr, sizeof(int), arr_length, compare_int); // O(nlogn)
    int data[k - 1];
    int(*combinations_ix)[100][k - 1] = malloc(sizeof(*combinations_ix));
    int counter = 0;
    prepare_combinations(data, &counter, arr_length, k - 1, 0, 0, *combinations_ix); // O(n^(k-1))

    bool found = false;

    for (int i = 0; i < counter; i++) // O(n^(k-1))
    {
        int sum = 0;
        for (int j = 0; j < k - 1; j++)
        {
            int index = (*combinations_ix)[i][j];
            sum += arr[index];
        }

        int search_res = binary_search(arr, 0, arr_length - 1, t - sum); // O(log n)

        if (search_res != -1)
        {
            found = true;
            break;
        }
    }

    printf("%s sum in an array\n", found ? "Found" : "Didn't find");

    free(combinations_ix);
}

void prepare_combinations(int *data, int *counter, int n, int k, int start, int index, int combinations_ix[][k])
{
    if (index == k)
    {
        for (int i = 0; i < k; i++)
        {
            combinations_ix[*counter][i] = data[i];
        }
        (*counter) += 1;
        return;
    }

    for (int i = start; i < n; i++)
    {
        data[index] = i;
        prepare_combinations(data, counter, n, k, i + 1, index + 1, combinations_ix);
    }
}

int binary_search(int *arr, int l, int h, int x)
{
    if (l > h)
        return -1;

    int mid = l + (h - l) / 2;

    if (arr[mid] == x)
        return mid;

    if (arr[mid] < x)
        return binary_search(arr, l, mid - 1, x);

    if (arr[mid] > x)
        return binary_search(arr, mid + 1, h, x);
}

//------------------------------------------------------------------------------------------------------------

// Exercise 4.13
struct TimeLog
{
    int time;
    int type; // enter = 0, exit = 1
};

int compare_timelog(const void *a, const void *b)
{
    struct TimeLog *p = (struct TimeLog *)a;
    struct TimeLog *q = (struct TimeLog *)b;

    if (p->time < q->time)
        return -1;

    if (p->time > q->time)
        return 1;

    return 0;
}

void find_most_people_present()
{
    printf("\nExercise 4.13\n");

    int intervals[5][2] = {
        {0, 9},
        {1, 4},
        {5, 8},
        {3, 6},
        {2, 7},
    };

    struct TimeLog log[10];

    for (int i = 0; i < 5; i++)
    {
        struct TimeLog enter = {
            .time = intervals[i][0],
            .type = 0,
        };

        struct TimeLog exit = {
            .time = intervals[i][1],
            .type = 1,
        };

        log[i * 2] = enter;
        log[i * 2 + 1] = exit;
    }

    quick_sort(log, sizeof(struct TimeLog), 10, compare_timelog);

    int current = 0;

    int currentMaxStart = 0;
    int currentMaxEnd = 0;
    int currentMax = 0;

    for (int i = 0; i < 10; i++)
    {
        if (log[i].type == 0)
        {
            current++;
        }

        if (log[i].type == 1)
        {
            if (currentMax < current)
            {
                currentMax = current;
                currentMaxStart = i - 1;
                currentMaxEnd = i;
            }
            current--;
        }
    }

    printf("The most people were present between %i and %i\n", log[currentMaxStart].time, log[currentMaxEnd].time);
}

//------------------------------------------------------------------------------------------------------------

// Exercise 4.13

int compare_intervals(const void *a, const void *b)
{
    int *p = (int *)a;
    int *q = (int *)b;

    if (p[0] < q[0])
        return -1;

    if (p[0] > q[0])
        return 1;

    return 0;
}

void merge_overlapping_intervals()
{
    printf("\nExercise 4.14\n");

    int intervals[6][2] = {
        {2, 6},
        {1, 3},
        {8, 10},
        {7, 9},
        {7, 18},
        {20, 22},
    };

    quick_sort(intervals, sizeof(int[2]), 4, compare_intervals);

    int currentStart = intervals[0][0];
    int currentEnd = intervals[0][1];

    int buffer[10][2];
    int counter = 0;

    for (int i = 0; i < 5; i++)
    {
        if (intervals[i][1] >= intervals[i + 1][0])
        {
            if (currentEnd > intervals[i + 1][1])
                continue;
            currentEnd = intervals[i + 1][1];
        }

        if (intervals[i][1] < intervals[i + 1][0])
        {
            buffer[counter][0] = currentStart;
            buffer[counter][1] = currentEnd;
            counter++;

            currentStart = intervals[i + 1][0];
            currentEnd = intervals[i + 1][1];
        }
    }

    buffer[counter][0] = currentStart;
    buffer[counter][1] = currentEnd;
    counter++;

    printf("Merged set into intervals: \n");
    for (int i = 0; i < counter; i++)
    {
        printf("* start: %i end: %i\n", buffer[i][0], buffer[i][1]);
    }
}

//------------------------------------------------------------------------------------------------------------

// Exercise 4.17

int heap_compare_int(const void *a, const void *b)
{
    int *p = (int *)a;
    int *q = (int *)b;

    if (*p < *q)
        return 1;

    if (*p == *q)
        return 0;

    return -1;
}

void find_k_smallest()
{
    printf("\nExercise 4.17\n");

    int k = 3;
    int array[] = {4, 1, 7, 9, 21, 3, 0, -3};
    int ARR_LENGTH = 8;

    Heap *heap;

    init_heap(&heap, ARR_LENGTH, sizeof(int), heap_compare_int);
    make_heap(heap, array, ARR_LENGTH); // O(n)

    printf("Printing k smallest elements of the array:\n");
    for (int i = 0; i < k; i++) // O(k*log(n))
    {
        int min;
        extract_root(heap, &min);

        printf("The %i smallest element: %i\n", i + 1, min);
    }

    free_heap(heap);
}

//------------------------------------------------------------------------------------------------------------

// Exercise 4.18 O(nk)

void do_merge_sorted_arrays_nk(int k, int n, int *arrays[k], int arrays_len[k], int res[n]);
void merge_sorted_arrays_nk()
{
    printf("\nExercise 4.18 O(nk)\n");

    int array1[] = {1, 4, 8};
    int array2[] = {0, 6, 12, 14};
    int array3[] = {-1, 3, 7, 11, 21};

    int *arrays[] = {
        array1,
        array2,
        array3,
    };

    int arrays_len[3] = {
        3,
        4,
        5,
    };

    int res[12];

    do_merge_sorted_arrays_nk(3, 12, arrays, arrays_len, res);

    printf("Merged arrays using O(nk) algorithm\n");
    for(int i = 0; i < 12; i++){
        printf("%i ", res[i]);
    }
    printf("\n\n");
}

void do_merge_sorted_arrays_nk(int k, int n, int *arrays[k], int arrays_len[k], int res[n])
{
    int currentIndexes[k];
    int currentResIndex = 0;

    for (int i = 0; i < k; i++)
    {
        currentIndexes[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        int currentMin_ix = -1;
        for (int j = 0; j < k; j++)
        {
            if (currentIndexes[j] >= arrays_len[j])
                continue;

            if (currentMin_ix == -1)
            {
                currentMin_ix = j;
                continue;
            }

            if (arrays[j][currentIndexes[j]] < arrays[currentMin_ix][currentIndexes[currentMin_ix]])
                currentMin_ix = j;
        }

        res[currentResIndex] = arrays[currentMin_ix][currentIndexes[currentMin_ix]];
        currentResIndex++;
        currentIndexes[currentMin_ix]++;
    }
}

//------------------------------------------------------------------------------------------------------------
