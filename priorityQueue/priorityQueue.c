#include <stdio.h>
#include <stdlib.h>

void maxHeapify(int *arr, int i, int size)
{
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	int max, t;

	if (l < size && arr[l] > arr[i])
		max = l;
	else
		max = i;

	if (r < size && arr[r] > arr[max])
		max = r;

	if (max != i)
	{
		t = arr[i];
		arr[i] = arr[max];
		arr[max] = t;
		maxHeapify(arr, max, size);
	}
}

void buildMaxHeap(int *arr, int size)
{
	int i;
	for (i = size / 2 - 1; i >= 0; i--)
	{
		maxHeapify(arr, i, size);
	}
}

void enqueue(int *arr, int size, int *i, int x)
{
    (*i)++;
    if ((*i) >= size)
    {
        printf("Overflow\n");
        (*i)--; // Prevent out-of-bounds issues
        return;
    }

    arr[*i] = x; // Insert new element at the end
    int child = *i;
    int parent = (child - 1) / 2;

    // Corrected while loop to bubble up properly
    while (child > 0 && arr[parent] < arr[child])
    {
        // Swap parent and child
        int temp = arr[parent];
        arr[parent] = arr[child];
        arr[child] = temp;

        // Move up the heap
        child = parent;
        parent = (child - 1) / 2;
    }
}

void dequeue(int *arr, int size, int *i)
{
	if ((*i) < 0)
	{
		printf("Underflow\n");
		return;
	}
	int max = arr[0];
	arr[0] = arr[(*i)];
	(*i)--;
	maxHeapify(arr, 0, (*i) + 1);

	printf("Dequeued = %d\n", max);
}

void display(int *arr, int i)
{
	if(i < 0)
		return;
		
	int j;
	for (j = 0; j <= i; j++)
		printf("%d ", arr[j]);
	printf("\n");
}

int main()
{
	int i = -1, n, ch, k;
	printf("Enter the size\n");
	scanf("%d", &n);
	int *arr = (int *)malloc(n * sizeof(int));

	while (1)
	{
		printf("Enter\n 1. Enqueue\n 2. Dequeue\n 3. Exit\n");
		scanf("%d", &ch);
		switch (ch)
		{
		case 1:
			printf("Enter Ele\n");
			scanf("%d", &k);
			enqueue(arr, n, &i, k);
			display(arr, i);
			break;
		case 2:
			dequeue(arr, n, &i);
			display(arr, i);
			break;
		case 3:
			printf("EOP\n");
			free(arr);
			exit(0);
		default:
			printf("Wrong Choice!\n");
		}
	}

	return 0;
}