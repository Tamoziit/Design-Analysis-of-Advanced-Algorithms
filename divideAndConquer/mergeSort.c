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
        if (p > mid)
        {
            arrCpy[k++] = arr[q++];
            c = 1;
        }
        else if (q > end)
        {
            arrCpy[k++] = arr[p++];
            c = 2;
        }
        else if (arr[p] < arr[q])
        {
            arrCpy[k++] = arr[p++];
            c = 3;
        }
        else
        {
            arrCpy[k++] = arr[q++];
            c = 4;
        }

        *comps = (*comps) + c;
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
    int arr1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int arr2[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int arr3[10] = {6, 3, 9, 1, 8, 10, 2, 5, 4, 7};
    int n = 10, start = 0, end = 9, comps = 0;

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