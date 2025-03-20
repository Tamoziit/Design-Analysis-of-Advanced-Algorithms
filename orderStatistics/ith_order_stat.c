#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int comps = 0;

int randomizedPartition(int *arr, int p, int r)
{
    int randomIndex = p + rand() % (r - p + 1);
    int temp = arr[randomIndex];
    arr[randomIndex] = arr[r];
    arr[r] = temp;

    int pivot = arr[r];
    int i = p - 1, j;

    for (j = p; j < r; j++)
    {
        comps++;
        if (arr[j] < pivot)
        {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    temp = arr[i + 1];
    arr[i + 1] = arr[r];
    arr[r] = temp;

    return i + 1;
}

int randomizedSelect(int *arr, int p, int r, int i)
{
    if (p == r)
    {
        return arr[p];
    }

    int q = randomizedPartition(arr, p, r);
    int k = q - p + 1;
    if (i == k)
    {
        return arr[q];
    }
    else if (i < k)
    {
        return randomizedSelect(arr, p, q - 1, i);
    }
    else
    {
        return randomizedSelect(arr, q + 1, r, i - k);
    }
}

int main()
{
    srand(time(NULL));
    int n;
    printf("Enter the size of the array\n");
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    int p = 0, r = n - 1, i, j;

    printf("Enter the elements of the array\n");
    for (j = 0; j < n; j++)
    {
        scanf("%d", &arr[j]);
    }

    printf("Array = ");
    for (j = 0; j < n; j++)
        printf("%d ", arr[j]);
    printf("\n");

    printf("Enter the ith order statistics to be found\n");
    scanf("%d", &i);
    int res = randomizedSelect(arr, p, r, i);
    printf("%dth order statistics of the array = %d\n", i, res);
    return 0;
}