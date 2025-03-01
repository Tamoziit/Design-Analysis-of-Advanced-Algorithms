#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Partition function with different pivot selection strategies
int partition(int arr[], int low, int high, int *c, int pivotIdx)
{
    // Moving pivot to the end
    int temp = arr[pivotIdx];
    arr[pivotIdx] = arr[high];
    arr[high] = temp;

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        (*c)++;
        if (arr[j] < pivot)
        {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

// QuickSort function
void quickSort(int arr[], int low, int high, int *c, int pivotType)
{
    static int pivotIdx;
    if (low < high)
    {
        switch (pivotType)
        {
        case 1: // First element as pivot
            pivotIdx = low;
            break;
        case 2: // Last element as pivot
            pivotIdx = high;
            break;
        case 3: // Middle element as pivot
            pivotIdx = low + (high - low) / 2;
            break;
        case 4: // Random element as pivot
            pivotIdx = low + rand() % (high - low + 1);
            break;
        default:
            pivotIdx = high; // Defaulting to last element as pivot
        }
        pivotIdx = partition(arr, low, high, c, pivotIdx);
        quickSort(arr, low, pivotIdx - 1, c, pivotType);
        quickSort(arr, pivotIdx + 1, high, c, pivotType);
    }
}

void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    srand(time(NULL)); // Seed for random pivot selection
    int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int arr2[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int arr3[] = {3, 7, 1, 9, 4, 6, 8, 2, 10, 5};
    int size = sizeof(arr1) / sizeof(arr1[0]);
    int c;
    int arrCopy[size];

    printf("Before Sorting The arrays\n");
    printf("Array 1: ");
    printArray(arr1, size);
    printf("Array 2: ");
    printArray(arr2, size);
    printf("Array 3: ");
    printArray(arr3, size);
    printf("\n");

    printf("After Sorting:\n");
    printf("For Array 1:\n");
    for (int i = 1; i <= 4; i++)
    {
        for (int j = 0; j < size; j++)
            arrCopy[j] = arr1[j];
        c = 0;
        printf("QuickSort using Pivot Type %d:\n", i);
        quickSort(arrCopy, 0, size - 1, &c, i);
        printf("Sorted array: ");
        printArray(arrCopy, size);
        printf("Comparisons = %d\n", c);
    }
    printf("\n");

    printf("For Array 2:\n");
    for (int i = 1; i <= 4; i++)
    {
        for (int j = 0; j < size; j++)
            arrCopy[j] = arr2[j];
        c = 0;
        printf("QuickSort using Pivot Type %d:\n", i);
        quickSort(arrCopy, 0, size - 1, &c, i);
        printf("Sorted array: ");
        printArray(arrCopy, size);
        printf("Comparisons = %d\n", c);
    }
    printf("\n");

    printf("For Array 3:\n");
    for (int i = 1; i <= 4; i++)
    {
        for (int j = 0; j < size; j++)
            arrCopy[j] = arr3[j];
        c = 0;
        printf("QuickSort using Pivot Type %d:\n", i);
        quickSort(arrCopy, 0, size - 1, &c, i);
        printf("Sorted array: ");
        printArray(arrCopy, size);
        printf("Comparisons = %d\n", c);
    }
    printf("\n");

    return 0;
}