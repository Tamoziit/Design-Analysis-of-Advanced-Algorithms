#include <stdio.h>
#include <stdlib.h>

void merge(int *arr, int start, int mid, int end, int *comps)
{
    int p = start, q = mid + 1;
    int arrCpy[end - start + 1], k = 0, c;

    int i;
    // merging the subarrays in sorted order
    for (i = start; i <= end; i++)
    {
        (*comps)++;
        if (p > mid)
            arrCpy[k++] = arr[q++];
        else if (q > end)
            arrCpy[k++] = arr[p++];
        else if (arr[p] < arr[q])
            arrCpy[k++] = arr[p++];
        else
            arrCpy[k++] = arr[q++];
    }

    // copying back the elements
    for (i = 0; i < k; i++)
    {
        arr[start + i] = arrCpy[i];
    }
}

void mergeSort(int *arr, int start, int end, int *comps)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        // dividing into 2 subarrays
        mergeSort(arr, start, mid, comps);
        mergeSort(arr, mid + 1, end, comps);

        merge(arr, start, mid, end, comps); // for merging the 2 subarrays
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
    int arr1[10];
    int arr2[10];
    int arr3[10];
    int n = 10, start = 0, end = 9, comps = 0, i;

    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("Error in reading input file\n");
        exit(1);
    }

    for (i = 0; i < n; i++)
    {
        fscanf(file, "%d\n", &arr1[i]);
    }
    for (i = 0; i < n; i++)
    {
        fscanf(file, "%d\n", &arr2[i]);
    }
    for (i = 0; i < n; i++)
    {
        fscanf(file, "%d\n", &arr3[i]);
    }
    fclose(file);

    printf("Before sorting\n");
    printf("Array 1: ");
    display(arr1, n);
    printf("Array 2: ");
    display(arr2, n);
    printf("Array 3: ");
    display(arr3, n);
    printf("\n");

    printf("After sorting\n");
    mergeSort(arr1, start, end, &comps);
    printf("Array 1: ");
    display(arr1, n);
    printf("No. of Comparisons = %d", comps);
    printf("\n");
    comps = 0;

    mergeSort(arr2, start, end, &comps);
    printf("Array 2: ");
    display(arr2, n);
    printf("No. of Comparisons = %d", comps);
    printf("\n");
    comps = 0;

    mergeSort(arr3, start, end, &comps);
    printf("Array 3: ");
    display(arr3, n);
    printf("No. of Comparisons = %d", comps);
    printf("\n");
    comps = 0;

    return 0;
}