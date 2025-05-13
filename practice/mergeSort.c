#include <stdio.h>
#include <stdlib.h>
#define MAX 20

void merge(int *arr, int start, int end, int mid, int *c)
{
    int p = start, q = mid + 1, k = 0, i;
    int arrCpy[end - start + 1];

    for (i = start; i <= end; i++)
    {
        (*c)++;
        if (p > mid)
            arrCpy[k++] = arr[q++];
        else if (q > end)
            arrCpy[k++] = arr[p++];
        else if (arr[p] < arr[q])
            arrCpy[k++] = arr[p++];
        else
            arrCpy[k++] = arr[q++];
    }

    for (i = 0; i < k; i++)
    {
        arr[start + i] = arrCpy[i];
    }
}

void mergesort(int *arr, int start, int end, int *c)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        mergesort(arr, start, mid, c);
        mergesort(arr, mid + 1, end, c);

        merge(arr, start, end, mid, c);
    }
}

void readInput(int *arr, int n, FILE *file)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (fscanf(file, "%d", &arr[i]) != 1)
        {
            printf("Error in reading input at pos: %d\n", i);
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
    int n, c = 0;
    int *arr1 = (int *)malloc(MAX * sizeof(int));
    int *arr2 = (int *)malloc(MAX * sizeof(int));
    int *arr3 = (int *)malloc(MAX * sizeof(int));
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

    readInput(arr1, n, file);
    printf("Ascending sorted array: ");
    display(arr1, n);
    printf("After Merge Sorting: ");
    mergesort(arr1, 0, n - 1, &c);
    display(arr1, n);
    printf("No. of comparisons = %d\n\n", c);
    c = 0;

    readInput(arr2, n, file);
    printf("Descending sorted array: ");
    display(arr2, n);
    printf("After Merge Sorting: ");
    mergesort(arr2, 0, n - 1, &c);
    display(arr2, n);
    printf("No. of comparisons = %d\n\n", c);
    c = 0;

    readInput(arr3, n, file);
    printf("Unsorted array: ");
    display(arr3, n);
    printf("After Merge Sorting: ");
    mergesort(arr3, 0, n - 1, &c);
    display(arr3, n);
    printf("No. of comparisons = %d\n\n", c);

    free(arr1);
    free(arr2);
    free(arr3);
    free(filename);
    return 0;
}