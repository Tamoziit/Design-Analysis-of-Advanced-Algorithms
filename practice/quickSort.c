#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 20

int partition(int *arr, int low, int high, int pivotIdx, int *c)
{
    int temp;
    temp = arr[pivotIdx];
    arr[pivotIdx] = arr[high];
    arr[high] = temp;

    int pivot = arr[high];
    int i = low - 1, j;

    for (j = low; j < high; j++)
    {
        (*c)++;
        if (arr[j] < pivot)
        {
            i++;
            temp = arr[j];
            arr[j] = arr[i];
            arr[i] = temp;
        }
    }

    temp = arr[high];
    arr[high] = arr[i + 1];
    arr[i + 1] = temp;

    return i + 1;
}

void quicksort(int *arr, int low, int high, int ch, int *c)
{
    static int pivotIdx;
    if (low < high)
    {
        switch (ch)
        {
        case 1:
            pivotIdx = low;
            break;
        case 2:
            pivotIdx = high;
            break;
        case 3:
            pivotIdx = low + (high - low) / 2;
            break;
        case 4:
            pivotIdx = low + rand() % (high - low + 1);
            break;
        default:
            pivotIdx = high;
        }
        pivotIdx = partition(arr, low, high, pivotIdx, c);
        quicksort(arr, low, pivotIdx - 1, ch, c);
        quicksort(arr, pivotIdx + 1, high, ch, c);
    }
}

void readInput(int *arr, int n, FILE *file)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (fscanf(file, "%d", &arr[i]) != 1)
        {
            printf("Error reading number at position %d\n", i);
            exit(1);
        }
    }
}

void display(int *arr, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    srand(time(NULL));
    int n, c = 0, i, j;
    int *arr1 = (int *)malloc(MAX * sizeof(int));
    int *arr2 = (int *)malloc(MAX * sizeof(int));
    int *arr3 = (int *)malloc(MAX * sizeof(int));
    int *arrCpy = (int *)malloc(MAX * sizeof(int));
    char *filename = (char *)malloc(MAX * sizeof(char));

    printf("Enter filename\n");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Error in reading file\n");
        exit(0);
    }
    if (fscanf(file, "%d", &n) != 1 || n <= 0 || n > MAX)
    {
        printf("Invalid array size in file.\n");
        fclose(file);
        exit(1);
    }

    printf("Ascending Sorted Array: ");
    readInput(arr1, n, file);
    display(arr1, n);

    printf("Descending Sorted Array: ");
    readInput(arr2, n, file);
    display(arr2, n);

    printf("Unsorted Array: ");
    readInput(arr3, n, file);
    display(arr3, n);
    printf("\n");

    printf("For Array 1 after Sorting\n");
    for (i = 1; i <= 4; i++)
    {
        c = 0;
        for (j = 0; j < n; j++)
        {
            arrCpy[j] = arr1[j];
        }
        printf("Sorting for pivot type: %d\n", i);
        quicksort(arrCpy, 0, n - 1, i, &c);
        printf("Sorted array: ");
        display(arrCpy, n);
        printf("Comparisons = %d\n", c);
    }
    printf("\n");

    printf("For Array 2 after Sorting\n");
    for (i = 1; i <= 4; i++)
    {
        c = 0;
        for (j = 0; j < n; j++)
        {
            arrCpy[j] = arr2[j];
        }
        printf("Sorting for pivot type: %d\n", i);
        quicksort(arrCpy, 0, n - 1, i, &c);
        printf("Sorted array: ");
        display(arrCpy, n);
        printf("Comparisons = %d\n", c);
    }
    printf("\n");

    printf("For Array 3 after Sorting\n");
    for (i = 1; i <= 4; i++)
    {
        c = 0;
        for (j = 0; j < n; j++)
        {
            arrCpy[j] = arr3[j];
        }
        printf("Sorting for pivot type: %d\n", i);
        quicksort(arrCpy, 0, n - 1, i, &c);
        printf("Sorted array: ");
        display(arrCpy, n);
        printf("Comparisons = %d\n", c);
    }
    printf("\n");

    free(arr1);
    free(arr2);
    free(arr3);
    free(arrCpy);
    free(filename);
    return 0;
}