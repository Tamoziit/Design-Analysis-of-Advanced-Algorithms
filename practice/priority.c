#include <stdio.h>
#include <stdlib.h>

void minHeapify(int *arr, int size, int i)
{
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int min;

    if (l < size && arr[l] < arr[i])
        min = l;
    else
        min = i;
    if (r < size && arr[r] < arr[min])
        min = r;

    if (min != i)
    {
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
        minHeapify(arr, size, min);
    }
}

void enqueue(int *arr, int x, int *i, int size)
{
    (*i)++;
    if ((*i) >= size)
    {
        printf("Overflow\n");
        (*i)--;
        return;
    }

    arr[(*i)] = x;
    int child = *i;
    int parent = (child - 1) / 2;
    while (child > 0 && arr[parent] > arr[child])
    {
        int temp = arr[parent];
        arr[parent] = arr[child];
        arr[child] = temp;

        child = parent;
        parent = (child - 1) / 2;
    }
}

void dequeue(int *arr, int *i, int size)
{
    if ((*i) < 0)
    {
        printf("Underflow\n");
        return;
    }

    int min = arr[0];
    arr[0] = arr[(*i)];
    (*i)--;
    minHeapify(arr, (*i) + 1, 0);

    printf("Dequeued = %d\n", min);
}

void heapDecreaseKey(int *arr, int i, int key, int size)
{
    if (i < 0 || i >= size)
    {
        printf("Invalid\n");
        return;
    }

    if (key > arr[i])
    {
        printf("New key shld be smaller\n");
        return;
    }

    arr[i] = key;
    int child = i;
    int parent = (child - 1) / 2;
    while (child > 0 && arr[parent] > arr[child])
    {
        int temp = arr[parent];
        arr[parent] = arr[child];
        arr[child] = temp;

        child = parent;
        parent = (child - 1) / 2;
    }
}

void display(int *arr, int i)
{
    if (i < 0)
        return;

    int j;
    for (j = 0; j <= i; j++)
        printf("%d ", arr[j]);
    printf("\n");
}

int main()
{
    int i = -1, n, ch, k, idx;
    printf("Enter the size\n");
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));

    while (1)
    {
        printf("Enter\n 1. Enqueue\n 2. Dequeue\n 3. Heap Decrease key\n 4. Exit\n");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("Enter Ele\n");
            scanf("%d", &k);
            enqueue(arr, k, &i, n);
            display(arr, i);
            break;
        case 2:
            dequeue(arr, &i, n);
            display(arr, i);
            break;
        case 3:
            printf("Enter index & new value\n");
            scanf("%d%d", &idx, &k);
            heapDecreaseKey(arr, idx, k, n);
            display(arr, i);
            break;
        case 4:
            printf("EOP\n");
            free(arr);
            exit(0);
        default:
            printf("Wrong Choice!\n");
        }
    }

    return 0;
}