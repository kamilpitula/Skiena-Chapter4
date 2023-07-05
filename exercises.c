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

    quick_sort(unsortedArray, 5);

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
    quick_sort(inputArray, 4);

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
    int set1[] = {2, 8, 4, 13, 1};
    int set2[] = {9, 7, 5, 11, 3};
    int target = 13;

    Tuple values = {.Item1 = -1, .Item2 = -1};
    bool result = does_sum_exist(set1, set2, 5, target, &values);

    printf("%s sum for target: %i\n", result ? "Found" : "Did not find", target);
    if (result)
        printf("Values: (%i, %i)", values.Item1, values.Item2);
}

bool does_sum_exist(int *firstSet, int *secondSet, size_t setsLength, int target, Tuple *result)
{
    quick_sort(firstSet, setsLength);
    quick_sort(secondSet, setsLength);

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