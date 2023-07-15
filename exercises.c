#include "exercises.h"
#include "sorting.h"
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
